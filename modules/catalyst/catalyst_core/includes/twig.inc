<?php

/**
 *
 */

function &catalyst_twig($options = array()) {
  $twig = &drupal_static(__FUNCTION__);
  $options += array(
    'cache' => sprintf('%s/catalyst-twig', file_directory_temp()),
    'debug' => TRUE,
    'autoescape' => FALSE,
  );
  if (!isset($twig)) {
    $path = libraries_get_path('twig');
    require_once DRUPAL_ROOT . '/' . $path . '/lib/Twig/Autoloader.php';
    Twig_Autoloader::register();
    $twig = new Twig_Environment(new Twig_Loader_Catalyst_Entity(), $options);
    $twig->addFilter(new Twig_SimpleFilter('t', 't'));
    $twig->addFunction(new Twig_SimpleFunction('t', 't'));
    $twig->addFunction(new Twig_SimpleFunction('plural', 'format_plural'));
    $twig->addFilter(new Twig_SimpleFilter('plural', 'format_plural'));
    $twig->addFilter(new Twig_SimpleFilter('url', 'url'));
    $twig->addFunction(new Twig_SimpleFunction('url', 'url'));
    $twig->addFilter(new Twig_SimpleFilter('l', 'l'));
    $twig->addFunction(new Twig_SimpleFunction('l', 'l'));
    $twig->addFunction(new Twig_SimpleFunction('drupal_get_destination', 'drupal_get_destination'));
    $twig->addFunction(new Twig_SimpleFunction('coreblock', 'catalyst_coreblock'));
    $twig->addFilter(new Twig_SimpleFilter('coreblock', 'catalyst_coreblock'));
    $twig->addFunction(new Twig_SimpleFunction('current_path', 'current_path'));
    $twig->addFunction(new Twig_SimpleFunction('show', 'catalyst_show'));
    $twig->addFunction(new Twig_SimpleFunction('hide', 'catalyst_hide'));

    $twig->addFunction(new Twig_SimpleFunction('render', 'catalyst_render'));
    $twig->addFunction(new Twig_SimpleFunction('entity_uri', 'entity_uri'));
    $twig->addFilter(new Twig_SimpleFilter('render', 'catalyst_render'));
    $twig->addFilter(new Twig_SimpleFilter('entity_valval', 'catalyst_twig_entity_valval'));
    $twig->addFunction(new Twig_SimpleFunction('form', 'catalyst_twigform'));

    drupal_alter('catalyst_twig', $twig);
  }
  return $twig;
}

function catalyst_show($element) {
  show($element);
  return drupal_render($element);
}

function catalyst_hide($element) {
  hide($element);
}

function catalyst_twig_render_entity_file($entity_type, CatalystEntity $entity, $filename, array $variables = array()) {
  $store = &drupal_static('catalyst_twig_entity');
  $store = $entity;
  catalyst_twig()->getLoader()->setEntity($entity_type, $entity);
  $variables += array('entity' => $entity);
  $result = catalyst_twig()->render($filename, $variables);
  return $result;
}

function catalyst_twig_render_template($filepath, $variables = array()) {
  return catalyst_twig()->render($filepath, $variables);
}

function catalyst_coreblock($module, $delta = 0, $render = true) {
  if ($block = block_load($module, $delta)) {
    if (!isset($block->title)) $block->title = null;
    if (!isset($block->region)) $block->region = null;
    $build = _block_get_renderable_array(_block_render_blocks(array($block)));
    return drupal_render($build);
    return $render ? drupal_render($build) : $build;
  }
  throw new Exception(t('Missing block %delta in %module', array(
    '%module' => $module,
    '%delta' => $delta,
  )));
}

function catalyst_twig_entity_valval($data) {
  if ($data) return entity_valval($data);
}

function catalyst_twigform($callback) {
  $args = func_get_args();
  $form = call_user_func_array('drupal_get_form', $args);
  return render($form);
}


function catalyst_render_block($module, $delta = '') {
  $block = block_load($module, $delta);
  $build = _block_get_renderable_array(_block_render_blocks(array($block)));
  return render($build);
}

function catalyst_render($v) {
  return render($v);
}

function catalyst_twig_render($template, &$variables = array(), $key = NULL) {
  if (empty($key)) {
    $key = 'index.html';
  }
  $original_loader = catalyst_twig()->getLoader();
  catalyst_twig()->setLoader(new Twig_Loader_Array(array($key => $template)));
  $result = catalyst_twig()->render($key, $variables);
  catalyst_twig()->setLoader($original_loader);
  return $result;
}
