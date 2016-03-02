<?php

/**
 * @file
 * Catalyst hooks for Catalyst template.
 */

/**
 * Implements hook_catalyst_plugin_info().
 */
function catalyst_template_catalyst_plugin_info() {
  return array(
    'template' => array(
      'title' => t('Templates'),
      'description' => t('Templates are assocated with entity types that are
      not exported here. Use features to export the relevant entity types.'),
      'entity_type' => 'catalyst',
      'bundle' => 'template',
      'exportables' => TRUE,
      'migration' => array(
        'class_name' => 'CatalystTemplateMigration',
      ),
      'crud' => array(
        'admin' => array(
          'path' => 'admin/structure/template',
          'menu_item' => array(
            'title' => 'Templates',
            'page callback' => 'catalyst_template_admin_list',
            'file path' => catalyst_get_path('template') . '/includes',
            'file' => 'admin.inc',
          ),
          'parent_menu_item' => array(
            'path' => 'admin/structure/template/list',
            'title' => 'List',
            'weight' => -10,
          ),
        ),
        'add' => array(
          'path' => 'admin/structure/template/add/%/%',
          'menu_item' => array(
            'page callback' => 'catalyst_template_admin_add',
            'page arguments' => array(4,5),
            'file path' => catalyst_get_path('template') . '/includes',
            'file' => 'admin.inc',
          ),
        ),
        'edit' => array(
          'path' => 'admin/structure/template/%eckentity',
          'entity_id' => 3,
        ),
        'delete' => array(
          'path' => 'admin/structure/template/%eckentity/delete',
          'entity_id' => 3,
        ),
        'view' => array(
          'path' => 'admin/structure/template/%eckentity/view',
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
function catalyst_template_catalyst_export_candidates($group) {
  if ($group['type'] == 'template') {
    return catalyst_export_entity_candidates($group['type']);
  }
}

/**
 * Implements hook_catalyst_prepare_export().
 */
function catalyst_template_catalyst_prepare_export($export, $group, $exports) {
  $wrapper = entity_metadata_wrapper('catalyst', $export);
  // Everything else should be attached in hook_catalyst_export_alter().
  return (object)array(
    // no id necessary
    'entity_type' => $wrapper->field__template_entity_type->value(),
    'bundle' => $wrapper->field__template_bundle->value(),
  );
}