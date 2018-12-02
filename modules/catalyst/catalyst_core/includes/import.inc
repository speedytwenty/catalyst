<?php

/**
 * @file
 * Catalyst import functions.
 */

/**
 * Masks for import "statuses".
 */

/**
 * The imported assets are considered part of the code base. Local files
 * will be leveraged. Files are registered with Drupal's filesystem but
 * not copied.
 */
define('CATALYST_IMPORT_STATUS_PERMANENT', 1);

/**
 * The imported assets are temporary (extracted from archive, etc); files
 * will be copied into Drupal's filesystem.
 */
define('CATALYST_IMPORT_STATUS_TEMPORARY', 0);

/**
 * Scan's a directory for import assets.
 */
function catalyst_import_scan_directory($dir) {
  if ($files_results = array_keys(file_scan_directory($dir, '/catalyst\.json/'))) {
    $results = array();
    foreach ($files_results AS $fr) {
      $fd = dirname($fr);
      $metadata = drupal_json_decode(file_get_contents($fr), TRUE);
      if (empty($metadata['files_path'])) {
        $metadata['files_path'] = 'files';
      }
      $metadata['filepath'] = $fr;
      if (_catalyst_import_is_legacy($metadata)) {
        catalyst_import_legacy_metadata($results, $metadata, $fr);
      }
      else {
        $fmap = array(
          'access' => 'access.php',
          'html_head' => 'head.html',
          'admin_notes' => 'README.md',
          'preprocess' => 'preprocess.php',
          'css_custom' => 'custom.css',
          'css_page' => 'page.css',
          'css_layout' => 'layout.css',
          'js_custom' => 'custom.js',
          'js_page' => 'page.js',
          'js_layout' => 'layout.js',
        );
        if ($body_field = catalyst_resolve_field('body', $metadata['type'])) {
          $ext = str_replace('catalyst_', '', $body_field['format']);
          $fmap['body'] = 'body.' . $ext;
        }
        foreach  ($fmap AS $k => $f) {
          if (file_exists($fd.'/'.$f)) {
            $metadata[$k] = preg_replace('/^\<\?php\n/', '', file_get_contents($fd.'/'.$f));
          }
        }
        if ($files_field = catalyst_resolve_field('files', $metadata['type'])) {
          if ($files = array_keys(file_scan_directory($fd . '/' . $metadata['files_path'], '/.*/'))) {
            $metadata['files'] = array();
            foreach ($files AS $file) {
              if (file_exists($file)) {
                $metadata['files'][] = basename($file);
              }
            }
          }
        }
        $metadata['assets'] = catalyst_import_component_assets($fd);
        drupal_alter('catalyst_import_metadata', $metadata);
        $results[] = $metadata;
      }
    }
    return $results;
  }
  else {
    return FALSE;
  }
}

function catalyst_import_directory($path, $status = CATALYST_IMPORT_STATUS_TEMPORARY) {
  $return = array('messages' => array());
  $results = catalyst_import_scan_directory($path);
  foreach ($results AS $metadata) {
    if ($wrapper = catalyst_import_entity($metadata, $status)) {
      $return['messages'][] = t('Imported/updated catalyst @type: @machine.', array(
        '@type' => $wrapper->getBundle(),
        '@machine' => $wrapper->field__machine->machine->value(),
      ));
    }
  }
  return $return;
}

