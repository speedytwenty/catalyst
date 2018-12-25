<?php

/**
 * @file
 * Code file handling and manipulation.
 */

class CatalystCodeFileException extends Exception {}
class CatalystCodeFileMismatchException extends Exception {}
class CatalystCodeFileExistsException extends Exception {}

function catalyst_code_entity_filepath(CatalystEntity $entity, $filename = 'catalyst.json') {
  return sprintf('%s/%s', catalyst_code_entity_directory($entity), $filename);
}

function catalyst_code_entity_directory(CatalystEntity $entity) {
  if (!empty($entity->filepath)) {
    return dirname($entity->filepath);
  }
  else if (!empty($entity->module)) {
    return catalyst_code_entity_module_directory($entity);
  }
  return sprintf('%s/%s/%s/%s', file_directory_temp(), $entity->wrapper()->type(), $entity->type, $entity->machine);
}

function catalyst_code_entity_module_directory(CatalystEntity $entity) {
  if (!empty($entity->module)) {
    if (empty($entity->subdir) || $entity->subdir == '.') {
      return sprintf('%s/%s/%s', drupal_get_path('module', $entity->module), $entity->type, $entity->machine);
    }
    return sprintf('%s/%s/%s/%s', drupal_get_path('module', $entity->module), $entity->subdir, $entity->type, $entity->machine);
  }
}

function catalyst_code_entity_public_directory(CatalystEntity $entity) {
  if (empty($entity->filepath) && empty($entity->module)) {
    return sprintf('%s://catalyst/%s/%s', file_default_scheme(), $entity->type, $entity->machine);
  }
  else if (!empty($entity->module)) {
    return catalyst_code_entity_module_directory($entity);
  }
  return catalyst_code_entity_tempory_directory($entity);
}

function catalyst_code_entity_public_filepath($entity, $filename) {
  $dir = catalyst_code_entity_public_directory($entity);
  return sprintf('%s/%s',  $dir, $filename);
}

function catalyst_code_entity_temporary_directory($entity) {
  return sprintf('%s/%s/%s/%s', file_directory_temp(), $entity->wrapper()->type(), $entity->type, $entity->machine);
}

function _catalyst_entity_directory_is_public($dir) {
  if ($dir = realpath($dir)) {
    $docroot = realpath(DRUPAL_ROOT);
    return $dir != $docroot && $dir != str_replace($docroot, '', $dir);
  }
  return FALSE;
}

function catalyst_code_field_formats($format = NULL) {
  $formats = array(
    'catalyst_php' => array(
    ),
    'catalyst_html' => array(),
    'catalyst_js' => array(
      'has_public_file' => TRUE,
    ),
    'catalyst_css' => array(
      'has_public_file' => TRUE,
    ),
    'catalyst_doc' => array(
    ),
  );
  return $format ? $formats[$format] : $formats;
}

