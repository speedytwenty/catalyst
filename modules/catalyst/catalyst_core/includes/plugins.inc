<?php


function catalyst_get_plugins($type = 'plugin', $name = null) {
  ctools_include('plugins');
  return ctools_get_plugins('catalyst', $type, $name);
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
  return catalyst_invoke(array(catalyst_get_bundles(), catalyst_get_plugins()), $hook, $args);
}

function catalyst_invoke(array $nested_plugins, $hook, array $args = array()) {
  $result = array();
  foreach ($nested_plugins AS $plugins) {
    $result = array_merge_recursive($result, catalyst_plugins_invoke($plugins, $hook, $args));
  }
  return $result;
}
