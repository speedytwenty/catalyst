<?php

$plugin = array(
  'label' => 'CSSJS: type',
  'get child' => 'catalyst_cssjs_plugin_get_child',
  'get children' => 'catalyst_cssjs_plugin_get_children',
  'entity save' => 'catalyst_cssjs_plugin_entity_save',
  'entity display' => 'catalyst_cssjs_plugin_display_router',
  'default settings' => array(
    'filename_pattern' => '@scope.@extension',
    'filename_pattern_public' => '@entity_type--@bundle--@machine--@scope.@extension',
  ),
);

function catalyst_cssjs_plugin_get_child($plugin, $parent, $child) {
  $children = catalyst_cssjs_plugin_get_children($plugin, $parent);
  return $children[$parent.':'.$child];
}

function catalyst_cssjs_plugin_get_children($plugin, $parent) {
  $types = array(
    'js' => array(
      'name' => 'Javascript',
      'display_callback' => 'catalyst_cssjs_plugin_js_add',
      'groups' => array(
        'custom' => CATALYST_JS_OTHER,
        'page' => CATALYST_JS_PAGE,
        'layout' => CATALYST_JS_LAYOUT,
      ),
    ),
    'css' => array(
      'name' => 'CSS',
      'display_callback' => 'catalyst_cssjs_plugin_css_add',
      'groups' => array(
        'custom' => CATALYST_CSS_OTHER,
        'page' => CATALYST_JS_PAGE,
        'layout' => CATALYST_JS_LAYOUT,
      ),
    ),
  );
  $scopes = array(
    'custom' => t('Custom'),
    'page' => t('Page'),
    'layout' => t('Layout'),
  );
  $plugins = array();
  foreach ($types AS $type => $type_info) {
    foreach ($scopes AS $scope => $scope_title) {
      $plugin['label'] = t('@scope: @name cssjs', array(
        '@scope' => $scope_title,
        '@name' => $type_info['name'],
        '@type' => $type,
      ));
      $plugin['default settings']['scope'] = $scope;
      $plugin['default settings']['group'] = $type_info['groups'][$scope];
      $plugin['default settings']['filename_extension'] = $type;
      $plugin['default settings']['display_callback'] = $type_info['display_callback'];
      if ($scope == 'custom') {
        $plugin['default settings']['field_name'] = sprintf('field__%s', $type);
        $name = sprintf('cssjs:%s', $type);
      }
      else {
        $plugin['default settings']['field_name'] = sprintf('field__%s__%s', $type, $scope);
        $name = sprintf('cssjs:%s__%s', $type, $scope);
      }
      $plugins[$name] = $plugin;
    }
    $key = sprintf('cssjs:%s_body', $type);
    $plugins[$key] = $plugin;
    $plugins[$key]['default settings']['field_name'] = 'field__body';
    $plugins[$key]['default settings']['scope'] = 'custom';
    $plugins[$key]['default settings']['group'] = $type_info['groups']['custom'];
    unset($plugins[$key]['entity display']);
  }
  return $plugins;
}

function catalyst_cssjs_plugin_entity_save($entity_type, $entity, $transaction, $plugin) {
  catalyst_include('code');
  $settings = $plugin['settings'];
  $filename = catalyst_cssjs_plugin_entity_filename($entity_type, $entity, $settings, array(
    '@scope' => $settings['scope'],
  ));
  $public_filename = catalyst_cssjs_plugin_entity_filename($entity_type, $entity, array(
      'filename_pattern' => $settings['filename_pattern_public'],
    ) + $settings,
    array(
      '@scope' => $settings['scope'],
    )
  );
  catalyst_code_upsert_entity_code_file($entity, $settings['field_name'], $filename, $public_filename);
}

function catalyst_cssjs_plugin_display_router($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  $settings = $plugin['settings'];
  $type = $settings['filename_extension'];
  $options = array(
    'group' => $settings['group'],
  );
  catalyst_include('code');
  return catalyst_code_render_entity_cssjs($entity, $settings['field_name'], $type, $options);
}

function catalyst_cssjs_plugin_entity_filename($entity_type, CatalystEntity $entity, $settings, $extra_args = array()) {
  $args = array(
    '@entity_type' => $entity_type,
    '@bundle' => $entity->wrapper()->getBundle(),
    '@id' => $entity->wrapper()->getIdentifier(),
    '@extension' => $settings['filename_extension'],
    '@field_abbreviation' => str_replace(array('field__', 'field_'), '', $settings['field_name']),
    '@field_name' => $settings['field_name'],
    '@machine' => $entity->machine,
  ) + $extra_args;
  return format_string($settings['filename_pattern'], $args);
}
