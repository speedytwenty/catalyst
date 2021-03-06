<?php

/**
 * @file
 * Catalyst hook implementations for Catalyst Block.
 */

/**
 * Implements hook_catalyst_plugin_info().
 */
function catalyst_block_catalyst_plugin_info() {
  return array(
    'block' => array(
      'title' => t('Blocks'),
      'entity_type' => 'catalyst',
      'bundle' => 'block',
      'exportables' => TRUE,
      'migration' => array(
        'class_name' => 'CatalystBlockMigration',
      ),
      'migration sources' => array(
        'package', 'layout', 'stylesheet', 'javascript', 'file',
      ),
      'crud' => array(
        'admin' => array(
          'path' => 'admin/catalyst/block',
          'menu_item' => array(
            'title' => 'Blocks',
            'weight' => -10,
          ),
        ),
        'add' => array('path' => 'admin/catalyst/block/add'),
        'edit' => array(
          'path' => 'admin/catalyst/block/%eckentity',
          'entity_id' => 3,
        ),
        'delete' => array(
          'path' => 'admin/catalyst/block/%eckentity/delete',
          'entity_id' => 3,
        ),
        'view' => array(
          'path' => 'admin/catalyst/block/%eckentity/view',
          'entity_id' => 3,
          'menu_item' => FALSE,
        ),
      ),
    ),
  );
}

/**
 * Implements hook_catalyst_export_candidates().
 */
function catalyst_block_catalyst_export_candidates($group) {
  $args = func_get_args();
  if ($group['type'] == 'block') {
    return catalyst_export_entity_candidates($group['type']);
  }
}

/**
 * Implements hook_catalyst_export_dependencies().
 */
function catalyst_block_catalyst_export_dependencies($export, $group) {
  if (isset($group['entity_type'])) {
    $dependencies = array();
    $wrapper = entity_metadata_wrapper($group['entity_type'], $export);
    // Related blocks
    if (isset($wrapper->field__blocks_related)) {
      foreach ($wrapper->field__blocks_related AS $item) {
        catalyst_add_export($dependencies, 'block', catalyst_export_entity_id($item));
      }
    }

    // Determine dependencies for entities using block placements
    $placement_fields = array(
      'field__blockplacements__layfield',
      'field__blockplacements__layout',
      'field___block_placements_entity',
    );
    foreach ($placement_fields AS $field) {
      if (isset($wrapper->{$field})) {
        foreach ($wrapper->{$field} AS $item) {
          $block_id = $item->block_id->value();
          $block = entity_metadata_wrapper('catalyst', $block_id);
          catalyst_add_export($dependencies, 'block', catalyst_export_entity_id($block));
          if (isset($item->layout_id) && $layout_id = $item->layout_id->value()) {
            $layout = entity_metadata_wrapper('catalyst', $layout_id);
            catalyst_add_export($dependencies, 'layout', catalyst_export_entity_id($layout));
          }
        }
      }
    }
    return $dependencies;
  }
}

/**
 * Implements hook_catalyst_export_alter().
 */
function catalyst_block_catalyst_export_alter(&$export, $original, $group, $exports) {
  if (!isset($group['entity_type'])) {
    return;
  }
  if (!isset($export->blocks_reference) && isset($wrapper->field__blocks_related)) {
    $export->blocks_reference = catalyst_export_helper_filter_references($wrapper->field__blocks_related, 'block', $exports);
  }
  $wrapper = entity_metadata_wrapper($group['entity_type'], $original);
  if (!isset($export->block_placements)) {
    $placement_fields = array(
      'field__blockplacements__block' => 'layout_id',
      'field__blockplacements__layout' => 'block_id',
      'field__blockplacements__layfield' => 'block_id',
    );
    foreach ($placement_fields AS $field_name => $id_key) {
      if (isset($wrapper->{$field_name})) {
        $export->block_placements = array();
        $export->block_placement_ids = array();
        foreach ($wrapper->{$field_name}->value() AS $placement) {
          $item = entity_load_single('catalyst', $placement[$id_key]);
          $item_wrapper = entity_metadata_wrapper('catalyst', $item);
          $export->block_placement_ids[] = catalyst_export_entity_id($item_wrapper);
          unset($placement[$id_key]);
          $export->block_placements[] = $placement;
        }
        break(1);
      }
    }
    $field_name = 'field___block_placements_entity';
    if (isset($wrapper->{$field_name}) && $values = $wrapper->{$field_name}->value()) {
      $export->entity_placements_block_id = array();
      $export->entity_placements_layout_id = array();
      foreach ($values AS $placement) {
        $block = entity_metadata_wrapper('catalyst', $placement['block_id']);
        $export->entity_placements_block_id[] = catalyst_export_entity_id($block);
        $layout = entity_metadata_wrapper('catalyst', $placement['layout_id']);
        $export->entity_placements_layout_id[] = catalyst_export_entity_id($layout);
        unset($placement['block_id'], $placement['layout_id']);
        $export->entity_placements[] = $placement;
      }
    }
  }
}

/**
 * Implements hook_catalyst_prepare_export().
 */
function catalyst_block_catalyst_prepare_export($export, $group, $exports) {
  return (object) array();
}
