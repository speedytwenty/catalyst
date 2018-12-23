<?php

/**
 * @file
 * Provides ability to define PHP phping that can be used to generate or
 * manipulate template output.
 */

$plugin = array(
  'label' => t('PHP: Include'),
  'entity save' => 'catalyst_php_plugin_entity_save',
  'entity display' => 'catalyst_php_plugin_entity_display',
  'default settings' => array(
    'filename' => 'include.php',
    'field_name' => 'field__php',
    'display_callback' => 'catalyst_twig_plugin_include_display_callback',
  ),
  'get child' => 'catalyst_php_plugin_get_child',
  'get children' => 'catalyst_php_plugin_get_children',
);

function catalyst_php_plugin_get_child($plugin, $parent, $child) {
  $children = catalyst_php_plugin_get_children($plugin, $parent);
  return $children[$parent.':'.$child];
}

function catalyst_php_plugin_get_children($plugin, $parent) {
  $plugins = array('php:include' => $plugin);
  $plugin['label'] = t('PHP: Preprocess');
  $plugin['default settings']['filename'] = 'preprocess.php';
  $plugin['default settings']['field_name'] = 'field__preprocess';
  $plugin['default settings']['display_callback'] = 'catalyst_php_plugin_preprocess_display_callback';
  $plugin['prepare display'] = 'catalyst_php_plugin_preprocess_prepare_display';
  $plugins['php:preprocess'] = $plugin;
  $plugin['label'] = t('PHP: Preprocess Custom');
  $plugin['default settings']['display_callback'] = FALSE;
  $plugin['prepare display'] = FALSE;
  $plugins['php:preprocess_custom'] = $plugin;
  return $plugins;
}

function catalyst_php_plugin_entity_display($entity_type, CatalystEntity $entity, $page, $plugin) {
  if (!$plugin['settings']['display_callback']) return;
  $settings = $plugin['settings'];
  catalyst_include('code');
  if ($file_info = catalyst_code_entity_file_info($entity, $settings['filename'])) {
    return $settings['display_callback']($entity_type, $entity, $page, $plugin, $file_info);
  }
}

function catalyst_php_plugin_entity_save($entity_type, CatalystEntity $entity, $transaction, $plugin) {
  catalyst_include('code');
  $settings = $plugin['settings'];
  catalyst_code_upsert_entity_code_file($entity_type, $entity, $settings['field_name'], $settings['filename']);
}

function catalyst_php_plugin_preprocess_display_callback($entity_type, CatalystEntity $entity, $page = NULL,$plugin, $file_info) {
  $entity->content['#pre_render'][] = 'catalyst_php_plugin_preprocess_pre_render';
  $entity->content['#preprocess'] = array('file_info' => $file_info);
}
function catalyst_php_plugin_preprocess_prepare_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  return;
  catalyst_include('code');
  if ($file_info = catalyst_code_entity_file_info($entity, $plugin['settings']['filename'])) {
    catalyst_php_plugin_preprocess($entity_type, $entity, $file_info);
  }
}

function catalyst_php_plugin_preprocess_pre_render(&$build) {
  catalyst_php_plugin_preprocess($build['#entity_type'], $build['#entity'], $build['#preprocess']['file_info']);
  return $build;
}

function catalyst_php_plugin_preprocess($entity_type, CatalystEntity $entity, $file_info) {
  if (isset($entity->preprocessed)) return;
  $filepath =& drupal_static(__FUNCTION__);
  $filepath = $file_info['filepath'];
  $variables = _catalyst_php_plugin_preprocess($entity->variables());
  $entity->setVariables($variables);
  $entity->preprocessed = TRUE;
}

function _catalyst_php_plugin_preprocess($variables) {
  include drupal_static('catalyst_php_plugin_preprocess');
  drupal_static_reset('catalyst_php_plugin_preprocess');
  return $variables;
}

function catalyst_php_plugin_include_display_callback($entity_type, CatalystEntity $entity, $page = NULL, $plugin, $file_info) {
  catalyst_php_plugin_include($entity_type, $entity, $plugin, $file_info);
}

function catalyst_php_plugin_include($entity_type, CatalystEntity $entity, $file_info) {
  $filepath =& drupal_static(__FUNCTION__);
  $filepath = $file_info['filepath'];
  $variables = _catalyst_php_plugin_include($entity->variables());
  $entity->setVariables($variables);
}

function _catalyst_php_plugin_include($variables) {
  require_once drupal_static('catalyst_php_plugin_include');
  drupal_static_reset('catalyst_php_plugin_include');
  return $variables;
}

