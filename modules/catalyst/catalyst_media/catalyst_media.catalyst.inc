<?php

/**
 * @file
 * Catalyst hook implementations for Catalyst Media
 */

/**
 * Implements hook_catalyst_plugin_info().
 */
function catalyst_media_catalyst_plugin_info() {
  $defaults = array(
    'entity_type' => 'catalyst',
    'exportables' => TRUE,
  );
  return array(
    'stylesheet' => array(
      'title' => t('Stylesheets'),
      'bundle' => 'stylesheet',
      'migration' => array(
        'class_name' => 'CatalystMediaStylesheetMigration',
      ),
      'migration sources' => array('package', 'file'),
      'crud' => array(
        'admin' => array(
          'path' => 'admin/catalyst/stylesheet',
          'menu_item' => array(
            'title' => 'Stylesheets',
            'weight' => 30,
          ),
        ),
        'add' => array('path' => 'admin/catalyst/stylesheet/add'),
        'edit' => array(
          'path' => 'admin/catalyst/stylesheet/%eckentity',
          'entity_id' => 3,
        ),
        'delete' => array(
          'path' => 'admin/catalyst/stylesheet/%eckentity/delete',
          'entity_id' => 3,
        ),
        'view' => array(
          'path' => 'admin/catalyst/stylesheet/%eckentity/view',
          'entity_id' => 3,
          'menu_item' => FALSE,
        ),
      ),
    ) + $defaults,
    'javascript' => array(
      'title' => t('Javascripts'),
      'bundle' => 'javascript',
      'migration' => array(
        'class_name' => 'CatalystMediaJavascriptMigration',
      ),
      'migration sources' => array('package'),
      'crud' => array(
        'admin' => array(
          'path' => 'admin/catalyst/javascript',
          'menu_item' => array(
            'title' => 'Javascripts',
            'weight' => 40,
          ),
        ),
        'add' => array('path' => 'admin/catalyst/javascript/add'),
        'edit' => array(
          'path' => 'admin/catalyst/javascript/%eckentity',
          'entity_id' => 3,
        ),
        'delete' => array(
          'path' => 'admin/catalyst/javascript/%eckentity/delete',
          'entity_id' => 3,
        ),
        'view' => array(
          'path' => 'admin/catalyst/javascript/%eckentity/view',
          'entity_id' => 3,
          'menu_item' => FALSE,
        ),
      ),
    ) + $defaults,
    'file' => array(
      'title' => t('Shared Files'),
      'bundle' => 'file',
      'migration' => array(
        'class_name' => 'CatalystMediaFileMigration',
      ),
      'migration sources' => array('package'),
      'crud' => array(
        'admin' => array(
          'path' => 'admin/catalyst/file',
          'menu_item' => array(
            'title' => 'Files',
            'weight' => 50,
          ),
        ),
        'add' => array('path' => 'admin/catalyst/file/add'),
        'edit' => array(
          'path' => 'admin/catalyst/file/%eckentity',
          'entity_id' => 3,
        ),
        'delete' => array(
          'path' => 'admin/catalyst/file/%eckentity/delete',
          'entity_id' => 3,
        ),
        'view' => array(
          'path' => 'admin/catalyst/file/%eckentity/view',
          'entity_id' => 3,
          'menu_item' => FALSE,
        ),
      ),
    ) + $defaults,
  );
}

/**
 * Implements hook_catalyst_export_candidates().
 */
function catalyst_media_catalyst_export_candidates($group) {
  if (in_array($group['type'], array('stylesheet', 'javascript', 'file'))) {
    return catalyst_export_entity_candidates($group['type']);
  }
}

/**
 * Implements hook_catalyst_export_dependencies().
 */
function catalyst_media_catalyst_export_dependencies($export, $group) {
  if (isset($group['entity_type'])) {
    $dependencies = array();
    $fields = array(
      // field => type
      'field__media_stylesheets' => 'stylesheet',
      'field__media_stylesheets__page' => 'stylesheet',
      'field__media_stylesheets__layout' => 'stylesheet',
      'field__media_javascripts' => 'javascript',
      'field__media_javascripts__page' => 'javascript',
      'field__media_javascripts__layout' => 'javascript',
      'field__media_files' => 'file',
    );
    $wrapper = entity_metadata_wrapper($group['entity_type'], $export);
    foreach ($fields AS $field => $_type) {
      if (isset($wrapper->{$field})) {
        foreach ($wrapper->{$field} AS $item) {
          catalyst_add_export($dependencies, $_type, catalyst_export_entity_id($item));
        }
      }
    }
    return $dependencies;
  }
}

/**
 * Implements hook_catalyst_prepare_export().
 */
function catalyst_media_catalyst_prepare_export($export, $group, $exports) {
  $wrapper = entity_metadata_wrapper($group['entity_type'], $export);
  $export = (object) array(
    'media_type' => $wrapper->field__media_type->value(),
    'media_path' => $wrapper->field__media_path->value(),
  );
  switch ($group['type']) {
    case 'stylesheet':
      $export->media = $wrapper->field__media_stylesheet_media->value();
      $export->files_shared = catalyst_export_helper_filter_references($wrapper->field__media_files, 'file', $exports);
      break;
    case 'javascript':
      $export->defer = $wrapper->field__media_javascript_defer->value();
      $export->scope = $wrapper->field__media_javascript_scope->value();
      break;
    case 'file':
      $export->file_path = catalyst_export_helper_files($wrapper->field__media_file, catalyst_export_entity_id($wrapper));
      break;
  }
  return $export;
}

