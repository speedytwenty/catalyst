<?php

/**
 * @file
 * Catalyst hook implementations for Catalyst Page.
 */

/**
 * Implements hook_catalyst_plugin_info().
 */
function catalyst_page_catalyst_plugin_info() {
  return array(
    'cpage' => array(
      'title' => t('Pages'),
      'entity_type' => 'node',
      'bundle' => 'cpage',
      'exportables' => TRUE,
      'migration' => array(
        'class_name' => 'CatalystPageMigration',
      ),
      'migration sources' => array('block', 'layout', 'stylesheet', 'javascript', 'file'),
    ),
  );
}

/**
 * Implements hook_catalyst_export_candidates().
 */
function catalyst_page_catalyst_export_candidates($group) {
  if ($group['type'] == 'cpage') {
    return catalyst_export_entity_candidates($group['type'], 'node');
  }
  if ($group['type'] == 'menu_link') {
    $candidates = array();
    // Get all cpage menu links
    $query = db_select('menu_links', 'ml')->fields('ml');
    $query->join('node', 'n');
    $query->addField('n', 'nid', 'cpage_id');
    $query->condition('n.type', 'cpage', '=')
      ->condition('ml.menu_name', array_keys(catalyst_load_menus()), 'IN')
      ->condition('ml.router_path', 'node/%', '=')
      ->where("ml.link_path = CONCAT('node/', n.nid)");
    $links = $query->execute();
    foreach ($links AS $link) {
      $candidates[] = array(
        'id' => $link->mlid,
        'label' => t('@depth @title', array(
          '@depth' => str_repeat('--', $link->depth-1),
          '@title' => $link->link_title,
        )),
        'export' => $link,
      );
    }
    return $candidates;
  }
}

/**
 * Implements hook_catalyst_export_dependencies().
 */
function catalyst_page_catalyst_export_dependencies($export, $group) {
  $dependencies = array();
  if ($group['type'] == 'menu_link' && $export->router_path == 'node/%') {
    $nid = arg(1, $export->link_path);
    $result = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('n.nid', $nid, '=')
      ->condition('n.type', 'cpage', '=')
      ->range(0,1)
      ->execute();
    if (count($result)) {
      catalyst_add_export($dependencies, 'cpage', $nid);
    }
  }
  return $dependencies;
}

/**
 * Implements hook_catalyst_prepare_export().
 */
function catalyst_page_catalyst_prepare_export($export, $group, $exports) {
  $wrapper = entity_metadata_wrapper($group['entity_type'], $export);
  $block_placements = array();
  $block_placement_block_ids = array();
  foreach ($wrapper->field__blockplacements__layfield->value() AS $placement) {
    if (catalyst_export_exists($placement['block_id'], 'block', $exports)) {
      $block_placement_block_ids[] = $placement['block_id'];
      unset($placement['block_id']);
      $block_placements[] = $placement;
    }
  }
  return array(
    'id' => $wrapper->getIdentifier(),
    'title' => $wrapper->title->value(),
    'created' => $wrapper->created->value(),
    'changed' => $wrapper->changed->value(),
    'status' => $wrapper->status->value(),
    // These still need to be filtered by block id and layout id
    'block_placements' => $block_placements,
    'block_placement_block_ids' => $block_placement_block_ids,
    'layout' => catalyst_export_helper_filter_references(
      $wrapper->field__layout, 'layout', $exports),
    'css_includes' => catalyst_export_helper_filter_references(
      $wrapper->field__media_stylesheets__page, 'stylesheet', $exports),
    'js_includes' => catalyst_export_helper_filter_references(
      $wrapper->field__media_javascripts__page, 'javascript', $exports),
    'files_shared' => catalyst_export_helper_filter_references(
      $wrapper->field__media_files, 'file', $exports),
    'files_custom' => catalyst_export_helper_files(
      $wrapper->field__files, $wrapper->getIdentifier()),
    'blocks_ref' => catalyst_export_helper_filter_references(
      $wrapper->field__blocks_related, 'block', $exports),
    'content' => entity_valval($wrapper->field__body),
    'css_custom' => entity_valval($wrapper->field__css__page),
    'js_custom' => entity_valval($wrapper->field__js__page),
    'html_head' => entity_valval($wrapper->field__html_head),
    'preprocess_php' => entity_valval($wrapper->field__preprocess),
  );
}