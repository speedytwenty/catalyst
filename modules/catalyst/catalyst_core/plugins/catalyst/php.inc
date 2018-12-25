<?php

/**
 * @file
 * Provides ability to define PHP phping that can be used to generate or
 * manipulate template output.
 */

$plugin = array(
  'label' => t('PHP: Include'),
  'entity save' => 'catalyst_php_plugin_entity_save',
  'prepare display' => 'catalyst_php_plugin_prepare_display',
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
  $plugin['label'] = t('PHP: Preprocess Custom');
  $plugin['default settings']['filename'] = 'preprocess.php';
  $plugin['default settings']['field_name'] = 'field__preprocess';
  $plugins['php:preprocess_custom'] = $plugin;
  $plugin['label'] = t('PHP: Preprocess');
  $plugin['prepare display'] = 'catalyst_php_plugin_preprocess_prepare_display';
  $plugins['php:preprocess'] = $plugin;
  return $plugins;
}


function catalyst_php_plugin_entity_save($entity_type, CatalystEntity $entity, $transaction, $plugin) {
  catalyst_include('code');
  $settings = $plugin['settings'];
  catalyst_code_upsert_entity_code_file($entity, $settings['field_name'], $settings['filename']);
}

function catalyst_php_plugin_preprocess_prepare_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  catalyst_php_plugin_preprocess($entity, $plugin['settings']['field_name']);
}

/**
 * Unused. For implementors of php:preprocess_custom plugin.
 */
function catalyst_php_plugin_preprocess_entity_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  $entity->content['#pre_render'][] = 'catalyst_php_plugin_preprocess_pre_render';
  $entity->content['#preprocess_fields'][] = $plugin['settings']['field_name'];
}

/**
 * Unused. For implementors of php:preprocess_custom plugin.
 */
function catalyst_php_plugin_preprocess_pre_render($build) {
  $field_name = array_shift($build['#preprocess_fields']);
  catalyst_php_plugin_preprocess($build['#entity'], $field_name);
  return $build;
}

function catalyst_php_plugin_preprocess(CatalystEntity $entity, $field_name) {
  if (isset($entity->preprocessed)) return;
  catalyst_include('code');
  $value = $entity->wrapper()->{$field_name}->value();
  if ($file_info = catalyst_code_entity_file_is_fresh($entity, $field_name, $value['value'])) {
    $filepath =& drupal_static(__FUNCTION__);
    $filepath = $file_info['filepath'];
    $variables = catalyst_php_plugin_preprocess_entity_file($entity, $entity->variables());
    $entity->setVariables($variables);
    $entity->preprocessed = TRUE;
    return $variables;
  }
  $variables = catalyst_eval($value['value'], $variables, array('entity' => $entity));
  $entity->preprocessed = TRUE;
  return $variables;
}

function catalyst_php_plugin_preprocess_entity_file(CatalystEntity $entity, array $variables) {
  include drupal_static('catalyst_php_plugin_preprocess');
  drupal_static_reset('catalyst_php_plugin_preprocess');
  return $variables;
}

function catalyst_php_plugin_preprocess_entity_eval(CatalystEntity $entity, array $variables) {
  drupal_static_reset('catalyst_php_plugin_preprocess_eval');
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

