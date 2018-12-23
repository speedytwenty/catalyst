<?php

/**
 * @file
 * Catalyst Layout Doctype Bundle plugin.
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
  'label' => 'Doctype',
  'description' => 'Provides handling for the doctype bundle.',
  'plugins' => array(
    'php:preprocess',
    'twig:wrapper' => array(
      'content_variable_name' => 'page',
    ),
  ),
);

