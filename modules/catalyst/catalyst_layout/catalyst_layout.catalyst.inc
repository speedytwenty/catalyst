<?php

/**
 * @file
 * Catalyst hook implementations for Catalyst Layout
 */

/**
 * Implements hook_catalyst_plugin_info().
 */
function catalyst_layout_catalyst_plugin_info() {
  return array(
    'layout' => array(
      'title' => t('Layouts'),
      'entity_type' => 'catalyst',
      'bundle' => 'layout',
      'exportables' => TRUE,
      'migration' => array(
        'class_name' => 'CatalystLayoutMigration',
      ),
      'migration sources' => array(
        'package', 'block', 'doctype', 'stylesheet','javascript', 'file',
      ),
      'crud' => array(
        'admin' => array(
          'path' => 'admin/catalyst/layout',
          'menu_item' => array(
            'title' => 'Layouts',
            'weight' => 10,
          ),
        ),
        'add' => array(
          'path' => 'admin/catalyst/layout/add',
        ),
        'edit' => array(
          'path' => 'admin/catalyst/layout/%eckentity',
          'entity_id' => 3,
        ),
        'delete' => array(
          'path' => 'admin/catalyst/layout/%eckentity/delete',
          'entity_id' => 3,
        ),
        'view' => array(
          'path' => 'admin/catalyst/layout/%eckentity/view',
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
function catalyst_layout_catalyst_export_candidates($group) {
  if ($group['type'] == 'layout') {
    return catalyst_export_entity_candidates($group['type']);
  }
}

/**
 * Implements hook_catalyst_export_dependencies().
 */
function catalyst_layout_catalyst_export_dependencies($export, $group) {
  if (isset($group['entity_type'])) {
    $dependencies = array();

    // Determine dependencies for entities that rely on layouts
    if (!empty($export->field__layout)) {
      $wrapper = entity_metadata_wrapper($group['entity_type'], $export);
      $layout = $wrapper->field__layout;
      catalyst_add_export($dependencies, 'layout', catalyst_export_entity_id($layout));
    }
    return $dependencies;
  }
}

/**
 * Implements hook_catalyst_prepare_export().
 */
function catalyst_layout_catalyst_prepare_export($export, $group, $exports) {
  $wrapper = entity_metadata_wrapper($group['entity_type'], $export);
  return (object) array(
    'regions' => $wrapper->field__layout_regions->value(),
    'drupal_css_options' => $wrapper->field__layout_drupal_css->value(),
    'drupal_js_options' => $wrapper->field__layout_drupal_js->value(),
    'page_title_pattern' => $wrapper->field__layout_page_title_pattern->value(),
    'show_messages' => $wrapper->field__layout_show_messages->value(),
  );
}

/**
 * Implements hook_catalyst_export_alter().
 */
function catalyst_layout_catalyst_export_alter(&$export, $original, $group, $exports) {
  if (isset($group['entity_type'])) {
    $wrapper = entity_metadata_wrapper($group['entity_type'], $original);
    if (!isset($export->layout) && isset($wrapper->field__layout)) {
      $export->layout = catalyst_export_helper_filter_references($wrapper->field__layout, 'layout', $exports);
    }
  }
}

/**
 * Implements hook_catalyst_ignore_menus_alter().
 */
function catalyst_layout_catalyst_ignore_menus_alter(&$ignore_menus) {
  $ignore_menus['devel'] = TRUE;
}

/**
 * Implements hook_catalyst_export_metadata().
 */
function catalyst_layout_catalyst_export_metadata($component) {
  $metadata = array();
  foreach (array('drupal_css', 'drupal_js', 'page_title_pattern', 'regions', 'show_messages') AS $suffix) {
    $fn = 'field__layout_' . $suffix;
    if (isset($component->wrapper->{$fn}) && $val = $component->wrapper->{$fn}->value()) {
      $metadata['layout_'.$suffix] = $val;
    }
  }
  if (!empty($component->layout) && $layout_field = catalyst_resolve_field('layout', $component->type)) {
    $metadata['layout'] = $component->layout;
  }
  return $metadata;
}

/**
 * Implements hook

/**
 * Implements hook_catalyst_import_alter().
 */
function catalyst_layout_catalyst_import_alter(&$wrapper, $metadata, $path) {
  if (!empty($metadata['layout'])) {
    catalyst_import_set_reference($wrapper, 'field__layout', 'layout', $metadata['layout']);
  }
  $sufs = array('drupal_css', 'drupal_js', 'page_title_pattern', 'regions', 'show_messages');
  foreach ($sufs AS $suf) {
    $key = 'layout_'.$suf;
    if (isset($metadata[$key])) {
      $fn = 'field__'.$key;
      $wrapper->{$fn}->set($metadata[$key]);
    }
  }
}

/**
 * Implements hook_catalyst_registry_alter().
 */
function catalyst_layout_catalyst_registry_alter(&$registry) {
  foreach ($registry AS $bundle => &$entries) {
    if ($layout_field = catalyst_resolve_field('layout', $bundle)) {
      foreach ($entries AS $machine => &$entry) {
        if (isset($entry->wrapper) && isset($entry->wrapper->field__layout) && $entry->wrapper->field__layout->value()) {
          $entry->layout = $entry->wrapper->field__layout->field__machine->machine->value();
        }
      }
    }
  }
}
