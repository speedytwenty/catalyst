<?php

/**
 * @file
 * @see catalyst_core_form_alter()
 */

function catalyst_package_form_alter(&$form, &$form_state) {
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $wrapper = entity_metadata_wrapper($entity_type, $form_state[$entity_type]);
  $language = $form['field__data']['#language'];
  $field_instance = field_info_instance($entity_type, 'field__data', $bundle);
  if (isset($form_state['values']['field__data'][$language][0]['value'])) {
    $data = $form_state['values']['field__data'][$language][0]['value'];
  }
  else {
    $data = entity_valval($wrapper->field__data);
  }

  //$form['#submit'][] = 'catalyst_package_form_submit';
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
  $form['field__data'][$language][0]['value'] = $widget;
}

function catalyst_package_form_submit($form, &$form_state) {
  dsm($form);
  dsm($form_state);
  die;
}
