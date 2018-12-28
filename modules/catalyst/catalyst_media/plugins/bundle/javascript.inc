<?php

/**
 * @file
 * Catalyst Media Javascript Bundle plugin.
 */

/**
 * This plugin defintion gets directly inserted into catalyst's entity type
 * bundle information.
 *
 * Eg.
 * @code
 * $entity_info['catalyst']['bundles'][$plugin_name] = $my_plugin_definition;
 * @endcode
 *
 * @see catalyst_core_entity_info_alter().
 */
$plugin = array(
  'label' => 'Media: Javascript',
  'description' => 'Provides handling for the javascript bundle.',
  'entity display' => 'catalyst_media_javascript_entity_display',
);

function catalyst_media_javascript_entity_display($entity_type, CatalystEntity $entity, $page = NULL) {
  $media_type = $entity->wrapper()->field__media_type->value();
  catalyst_include('code');
  if ($media_type == 'local') {
    $path = $entity->wrapper()->field__media_path->value();
    drupal_add_js($path, array(
      'file' => 'file',
      'group' => $entity->getVariable('group'),
      'scope' => $entity->wrapper()->field__media_javascript_scope->value(),
    ));
  }
  elseif ($media_type == 'remote') {
    $path = $entity->wrapper()->field__media_path->value();
    drupal_add_js($path, array(
      'group' => $entity->getVariable('group'),
      'scope' => $entity->wrapper()->field__media_javascript_scope->value(),
      'type' => 'external',
    ));
  }
  else {
    catalyst_code_render_entity_cssjs($entity, 'field__body', 'js', array(
      'scope' => $entity->wrapper()->field__media_javascript_scope->value(),
      'group' => $entity->getVariable('group'),
    ));
  }
}
