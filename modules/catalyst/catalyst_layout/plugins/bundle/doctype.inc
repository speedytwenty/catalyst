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
  if (isset($form['#entity']->is_new)) {
    $form['field__body'][LANGUAGE_NONE][0]['#after_build'][] = 'field__body_set_default_value';
  }
}

function catalyst_doctype_display($entity_type, CatalystEntity $entity, $page, $plugin) {
}

function catalyst_doctype_preprocess($doctype, $layout) {
  $doctype->setVariable('layout', $layout->normalize());
  if (empty($content_type)) $content_type = 'text/html';
  if (empty($charset)) $charset = 'utf-8';
  $doctype->setVariable('http_content_type', $content_type);
  $doctype->setVariable('http_charset', $charset);
  drupal_add_http_header('Content-type', implode(';', array(
    $content_type,
    'charset=' . $charset,
  )));
  if ($drupal_processing = (bool)$doctype->wrapper()->field__drupal_processing->value()) {
    catalyst_doctype_preprocess_drupal($doctype);
  }
  $doctype->setVariable('drupal_processing', $drupal_processing);
  $head_title = array('name' => check_plain(variable_get('site_name', 'Drupal')));
  if ($title = drupal_get_title()) {
    $head_title['title'] = $title;
  }
  elseif ($slogan = filter_xss_admin(variable_get('site_slogan', ''))) {
    $head_title['slogan'] = $slogan;
  }
  $doctype->setVariable('head_title_array', $head_title);
  if (!empty($layout->field__layout_page_title_pattern)) {
    catalyst_include('twig');
    $key = sprintf('layout:%s', $layout->machine);
    $pattern = $layout->wrapper()->field__layout_page_title_pattern->value();
    $doctype->setVariable('head_title', catalyst_twig_render($pattern, $head_title));
  }
  else $doctype->setVariable('head_title', implode(' | ', $head_title));

  $plugins = $doctype->plugins();
  if (isset($plugins['php:preprocess'])) {
    catalyst_php_plugin_preprocess($doctype, $plugins['php:preprocess']['settings']['field_name']);
  }
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

function catalyst_doctype_post_render(CatalystEntity $doctype, $content) {
  if ($doctype->getVariable('drupal_processing')) {
    drupal_doctype_process_drupal($doctype);
  }
  $variables = $doctype->variables();
  $variables['head'] = drupal_get_html_head();
  $variables['page_top'] = drupal_render($variables['page']['page_top']);
  $variables['page_bottom'] = drupal_render($variables['page']['page_bottom']);
  $variables['page_bottom'] .= catalyst_get_js('footer');
  $variables['styles'] = catalyst_get_css();
  $variables['scripts'] = catalyst_get_js();
  $variables['page'] = $content;
  $doctype->setVariables($variables);
}

function catalyst_doctype_preprocess_drupal($doctype) {
  $variables = $doctype->variables();
  // Not sure why this isn't being called automatically
  template_preprocess($variables, 'doctype');
  // Compile a list of classes that are going to be applied to the body element.
  // This allows advanced theming based on context (home page, node of certain type, etc.).
  // Add a class that tells us whether we're on the front page or not.
  $variables['classes_array'][] = $variables['is_front'] ? 'front' : 'not-front';
  // Add a class that tells us whether the page is viewed by an authenticated user or not.
  $variables['classes_array'][] = $variables['logged_in'] ? 'logged-in' : 'not-logged-in';
  // Add information about the number of sidebars.
  if (!empty($variables['page']['region']['sidebar_first']) && !empty($variables['region']['sidebar_second'])) {
    $variables['classes_array'][] = 'two-sidebars';
  }
  elseif (!empty($variables['page']['region']['sidebar_first'])) {
    $variables['classes_array'][] = 'one-sidebar sidebar-first';
  }
  elseif (!empty($variables['page']['region']['sidebar_second'])) {
    $variables['classes_array'][] = 'one-sidebar sidebar-second';
  }
  else {
    $variables['classes_array'][] = 'no-sidebars';
  }
  // If on an individual node page, add the node type to body classes.
  if ($node = menu_get_object()) {
    $variables['classes_array'][] = drupal_html_class('node-type-' . $node->type);
  }
  // RDFa allows annotation of XHTML pages with RDF data, while GRDDL provides
  // mechanisms for extraction of this RDF content via XSLT transformation
  // using an associated GRDDL profile.
  $variables['rdf_namespaces']    = drupal_get_rdf_namespaces();
  $variables['grddl_profile']     = 'http://www.w3.org/1999/xhtml/vocab';
  $variables['language']          = $GLOBALS['language'];
  $variables['language']->dir     = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $doctype->setVariables($variables);
}

function drupal_doctype_process_drupal($doctype) {
  $variables = $doctype->variables();
  template_process($variables, 'doctype');
  $doctype->setVariables($variables);
}
