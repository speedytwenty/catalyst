<?php

/**
 *
 */

function catalyst_twig_render($template, $variables = array(), $key = NULL) {
  $path = libraries_get_path('twig');
  require_once DRUPAL_ROOT . '/' . $path . '/lib/Twig/Autoloader.php';
  Twig_Autoloader::register();
  if (empty($key)) {
    $key = 'index.html';
  }
  $loader = new Twig_Loader_Array(array($key => $template));
  $twig = new Twig_Environment($loader, array(
    'debug' => TRUE,
    'autoescape' => FALSE,
  ));

  $extensions = array(
    'addFunction' => array(
      'drupal_get_destination' => new Twig_SimpleFunction('drupal_get_destination', 'drupal_get_destination'),
      't' => new Twig_SimpleFunction('t', 't'),
      'render' => new Twig_SimpleFunction('render', 'catalyst_render'),
      'url' => new Twig_SimpleFunction('url', 'url'),
      'l' => new Twig_SimpleFunction('l', 'l'),
    ),
    'addFilter' => array(
      't' => new Twig_SimpleFilter('t', 't'),
      'render' => new Twig_SimpleFilter('render', 'catalyst_render'),
      'show' => new Twig_SimpleFilter('show', 'show'),
      'hide' => new Twig_SimpleFilter('show', 'hide'),
    ),
  );
  drupal_alter(__FUNCTION__, $twig, $extensions, $variables, $key);

  foreach ($extensions AS $callback => $items) {
    foreach ($items AS $extension) {
      $twig->{$callback}($extension);
    }
  }
  return $twig->render($key, $variables);
}

function catalyst_render($var) {
  return render($var);
}

function catalyst_twig_render_template($filepath, $variables = array()) {
  $filename = basename($filepath);
  $path = libraries_get_path('twig');
  require_once DRUPAL_ROOT . '/' . $path . '/lib/Twig/Autoloader.php';
  Twig_Autoloader::register();
  $loader = new Twig_Loader_Filesystem(dirname($filepath));
  $twig = new Twig_Environment($loader, array(
    'debug' => TRUE,
    'autoescape' => FALSE,
    'cache' => sprintf('%s/catalyst-twig/%s', file_directory_temp(), md5($filepath)),
  ));

  $extensions = array(
    'addFunction' => array(
      'drupal_get_destination' => new Twig_SimpleFunction('drupal_get_destination', 'drupal_get_destination'),
      't' => new Twig_SimpleFunction('t', 't'),
      'render' => new Twig_SimpleFunction('render', 'catalyst_render'),
      'url' => new Twig_SimpleFunction('url', 'url'),
      'l' => new Twig_SimpleFunction('l', 'l'),
    ),
    'addFilter' => array(
      't' => new Twig_SimpleFilter('t', 't'),
      'render' => new Twig_SimpleFilter('render', 'catalyst_render'),
      'show' => new Twig_SimpleFilter('show', 'show'),
      'hide' => new Twig_SimpleFilter('show', 'hide'),
    ),
  );
  drupal_alter('catalyst_twig_render', $twig, $extensions, $variables, $filepath);

  foreach ($extensions AS $callback => $items) {
    foreach ($items AS $extension) {
      $twig->{$callback}($extension);
    }
  }
  return $twig->render($filename, $variables);
}
