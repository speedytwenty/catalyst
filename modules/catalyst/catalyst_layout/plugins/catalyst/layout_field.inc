<?php

/**
 * @file
 * This plugin is relevant to entity bundles that are associated with layouts
 * and not layouts themselves.
 */

$plugin = array(
  'label' => 'Layout field',
  'description' => 'Associate with a layout.',
  'entity build' => 'catalyst_layout_field_plugin_entity_build',
);

function catalyst_layout_field_plugin_entity_build(&$build, $settings = array()) {
  if (!empty($build['#entity']->field__layout) && $build['#page']) {
    catalyst_set_layout($build['#entity']->wrapper()->field__layout->value());
  }
}


