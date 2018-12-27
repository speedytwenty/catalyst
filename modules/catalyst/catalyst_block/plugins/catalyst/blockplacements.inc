<?php

/**
 * @file
 * Handles block placements for:
 *   - field__blockplacements__layfield
 *   - field___placementsments_entity <-Jacked up name
 */

$plugin = array(
  'label' => 'Block placements',
  'entity display' => 'catalyst_blockplacements_plugin_entity_display',
  'get child' => 'catalyst_blockplacements_plugin_get_child',
  'get children' => 'catalyst_blockplacements_plugin_get_children',
  'field_name' => 'field__blockplacements__layfield',
);

function catalyst_blockplacements_plugin_get_child($plugin, $parent, $child) {
  $plugins = catalyst_blockplacements_plugin_get_children($plugin, $parent);
  return $plugins[$parent.':'.$child];
}

function catalyst_blockplacements_plugin_get_children($plugin, $parent) {
  $plugins = array('blockplacements:layfield' => $plugin);
  $plugin['field_name'] = 'field___block_placements_entity';
  $plugins['blockplacements:advanced'] = $plugin;
  return $plugins;
}

function catalyst_blockplacements_plugin_entity_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  if (!empty($entity->{$plugin['field_name']})) {
    foreach ($entity->wrapper()->{$plugin['field_name']}->value() AS $placement) {
      catalyst_block_add_static_placement($placement);
    }
  }
}



