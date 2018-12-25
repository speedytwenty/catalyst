<?php

/**
 * @file
 * Catalyst Media Stylesheet Bundle plugin.
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
  'label' => 'Media: Stylesheet',
  'description' => 'Provides handling for the stylesheet bundle.',
  'plugins' => array(
    'cssjs:css_body',
  ),
  'entity display' => 'catalyst_media_stylesheet_entity_display',
);

function catalyst_media_stylesheet_entity_display($entity_type, CatalystEntity $entity, $page = NULL) {
  $media_type = $entity->wrapper()->field__media_type->value();
  $options = array(
    'group' => $entity->getVariable('group'),
  );
  if ($media_type == 'remote') {
    $options['type'] = 'external';
    $data = $entity->wrapper()->field__media_path->value();
  }
  elseif ($media_type == 'local') {
    $options['type'] = 'file';
    $data = $entity->wrapper()->field__media_path->value();
  }
  elseif ($media_type == 'custom') {
    $value = $entity->wrapper()->field__body->value();
    if (empty($value)) return;
    if ($public_filepath = catalyst_code_entity_public_file_is_fresh($entity, 'field_body', $value['value'])) {
      $options['type'] = 'file';
      $data = file_create_url($public_filepath);
    }
    else {
      $options['type'] = 'inline';
      catalyst_include('twig');
      $data = $value['value'];
    }
  }
  drupal_add_css($data, $options);
}

