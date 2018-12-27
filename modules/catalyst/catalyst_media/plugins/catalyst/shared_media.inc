<?php

/**
 * @file
 * Catalyst media shared JS and CSS.
 */

$plugin = array(
  'label' => 'Shared Media: type',
  'description' => 'Provides output handling for entities referencing media.',
  'get children' => 'catalyst_shared_media_get_children',
  'get child' => 'catalyst_shared_media_get_child',
  'prepare display' => 'catalyst_shared_media_prepare_display',
  'default settings' => array(
    'field_name' => 'field__media_stylesheets',
    'source_field_name' => 'field__body',
    'function' => 'drupal_add_css',
    'scope' => 'custom',
    'group' => CATALYST_CSS_OTHER,
    'weight' => 0,
  ),
);

function catalyst_shared_media_get_child($plugin, $parent, $child) {
  $children = catalyst_shared_media_get_children($plugin, $parent);
  return $children[$parent.':'.$child];
}


function catalyst_shared_media_get_children($plugin, $parent) {
  $plugins = array('shared_media:css' => $plugin);
  $plugin['label'] = t('Shared Media: @type', array('@type' => 'Stylesheets'));
  $scopes = array('page' => CATALYST_CSS_PAGE, 'layout' => CATALYST_CSS_LAYOUT);
  foreach ($scopes AS $scope => $group) {
    $plugin['default settings']['field_name'] = sprintf('field__media_stylesheets__%s', $scope);
    $plugin['default settings']['group'] = $group;
    $plugin['default settings']['scope'] = $scope;
    $plugin['label'] = t('Shared Media: @scope Stylesheet', array('@scope' => ucfirst($plugin['default settings']['scope'])));
    $plugins['shared_media:css__'.$scope] = $plugin;
  }
  $plugin['default settings']['field_name'] = 'field__media_javascripts';
  $plugin['default settings']['group'] = CATALYST_JS_OTHER;
  $plugin['default settings']['scope'] = 'custom';
  $plugin['default settings']['function'] = 'drupal_add_js';
  $plugin['label'] = t('Shared Media: @type', array('@type' => 'Javascripts'));
  $plugins['shared_media:js'] = $plugin;
  $scopes = array('page' => CATALYST_JS_PAGE, 'layout' => CATALYST_JS_LAYOUT);
  foreach ($scopes AS $scope => $group) {
    $plugin['default settings']['field_name'] = sprintf('field__media_javascripts__%s', $scope);
    $plugin['default settings']['group'] = $group;
    $plugin['default settings']['scope'] = $scope;
    $plugin['label'] = t('Shared Media: @scope Stylesheet', array('@scope' => ucfirst($plugin['default settings']['scope'])));
    $plugins['shared_media:js__'.$scope] = $plugin;
  }
  return $plugins;
}

function catalyst_shared_media_prepare_display($entity_type, CatalystEntity $entity, $page = NULL, $plugin) {
  $settings = $plugin['settings'];
  if (!empty($entity->{$settings['field_name']})) {
    catalyst_include('code');
    foreach ($entity->wrapper()->{$settings['field_name']}->value() AS $media) {
      $media->setVariable('group', $settings['group']);
      $media->display(TRUE);
    }
  }
}
