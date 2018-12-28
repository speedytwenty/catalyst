<?php


function catalyst_registry_build($dirs = NULL) {
  if (!$dirs) {
    $dirs = array(
      'profiles/catalyst',
      'sites/all/modules',
      'sites/all/catalyst',
    );
  }
  $registry = $default_reg = array(
    'block' => array(),
    'doctype' => array(),
    'file' => array(),
    'javascript' => array(),
    'package' => array(),
    'page' => array(),
    'stylesheet' => array(),
    'template' => array(),
  );
  $entities = entity_load('catalyst', FALSE, array(), TRUE);
  foreach ($entities AS $entity) {
    $wrapper = entity_metadata_wrapper('catalyst', $entity);
    $machine = $wrapper->field__machine->machine->value();
    $type = $wrapper->getBundle();
    $registry_entry = (object)array(
      'id' => (int)$wrapper->getIdentifier(),
      'label' => $wrapper->label(),
      'dependencies' => $default_reg,
      'internal' => (bool)$wrapper->field__internal->value(),
      'type' => $wrapper->getBundle(),
      'machine' => $machine,
      'entity' => $entity,
      'wrapper' => $wrapper,
    );
    if ($type == 'package') {
      $package = $machine;
      $data = entity_valval($wrapper->field__data);
    }
    elseif (!empty($wrapper->field__package->value())) {
      $package = $wrapper->field__package->field__machine->machine->value();
      $data = entity_valval($wrapper->field__package->field__data);
      $package_is_exportable = !empty($data['module']);
    }
    else $package = NULL;
    if (isset($data)) {
      foreach (array('module', 'subdir') AS $k) {
        if (!empty($data[$k])) $registry_entry->{$k} = $data[$k];
      }
    }

    if ($package) {
      $registry_entry->package_is_exportable = !empty($data['module']);
      if ($type != 'package') {
        $registry_entry->package = $package;
      }
    }
    if (isset($wrapper->field__menu) && $menu = entity_valval($wrapper->field__menu)) {
      $registry_entry->menu = $menu;
    }
    if (isset($wrapper->field__files) && $files = $wrapper->field__files->value()) {
      $registry_entry->files = array();
      foreach ($files AS $file) {
        //_catalyst_registry_entry_set_timestamp($entry, 'timestamp', $file['timestamp'], 'files');
        $registry_entry->files[] = $file + array('source' => 'files');
      }
    }
    $registry[$type][$machine] = $registry_entry;
  }
  $results = array();
  foreach ($dirs AS $dir) {
    $results = array_merge($results, array_keys(file_scan_directory(DRUPAL_ROOT, '/catalyst\.json/')));
  }
  $results = array_unique($results);
  foreach ($results AS $result) {
    $json = drupal_json_decode(file_get_contents($result), TRUE);
    if (!isset($json['machine'])) continue;
    $type = $json['type'];
    $machine = $json['machine'];
    if (isset($registry[$type][$machine])) {
      $registry_entry = $registry[$type][$machine];
    }
    else {
      $registry_entry = (object)array(
        'label' => $json['label'],
        'type' => $type,
        'machine' => $machine,
        'dependencies' => $default_reg,
      );
    }
    if (!empty($json['package']) && empty($registry_entry->package)) {
      $registry_entry->package = $json['package'];
    }
    elseif ($json['type'] == 'package') {
      foreach (array('module', 'subdir') AS $k) {
        if (!empty($json[$k])) {
          $registry_entry->{$k} = $json[$k];
        }
      }
    }
    $dirpre = dirname($result);
    $files = file_scan_directory($dirpre, '/.*/');
    $assets = array();
    foreach ($files AS $filepath => $file) {
      $fpre = str_replace($dirpre . '/', '', $filepath);
      $assets[$fpre] = (object)array(
        'filepath' => $filepath,
        'filename' => $file->filename,
        'timestamp' => filemtime($filepath),
        'hash' => md5(file_get_contents($filepath)),
      );
    }
    if (empty($registry[$type][$machine]->filepath)) {
      if ($assets) {
        $registry_entry->assets = $assets;
      }
      $registry_entry->filepath = str_replace(DRUPAL_ROOT . '/', '', $result);
      $registry[$type][$machine] = $registry_entry;
    }
    else {
      if (!isset($registry[$type][$machine]->duplicates)) {
        $registry[$type][$machine]->duplicates = array();
      }
      $registry_entry->filepath = $result;
      $registry_entry->wrapper = $registry_entry->entity = NULL;
      unset($registry_entry->wrapper);
      unset($registry_entry->entity);
      unset($registry_entry->id);
      $dup = array('filepath' => $registry_entry->filepath);
      if (!empty($registry_entry->package)) {
        $dup['package'] = $registry_entry->package;
      }
      if ($assets) {
        $dup['assets'] = $assets;
      }
      $registry[$type][$machine]->duplicates[] = $dup;
    }
  }
  $package_info = catalyst_registry_sort_packages($registry);
  foreach ($registry AS $type => &$entries) {
    foreach ($entries AS $machine => &$entry) {
      if (!empty($entry->package)) {
        $p = $entry->package;
        $dep = (object)array('machine' => $p);
        if (!empty($registry['package']) && !empty($registry['package'][$p])) {
          if (!empty($registry['package'][$p]->id)) {
            $dep->id = $registry['package'][$p]->id;
          }
          if (!empty($registry['package'][$p]->filepath)) {
            $dep->filepath = $registry['package'][$p]->filepath;
          }
          if (!empty($registry['package'][$p]->filepath)) {
            $dep->filepath = $registry['package'][$p]->filepath;
          }
        }
        $entry->dependencies['package'][] = $dep;
      }
      if ($type == 'package') {
        $entry->entries = $package_info['packages'][$entry->machine]->entries;
        $entry->total_entries = 0;
        foreach (array_keys($entry->entries) AS $t) {
          $entry->total_entries += count($entry->entries[$t]);
        }
      }
      $entry->dependencies = array_filter($entry->dependencies);
    }
  }
  drupal_alter('catalyst_registry', $registry);
  foreach ($registry AS $type => &$entries) {
    foreach ($entries AS $machine => &$entry) {
      unset($entry->entity);
      unset($entry->wrapper);
    }
  }
  return $registry;
}

