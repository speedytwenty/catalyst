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
  'entity create' => 'catalyst_files_plugin_entity_create',
  'entity save' => 'catalyst_files_plugin_entity_save',
  'entity normalize' => 'catalyst_files_plugin_entity_normalize',
  'entity export' => 'catalyst_files_plugin_entity_normalize',
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

function catalyst_files_plugin_entity_create($entity_type, CatalystEntity $entity, array $values, $plugin) {
  $settings = $plugin['settings'];
  if (empty($values[$settings['normal_name']])) return;

  $dir_uri = variable_get('filefield_paths_temp_location', 'public://filefield_paths');
  $dir = file_prepare_directory($dir_uri, FILE_CREATE_DIRECTORY);
  $files = array();
  foreach ($values[$settings['normal_name']] AS $fn => $fi) {
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

function catalyst_files_plugin_entity_normalize($entity_type, CatalystEntity $entity, stdClass $normal, $plugin) {
  if (!empty($entity->field__files)) {
    $files = array();
    foreach ($entity->wrapper()->field__files->value() AS $fi) {
      $files[$fi['origname']] = base64_encode(file_get_contents(drupal_realpath($fi['uri'])));
    }
    $normal->files_custom = $files;
  }
}