function catalyst_code_upsert_entity_code_file(CatalystEntity $entity, $field_info, $filename, $public_filename = NULL) {
  if (is_string($field_info)) {
    // Allow passing a field name in place of field instance info
    $fn = $field_info;
    if (!$field_info = field_info_instance($entity->wrapper()->type(), $fn, $entity->wrapper()->getBundle())) {
      throw new CatalystCodeFileException(t('Unknown field instance: @field_name for @entity_type @bundle (@machine).', array(
        '@field_name' => $fn,
        '@entity_type' => $entity_type,
        '@bundle' => $entity->wrapper()->getBundle(),
        '@machine' => $entity->machine,
      )), E_USER_WARNING);
      return;
    }
  }
  else $fn = $field_info['field_name'];

  if (empty($field_info['settings']['better_formats']['allowed_formats'])) {
    trigger_error(t('Unable to resolve field format for @field_label (@field_name)', array(
      '@field_name' => $fn,
      '@field_label' => check_plain($field_info['label']),
    )), E_USER_WARNING);
  }
  $formats = array_filter($field_info['settings']['better_formats']['allowed_formats']);
  $format = array_shift($formats);

  $dest_filepath = catalyst_code_entity_filepath($entity, $filename);
  $dest_exists = file_exists($dest_filepath);
  $dest_hash = $dest_exists ? _catalyst_code_hash(file_get_contents($dest_filepath), $filename) : NULL;
  $dest_public_filepath = $public_filename ? catalyst_code_entity_public_filepath($entity, $public_filename) : NULL;
  $dest_public_realpath = $dest_public_filepath ? drupal_realpath($dest_public_filepath) : NULL;
  $dest_public_exists = $dest_public_realpath ? file_exists($dest_public_realpath) : FALSE;

  $value = entity_valval($entity->wrapper()->{$fn});
  if ($format == 'catalyst_php' && strpos($value, '<?') !== 0) {
    $value = "<?php\n".$value;
  }
  if (!empty($value) && !preg_match("/\n$/", $value)) {
    $value .= "\n";
  }
  $value_hash = _catalyst_code_hash($value, $filename);


  $file_info = array(
    'filepath' => $dest_filepath,
    'hash' => $value_hash,
    'timestamp' => time(),
  );
  catalyst_code_entity_set_file_info($entity, $fn, $file_info);

  if (!empty($entity->original) && $original = catalyst_code_entity_file_info($entity->original, $filename)) {
    $is_move = $original['filepath'] != $dest_filepath;
    if (!file_exists($original['filepath'])) {
      $needs_restored = !$dest_exists;
      trigger_error(t('Missing code file @filename for @label: @filepath', array(
        '@label' => $entity->wrapper()->label(),
        '@filename' => $filename,
        '@filepath' => $original['filepath'],
      )), E_USER_NOTICE);
    }
    else {
      $orig_file_hash = _catalyst_code_hash(file_get_contents($original['filepath']), $filename);
      $is_change = $orig_file_hash != $value_hash;
      // False represents that the original file has been externally modified
      $orig_status = $original['hash'] == $orig_file_hash;
      if (!$orig_status) {
        if ($is_move) {
          trigger_error(E_USER_NOTICE, t('Potential code loss detected: @filepath', array(
            '@filepath' => $dest_filepath,
          )));
        }
        elseif ($original['hash'] != $orig_file_hash && !isset($entity->force_overwrite)) {
          // Overwritting external changes
          $message = 'Code file mismatch detected: @filepath';
          throw new CatalystCodeFileMismatchException(t($message, array(
            '@filepath' => $dest_filepath,
          )));
        }
      }
      if (!$is_change && !$is_move && $dest_hash == $orig_file_hash) {
        if ($public_filename && !empty($value) && $dest_exists && !$dest_public_exists) {
          if (_catalyst_code_entity_upsert_public_file($entity, $fn, $dest_filepath, $dest_public_filepath)) {
            trigger_error(t('Restored missing public file (@filename) for @label @entity_type:@bundle:@machine). Restored to: @filepath', array(
              '@filepath' => $dest_public_filepath,
              '@filename' => $public_filename,
              '@label' => $entity->wrapper()->label(),
              '@entity_type' => $entity_type,
              '@bundle' => $entity->wrapper()->getBundle(),
              '@machine' => $entity->machine,
            )));
          }
          return;
        }
        else {
          // need to ensure the public file is good here
          return;
        }
      }

      if ($orig_status || !$is_move) {
        // The original file is as expected and will be moving or overwritten
        // unless the $value is empty
        unlink($original['filepath']);
        if ($public_filename && !empty($original['public_filepath'])) {
          _catalyst_code_unlink_public_file($original['public_filepath']);
        }
      }
    }
  }


  if ($dest_exists) unlink($dest_filepath);
  if (empty($value)) {
    catalyst_code_entity_set_file_info($entity, $fn, NULL);
    return;
  }

  if (file_exists($dest_filepath)) {
    throw new CatalystCodeFileExistsException(t('Code file error: The destination file already exists: @filepath', array(
      '@filepath' => $dest_filepath,
    )));
  }

  $dest_dir = dirname($dest_filepath);
  if (!is_dir($dest_dir)) {
    drupal_mkdir($dest_dir, NULL, TRUE);
  }
  file_unmanaged_save_data($value, $dest_filepath, FILE_EXISTS_REPLACE);

  if ($public_filename) {
    _catalyst_code_entity_upsert_public_file($entity, $fn, $dest_filepath, $dest_public_filepath);
  }

  return catalyst_code_entity_file_info($entity, $fn);
}

function catalyst_code_entity_set_file_info(CatalystEntity $entity, $field_name, $file_info) {
  $code_fields = $entity->getDataValue('code_fields');
  if ($file_info) {
    $code_fields[$field_name] = $file_info;
  }
  elseif (isset($code_fields[$field_name])) {
    unset($code_fields[$field_name]);
  }
  $entity->setDataValue('code_fields', $code_fields);
}

function catalyst_code_entity_set_public_file_info(CatalystEntity $entity, $field_name, $public_filepath) {
  if ($file_info = catalyst_code_entity_file_info($entity, $field_name)) {
    if ($public_filepath) {
      $file_info['public_filepath'] = $public_filepath;
    }
    else {
      unset($file_info['public_filepath']);
    }
    catalyst_code_entity_set_file_info($entity, $field_name, $file_info);
  }
  elseif ($public_filepath) {
    trigger_error(t('Unable to set public_path for @field_name as the file info is not set.', array(
      '@field_name' => $field_name,
    )), E_USER_WARNING);
  }
}

