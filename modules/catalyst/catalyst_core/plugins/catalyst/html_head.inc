<?php

/**
 * @file
 */

$plugin = array(
  'label' => t('HTML Head'),
  'entity build' => 'catalyst_html_head_plugin_entity_build',
  'entity save' => 'catalyst_html_head_plugin_entity_save',
  'default settings' => array(
    'field_name' => 'field__html_head',
    'preserve_files' => TRUE,
    'safe_delete' => TRUE,
    'safe_overwrite' => TRUE,
  ),
);

function catalyst_html_head_plugin_entity_build(&$build, $settings = array()) {
  if (!empty($build['#entity']->field__html_head)) {
    if ($html_head = entity_valval($build['#entity']->wrapper()->field__html_head)) {
      $id = sprintf('%s:%s:%s', $build['#entity_type'], $build['#entity']->type, $build['#entity']->machine);
      drupal_add_html_head(array('#markup' => $html_head, '#type' => 'markup'), $id);
    }
  }
}

function catalyst_html_head_plugin_entity_normalize($entity_type, $entity, $settings = array()) {
  if (!empty($entity->field__html_head)) {
    $entity->html_head = $entity->wrapper()->field__html_head->value();
  }
}
function catalyst_html_head_plugin_entity_import($entity_type, $entity, $settings = array()) {
}

function catalyst_html_head_plugin_entity_create($entity_type, $entity, $settings = array()) {
}

function catalyst_html_head_plugin_entity_export($entity_type, $entity, $original, $settings = array()) {
  unset($entity->html_head);
  unset($entity->field__html_head);
}

function catalyst_html_head_plugin_entity_archive($entity_type, $entity, ZipArchive $archive, $settings = array()) {
}

function catalyst_html_head_plugin_entity_extract($entity_type, $entity, $settings = array()) {
}
