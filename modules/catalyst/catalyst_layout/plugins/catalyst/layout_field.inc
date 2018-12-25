<?php

/**
 * @file
 * This plugin is relevant to entity bundles that are associated with layouts
 * and not layouts themselves.
 */

$plugin = array(
  'label' => 'Layout field',
  'description' => 'Associate with a layout.',
  'entity display' => 'catalyst_layout_field_plugin_entity_display',
);

function catalyst_layout_field_plugin_entity_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  if (catalyst_theme_active() && !empty($entity->field__layout) && $page) {
    $layout = $entity->wrapper()->field__layout->value();
    catalyst_set_layout($layout);
    return;
    $entity->content['#post_render'][] = 'catalyst_layout_plugin_post_render';
    $entity->content['#layout'] = $layout;
  }
}

function catalyst_layout_plugin_post_render($content, $context) {
  $layout = $context['#layout'];
  $layout->setVariable('content', $content);
  $build = $layout->display(TRUE);
  return drupal_render($build);
}