/**
 * Implements hook_catalyst_export_alter().
 */
function catalyst_media_catalyst_export_alter(&$export, $original, $group, $exports) {
  if (isset($group['entity_type'])) {
    $wrapper = entity_metadata_wrapper($group['entity_type'], $original);
    $setprops = array(
      'field__media_stylesheets' => 'stylesheets',
      'field__media_stylesheets__layout' => 'stylesheets',
      'field__media_stylesheets__page' => 'stylesheets',
      'field__media_javascripts' => 'javascripts',
      'field__media_javascripts__layout' => 'javascripts',
      'field__media_javascripts__page' => 'javascripts',
      'field__media_files' => 'files_shared',
    );
    foreach ($setprops AS $from => $to) {
      if (!isset($export->{$to}) && isset($wrapper->{$from})) {
        switch ($to) {
          case 'javascripts':
            $export->{$to} = catalyst_export_helper_filter_references($wrapper->{$from}, 'javascript', $exports);
            break;
          case 'stylesheets':
            $export->{$to} = catalyst_export_helper_filter_references($wrapper->{$from}, 'stylesheet', $exports);
            break;
          case 'files_shared':
            $export->{$to} = catalyst_export_helper_filter_references($wrapper->{$from}, 'file', $exports);
            break;
          default:
            $export->{$to} = $wrapper->{$from}->value();
            break;
        }
      }
    }
  }
}

/**
 * Implements hook_catalyst_export_metadata().
 */
function catalyst_media_catalyst_export_metadata($entity, $wrapper) {
  $metadata = array();
  $sufs = array('javascript_defer', 'javascript_scope', 'path', 'type', 'stylesheet_media');
  foreach ($sufs AS $suf) {
    $fn = 'field__media_'.$suf;
    if (isset($wrapper->{$fn}) && $mt = $wrapper->{$fn}->value()) {
    drush_print($fn);
      $metadata['media_'.$suf] = $wrapper->{$fn}->value();
    }
  }
  $mfs = array(
    'files',
    'javascripts',
    'javascripts__layout',
    'javascripts__page',
    'stylesheets',
    'stylesheets__layout',
    'stylesheets__page',
  );
  foreach ($mfs AS $suffix) {
    $fn = 'field__media_' . $suffix;
    if (isset($wrapper->{$fn}) && $vals = $wrapper->{$fn}->value()) {
      $ms = array();
      foreach ($vals AS $val) {
        $ms[] = entity_metadata_wrapper('catalyst', $val)->field__machine->machine->value();
      }
      $metadata['media_'.$suffix] = $ms;
    }
  }
  return $metadata;
}

/**
 * Implements hook_catalyst_export_entity().
 */
function catalyst_media_catalyst_export_entity(&$archive, $entity, $wrapper) {
  $machine = $wrapper->field__machine->machine->value();
  if (isset($wrapper->field__media_file) && $file = $wrapper->field__media_file->value()) {
    $archive->addFile(drupal_realpath($file['uri']), sprintf('%s/%s/%s', $entity->type, $machine, $file['origname']));
  }
}

/**
 * Implements hook_catalyst_import_entity_alter().
 */
function catalyst_media_catalyst_import_entity_alter(&$wrapper, $metadata, $path) {
  if (!empty($metadata['media_files'])) {
    catalyst_import_set_reference($wrapper, 'field__media_files', 'file', $metadata['media_files']);
  }
  foreach (array('javascript' => 'javascripts', 'stylesheet' => 'stylesheets') AS $type => $fsuf) {
    foreach (array('', '__layout', '__page') AS $suf) {
      $key = 'media_'.$fsuf.$suf;
      if (isset($metadata[$key])) {
        $fn = 'field__'.$key;
        if (!empty($metadata[$key])) {
          catalyst_import_set_reference($wrapper, $fn, $type, $metadata[$key]);
        }
      }
    }
  }
  $sufs = array('javascript_defer', 'javascript_scope', 'path', 'type', 'stylesheet_media');
  foreach ($sufs AS $suf) {
    $key = 'media_'.$suf;
    if (isset($metadata[$key])) {
      $fn = 'field__'.$key;
      $wrapper->{$fn}->set($metadata[$key]);
    }
  }
}

/**
 * Implements hook_catalyst_registry_alter().
 */
function catalyst_media_catalyst_registry_alter(&$registry) {
  foreach ($registry AS $type => &$entries) {
    foreach ($entries AS $machine => &$entry) {
      if (isset($entry->wrapper)) {
        if (isset($entry->wrapper->field__media_file) && $file = $entry->wrapper->field__media_file->value()) {
          if (!isset($entry->files)) $entry->files = array();
          $entry->files[] = $file + array('source' => 'media_file');
        }
      }
    }
  }
}
