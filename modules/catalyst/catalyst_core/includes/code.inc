<?php

/**
 * @file
 * Code file handling and manipulation.
 */

class CatalystCodeFileException extends Exception {}
class CatalystCodeFileMismatchException extends Exception {}
class CatalystCodeFileExistsException extends Exception {}

function catalyst_code_entity_filepath($entity_type, CatalystEntity $entity, $filename = 'catalyst.json') {
  return sprintf('%s/%s', catalyst_code_entity_directory($entity_type, $entity), $filename);
}

function catalyst_code_entity_directory($entity_type, CatalystEntity $entity) {
  if (!empty($entity->filepath)) {
    return dirname($entity->filepath);
  }
  else if (!empty($entity->module)) {
    return catalyst_code_entity_module_directory($entity_type, $entity);
  }
  return sprintf('%s/%s/%s/%s', file_directory_temp(), $entity_type, $entity->type, $entity->machine);
}

function catalyst_code_entity_module_directory($entity_type, CatalystEntity $entity) {
  if (!empty($entity->module)) {
    if (empty($entity->subdir) || $entity->subdir == '.') {
      return sprintf('%s/%s/%s', drupal_get_path('module', $entity->module), $entity->type, $entity->machine);
    }
    return sprintf('%s/%s/%s/%s', drupal_get_path('module', $entity->module), $entity->subdir, $entity->type, $entity->machine);
  }
}

function catalyst_code_entity_public_directory($entity_type, CatalystEntity $entity) {
  if (empty($entity->filepath) && empty($entity->module)) {
    return sprintf('%s://catalyst/%s/%s', file_default_scheme(), $entity->type, $entity->machine);
  }
  else if (!empty($entity->module)) {
    return catalyst_code_entity_module_directory($entity_type, $entity);
  }
  return catalyst_code_entity_tempory_directory($entity_type, $entity);
}

function catalyst_code_entity_public_filepath($entity_type, $entity, $filename) {
  $dir = catalyst_code_entity_public_directory($entity_type, $entity);
  return sprintf('%s/%s',  $dir, $filename);
}

function catalyst_code_entity_temporary_directory($entity_type, $entity) {
  return sprintf('%s/%s/%s/%s', file_directory_temp(), $entity_type, $entity->type, $entity->machine);
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

function catalyst_code_upsert_entity_code_file($entity_type, CatalystEntity $entity, $field_info, $filename, $public_filename = NULL) {
  if (is_string($field_info)) {
    // Allow passing a field name in place of field instance info
    $fn = $field_info;
    if (!$field_info = field_info_instance($entity_type, $fn, $entity->wrapper()->getBundle())) {
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

  $dest_filepath = catalyst_code_entity_filepath($entity_type, $entity, $filename);
  $dest_exists = file_exists($dest_filepath);
  $dest_hash = $dest_exists ? _catalyst_code_hash(file_get_contents($dest_filepath), $filename) : NULL;
  $dest_public_filepath = $public_filename ? catalyst_code_entity_public_filepath($entity_type, $entity, $public_filename) : NULL;
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

  if (isset($entity->original) && $original = catalyst_code_entity_file_info($entity->original, $filename)) {
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
          if ($public_realpath = _catalyst_code_entity_upsert_public_file($entity_type, $entity, $filename, $dest_filepath, $dest_public_filepath)) {
            $file_info['public_filepath'] = $dest_public_filepath;
            catalyst_code_entity_set_file_info($entity, $filename, $file_info);
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
        //catalyst_code_unlink($original['filepath'], $original['hash']);
        unlink($original['filepath']);
        if ($public_filename && !empty($original['public_filepath'])) {
          _catalyst_code_unlink_public_file($original['public_filepath']);
        }
      }
    }
  }


  _catalyst_code_unlink($entity, $filename);
  if (empty($value)) return;

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

  if ($public_filename && _catalyst_code_entity_upsert_public_file($entity_type, $entity, $filename, $dest_filepath, $dest_public_filepath)) {
    $file_info['public_filepath'] = $dest_public_filepath;
  }

  catalyst_code_entity_set_file_info($entity, $filename, $file_info);

  return $file_info;
}

function catalyst_code_entity_set_file_info(CatalystEntity $entity, $filename, $file_info) {
  $code_files = $entity->getDataValue('code_files');
  $code_files[$filename] = $file_info;
  $entity->setDataValue('code_files', $code_files);
}

function _catalyst_code_entity_upsert_public_file($entity_type, CatalystEntity $entity, $filename, $filepath, $public_filepath) {
  _catalyst_code_unlink_public_file($public_filepath);
  $dir = drupal_dirname($public_filepath);
  if (!is_dir($dir)) {
    drupal_mkdir($dir, NULL, TRUE);
  }
  catalyst_include('twig');
  $variables = $entity->variables() + array('entity' => $entity);
  //if ($result = catalyst_twig_render_template($filepath, $variables)) {
  if ($result = catalyst_twig_render_entity_file($entity_type, $entity, $filename)) {
    file_unmanaged_save_data($result, $public_filepath, FILE_EXISTS_REPLACE);
    $rp = drupal_realpath($public_filepath);
    return $rp && file_exists($rp);
  }
  trigger_error(t('No output created for public file @filepath from @source_filepath (@entity_type:@bundle:@machine).', array(
    '@filepath' => str_replace(DRUPAL_ROOT, '', drupal_realpath($public_filepath)),
    '@source_filepath' => $filepath,
    '@entity_type' => $entity_type,
    '@bundle' => $entity->wrapper()->getBundle(),
    '@machine' => $entity->machine,
  )));
}

function catalyst_code_entity_file_info(CatalystEntity $entity, $filename, $create = FALSE) {
  $code_files = $entity->getDataValue('code_files');
  if (isset($code_files[$filename])) {
    return $code_files[$filename];
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

function catalyst_code_entity_fields($entity_type, $bundle, $format = NULL) {
  static $cache = array();
  if (!isset($cache[$entity_type])) $cache[$entity_type] = array();
  if (!isset($cache[$entity_type][$bundle])) {
    $cache[$entity_type][$bundle] = array();
    $instances = field_info_instances($entity_type, $bundle);
    foreach ($instances AS $instance) {
      if (!empty($instance['settings']['allowed_formats'])) {
        $formats = array_filter($instance['settings']['allowed_formats']);
        $format = array_shift($format);
        if (in_array($format, array_keys(catalyst_code_field_formats()))) {
          $field_name = $instance['field__name'];
          $cache[$entity_type][$bundle][$field_name] = $format;
        }
      }
    }
  }
  if ($format) {
    if (in_array($cache[$entity_type][$bundle])) {
      $field_name = array_search($format, $cache[$entity_type][$bundle]);
      return $cache[$entity_type][$bundle][$field_name];
    }
    return array();
  }
  return $cache[$entity_type][$bundle];
}

function _catalyst_code_unlink($entity, $filename) {
  if ($code_files = $entity->getDataValue('code_files')) {
    unset($code_files[$filename]);
    $entity->setDataValue('code_files', $code_files);
  }
}

