<?php

/**
 * @file
 * This plugin is relevant to entity bundles that are associated with layouts
 * and not layouts themselves.
 */

$plugin = array(
  'label' => 'Layout field',
  'description' => 'Associate with a layout.',
  'entity display' => 'catalyst_layout_field_plugin_entity_display',
  'weight' => -50,
);

function catalyst_layout_field_plugin_entity_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  if (catalyst_theme_active() && !empty($entity->field__layout) && $page) {
    $layout = $entity->wrapper()->field__layout->value();
    catalyst_set_layout($layout);
  }
}
