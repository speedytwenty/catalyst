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
  'entity form alter' => 'catalyst_doctype_form_alter',
  'entity display' => 'catalyst_doctype_display',
);

function catalyst_doctype_form_alter(&$form, &$form_state, $plugin) {
  form_load_include($form_state, 'inc', 'catalyst_core', 'plugins/bundle/doctype');
  // Set the default value for the doctype content
  if ($form['#entity']->is_new) {
    $form['field__body'][LANGUAGE_NONE][0]['#after_build'][] = 'field__body_set_default_value';
  }
}

function catalyst_doctype_display($entity_type, CatalystEntity $entity, $page, $plugin) {
}

/**
 * After build callback for setting the doctype content default value.
 *
 * @see catalyst_doctype_form_alter().
 */
function field__body_set_default_value($element) {
  if (empty($element['#value'])) {
    $element['#value'] = field__body_default_value();
  }
  return $element;
}

function field__body_default_value() {
  $layout = catalyst_layout_fallback();
  $doctype = $layout->wrapper()->field__doctype->value();
  return entity_valval($doctype->wrapper()->field__body);
  return implode("\n", array(
    '<html>',
    '  <head>',
    '    {{ head }}',
    '    <title>{{ head_title }}</title>',
    '    {{ styles }}',
    '    {{ scripts }}',
    '  </head>',
    '  <body>',
    '    {{ page_top }}',
    '    {{ page }}',
    '    {{ page_bottom }}',
    '  </body>',
    '</html>',
  ));
}

