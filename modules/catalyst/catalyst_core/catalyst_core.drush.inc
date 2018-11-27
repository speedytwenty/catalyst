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
  );
}


function drush_catalyst_core_catalyst_import($path = '') {
  if (empty($path)) {
    drush_set_error(NULL, dt('Missing path argument.'));
    return;
  }
  if (file_exists($path)) {
    catalyst_include('import');
    if (is_dir($path)) {
      drush_print(dt('Importing from directory: @path', array('@path' => $path)));
      catalyst_import_directory($path);
    }
    else {
      if (mime_content_type($path) == 'zip') {
        drush_print(dt('Importing from archive: @path', array('@path' => $path)));
        catalyst_import_archive($path);
      }
      else {
        drush_set_error(NULL, dt('Unknown mime type for @path.', array('@path' => $path)));
      }
    }
  }
  else {
    drush_set_error(NULL, dt('@path not found.', array('@path' => $path)));
  }
}

function drush_catalyst_core_catalyst_package_revert() {
}

function drush_catalyst_core_catalyst_revert_all_packages() {
}

function drush_catalyst_core_catalyst_package_info($machine) {
  $package = catalyst_lookup_entity('package', $machine);
  $p = entity_metadata_wrapper('catalyst', $package);
  $data = entity_valval($p->field__menu);
  drush_print($p->label());
  if ($admin_notes == $p->field__admin_notes->value()) {
    drush_print($admin_notes);
  }
  drush_print(dt('Module: @module', array('@module' => empty($data['module']) ? '-' : $data['module'])));
  drush_print(dt('Subdirectory: @subdir', array('@subdir' => empty($data['subdir']) ? '-' : $data['subdir'])));
  $entities = catalyst_package_load_entities($p->getIdentifier());
  if ($entities) {
    drush_print(dt('Entities contained in @package:', array('@package' => $p->label())));
    $table = array(array('Label', 'Type', 'Machine name', 'Modified'));
    foreach ($entities AS $entity) {
      $e = entity_metadata_wrapper('catalyst', $entity);
      $table[] = array(
        $e->label(),
        $e->type->value(),
        $e->field__machine->machine->value(),
        date('D M j G:i:s T Y', $p->changed->value()),
      );
    }
    drush_print_table($table);
  }
  drush_print(dt('@count total entities.', array('@count' => count($entities))));
}

function drush_catalyst_core_catalyst_package_list() {
  $packages = catalyst_load('package');
  if ($packages) {
    $table = array(array('Name', 'Machine name', 'Module', 'Subdirectory'));
    foreach ($packages AS $package) {
      $p = entity_metadata_wrapper('catalyst', $package);
      $data = entity_valval($p->field__menu);
      $table[] = array(
        $p->title->value(),
        $p->field__machine->machine->value(),
        empty($data['module']) ? '-' : $data['module'],
        empty($data['subdir']) ? '-' : $data['subdir'],
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
    $archive_path =& catalyst_export_entities($entities);
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