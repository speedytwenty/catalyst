<?php

/**
 * @file
 * Catalyst import functions.
 */

/**
 * Might need to extend this to support batching..
 */
function catalyst_import($source_directory, $deregister = FALSE, $update = TRUE) {
  $info = catalyst_load_import($source_directory);
  catalyst_register_import($info);
  catalyst_process_import($info['migrations'], $update);
  if ($deregister) {
    catalyst_deregister_import($info);
  }
}

function catalyst_import_update($module, $subpath = 'catalyst') {
  $source_directory = drupal_get_path('module', $module) . '/' . $subpath;
  catalyst_import($source_directory, TRUE);
}

function catalyst_process_import($migrations, $update = TRUE) {
  foreach (array_keys($migrations) AS $instance) {
    migrate_static_registration(array($instance));
    $migration = Migration::getInstance($instance);
    if ($update) {
      $migration->prepareUpdate();
    }
    $migration->processImport();
  }
}

function catalyst_process_rollback_import($migrations) {
  foreach (array_keys($migrations) AS $instance) {
    //migrate_static_registration(array($instance));
    $migration = Migration::getInstance($instance);
    $migration->processRollback();
  }
}

function catalyst_rollback_import($path, $deregister = TRUE) {
  $info = catalyst_load_import($path);
  catalyst_process_rollback_import($info['migrations']);

  if ($deregister) {
    catalyst_deregister_import($info);
  }
}

function catalyst_load_import($path, $filename = 'catalyst.json') {
  $info = drupal_json_decode(file_get_contents($path . '/' . $filename));
  foreach ($info['migrations'] AS &$migration) {
    $migration['source_directory'] = $path;
  }
  return $info;
}

function catalyst_register_import($info) {
  if (isset($info['groups']) && is_array($info['groups'])) {
    foreach ($info['groups'] as $name => $arguments) {
      $title = $arguments['title'];
      unset($arguments['title']);
      MigrateGroup::register($name, $title, $arguments);
    }
  }
  // Register any migrations defined via the hook.
  if (isset($info['migrations']) && is_array($info['migrations'])) {
    foreach ($info['migrations'] as $machine_name => $arguments) {
      $class_name = $arguments['class_name'];
      unset($arguments['class_name']);
      // Call the right registerMigration implementation. Note that this means
      // that classes that override registerMigration() must always call it
      // directly, they cannot register those classes by defining them in
      // hook_migrate_api() and expect their extension to be called.
      if (is_subclass_of($class_name, 'Migration')) {
        Migration::registerMigration($class_name, $machine_name, $arguments);
      }
      else {
        MigrationBase::registerMigration($class_name, $machine_name, $arguments);
      }
    }
  }
}

function catalyst_deregister_import($info) {
  // Register any migrations defined via the hook.
  if (isset($info['migrations']) && is_array($info['migrations'])) {
    foreach ($info['migrations'] as $machine_name => $arguments) {
      if (is_subclass_of($arguments['class_name'], 'Migration')) {
        Migration::deregisterMigration($machine_name);
      }
      else {
        MigrationBase::deregisterMigration($machine_name);
      }
    }
  }
  if (isset($info['groups']) && is_array($info['groups'])) {
    foreach (array_keys($info['groups']) as $name) {
      MigrateGroup::deregister($name);
    }
  }
}

function catalyst_import_directory($path) {
  $files_results = array_keys(file_scan_directory($path, '/catalyst\.json/'));
  foreach ($files_results AS $fr) {
    $metadata = drupal_json_decode(file_get_contents($fr), TRUE);
    if (_catalyst_import_is_legacy($metadata)) {
      catalyst_import_directory_legacy($path);
    }
    else {
      catalyst_import_entity($metadata, dirname($fr));
    }
  }
}

function catalyst_import_clone_entity($machine, $metadata, $path, $title = '') {
  $metadata['machine'] = $machine;
  $metadata['title'] = $title;
  return catalyst_import_entity($metadata, $path);
}

