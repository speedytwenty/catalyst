<?php

$plugin = array(
  'label' => 'Body field',
  'description' => 'Controls body to viewing a component (in action).',
  'field info' => 'catalyst_body_field_info',
  'field bases' => 'catalyst_body_field_bases',
  'field instance' => 'catalyst_body_field_instance',
  'entity create' => 'catalyst_body_entity_create',
  'entity insert' => 'catalyst_body_entity_save',
  'entity update' => 'catalyst_body_entity_save',
  'entity delete' => 'catalyst_body_entity_delete',
  'entity export' => 'catalyst_body_entity_export',
  'entity archive' => 'catalyst_body_entity_archive',
  'entity form' => 'catalyst_body_entity_form',
  'entity build' => 'catalyst_body_entity_build',
);

function catalyst_body_entity_has_body($entity_type, $entity) {
  $store = &drupal_static(__FUNCTION__, array());
  if (!isset($store[$entity_type])) $store[$entity_type] = array();
  $bundle = $entity->wrapper()->getBundle();
  if (!isset($store[$entity_type][$bundle])) {
    $store[$entity_type][$bundle] = FALSE;
  }
  return $store[$entity_type][$bundle];
}

/**
 * Weeeeeeeee!!!!
 * This is the magic.
 */
function catalyst_body_entity_build(&$build, $settings = array()) {
  $field = field_view_field('catalyst', $build['#entity'], 'field__body', array(
    'type' => 'catalyst_twig_formatter',
  ));
  $build['body'] = $field[0] + array(
    '#weight' => 99999,
  );
}
