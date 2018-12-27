<?php

/**
 * @file
 * Catalyst Block Bundle plugin.
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
  'label' => 'Block',
  'description' => 'Provides handling for the block bundle.',
  'plugins' => array(
    'files:default',
    'cssjs:css',
    'cssjs:js',
    'shared_media:css',
    'shared_media:js',
    'php:preprocess',
    'twig:html_head',
    'twig:content',
  ),
  'entity display' => 'catalyst_block_entity_display',
);

function catalyst_block_entity_display($entity_type, CatalystEntity $entity, $page = NULL) {
  $entity->setVariable('title', $entity->wrapper()->label());
}