function catalyst_import_entity($metadata, $path) {
  if ($id = catalyst_import_lookup_id($metadata['type'], $metadata['machine'])) {
    $entity = entity_load_single('catalyst', $id);
    $wrapper = entity_metadata_wrapper('catalyst', $id);
  }
  else {
    $entity = entity_create('catalyst', array('type' => $metadata['type']));
    $wrapper = entity_metadata_wrapper('catalyst', $entity);
    if (isset($metadata['created'])) {
      $wrapper->created->set(strtotime($metadata['created']));
    }
  }
  $wrapper->changed->set(strtotime($metadata['changed']));
  $wrapper->title->set($metadata['label']);
  $wrapper->field__machine->set(array('machine' => $metadata['machine']));
  if (file_exists($path .'/access.php')) {
    $wrapper->field__access->set(array(
      'value' => file_get_contents($path . '/access.php'),
      'format' => 'catalyst_php',
    ));
  }
  if (file_exists($path .'/head.html')) {
    $wrapper->field__html_head->set(array(
      'value' => file_get_contents($path . '/head.html'),
      'format' => 'catalyst_html',
    ));
  }
  if (file_exists($path . '/README.md')) {
    $wrapper->field__admin_notes->set(array(
      'value' => file_get_contents($path . '/README.md'),
      'format' => 'catalyst_doc',
    ));
  }
  if (file_exists($path . '/preprocess.php')) {
    $wrapper->field__preprocess->set(array(
      'value' => preg_replace('/^.+\n/', '', file_get_contents($path . '/preprocess.php')),
      'format' => 'catalyst_php',
    ));
  }
  switch ($metadata['type']) {
    case 'javascript': $ext = 'js'; break;
    case 'stylehseet': $ext = 'css'; break;
    default: $ext = 'html'; break;
  }
  if (file_exists($path .'/body.' . $ext)) {
    $wrapper->field__body->set(array(
      'value' => file_get_contents($path . '/body.' . $ext),
      'format' => 'catalyst_' . $ext,
    ));
  }
  if (!empty($metadata['package'])) {
    catalyst_import_set_reference($wrapper, 'field__package', 'package', $metadata['package']);
  }
  $ats = array(
    'css' => array(
      'custom.css' => 'css',
      'layout.css' => 'css__layout',
      'page.css' => 'css__page',
    ),
    'js' => array(
      'custom.js' => 'js',
      'layout.js' => 'js__layout',
      'page.js' => 'js__page',
    ),
  );
  foreach ($ats AS $atype => $adata) {
    foreach ($adata AS $fil => $suf) {
      if (file_exists($path . '/' . $fil)) {
        $fn = 'field__' . $suf;
        $wrapper->{$fn}->set(array(
          'value' => file_get_contents($path . '/' . $fil),
          'format' => 'catalyst_' . $atype,
        ));
      }
    }
  }
  foreach (array('debug', 'drupal_processing', 'internal') AS $suf) {
    $fn = 'field__'.$suf;
    if (isset($metadata[$suf])) {
      $wrapper->{$fn}->set($metadata[$suf]);
    }
  }
  foreach (array('menu','data') AS $suf) {
    $fn = 'field__'.$suf;
    if (!empty($metadata[$suf])) {
      $wrapper->{$fn}->set(array(
        'serialization' => 'json_encode',
        'value' => $metadata[$suf],
      ));
    }
  }
  if ($files = file_scan_directory($path . '/files', '/.*/')) {
    $values = [];
    foreach (array_keys($files) AS $filepath) {
      $values[] = catalyst_import_file($filepath);
    }
    $wrapper->field__files->set($values);
  }
  drupal_alter('catalyst_import_entity', $wrapper, $metadata, $path);
  $wrapper->save();
}

function _catalyst_import_is_legacy($metadata) {
  $keys = array_keys($metadata);
  return is_numeric($keys[0]);
}

function catalyst_import_create_stub($type, $machine) {
  $entity = catalyst_entity_create($type, $machine);
  $wrapper = entity_metadata_wrapper('catalyst', $entity);
  $wrapper->save();
  return $wrapper->getIdentifier();
}

