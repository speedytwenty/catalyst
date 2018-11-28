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
  if (_catalyst_import_is_legacy($path)) {
    catalyst_import_directory_legacy($path);
  }
  else {
    $files_results = array_keys(file_scan_directory($path, '/catalyst\.json/'));
    foreach ($files_results AS $fr) {
      $metadata = drupal_json_decode(file_get_contents($fr), TRUE);
      dsm($metadata['type'] . ':' . $metadata['machine']);
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
  if ($eid = catalyst_lookup_entity($metadata['type'], $metadata['machine'])) {
    $entity = entity_load_single('catalyst', $eid);
    $wrapper = entity_metadata_wrapper('catalyst', $entity);
  }
  else {
    dsm('NEW entity');
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
  drupal_alter('catalyst_import_entity', $wrapper, $metadata, $path);
  $wrapper->save();
}

function _catalyst_import_is_legacy($path) {
  return file_exists($path . '/catalyst.json');
}

function catalyst_import_create_stub($type, $machine) {
  $entity = catalyst_entity_create($type, $machine);
  $wrapper = entity_metadata_wrapper('catalyst', $machine);
  $wrapper->save();
  return $wrapper->getIdentifier();
}

function catalyst_import_ensure_stub($type, $machine) {
  if ($eid = catalyst_lookup_entity($type, $machine)) {
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
          continue (1);
        }
      }
      array_push($cvalues, entity_load_single('catalyst', $pid));
      $pids[] = $pid;
    }
    $wrapper->{$field_name}->set($cvalues);
    return $pids;
  }
  $pid = catalyst_import_ensure_stub($type, $machine);
  $wrapper->{$field_name}->set($pid);
  return $pid;
}