function catalyst_registry_entry($type, $machine, $refresh = FALSE) {
  $registry = catalyst_get_registry($refresh);
  return isset($registry[$type][$machine]) ? $registry[$type][$machine] : FALSE;
}

function catalyst_registry_index_entry($id, $refresh = FALSE) {
  $registry = catalyst_registry_list(CATALYST_REGISTRY_LIST_INDEX, $refresh);
  return isset($registry[$id]) ? $registry[$id] : FALSE;
}

function catalyst_registry_package($machine, $refresh = FALSE) {
  $packages = catalyst_registry_list(CATALYST_REGISTRY_LIST_PACKAGES, $refresh);
  return isset($packages[$machine]) ? $packages[$machine] : FALSE;
}

define('CATALYST_REGISTRY_LIST_ALL', 'all');
define('CATALYST_REGISTRY_LIST_ENABLED', 'enabled');
define('CATALYST_REGISTRY_LIST_DISABLED', 'disabled');
define('CATALYST_REGISTRY_LIST_PACKAGES', 'packages');
define('CATALYST_REGISTRY_LIST_PACKAGES_ENABLED', 'packages_enabled');
define('CATALYST_REGISTRY_LIST_ORPHANS', 'orphans');
define('CATALYST_REGISTRY_LIST_ORPHANS_ENABLED', 'orphans_enabled');
define('CATALYST_REGISTRY_LIST_UNEXPORTED', 'unexported');
define('CATALYST_REGISTRY_LIST_INDEX', 'index');

