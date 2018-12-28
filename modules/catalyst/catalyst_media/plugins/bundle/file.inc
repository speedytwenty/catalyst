<?php

/**
 * @file
 * Catalyst Media File Bundle plugin.
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
  'label' => 'Media: File',
  'description' => 'Provides handling for the file bundle.',
  'plugins' => array(
  ),
);

