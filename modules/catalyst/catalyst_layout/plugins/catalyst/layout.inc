<?php

/**
 * @file
 */

$plugin = array(
  'label' => 'Layout',
  'description' => 'Handling for layouts',
  'entity build' => 'catalyst_layout_plugin_entity_build',
);

function catalyst_layout_plugin_entity_build(&$build, $settings = array()) {
  if ($build['#entity']->wrapper()->getBundle() == 'layout') {
    $build['#pre_render'][] = 'catalyst_layout_plugin_pre_render';
    $layout = $build['#entity'];
    $layout->setVariable('show_messages', $layout->wrapper()->field__layout_show_messages->value());
    $layout->setVariable('debug', $layout->wrapper()->field__debug->value());
    $layout->setVariable('drupal_processing', $layout->wrapper()->field__drupal_processing->value());
    if ($layout->getVariable('drupal_processing')) {
      catalyst_layout_plugin_preprocess_drupal($layout);
    }
    $regions = array();
    foreach ($layout->wrapper()->field__layout_regions->value() AS $region_info) {
      $regions[$region_info['machine']] = catalyst_blocks_by_region($region_info['machine']);
    }
    $layout->setVariable('region', $regions);
  }
}

function catalyst_layout_plugin_pre_render($build) {
  $layout = $build['#entity'];
  $layout->setVariable('title', drupal_get_title());
  $regions = $layout->getVariable('region');
  foreach (array_keys($regions) AS $region) {
    $regions[$region] = drupal_render($regions[$region]);
  }
  $layout->setVariable('region', $regions);
  if ($layout->getVariable('drupal_processing')) {
    catalyst_layout_plugin_preprocess_drupal($layout);
  }
  ctools_include('plugins');
  $preprocess = ctools_get_plugins('catalyst', 'plugin', 'preprocess');
  catalyst_preprocess_plugin_preprocess('catalyst', $layout);
  if ($layout->getVariable('show_messages')) {
    $layout->setVariable('messages', theme('status_messages'));
  }
  return $build;
}

function catalyst_layout_plugin_preprocess_drupal($layout) {
  $variables = $layout->variables();
  template_preprocess($variables, 'layout');
  // Set up layout variable.
  $variables['page_layout'] = 'none';
  if (!empty($variables['region']['sidebar_first'])) {
    $variables['page_layout'] = 'first';
  }
  if (!empty($variables['region']['sidebar_second'])) {
    $variables['page_layout'] = ($variables['page_layout'] == 'first') ? 'both' : 'second';
  }

  $variables['base_path']         = base_path();
  $variables['front_page']        = url();
  $variables['feed_icons']        = drupal_get_feeds();
  $variables['language']          = $GLOBALS['language'];
  $variables['language']->dir     = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['logo']              = theme_get_setting('logo');
  //$variables['main_menu']         = theme_get_setting('toggle_main_menu') ? menu_main_menu() : array();
  //$variables['secondary_menu']    = theme_get_setting('toggle_secondary_menu') ? menu_secondary_menu() : array();
  $variables['action_links']      = menu_local_actions();
  $variables['site_name']         = (theme_get_setting('toggle_name') ? filter_xss_admin(variable_get('site_name', 'Drupal')) : '');
  $variables['site_slogan']       = (theme_get_setting('toggle_slogan') ? filter_xss_admin(variable_get('site_slogan', '')) : '');
  $variables['tabs']              = menu_local_tabs();

  if ($node = menu_get_object()) {
    $variables['node'] = $node;
  }
  $layout->setVariables($variables);
}

function catalyst_layout_plugin_process_drupal($layout) {
  $variables = $layout->variables();
  $variables['actions_links'] = drupal_render($variables['action_links']);
  $variables['tabs'] = drupal_render($variables['tabs']);
  template_process($variables, 'layout');
  $layout->setVariables($variables);
}