function catalyst_code_render_entity_code(CatalystEntity $entity, $plugin) {
  $field_name = $plugin['field_name'];
  $value = $entity->wrapper()->{$field_name}->value();
  if (empty($value['value'])) return;
  return $plugin['code renderer']($entity, $plugin['field_name'], $plugin);
}

function catalyst_code_render_entity_twig(CatalystEntity $entity, $field_name) {
  $value = $entity->wrapper()->{$field_name}->value();
  if (empty($value['value'])) return;
  if ($file_info = catalyst_code_entity_file_is_fresh($entity, $field_name, $value['value'])) {
    catalyst_include('twig');
    $variables = $entity->variables() + array('entity' => $entity);
    catalyst_twig()->getLoader()->setEntity($entity);
    return catalyst_twig()->render($field_name, $variables);
  }
  catalyst_include('twig');
  // Fallback to field value
  $variables = $entity->variables() + array('entity' => $entity);
  return catalyst_twig_render($value['value'], $variables);
}

function _catalyst_code_entity_upsert_public_file(CatalystEntity $entity, $field_name, $filepath, $public_filepath) {
  $dir = drupal_dirname($public_filepath);
  if (!is_dir($dir)) {
    drupal_mkdir($dir, NULL, TRUE);
  }
  $variables = $entity->variables() + array('entity' => $entity);
  if ($result = catalyst_code_render_entity_twig($entity, $field_name)) {
    _catalyst_code_unlink_public_file($public_filepath);
    file_unmanaged_save_data($result, $public_filepath, FILE_EXISTS_REPLACE);
    return catalyst_code_entity_set_public_file_info($entity, $field_name, $public_filepath);
  }
  catalyst_code_entity_set_public_file_info($entity, $field_name, NULL);
  trigger_error(t('No output created for public file @filepath from @source_filepath (@entity_type:@bundle:@machine).', array(
    '@filepath' => str_replace(DRUPAL_ROOT, '', drupal_realpath($public_filepath)),
    '@source_filepath' => $filepath,
    '@entity_type' => $entity->wrapper()->type(),
    '@bundle' => $entity->wrapper()->getBundle(),
    '@machine' => $entity->machine,
  )));
}

function catalyst_code_entity_file_info(CatalystEntity $entity, $field_name) {
  $code_fields = $entity->getDataValue('code_fields');
  if (isset($code_fields[$field_name])) {
    return $code_fields[$field_name];
  }
  return array();
}

function _catalyst_code_unlink_public_file($public_filepath) {
  $rp = drupal_realpath($public_filepath);
  if ($rp && file_exists($rp)) {
    drupal_unlink($public_filepath);
  }
}

function _catalyst_code_file_hash($filepath, $filename) {
  $value = file_get_contents($filepath);
  if (trim($value)) {
    return _catalyst_code_hash($value, $filename);
  }
}
function _catalyst_code_hash($value, $filename) {
  return trim($value) ? md5(sprintf('%s:%s', $value, $filename)) : NULL;
}

function _catalyst_code_unlink(CatalystEntity $entity, $field_name) {
  if ($file_info = catalyst_code_entity_file_info($entity, $field_name)) {
    unlink($file_info['filepath']);
    if (!empty($file_info['public_filepath'])) {
      drupal_unlink($file_info['public_filepath']);
    }
    $code_fields = $entity->getDataValue('code_fields');
    unset($code_fields[$field_name]);
    $entity->setDataValue('code_fields', $code_fields);
  }
}

function catalyst_code_entity_delete(CatalystEntity $entity) {
  if ($code_fields = $entity->getDataValue('code_fields')) {
    foreach ($code_fields AS $field_name => $file_info) {
      _catalyst_code_unlink($entity, $field_name);
    }
  }
}

function catalyst_code_entity_file_is_fresh(CatalystEntity $entity, $field_name, $value) {
  if ($file_info = catalyst_code_entity_file_info($entity, $field_name)) {
    if (file_exists($file_info['filepath'])) {
      if (filemtime($file_info['filepath']) >= $entity->changed) {
        return $file_info;
      }
    }
  }
  return FALSE;
}

function catalyst_code_entity_public_file_is_fresh(CatalystEntity $entity, $field_name, $value) {
  if ($file_info = catalyst_code_entity_file_info($entity, $field_name)) {
    if (file_exists($file_info['public_filepath'])) {
      return $file_info['public_filepath'];
      $mtime = filemtime($file_info['public_filepath']);
      if ($mtime >= $entity->changed && $mtime >= filemtime($file_info['filepath'])) {
        return $file_info['public_filepath'];
      }
    }
  }
  return FALSE;
}

