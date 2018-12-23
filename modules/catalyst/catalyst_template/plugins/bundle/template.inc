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
    'cssjs:css__page',
    'cssjs:js__page',
    'twig:content',
    'twig:html_head',
  ),
);

