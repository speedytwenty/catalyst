<?php
/**
 * @file
 * catalyst_test.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function catalyst_test_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function catalyst_test_eck_bundle_info() {
  $items = array(
    'catalyst_core_test' => array(
      'machine_name' => 'catalyst_core_test',
      'entity_type' => 'catalyst',
      'name' => 'core_test',
      'label' => 'Core Test',
      'config' => array(),
    ),
  );
  return $items;
}
