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
  'entity display' => 'catalyst_twig_plugin_entity_display',
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
  catalyst_code_upsert_entity_code_file($entity_type, $entity, $settings['field_name'], $settings['filename']);
}

function catalyst_twig_plugin_entity_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  $settings = $plugin['settings'];
  catalyst_include('code');
  if ($file_info = catalyst_code_entity_file_info($entity, $settings['filename'])) {
    return $settings['display_callback']($entity_type, $entity, $page, $settings, $file_info);
  }
}

function catalyst_twig_plugin_content_display($entity_type, CatalystEntity $entity, $page, $settings, $file_info) {
  catalyst_include('twig');
  $entity->content['#post_render'][] = 'catalyst_twig_plugin_content_post_render';
  $entity->content['#post_render_filename'] = $settings['filename'];
  return;
  $entity->content['content'] = array(
    '#post_render' => array('catalyst_twig_plugin_content_post_render'),
    '#filename' => $settings['filename'],
    '#entity_type' => $entity_type,
    '#bundle' => $entity->wrapper()->getBundle(),
    '#entity' => $entity,
    //'#markup' => catalyst_twig_render_entity_file($entity_type, $entity, $settings['filename'], $entity->variables()),
    '#weight' => 9999,
  );
}

function catalyst_twig_plugin_content_post_render($content, &$context) {
  catalyst_include('twig');
  $variables = array('entity' => $context['#entity']) + $context['#entity']->variables();
  return catalyst_twig_render_entity_file($context['#entity_type'], $context['#entity'], $context['#post_render_filename'], $variables);
}

function catalyst_twig_plugin_html_head_display($entity_type, CatalystEntity $entity, $page, $settings, $file_info) {
  $id = sprintf('%s:%s:%s', $entity_type, $entity->type, $entity->machine);
  $html_head = catalyst_twig_render_entity_file($entity_type, $entity, $settings['filename'], $entity->variables());
  drupal_add_html_head(array('#markup' => $html_head, '#type' => 'markup'), $id);
}

function catalyst_twig_plugin_wrapper_display($entity_type, CatalystEntity $entity, $page, $settings, $file_info) {
  $entity->content['#post_render'][] = 'catalyst_twig_plugin_wrapper_post_render';
  $entity->content['#wrapper_info'] = array(
    'settings' => $settings,
    'file_info' => $file_info,
  );
}

function catalyst_twig_plugin_wrapper_post_render($content, $context) {
  $variables = $context['#entity']->variables();
  $settings = $context['#wrapper_info']['settings'];
  $var = $settings['content_variable_name'];
  $settings[$var] = $content;
  return catalyst_twig_render_entity_file($context['#entity_type'], $context['#entity'], $settings['filename'], $variables);
}
