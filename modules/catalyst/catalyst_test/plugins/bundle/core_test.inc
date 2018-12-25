<?php

/**
 * @file
 * Catalyst Core Test Bundle plugin.
 */

$plugin = array(
  'label' => 'Core test',
  'description' => 'Provides handling for the core_test bundle.',
  'plugins' => array(
    'php:preprocess',
    'twig:content',
    'cssjs:css',
  ),
);

