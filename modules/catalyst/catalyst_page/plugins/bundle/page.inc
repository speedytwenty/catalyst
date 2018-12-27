<?php

/**
 * @file
 * Catalyst Page Bundle plugin.
 */

/**
 * This plugin defintion gets directly inserted into catalyst's entity type
 * bundle information.
 *
 * Eg.
 * @code
 * $entity_info['catalyst']['bundles'][$plugin_name] = $my_plugin_definition;
 * @endcode
 *
 * @see catalyst_core_entity_info_alter().
 */
$plugin = array(
  'label' => 'Page',
  'description' => 'Provides handling for the page bundle.',
  'plugins' => array(
    'layout_field',
    'files:default',
    'blockplacements:layfield',
    'blockplacements:advanced',
    'cssjs:css__page',
    'cssjs:js__page',
    'menu',
    'shared_media:css__page',
    'shared_media:js__page',
    'twig:html_head',
    'php:preprocess',
    'twig:content',
    //'php:include',
  ),
  'prepare display' => 'catalyst_page_prepare_display',
);

function catalyst_page_prepare_display($entity_type, CatalystEntity $entity, $page = NULL) {
  if (!$entity->getVariable('title')) {
    $entity->setVariable('title', drupal_get_title());
  }
}
