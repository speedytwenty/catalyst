<?php

/**
 * @file
 * Add "Save & Edit" buttons to catalyst entity and node forms.
 *
 * Currently this applies to all eck entity and node forms but it should
 * detect catalyst verses custom entities and allow being disabled for
 * non-catalyst forms.
 *
 * This is closely modeled after the save_edit module which only supports
 * nodes.
 *
 * @see catalyst_admin_form_eck__entity__form_alter().
 * @see catalyst_admin_form_node_form_alter().
 */

/**
 * Add a Save & Edit button to a form's actions.
 */
function catalyst_admin_save_edit_form_alter(&$form, &$form_state) {
  // Depend on the base form id and actions element
  if (!isset($form_state['build_info']['base_form_id']) || !isset($form['actions'])) {
    return;
  }
  if ($form_state['build_info']['base_form_id'] == 'eck__entity__form') {
    array_unshift($form['#submit'], 'catalyst_admin_save_edit_submit');
    $form['actions']['save_edit'] = array(
      '#weight' => 99999,
      '#type' => 'checkbox',
      '#title' => t('Continue editing'),
      '#default_value' => variable_get('catalyst_save_edit', 1),
    );
  }
}

/**
 * Save & Edit submit handler.
 */
function catalyst_admin_save_edit_submit($form, &$form_state) {
  if ($form_state['values']['save_edit']) {
    if ($redirect = catalyst_admin_save_edit_redirect($form, $form_state)) {
      if (isset($_REQUEST['destination'])) {
        $form_state['redirect'] = url($redirect, array(
          'query' => array(
            'destination' => $_REQUEST['destination'],
          ),
          'absolute' => TRUE,
        ));
        $_GET['destination'] = $form_state['redirect'];
        unset($_REQUEST['destination']);
      }
      else {
        // just go back to the form edit page, and dont worry about the redirect
        $form_state['redirect'] = $redirect;
      }
    }
  }
}

/**
 * Save & Edit redirect handler for eck entities.
 */
function catalyst_admin_save_edit_redirect($form, $form_state) {
  if (isset($form['#entity_type'], $form['#entity']->type, $form['#entity']->id)) {
    $crud_info = get_bundle_crud_info($form['#entity_type'], $form['#entity']->type);
    return str_replace('%eckentity', $form['#entity']->id, $crud_info['edit']['path']);
  }
}
