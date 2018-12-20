<?php

/**
 * @file
 * This plugin is relevant to entity bundles that are associated with doctypes
 * and not doctypes themselves.
 */

$plugin = array(
  'label' => 'Doctype field',
  'description' => 'Associate with a doctype.',
  'entity build' => 'catalyst_doctype_plugin_entity_build',
);

function catalyst_doctype_plugin_entity_build(&$build, $settings = array()) {
  if (!empty($build['#entity']->field__doctype)) {
    $build['#pre_render'][] = 'catalyst_doctype_plugin_layout_pre_render';
    $build['#post_render'][] = 'catalyst_doctype_plugin_layout_post_render';
  }
}

function catalyst_doctype_plugin_layout_pre_render($build) {
  $layout = $build['#entity'];
  $doctype = catalyst_get_doctype();
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
    catalyst_doctype_plugin_preprocess_drupal($doctype);
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
    $key = sprintf('layout:%s', $build['#entity']->machine);
    $pattern = $layout->wrapper()->field__layout_page_title_pattern->value();
    $doctype->setVariable('head_title', catalyst_twig_render($pattern, $head_title));
  }
  else $doctype->setVariable('head_title', implode(' | ', $head_title));

  ctools_include('plugins');
  $preprocess = ctools_get_plugins('catalyst', 'plugin', 'preprocess');
  catalyst_preprocess_plugin_preprocess('catalyst', $doctype);
  return $build;
}

function catalyst_doctype_plugin_layout_post_render($content, $context) {
  $doctype = catalyst_get_doctype();
  if ($doctype->getVariable('drupal_processing')) {
    drupal_doctype_plugin_process_drupal($doctype);
  }
  $page = $doctype->getVariable('page');
  $doctype->setVariable('page_top', drupal_render($page['page_top']));
  $doctype->setVariable('page_bottom', drupal_render($page['page_bottom']) . catalyst_get_js('footer'));
  $doctype->setVariable('page', $content);
  $doctype->setVariable('head', drupal_get_html_head());
  $doctype->setVariable('styles', catalyst_get_css());
  $doctype->setVariable('scripts', catalyst_get_js());
  $build = $doctype->view('template', LANGUAGE_NONE, TRUE);
  return drupal_render($build);
}

function catalyst_doctype_plugin_preprocess_drupal($doctype) {
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

function drupal_doctype_plugin_process_drupal($doctype) {
  $variables = $doctype->variables();
  template_process($variables, 'doctype');
  $doctype->setVariables($variables);
}