function catalyst_registry_list($type = CATALYST_REGISTRY_LIST_ENABLED, $refresh = FALSE) {
  $lists =& drupal_static(__FUNCTION__);
  if (isset($lists[$type]) && !$refresh) return $lists[$type];
  switch ($type) {
    case CATALYST_REGISTRY_LIST_ALL:
      $lists[$type] = catalyst_get_registry($refresh);
      break;
    case CATALYST_REGISTRY_LIST_ENABLED:
    case CATALYST_REGISTRY_LIST_DISABLED:
      $registry = $enabled = $disabled = catalyst_get_registry($refresh);
      foreach ($registry AS $t => $entries) {
        foreach ($entries AS $machine => $entry) {
          if (empty($entry->id)) {
            unset($enabled[$t][$machine]);
          }
          else {
            unset($disabled[$t][$machine]);
          }
        }
      }
      $lists[CATALYST_REGISTRY_LIST_ENABLED] = array_filter($enabled);
      $lists[CATALYST_REGISTRY_LIST_DISABLED] = array_filter($disabled);
      break;
    case CATALYST_REGISTRY_LIST_PACKAGES:
    case CATALYST_REGISTRY_LIST_ORPHANS:
      $registry = catalyst_get_registry($refresh);
      $result = catalyst_registry_sort_packages($registry);
      $lists[CATALYST_REGISTRY_LIST_PACKAGES] = $result['packages'];
      $lists[CATALYST_REGISTRY_LIST_ORPHANS] = $result['orphans'];
      break;
    case CATALYST_REGISTRY_LIST_PACKAGES_ENABLED:
    case CATALYST_REGISTRY_LIST_ORPHANS_ENABLED:
      $registry = catalyst_registry_list(CATALYST_REGISTRY_LIST_ENABLED, $refresh);
      $result = catalyst_registry_sort_packages($registry);
      $lists[CATALYST_REGISTRY_LIST_PACKAGES_ENABLED] = $result['packages'];
      $lists[CATALYST_REGISTRY_LIST_ORPHANS_ENABLED] = $result['orphans'];
      break;
    case CATALYST_REGISTRY_LIST_UNEXPORTED:
      $registry = catalyst_registry_list(CATALYST_REGISTRY_LIST_ENABLED, $refresh);
      foreach ($registry AS $type => $entries) {
        foreach ($entries AS $machine => $entry) {
          if (!empty($entry->filepath)) {
            unset($registry[$type][$machine]);
          }
        }
      }
      $lists[$type] = $registry;
      break;
    case CATALYST_REGISTRY_LIST_INDEX:
      $index = array();
      $registry = catalyst_registry_list(CATALYST_REGISTRY_LIST_ENABLED, $refresh);
      foreach ($registry AS $t => $entries) {
        foreach ($entries AS $machine => $entry) {
          $index[$entry->id] = array(
            'type' => $t,
            'machine' => $machine,
          )+$entry;
        }
      }
      $lists[$type] = $index;
      break;
  }
  return $lists[$type];
}

function catalyst_registry_list_details($refresh = FALSE, $types = array()) {
  if ($refresh) {
    drupal_static_reset('catalyst_registry_list');
  }
  if (!$types) {
    $types = array(
      CATALYST_REGISTRY_LIST_ENABLED,
      CATALYST_REGISTRY_LIST_DISABLED,
      CATALYST_REGISTRY_LIST_PACKAGES,
      CATALYST_REGISTRY_LIST_PACKAGES_ENABLED,
      CATALYST_REGISTRY_LIST_ORPHANS,
      CATALYST_REGISTRY_LIST_ORPHANS_ENABLED,
      CATALYST_REGISTRY_LIST_UNEXPORTED,
    );
  }
  $return = array();
  foreach ($types AS $type) {
    $return[$type] = catalyst_registry_list($type);
  }
  return $return;
}

function catalyst_registry_entry_packages($re, $type, $machine) {
  if ($type == 'package') return array($machine);
  $packages = array();
  if (!empty($re->package)) $packages[] = $re->package;
  if (!empty($re->duplicates)) {
    foreach ($re->duplicates AS $dup) {
      if (!empty($dup->package)) $packages[] = $dup->package;
    }
  }
  return $packages;
}

function catalyst_registry_sort_packages($registry) {
  $packages = array();
  $orphans = array();
  foreach ($registry AS $type => &$entries) {
    foreach ($entries AS $machine => &$registry_entry) {
      if ($pks = catalyst_registry_entry_packages($registry_entry, $type, $machine)) {
        foreach ($pks AS $pkg) {
          if (!isset($packages[$pkg])) {
            $packages[$pkg] = (object)array('entries' => array());
          }
          if ($type == 'package') {
            $packages[$pkg] = (object)array_merge((array)$registry_entry, (array)$packages[$pkg]);
          }
          else {
            if (!isset($packages[$pkg]->entries[$type])) {
              $packages[$pkg]->entries[$type] = array();
            }
            $packages[$pkg]->entries[$type][$machine] = $registry_entry->machine;
          }
        }
      }
      else {
        if (!isset($orphans[$type])) {
          $orphans[$type] = array();
        }
        $orphans[$type][$machine] = $registry_entry;
      }
    }
  }
  return array('packages' => $packages, 'orphans' => $orphans);
}


/**
 */
function catalyst_get_registry($refresh = FALSE) {
  $registry =& drupal_static(__FUNCTION__);
  $refresh = $refresh || variable_get('catalyst_registry_rebuild', FALSE);
  if (!$registry || $refresh) {
    if (!$refresh && $cached = cache_get('catalyst_registry')) {
      $registry = $cached->data;
    }
    else {
      $registry = catalyst_registry_build();
      cache_set('catalyst_registry', $registry);
      variable_del('catalyst_registry_rebuild');
    }
  }
  return $registry;
}

function catalyst_registry_needs_rebuild() {
  variable_set('catalyst_registry_rebuild', 1);
}
