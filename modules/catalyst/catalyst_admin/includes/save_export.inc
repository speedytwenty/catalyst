<?php

/**
 * @file
 * Add "Save & Edit" buttons to catalyst entity and node forms.
 *
 * Currently this applies to all eck entity and node forms but it should
 * detect catalyst verses custom entities and allow being disabled for
 * non-catalyst forms.
 *
 * This is closely modeled after the save_export module which only supports
 * nodes.
 *
 * @see catalyst_admin_form_eck__entity__form_alter().
 * @see catalyst_admin_form_node_form_alter().
 */

/**
 * Add a Save & Edit button to a form's actions.
 */
function catalyst_admin_save_export_form_alter(&$form, &$form_state) {
  // Depend on eck base form id and actions element
  if (!isset($form_state['build_info']['base_form_id'])
  || $form_state['build_info']['base_form_id'] != 'eck__entity__form'
  || !isset($form_state['catalyst'])
  || !isset($form['actions'])) {
    return;
  }
  $wrapper = entity_metadata_wrapper('catalyst', $form_state['catalyst']);
  if ($wrapper->getBundle() == 'package') {
    $package = $wrapper;
  }
  else {
    if (!$wrapper->field__package->value()) return;
    $package = $wrapper->field__package;
  }
  $data = entity_valval($package->field__data);
  if (empty($data['module'])) return;
  $form_state['save_export'] = array(
    'module' => $data['module'],
    'subdir' => !empty($data['subdir']) ? $data['subdir'] : '.',
  );
  $export_path = drupal_get_path('module', $data['module']) . '/' . $data['subdir'] . '/' . $wrapper->getBundle() . '/' . $wrapper->field__machine->machine->value();
  $form['actions']['save_export'] = array(
    '#weight' => 10000,
    '#type' => 'checkbox',
    '#title' => t('Export after save.'),
    '#default_value' => variable_get('catalyst_save_export', FALSE),
    '#description' => drupal_realpath($export_path),
  );
  $form['#submit'][] = 'catalyst_admin_save_export_submit';
}

/**
 * Save & export submit handler
 */
function catalyst_admin_save_export_submit($form, &$form_state) {
  if ($form_state['values']['save_export']) {
    catalyst_include('export');
    $entry = catalyst_load_single($form_state['catalyst']->id);
    $archive_path = catalyst_export_entities(array($entry->entity));
    $export_path = drupal_get_path('module', $form_state['save_export']['module']) . '/' . $form_state['save_export']['subdir'];
    $archive = new ZipArchive;
    if ($archive->open($archive_path)) {
      $archive->extractTo($export_path);
      $archive->close();
    }
    unlink($archive_path);
    drupal_set_message(t('Exported %source_label (@type:@machine )to %path', array(
      '@type' => $entry->type,
      '@machine' => $entry->machine,
      '%source_label' => $entry->wrapper->getLabel(),
      '%path' => $export_path,
    )));
  }
}
