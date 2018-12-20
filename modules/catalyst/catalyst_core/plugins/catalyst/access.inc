<?php

$plugin = array(
  'label' => 'Access control',
  'description' => 'Controls access to viewing a component (in action).',
  'field info' => 'catalyst_access_field_info',
  'field bases' => 'catalyst_access_field_bases',
  'field instance' => 'catalyst_access_field_instance',
  'entity create' => 'catalyst_access_entity_create',
  'entity insert' => 'catalyst_access_entity_save',
  'entity update' => 'catalyst_access_entity_save',
  'entity delete' => 'catalyst_access_entity_delete',
  'entity export' => 'catalyst_access_entity_export',
  'entity archive' => 'catalyst_access_entity_archive',
  'entity form' => 'catalyst_access_entity_form',
  'entity build' => 'catalyst_access_entity_build',
);

function catalyst_access_entity_has_access($entity_type, $entity) {
  $store = &drupal_static(__FUNCTION__, array());
  if (!isset($store[$entity_type])) $store[$entity_type] = array();
  $bundle = $entity->wrapper()->getBundle();
  if (!isset($store[$entity_type][$bundle])) {
    $store[$entity_type][$bundle] = FALSE;
  }
  return $store[$entity_type][$bundle];
}

function catalyst_access_entity_build(&$build) {
}

function catalyst_access_entity_form(&$form, &$form_state) {
  form_load_include($form_state, 'inc', 'catalyst', 'plugins/catalyst/access');
  $plugins = array_filter(ctools_get_plugins('ctools', 'access'), function ($v) {
    return empty($v['required context']);
  });
  $html_id = drupal_html_id('catalyst_entity_access_form');
  if (!empty($form_state['values'])) {
    $values = $form_state['values']['access'];
  }
  else {
    $data = (array)$form['#entity']->wrapper()->field__data->value();
    $data += array('access' => array());

    $values = $data['access'] + array(
      'settings' => array(),
      'plugin' => 'php',
    );
  }
  $form['access'] = array(
    '#type' => 'fieldset',
    '#prefix' => sprintf('<div id="%s">', $html_id),
    '#suffix' => '</div>',
    '#title' => t('Access settings'),
    '#tree' => TRUE,
  );
  $options = array();
  foreach ($plugins AS $key => $plugin) {
    $options[$key] = $plugin['title'];
  }
  $form['access']['plugin'] = array(
    '#type' => 'select',
    '#title' => t('Handler'),
    '#options' => $options,
    '#default_value' => $values['plugin'],
    '#ajax' => array(
      'wrapper' => $html_id,
      'callback' => 'catalyst_access_entity_form_ajax',
    ),
  );
  if (!empty($values['plugin'])) {
    $plugin = $plugins[$values['plugin']];
    if (!empty($plugin['default'])) {
      $values['settings'] += $plugin['default'];
    }
    if ($form_func = ctools_plugin_get_function($plugin, 'settings form')) {
      $form['access'] = $form_func($form['access'], $form_state, $values['settings']);
    }
  }
  array_unshift($form['#validate'], 'catalyst_access_entity_form_validate');
  return $form;
}

function catalyst_access_entity_form_validate(&$form, &$form_state) {
  $form_state['values']['field__data'][LANGUAGE_NONE][0]['access'] = $form_state['values']['access'];
}

function catalyst_access_entity_form_ajax($form, &$form_state) {
  return $form['access'];
}

function catalyst_access_field_bases() {
  return array(
    'field__access' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array('catalyst'),
      'indexes' => array('format' => array('format')),
      'locked' => 1,
      'module' => 'catalyst',
    ),
  );
}

function catalyst_access_field_instance() {
}
