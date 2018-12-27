<?php

/**
 * @file
 * Catalyst Core Test Bundle plugin.
 */

$plugin = array(
  'label' => 'Core test',
  'description' => 'Provides handling for the core_test bundle.',
  'plugins' => array(
    'files:default',
    'cssjs:css',
    'cssjs:css__page',
    'cssjs:css__layout',
    'cssjs:js',
    'cssjs:js__page',
    'cssjs:js__layout',
    'php:preprocess',
    'twig:content',
  ),
);