function catalyst_import_ensure_stub($type, $machine) {
  if ($eid = catalyst_import_lookup_id($type, $machine)) {
    return $eid;
  }
  return catalyst_import_create_stub($type, $machine);
}

function catalyst_entity_create($type, $machine) {
  $entity = entity_create('catalyst', array('type' => $type));
  $wrapper = entity_metadata_wrapper('catalyst', $entity);
  $wrapper->field__machine->set(array('machine' => $machine));
  return $wrapper->value();
}

function catalyst_import_set_reference(&$wrapper, $field_name, $type, $machine) {
  if (is_array($machine)) {
    $cvalues = $wrapper->{$field_name}->value();
    $pids = array();
    foreach ($machine AS $mach) {
      $pid = (int)catalyst_import_ensure_stub($type, $mach);
      foreach ($cvalues AS $cval) {
        if ($cval->id == $pid) {
          continue (2);
        }
      }
      array_push($cvalues, entity_load_single('catalyst', $pid));
      $pids[] = $pid;
    }
    $wrapper->{$field_name}->set($cvalues);
    return $pids;
  }
  else if (empty($machine)) {
    throw new InvalidArgumentException(t('Missing or empty machine parameter.'));
  }
  $pid = catalyst_import_ensure_stub($type, $machine);
  $wrapper->{$field_name}->set($pid);
  return $pid;
}

function catalyst_import_rollback_directory($dir, $package = NULL) {
  $return = array(
    'messages' => array(),
  );
  if (!is_dir($dir)) {
    $return['error'] = t('The directory %dir does not exist.', array('%dir' => $dir));
    return $return;
  }
  if (!file_exists($dir)) {
    $return['error'] = t('The directory %dir does not exist.', array('%dir' => $dir));
    return $return;
  }
  if (!$files = array_keys(file_scan_directory($dir, '/catalyst\.json/'))) {
    $return['error'] = t('The directory %dir does not contain any catalyst.json files.', array('%dir' => $dir));
    return $return;
  }
  $ids = array();
  foreach ($files AS $filepath) {
    $json = drupal_json_decode(file_get_contents($filepath), TRUE);
    if ($id = catalyst_import_lookup_id($json['type'], $json['machine'])) {
      $ids[] = $id;
      $return['messages'][] = t('Removed catalyst @type @id (@machine)', array(
        '@type' => $json['type'],
        '@id' => $id,
        '@machine' => $json['machine'],
      ));
    }
  }
  entity_delete_multiple('catalyst', $ids);
  return $return;
}

function catalyst_import_file($filepath) {
  $file = catalyst_import_create_file_entity($filepath);
  return (array) file_save($file);
}

function catalyst_import_create_file_entity($destination, $uid = 1) {
  $file = (object) array(
    'uri' => $destination,
    'uid' => $uid,
    'filename' => drupal_basename($destination),
    'filemime' => file_get_mimetype(urldecode($destination)),
    'status' => FILE_STATUS_PERMANENT,
    'display' => 1,
  );

  if ($slash_pos = strpos($file->filemime, '/')) {
    $file->type = substr($file->filemime, 0, $slash_pos);
  }
  else $file->type = 'file';

  $existing_files = file_load_multiple(array(), array('uri' => $file->uri));
  if (count($existing_files)) {
    $existing = reset($existing_files);
    $file->fid = $existing->fid;
    $file->filename = $existing->filename;
  }
  return $file;
}

function catalyst_import_lookup_id($type, $machine, $multiple = FALSE) {
  $query = new EntityFieldQuery;
  $result = $query->entityCondition('entity_type', 'catalyst', '=')
    ->entityCondition('bundle', $type)
    ->fieldCondition('field__machine', 'machine', $machine, '=')
    ->execute();
  if (!empty($result['catalyst'])) {
    $keys = array_keys($result['catalyst']);
    return $multiple ? $keys : array_shift($keys);
  }
  return NULL;
}
