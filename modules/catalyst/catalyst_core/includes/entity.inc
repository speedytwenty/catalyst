<?php

/**
 * @file
 * Catalyst entity specific functions.
 */

function catalyst_ensure_file_exists($filepath, $contents) {
  if (!file_exists($filepath)) {
    drupal_mkdir(dirname($filepath), NULL, TRUE);
    file_unmanaged_save_data($contents, $filepath, FILE_EXISTS_REPLACE);
  }
}

function catalyst_entity_get_filepath($entity_type, $entity, $filename = 'catalyst.json') {
  return sprintf('%s/%s', catalyst_entity_get_directory($entity_type, $entity), $filename);
}

function catalyst_entity_get_directory($entity_type, $entity) {
  if ($entry = catalyst_registry_entry($entity->type, $entity->machine)) {
    if (!empty($entry->filepath)) {
      return dirname($entry->filepath);
    }
    else if (!empty($entry->module)) {
      return catalyst_entry_get_module_directory($entry, $entity_type, $entity);
    }
  }
  return sprintf('%s/%s/%s/%s', file_directory_temp(), $entity_type, $entity->type, $entity->machine);
}

function catalyst_entity_twig_template_filepath($entity_type, $entity) {
  switch ($entity->type) {
    case 'javascript': $ext = 'js'; break;
    case 'stylesheet': $ext = 'js'; break;
    default: $ext = 'html'; break;
  }
  return catalyst_entity_get_filepath($entity_type, $entity, sprintf('body.%s', $ext));
}

function catalyst_entry_get_module_directory($entry, $entity_type, $entity) {
  if (!empty($entry->module)) {
    if (empty($entry->subdir) || $entry->subdir == '.') {
      return sprintf('%s/%s/%s', drupal_get_path('module', $entry->module), $entity->type, $entity->machine);
    }
    return sprintf('%s/%s/%s/%s', drupal_get_path('module', $entry->module), $entry->subdir, $entity->type, $entity->machine);
  }
}

function catalyst_entity_get_public_directory($entity_type, $entity) {
  if ($entry = catalyst_registry_entry($entity->type, $entity->machine)) {
    if (empty($entry->filepath) && empty($entry->module)) {
      return sprintf('public://catalyst/%s/%s', $entity->type, $entity->machine);
    }
    else if (!empty($entry->module)) {
      return catalyst_entry_get_module_directory($entry, $entity_type, $entity);
    }
  }
  return catalyst_entity_get_tempory_directory($entity_type, $entity);
}

function catalyst_entity_get_public_filepath($entity_type, $entity, $filename) {
  $dir = catalyst_entity_get_public_directory($entity_type, $entity);
  return sprintf('%s/%s',  $dir, $filename);
}

function catalyst_entity_get_temporary_directory($entity_type, $entity) {
  return sprintf('%s/%s/%s/%s', file_directory_temp(), $entity_type, $entity->type, $entity->machine);
}

function _catalyst_entity_directory_is_public($dir) {
  if ($dir = realpath($dir)) {
    $docroot = realpath(DRUPAL_ROOT);
    return $dir != $docroot && $dir != str_replace($docroot, '', $dir);
  }
  return FALSE;
}
