<?php
/**
 * @file
 * catalyst_test.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function catalyst_test_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_catalyst_test';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_catalyst_test'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_catalyst_test';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_catalyst_test'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_catalyst_test';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_catalyst_test'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_catalyst__core_test';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_catalyst__core_test'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_catalyst_test';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_catalyst_test'] = $strongarm;

  return $export;
}
