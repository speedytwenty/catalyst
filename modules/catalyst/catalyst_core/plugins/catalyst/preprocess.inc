<?php

/**
 * @file
 * Provides ability to define PHP preprocessing that can be used to generate or
 * manipulate template output.
 */

$plugin = array(
  'label' => t('Preprocessing'),
  'entity build' => 'catalyst_preprocess_plugin_entity_build',
  'entity save' => 'catalyst_preprocess_plugin_entity_save',
  'default settings' => array(
    'preserve_files' => TRUE,
    'safe_delete' => TRUE,
    'safe_overwrite' => TRUE,
  ),
);

// psuedo
function catalyst_preprocess_plugin_settings_form($settings) {
  $settings += $plugin['default settings'];
  $form['preserve_files'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['preserve_files'],
    '#title' => t('Preserve files'),
    '#description' => t('Will prevent permanent (non-temporary) files from being removed when it may otherwise be deleted.'),
  );
  $form['safe_delete'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['safe_delete'],
    '#title' => t('Safe delete'),
    '#description' => implode(' ', array(
      t('Will prevent deleting permanent (non-temporary) files from being deleted if they have been modified.'),
      '<em>'.t('Not applicable when Preserve Files is active.').'</em>'
    )),
  );
}

function catalyst_preprocess_plugin_entity_build(&$build) {
  if (!empty($build['#entity']->field__preprocess)) {
    $build['#pre_render'][] = 'catalyst_preprocess_plugin_post_render';
  }
}

function catalyst_preprocess_plugin_post_render(&$build) {
  catalyst_preprocess_plugin_preprocess($build['#entity_type'], $build['#entity']);
  return $build;
}

function catalyst_preprocess_plugin_preprocess($entity_type, $entity) {
  if (!isset($entity->preprocessed) && $data = $entity->getDataValue('preprocess')) {
    $filepath =& drupal_static(__FUNCTION__);
    $filepath = $data['filepath'];
    $variables = _catalyst_preprocess_plugin_preprocess($entity->variables());
    $entity->setVariables($variables);
    $entity->preprocessed = TRUE;
  }
}

function _catalyst_preprocess_plugin_preprocess($variables) {
  include drupal_static('catalyst_preprocess_plugin_preprocess');
  drupal_static_reset('catalyst_preprocess_plugin_preprocess');
  return $variables;
}

function catalyst_preprocess_plugin_entity_save($entity_type, $entity, $settings = array()) {
  if (empty($entity->field__preprocess)) return;
  catalyst_include('entity');
  $value = entity_valval($entity->wrapper()->field__preprocess);
  $filepath = catalyst_entity_get_filepath($entity_type, $entity, 'preprocess.php');
  $exists = file_exists($filepath) && is_file($filepath);
  $data = $entity->getDataValue('preprocess');
  if (!empty($data) && !empty($entity->original->field__preprocess)) {
    $orig = entity_valval($entity->original->wrapper()->field__preprocess);
    if ($value == $orig && ($exists || empty($value))) return;
  }
  if (!strpos($value, '<?') !== 0) {
    $value = sprintf("<?php\n%s", $value);
  }
  $curhash = md5($value);
  if (!empty($data)) {
    _catalyst_preprocess_plugin_unlink($entity_type, $entity, $data);
  }
  $dir = dirname($filepath);
  if (!is_dir($dir)) {
    drupal_mkdir($dir, NULL, TRUE);
  }
  file_unmanaged_save_data($value, $filepath, FILE_EXISTS_REPLACE);
  $entity->setDataValue('preprocess', array(
    'filepath' => $filepath,
    'hash' => $curhash,
    'timestamp' => time(),
    'status' => 1,
  ));
}

/**
 * Implements catalyst_PLUGIN_entity_delete().
 */
function catalyst_preprocess_plugin_entity_delete($entity_type, $entity) {
  $settings += $plugin['default settings'];
  if ($data = $entity->getDataValue('preprocess')) {
    if (empty($data['status']) || !$settings['preserve_files']) {
      if ($settings['safe_delete']) {
        catalyst_preprocess_plugin_unlink($data['filepath']);
      }
      else unlink($data['filepath']);
    }
  }
}

/**
 * Used to ensure a file that is about to be deleted hasn't changed.
 */
function _catalyst_preprocess_plugin_unlink($entity_type, $entity, $data) {
  if (file_exists($data['filepath'])) {
    $contents = file_get_contents($data['filepath']);
    $hash = md5($contents);
    if (0 && $hash != $data['hash']) {
      $msg = 'File change detected when attempting to remove the preprocessing file from @entity_type:@bundle:@machine located at: @filepath';
      throw new Exception(format_string($msg, array(
        '@entity_type' => $entity_type,
        '@bundle' => $entity->wrapper()->getBundle(),
        '@machine' => $entity->machine,
        '@filepath' => $data['filepath'],
      )));
    }
  }
}

