<?php

/**
 * @file
 * Catalyst Package Bundle plugin.
 */

/**
 * This plugin defintion gets directly inserted into catalyst's entity type
 * bundle information.
 *
 * Eg.
 * @code
 * $entity_info['catalyst']['bundles'][$plugin_name] = $my_plugin_definition;
 * @endcode
 *
 * @see catalyst_core_entity_info_alter().
 */
$plugin = array(
  'label' => 'Package',
  'description' => 'Provides handling for the package bundle.',
  'entity form alter' => 'catalyst_package_form_alter',
);

function catalyst_package_form_alter(&$form, &$form_state) {
  $wrapper = $form['#entity']->wrapper();
  $field_instance = field_info_instance($wrapper->type(), 'field__data', $wrapper->getBundle());
  if (isset($form_state['values']['field__data'][LANGUAGE_NONE][0]['value'])) {
    $data = $form_state['values']['field__data'][LANGUAGE_NONE][0]['value'];
  }
  else {
    $data = entity_valval($wrapper->field__data);
  }
  $widget = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#attributes' => array('class' => array('container-inline')),
  );
  $widget['module'] = array(
    '#type' => 'select',
    '#title' => t('Module'),
    '#options' => array('' => '') + module_list(),
    '#default_value' => $data['module'],
    '#disabled' => !empty($data['module']),
  );
  $widget['subdir'] = array(
    '#type' => 'textfield',
    '#title' => t('Subdir'),
    '#default_value' => $data['subdir'],
    '#disabled' => !empty($data['module']),
    '#width' => 30,
  );
  $form['field__data'][LANGUAGE_NONE][0]['value'] = $widget;
}
