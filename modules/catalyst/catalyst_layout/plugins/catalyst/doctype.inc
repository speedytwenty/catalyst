<?php

/**
 * @file
 * This plugin is relevant to entity bundles that are associated with doctypes
 * and not doctypes themselves.
 */

$plugin = array(
  'label' => 'Doctype field',
  'description' => 'Associate with a doctype.',
  'entity display' => 'catalyst_doctype_field_plugin_entity_display',
  'weight' => 999,
);

function catalyst_doctype_field_plugin_entity_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  if (!empty($entity->field__doctype) && $page) {
    $entity->content['#post_render'][] = 'catalyst_doctype_plugin_layout_post_render';
  }
}

function catalyst_doctype_plugin_layout_post_render($content, $context) {
  $doctype = $context['#doctype'];
  catalyst_doctype_post_render($doctype, $content);
  $build = $doctype->display(TRUE);
  return drupal_render($build);
}
