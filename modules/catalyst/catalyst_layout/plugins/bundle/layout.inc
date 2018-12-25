<?php

/**
 * @file
 * Layout bundle handling.
 */


$plugin = array(
  'label' => t('Layout'),
  'description' => 'Handling for layouts',
  'entity display' => 'catalyst_layout_plugin_entity_display',
  'prepare display' => 'catalyst_layout_plugin_prepare_display',
  'plugins' => array(
    'cssjs:css__layout',
    'shared_media:css__layout',
    'cssjs:js__layout',
    'shared_media:js__layout',
    'twig:html_head',
    'php:preprocess_custom',
    'twig:wrapper',
    'doctype',
  ),
);

function catalyst_layout_plugin_prepare_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  $entity->setVariable('show_messages', $entity->wrapper()->field__layout_show_messages->value());
  $entity->setVariable('debug', $entity->wrapper()->field__debug->value());
  $entity->setVariable('drupal_processing', $entity->wrapper()->field__drupal_processing->value());
  if ($entity->getVariable('drupal_processing')) {
    catalyst_layout_plugin_preprocess_drupal($entity);
  }
  $regions = array();
  foreach ($entity->wrapper()->field__layout_regions->value() AS $region_info) {
    $regions[$region_info['machine']] = catalyst_blocks_by_region($region_info['machine']);
  }
  $entity->setVariable('region', $regions);
}

function catalyst_layout_plugin_pre_render(&$build) {
  //$build['#entity']->setVariable('messages', theme('status_messages'));
  return $build;
}

function catalyst_layout_post_render($content, &$context) {
  $context['#entity']->setVariable('messages', theme('status_messages'));
  return $content;
}

function catalyst_layout_plugin_entity_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  //$entity->content['#pre_render'][] = 'catalyst_layout_plugin_pre_render';
  $entity->content['#post_render'][] =  'catalyst_layout_post_render';
  //$entity->content['#doctype'] = catalyst_layout_get_doctype($entity);
  $entity->setVariable('title', drupal_get_title());
  $regions = $entity->getVariable('region');
  foreach (array_keys($regions) AS $region) {
    $regions[$region] = drupal_render($regions[$region]);
  }
  $entity->setVariable('region', $regions);
  if ($entity->getVariable('drupal_processing')) {
    catalyst_layout_plugin_preprocess_drupal($entity);
  }
  ctools_include('plugins');
  //$preprocess = ctools_get_plugins('catalyst', 'plugin', 'preprocess');
  //catalyst_preprocess_plugin_preprocess('catalyst', $entity);
  if ($entity->getVariable('show_messages')) {
    //$entity->setVariable('messages', theme('status_messages'));
  }
}

function catalyst_layout_plugin_preprocess_drupal(CatalystEntity $entity) {
  $variables = $entity->variables();
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
  $entity->setVariables($variables);
}

function catalyst_layout_plugin_process_drupal(CatalystEntity $entity) {
  $variables = $entity->variables();
  $variables['actions_links'] = drupal_render($variables['action_links']);
  $variables['tabs'] = drupal_render($variables['tabs']);
  template_process($variables, 'layout');
  $entity->setVariables($variables);
}

