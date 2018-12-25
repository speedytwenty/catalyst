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
    'cssjs:css',
    'shared_media:css',
    'shared_media:js',
    'twig:content',
    'twig:html_head',
  ),
);

