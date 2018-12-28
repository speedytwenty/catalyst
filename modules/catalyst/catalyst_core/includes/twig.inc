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
    _catalyst_twig_init($twig);
  }
  return $twig;
}

function _catalyst_twig_init(Twig_Environment $twig) {
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

  $twig->addFunction(new Twig_SimpleFunction('render', 'catalyst_render'));
  $twig->addFunction(new Twig_SimpleFunction('entity_uri', 'entity_uri'));
  $twig->addFilter(new Twig_SimpleFilter('render', 'catalyst_render'));
  $twig->addFilter(new Twig_SimpleFilter('entity_valval', 'catalyst_twig_entity_valval'));
  $twig->addFunction(new Twig_SimpleFunction('form', 'catalyst_twigform'));
  $twig->addFunction(new Twig_SimpleFunction('customfilepath', 'catalyst_media_customfilepath'));
  $twig->addFunction(new Twig_SimpleFunction('customfileurl', 'catalyst_media_customfileurl'));
  $twig->addFunction(new Twig_SimpleFunction('customfileuri', 'catalyst_media_customfileuri'));

  drupal_alter('catalyst_twig', $twig);
}

function catalyst_media_customfilepath($basename, $format = 'path') {
  if (empty($GLOBALS['catalyst_twig_entity'])) {
    throw new RuntimeException(t('Calling customfilepath(@basename) when no entity is being rendered.', array(
      '@basename' => $basename,
    )));
  }
  $entity = $GLOBALS['catalyst_twig_entity'];
  if (!empty($entity->field__files)) {
    foreach ($entity->wrapper()->field__files->value() AS $file) {
      if ($file['filename'] == $basename) {
        if ($format == 'url') {
          return $file['uri'];
        }
        elseif ($format == 'url') {
          return file_create_url($file['uri']);
        }
        else {
          $url = parse_url(file_create_url($file['uri']));
          return $url['path'];
        }
      }
    }
  }
  trigger_error(t('Unknown customfilepath: @basename. (@entity_type:@bundle:machine)', array(
    '@basename' => $basename,
    '@entity_type' => $entity->wrapper()->type(),
    '@bundle' => $entity->wrapper()->getBundle(),
    '@machine' => $entity->machine,
  )));
}
function catalyst_media_customfileurl($basename) {
  return catalyst_media_customfilepath($basename, 'url');
}

function catalyst_media_customfileuri($basename) {
  return catalyst_media_customfilepath($basename, 'uri');
}

function catalyst_twig_render_entity_file($entity_type, CatalystEntity $entity, $filename, array $variables = array()) {
  catalyst_twig()->getLoader()->setEntity($entity_type, $entity);
  $result = catalyst_twig()->render($field_name, $filename, $variables);
  $entity->setVariables($variables);
  return $result;
}

function catalyst_twig_render_template($filename, array &$variables = array()) {
  return catalyst_twig()->render($filepath, $variables);
}

function catalyst_coreblock($module, $delta = 0, $render = TRUE) {
  if ($block = block_load($module, $delta)) {
    if (!isset($block->title)) $block->title = null;
    if (!isset($block->region)) $block->region = null;
    $build = _block_get_renderable_array(_block_render_blocks(array($block)));
    return $render ? drupal_render($build) : $build;
  }
  trigger_error(t('Unknown block for the %module module: %delta', array(
    '%module' => $module,
    '%delta' => $delta,
  )), E_USER_WARNING);
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
