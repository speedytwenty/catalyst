<?php

/**
 * @file
 * Catalyst Template Bundle plugin.
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
  'label' => 'Template',
  'description' => 'Provides handling for the template bundle.',
  'plugins' => array(
    'layout_field',
    'files:default',
    'cssjs:css__page',
    'shared_media:js__page',
    'cssjs:js__page',
    'shared_media:css__page',
    'php:preprocess',
    'twig:html_head',
    'twig:content',
  ),
);

