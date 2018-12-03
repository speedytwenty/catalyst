<?php

/**
 * @file
 * Drush commands for catalyst.
 */

/**
 * Implements hook_drush_command().
 */
function catalyst_core_drush_command() {
  return array(
    'catalyst-import' => array(
      'description' => 'Import from an archive or directory.',
      'aliases' => array('cati'),
      'examples' => array(
        'drush cati ./path/to/my/export_archive.zip' => 'Import from a zip export.',
        'drush cati ./path/to/a/directory/with/exports' => 'Import from a directory containing catalyst exports.',
      ),
      'arguments' => array(
        'path' => 'The path of the directory or zip archive to import from.',
      ),
    ),
    'catalyst-rollback' => array(
      'description' => 'Deletes all database items that match exports in a directory (based on type+machine).',
      'arguments' => array(
        'path' => 'The path of the directory or zip archive to import from.',
      ),
    ),
    'catalyst-package-revert' => array(
      'description' => "Revert a (previously exported) package's database entities to the code state.",
      'aliases' => array('catpr'),
      'examples' => array(
        'drush catpr mypackage_machine_name' => "Revert a package to it's code state.",
      ),
      'arguments' => array(
        'package' => 'The machine name of the package to revert.',
      ),
    ),
    'catalyst-revert-all-packages' => array(
      'description' => 'Reverts all (previously exported) packages to their code state.',
      'aliases' => array('catrap'),
    ),
    'catalyst-package-info' => array(
      'description' => 'Displays package details including all catalyst entities assigned to the package.',
      'aliases' => array('catpi'),
      'examples' => array(
        'drush catalyst-package-info mypackage_machine_name' => 'Display info for a package.',
      ),
      'arguments' => array(
        'package' => 'The machine name of the package to view.',
      ),
    ),
    'catalyst-package-list' => array(
      'description' => 'Lists available packages for export.',
      'aliases' => array('catpl'),
    ),
    'catalyst-package-export' => array(
      'description' => 'Exports a package to the specified module and subdirectory.',
      'aliases' => array('catpe'),
      'examples' => array(
        'drush catpe mypackage_machine_name mymodule mysubdir',
        'drush catpe mypackage_machine_name',
      ),
      'arguments' => array(
        'package' => 'The machine name of the package to export.',
      ),
    ),
    'catalyst-package-rollback' => array(
      'description' => 'Deletes database entities for a package (based on type+machine).',
      'arguments' => array(
        'package' => 'The machine name of the package to export.',
      ),
    ),
  );
}


function drush_catalyst_core_catalyst_import($path = '') {
  if (empty($path)) {
    drush_set_error(NULL, dt('Missing path argument.'));
    return;
  }
  drush_print(dt('Importing from directory: @path', array('@path' => $path)));
  $result = array();
  catalyst_include('import');
  if (is_dir($path)) {
    $result = catalyst_import_directory($path);
  }
  else {
    if (mime_content_type($path) == 'zip') {
      drush_print(dt('Importing from archive: @path', array('@path' => $path)));
      $result = catalyst_import_archive($path);
    }
    else {
      drush_set_error(NULL, dt('Error: Invalid archive. Unknown mime type for @path.', array('@path' => $path)));
    }
  }
  drush_catalyst_result($result);
}

function drush_catalyst_core_catalyst_package_rollback($machine) {
  catalyst_include('import');
  $result = catalyst_import_rollback_package($package->file_path);
  drush_catalyst_result($result);
}


function drush_catalyst_core_catalyst_rollback($path) {
  $path = sprintf('%s/%s', DRUPAL_ROOT, $path);
  if (!file_exists($path)) {
    drush_print(dt('Error: @path does not exist.', array('@path' => $path)));
    return;
  }
  else if (!is_dir($path)) {
    drush_print(dt('Error: @path is not a directory.', array('@path' => $path)));
    return;
  }
  drush_print(dt('Rolling back directory: @dir', array('@dir' => $path)));
  catalyst_include('import');
  $result = catalyst_import_rollback_directory($path);
  drush_catalyst_result($result);
}

function drush_catalyst_result($result) {
  if (!empty($result['error'])) {
    drush_print(dt('Error: @error', array('@error' => $result['error'])));
  }
  if (!empty($result['messages'])) {
    foreach ($result['messages'] AS $msg) {
      drush_print($msg);
    }
  }
}

function drush_catalyst_core_catalyst_package_revert() {
}

function drush_catalyst_core_catalyst_revert_all_packages() {
}

function drush_catalyst_core_catalyst_package_info($machine) {
  if (!$package = catalyst_load_single('package', $machine)) {
    drush_print(dt('The catalyst package @machine does not exist.', array(
      '@machine' => $machine,
    )));
    return;
  }
  drush_print($package->label);
  if (isset($package->wrapper->field__admin_notes) && $admin_notes = $package->wrapper->field__admin_notes->value()) {
    drush_print($admin_notes);
  }
  drush_print(dt('Module: @module', array('@module' => empty($package->module) ? '-' : $package->module)));
  drush_print(dt('Subdirectory: @subdir', array('@subdir' => empty($package->subdir) ? '-' : $package->subdir)));
  if ($package->entries) {
    drush_print(dt('Components contained in @package:', array('@package' => $package->label)));
    $total = 0;
    foreach ($package->entries AS $bundle => $entries) {
      drush_print(t('@label (@count)', array(
        '@label' => ucfirst($bundle) . 's',
        '@count' => count($entries),
      )));
      $table = array(array('Label', 'Machine name', 'ID', 'Modified'));
      foreach ($entries AS $machine) {
        $entry = catalyst_load_single($bundle, $machine);
        $table[] = array(
          $entry->label,
          $entry->machine,
          !empty($entry->id) ? $entry->id : '-',
          isset($entry->wrapper) ? date('D M j G:i:s T Y', $entry->wrapper->changed->value()) : '-',
        );
        $total++;
      }
      drush_print_table($table);
    }
  }
  drush_print(dt('@count total entities.', array('@count' => $total)));
}

function drush_catalyst_core_catalyst_package_list() {
  $packages = catalyst_load('package');
  if ($packages) {
    $table = array(array('Name', 'Machine name', 'ID', 'Module', 'Subdirectory', 'Components'));
    foreach ($packages AS $package) {
      $table[] = array(
        $package->label,
        $package->machine,
        !empty($package->id) ? $package->id : '-',
        empty($package->module) ? '-' : $package->module,
        empty($package->subdir) ? '-' : $package->subdir,
        $package->total_entries,
      );
    }
    drush_print_table($table, TRUE);
  }
  drush_print(dt('@count total packages', array('@count' => count($packages))));
}

function drush_catalyst_core_catalyst_package_export($machine, $module, $subdir) {
  $package = catalyst_lookup_entity('package', $machine);
  $p = entity_metadata_wrapper('catalyst', $package);
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'catalyst')
    ->fieldCondition('field__package', 'target_id', $p->getIdentifier(), '=')
    ->execute();
  if ($result['catalyst']) {
    $ids = array_keys($result['catalyst']);
    $ids[] = $p->getIdentifier();
    $entities = entity_load('catalyst', $ids);
    catalyst_include('export');
    $archive_path =& catalyst_export_components($entities);
    $export_path = drupal_get_path('module', $module);
    if ($subdir) {
      $export_path .= '/' . $subdir;
    }
    $archive = new ZipArchive;
    if ($archive->open($archive_path)) {
      $archive->extractTo($export_path);
      $archive->close();
    }
    unlink($archive_path);
    drush_print('Export path: ' . $export_path);
    drush_print('Archive path: ' . $archive_path);
  }
}