function catalyst_import_entity($metadata, $status = CATALYST_IMPORT_STATUS_TEMPORARY) {
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
  if (isset($metadata['changed'])) {
    $wrapper->changed->set(strtotime($metadata['changed']));
  }
  $dir = dirname($metadata['filepath']);
  $wrapper->title->set($metadata['label']);
  $wrapper->field__machine->set(array('machine' => $metadata['machine']));
  $fmap = array(
    'admin_notes' => 'catalyst_doc',
    'access' => 'catalyst_php',
    'preprocess' => 'catalyst_php',
    'html_head' => 'catalyst_html',
  );
  foreach ($fmap AS $k => $format) {
    if (!empty($metadata[$k])) {
      $fn = 'field__'.$k;
      $wrapper->{$fn}->set(array(
        'value' => $metadata[$k],
        'format' => $format,
      ));
    }
  }
  if ($metadata['type'] == 'package') {
    if (!empty($metadata['module'])) {
      $wrapper->field__data->set(array(
        'serialization' => 'json_encode',
        'value' => array(
          'module' => $metadata['module'],
          'subdir' => empty($metadata['subdir']) ? NULL : $metadata['subdir'],
        ),
      ));
    }
  }
  else if (!empty($metadata['package'])) {
    catalyst_import_set_reference($wrapper, 'field__package', 'package', $metadata['package']);
  }
  $map = array(
    'admin_notes',
    'access',
    'preprocess',
    'html_head',
    'body',
    'js_custom' => 'js',
    'js_page' => 'js__page',
    'js_layout' => 'js__layout',
    'css_custom' => 'css',
    'css_page' => 'css__page',
    'css_layout' => 'css__layout',
  );
  foreach ($map AS $k => $f) {
    $k = is_numeric($k) ? $f : $k;
    if (!empty($metadata[$k])) {
      if ($field_info = catalyst_resolve_field($f, $wrapper->getBundle())) {
        $wrapper->{$field_info['field_name']}->set(array(
          'value' => $metadata[$k],
          'format' => $field_info['format'],
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
  if (!empty($metadata['menu']) && $menu_field = catalyst_resolve_field('menu', $metadata['type'])) {
    $wrapper->{$menu_field['field_name']}->set(array(
      'serialization' => $menu_field['settings']['serialization'],
      'value' => $metadata['menu'],
    ));
  }
  if (!empty($metadata['files'])) {
    $values = [];
    foreach ($metadata['files'] AS $basename) {
      $values[] = catalyst_import_file(sprintf('%s/%s/%s', $dir, $metadata['files_path'], $basename));
    }
    $wrapper->field__files->set($values);
  }
  drupal_alter('catalyst_import', $wrapper, $metadata);
  return $wrapper->save();
}


/**
 */
function catalyst_import_component_assets($dir) {
  $files = file_scan_directory($dir, '/.*/');
  $assets = array();
  foreach ($files AS $filepath => $file) {
    $fp = str_replace($dir . '/', '', $filepath);
    $assets[$fp] = (object) array(
      'filepath' => $filepath,
      'filename' => $file->filename,
      'timestamp' => filemtime($filepath),
      'hash' => md5(file_get_contents($filepath)),
    );
  }
  return $assets;
}

/**
 * Legacy import support (after dropping migrate)
 */
function catalyst_import_legacy_metadata(&$results, $info, $filepath) {
  $dir = dirname($filepath);
  foreach ($info['migrations'] AS $type_key => $m) {
    $type = str_replace('catalyst_test__', '', $type_key);
    $contents = file_get_contents($dir . '/' . $m['source_filename']);
    $items = drupal_json_decode($contents, TRUE);
    $map = array(
      'title' => 'label',
      'files_custom' => 'files',
      'files_shared' => 'media_files',
      'preprocess_php' => 'preprocess',
      'content' => 'body',
      'access_php' => 'access',
      'menu_options' => 'menu',
    );
    switch ($type) {
      case 'layout':
        $map += array(
          'javascripts' => 'media_javascripts__layout',
          'stylesheets' => 'media_stylesheets__layout',
        );
        break;
      case 'tempalte':
      case 'page':
        $map += array(
          'javascripts' => 'media_javascripts__page',
          'stylesheets' => 'media_stylesheets__page',
        );
        break;
      default:
        $map += array(
          'javascripts' => 'media_javascripts',
          'stylesheets' => 'media_stylesheets',
        );
        break;
    }
    foreach ($items AS $item) {
      $item['filepath'] =  $filepath;
      $item['type'] = $type;
      if (!empty($m['source_files_directory'])) {
        $item['files_path'] = $m['source_files_directory'];
      }
      foreach ($map AS $k => $v) {
        if (isset($item[$k])) {
          $item[$v] = $item[$k];
          unset($item[$k]);
        }
      }
      if (!empty($item['files'])) {
        $files_path = isset($item['files_path']) ? $item['files_path'] : 'files';
        $item['assets'] = array();
        foreach ($item['files'] AS $pathval) {
          $fp = sprintf('%s/%s/%s', $dir, $files_path, $pathval);
          $item['assets'][] = array(
            'filepath' => $fp,
            'filename' => drupal_basename($fp),
            'timestamp' => filemtime($fp),
            'hash' => md5(file_get_contents($fp)),
          );
        }
      }
      if (!empty($item['block_placements'])) {
        foreach (array_keys($item['block_placements']) AS $i) {
          switch ($type) {
            case 'block':
            case 'layout':
              $item['block_placements'][$i]['type'] = $type;
              break;
            case 'page':
            case 'template':
              $item['block_placements'][$i]['type'] = 'layfield';
              break;
          }
          $item['block_placements'][$i]['machine'] = $item['block_placement_ids'][$i];
        }
        unset($item['block_placement_ids']);
      }
      unset($item['id']);
      $results[] = $item;
    }
  }
}

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

function catalyst_import_clone_entity($machine, $metadata, $path, $title = '') {
  $metadata['machine'] = $machine;
  $metadata['title'] = $title;
  return catalyst_import_entity($metadata, $path);
}


function _catalyst_import_is_legacy($metadata) {
  return isset($metadata['migrations']);
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
  }
  else if (!file_exists($dir)) {
    $return['error'] = t('The directory %dir does not exist.', array('%dir' => $dir));
  }
  else if (!$items = catalyst_import_scan_directory($dir)) {
    $return['error'] = t('The directory %dir does not contain any catalyst.json files.', array('%dir' => $dir));
  }
  else {
    $ids = array();
    foreach ($items AS $item) {
      if ($id = catalyst_import_lookup_id($item['type'], $item['machine'])) {
        $ids[] = $id;
        $return['messages'][] = t('Removed catalyst @type @id (@machine)', array(
          '@type' => $item['type'],
          '@id' => $id,
          '@machine' => $item['machine'],
        ));
      }
    }
    entity_delete_multiple('catalyst', $ids);
  }
  return $return;
}

function catalyst_import_rollback_package($machine) {
  $return = array('messages' => array());
  if ($package = catalyst_load_single('package', $machine)) {
    $query = new EntityFieldQuery;
    $result = $query->entityCondition('entity_type', 'catalyst')
      ->fieldCondition('field__package', 'target_id', $package->id, '=')
      ->execute();
    if (!empty($result['catalyst'])) {
      entity_delete_multiple('catalyst', array_keys($result['catalyst']));
      $return['messages'][] = t('Rolled back @count entities of the @machine package.', array(
        '@count' => count($result['catalyst']),
        '@machine' => $machine,
      ));
    }
  }
  else $return['error'] = t('The package %machine does not exist.', array('%machine' => $machine));
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
    foreach ($keys AS $k => $key) {
      $keys[$k] = (int)$key;
    }
    return $multiple ? $keys : array_shift($keys);
  }
  return NULL;
}
