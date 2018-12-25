<?php


/**
 * @file
 * Twig field handling.
 */

$plugin = array(
  'label' => t('Twig: type'),
  'get children' => 'catalyst_twig_plugin_get_children',
  'get child' => 'catalyst_twig_plugin_get_child',
  'entity save' => 'catalyst_twig_plugin_entity_save',
  'entity display' => 'catalyst_twig_plugin_entity_display_router',
);

function catalyst_twig_plugin_get_child($plugin, $parent, $child) {
  $children = catalyst_twig_plugin_get_children($plugin, $parent);
  return $children[$parent.':'.$child];
}

function catalyst_twig_plugin_get_children($plugin, $parent) {
  $plugins = array();
  $plugin['label'] = t('Twig: HTML Head');
  $plugin['default settings']['field_name'] = 'field__html_head';
  $plugin['default settings']['filename'] = 'html_head.html';
  $plugin['default settings']['display_callback'] = 'catalyst_twig_plugin_html_head_display';
  $plugins[$parent . ':html_head'] = $plugin;
  $plugin['label'] = t('Twig: Content');
  $plugin['default settings']['field_name'] = 'field__body';
  $plugin['default settings']['filename'] = 'content.html';
  $plugin['default settings']['display_callback'] = 'catalyst_twig_plugin_content_display';
  $plugins[$parent . ':content'] = $plugin;
  $plugin['label'] = t('Twig: Wrapper');
  $plugin['default settings']['field_name'] = 'field__body';
  $plugin['default settings']['filename'] = 'content.html';
  $plugin['default settings']['display_callback'] = 'catalyst_twig_plugin_wrapper_display';
  $plugin['default settings']['content_variable_name'] = 'content';
  $plugins[$parent . ':wrapper'] = $plugin;
  return $plugins;
}

function catalyst_twig_plugin_entity_save($entity_type, CatalystEntity $entity, $transaction, $plugin) {
  catalyst_include('code');
  $settings = $plugin['settings'];
  catalyst_code_upsert_entity_code_file($entity, $settings['field_name'], $settings['filename']);
}

function catalyst_twig_plugin_entity_display_router($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  catalyst_include('code');
  $settings = $plugin['settings'];
  $fn = $settings['field_name'];
  if (!empty($entity->{$fn})) {
    return $settings['display_callback']($entity, $page, $settings);
  }
}

function catalyst_twig_plugin_content_display(CatalystEntity $entity, $page, $settings) {
  $entity->content['#post_render'][] = 'catalyst_twig_plugin_content_post_render';
  $entity->content['#post_render_settings'] = $settings;
}

function catalyst_twig_plugin_content_post_render($content, &$context) {
  $settings = $context['#post_render_settings'];
  return catalyst_code_render_entity_twig($context['#entity'], $settings['field_name']);
}

function catalyst_twig_plugin_html_head_display(CatalystEntity $entity, $page, $settings) {
  $id = sprintf('%s:%s:%s', $entity->wrapper()->type(), $entity->type, $entity->machine);
  $html_head = catalyst_code_render_entity_twig($entity, $settings['field_name']);
  drupal_add_html_head(array('#markup' => $html_head, '#type' => 'markup'), $id);
}

function catalyst_twig_plugin_wrapper_display(CatalystEntity $entity, $page, $settings) {
  $entity->content['#post_render'][] = 'catalyst_twig_plugin_wrapper_post_render';
  $entity->content['#post_render_settings'] = $settings;
}

function catalyst_twig_plugin_wrapper_post_render($content, $context) {
  $settings = $context['#post_render_settings'];
  $var = $settings['content_variable_name'];
  $settings[$var] = $content;
  return catalyst_code_render_entity_twig($context['#entity'], $settings['field_name']);
}

