<?php


function catalyst_get_plugins($type = 'plugin', $name = null) {
  ctools_include('plugins');
  return ctools_get_plugins('catalyst_core', $type, $name);
}

function catalyst_plugins_invoke_all($hook) {
  $args = func_get_args();
  unset($args[0]);
  return catalyst_plugins_invoke(catalyst_get_plugins(), $hook, $args);
}

function catalyst_plugins_invoke(array $plugins, $hook, array $args = array()) {
  $return = array();
  foreach ($plugins AS $plugin) {
    if ($function = ctools_plugin_get_function($plugin, $hook)) {
      $result = call_user_func_array($function, $args);
      if (isset($result) && is_array($result)) {
        $return = array_merge_recursive($return, $result);
      }
      elseif (isset($result)) {
        $return[] = $result;
      }
    }
  }
  return $return;
}

function catalyst_plugins_invoke_alter_all($hook, &$data, &$context1 = NULL, &$context2 = NULL, &$context3 = NULL) {
  return catalyst_plugins_invoke_alter(catalyst_get_plugins(), $data, $context1, $context2, $context3);
}

function catalyst_plugins_invoke_alter(array $plugins, $hook, &$data, &$context1 = NULL, &$context2 = NULL, &$context3 = NULL) {
  foreach ($plugins AS $plugin) {
    if ($function = ctools_plugin_get_function($plugin, $hook)) {
      $function($data, $context1, $context2, $context3);
    }
  }
}

function catalyst_invoke_all($hook) {
  catalyst_include('bundles');
  $args = func_get_args();
  unset($args[0]);
  return catalyst_invoke(array(catalyst_get_plugins('bundle'), catalyst_get_plugins()), $hook, $args);
}

function catalyst_invoke(array $nested_plugins, $hook, array $args = array()) {
  $result = array();
  foreach ($nested_plugins AS $plugins) {
    $result = array_merge_recursive($result, catalyst_plugins_invoke($plugins, $hook, $args));
  }
  return $result;
}

function catalyst_invoke_alter(array $nested_plugins, $hook, &$data, &$context1 = NULL, &$context2 = NUUl, $context3 = NULL) {
  foreach ($nested_plugins AS $plugins) {
    catalyst_plugins_invoke($plugins, $hook, $data, $context1, $context2, $context3);
  }
}

/**
 * @param $mixed
 *   Either a plugin name or an array of plugin names.
 * @param $plugin_type
 *   The type of (catalyst) plugin. Defaults to "plugin".
 */
function catalyst_plugins_require($mixed, $plugin_type = 'plugin') {
  $plugin_names = (array)$mixed;
  $result = array();
  foreach ($plugin_names AS $plugin_name) {
    if (empty($plugin_name)) continue; // Prevent fetching all
    if ($plugin = catalyst_get_plugins($plugin_name, $plugin_type)) {
      $result[$plugin_name] = $plugin;
    }
  }
  return $result;
}

function catalyst_process_bundle_plugin(&$plugin, $info) {
  if (!empty($plugin['plugins'])) {
    $processed_plugins = array();
    foreach ($plugin['plugins'] AS $plugin_name => $settings) {
       if (is_int($plugin_name)) {
         $plugin_name = $settings;
         $settings = array();
      }
      $child_plugin = catalyst_get_plugins('plugin', $plugin_name);
      if (!empty($child_plugin['settings'])) {
        $settings += $child_plugin['settings'];
      }
      if (!empty($child_plugin['default settings'])) {
        $settings += $child_plugin['default settings'];
      }
      $child_plugin['settings'] = $settings;
      $processed_plugins[$plugin_name] = $child_plugin;
    }
    $plugin['plugins'] = $processed_plugins;
  }
  else $plugin['plugins'] = array();
  return;
  if (empty($plugin['settings'])) {
    $plugin['settings'] = array();
    if (!empty($plugin['default settings'])) {
      $plugin['settings'] = $plugin['default settings'];
    }
  }
  $plugin['settings'] = $settings;
}
