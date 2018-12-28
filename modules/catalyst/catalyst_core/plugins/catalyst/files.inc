<?php

/**
 * @file
 * Handling for the field__files field.
 */


$plugin = array(
  'label' => 'Files',
  'entity import' => 'catalyst_files_plugin_entity_import',
  'get child' => 'catalyst_files_plugin_get_child',
  'get children' => 'catalyst_files_plugin_get_children',
  'entity import' => 'catalyst_files_plugin_entity_import',
  'entity export' => 'catalyst_files_plugin_entity_export',
  'entity revert' => 'catalyst_files_plugin_entity_revert',
  'default settings' => array(
    'field_name' => 'field__files',
    'normal_name' => 'files_custom',
  ),
);

function catalyst_files_plugin_get_child($plugin, $parent, $child) {
  $plugins = catalyst_files_plugin_get_children($plugin, $parent);
  return $plugins[$parent.':'.$child];
}

function catalyst_files_plugin_get_children($plugin, $parent) {
  $plugins = array('files:default' => $plugin);
  unset($plugin['default settings']['field_name'], $plugin['default settings']['normal_name']);
  $plugins[$parent.':custom'] = $plugin;
  return $plugins;
}

function catalyst_files_plugin_entity_import($entity_type, CatalystEntity $entity, array $export, $plugin) {
  $settings = $plugin['settings'];
  if (empty($export[$settings['normal_name']])) return;

  $dir_uri = variable_get('filefield_paths_temp_location', 'public://filefield_paths');
  $dir = file_prepare_directory($dir_uri, FILE_CREATE_DIRECTORY);
  $files = array();
  foreach ($export[$settings['normal_name']] AS $fn => $fi) {
    $path = sprintf('%s/%s--%s', $dir_uri, md5(microtime()), $fn);
    if ($file = file_save_data(base64_decode($fi), $path, FILE_EXISTS_REPLACE)) {
      $file->display = 0;
      $file->description = '';
      $file->origname = $fn;
      register_shutdown_function('file_delete', $file);
      $entity->field__files[LANGUAGE_NONE][] = (array)$file;
      continue;
    }
    throw new Exception(t('Unable to create temporary public @filename file at @filepath for @bundle: @machine.', array(
      '@filename' => $fn,
      '@filepath' => $path,
      '@bundle' => $entity->wrapper()->getBundle(),
      '@machine' => $entity->machine,
    )));
  }
}

function catalyst_files_plugin_entity_export(CatalystEntity $entity, array &$export, $prefix, $plugin) {
  $settings = $plugin['settings'];
  if (!empty($entity->{$settings['field_name']})) {
    $files = array();
    foreach ($entity->wrapper()->{$settings['field_name']}->value() AS $fi) {
      $files[$fi['origname']] = base64_encode(file_get_contents(drupal_realpath($fi['uri'])));
    }
    $export[$settings['normal_name']] = $files;
  }
  return $export;
}
