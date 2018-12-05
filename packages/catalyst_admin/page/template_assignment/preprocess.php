<?php
$entity_info = catalyst_template_entity_info();
if (!module_exists('catalyst_devel')) unset($entity_info['catalyst']);
$variables['entity_types'] = $entity_info;
//$variables['entity_types'] = array('user' => $entity_info['user']);


function catalyst_template_selection_form($form, &$form_state, $entity_type, $bundle = NULL, $view_mode = NULL) {
  $candidates = catalyst_template_candidates($entity_type, $bundle, $view_mode);
  $default = $setting = $parent_default = NULL;
  if ($candidates && $options = catalyst_template_options($entity_type, $bundle, $view_mode, $candidates)) {
    $callargs = array();
    if ($bundle) $callargs[] = array($entity_type);
    if ($view_mode) $callargs[] = array($entity_type, $bundle);
    $parent_defaults = array();
    foreach ($callargs AS $args) {
      if ($parent = call_user_func_array('catalyst_template_default', $args)) {
        $parent_defaults[$parent->machine] = $parent;
      }
    }
    if (isset($form_state['values']['template']) && !empty($form_state['values']['template'])) {
      $default = $candidates[$form_state['values']['template']];
    }
    else {
      $default = catalyst_template_default($entity_type, $bundle, $view_mode, $candidates);
    }
    //array_unshift($options, array('___disabled___' => t('Disabled')));
    $setting = catalyst_template_setting_get($entity_type, $bundle, $view_mode);
    if ($default) {
      $options = array('' => t('Auto: @label', array('@label' => $default->label))) + $options;
      $parent_default = array_key_exists($default->machine, $parent_defaults);
    }
    
    $html_id = drupal_html_id(__FUNCTION__);
    $form['#prefix'] = sprintf('<div id="%s">', $html_id);
    $form['#suffix'] = '</div>';
    $form['#attributes']['class'][] = 'container-inline';
    $form['#entity_type'] = $entity_type;
    $form['#bundle'] = $bundle;
    $form['#view_mode'] = $view_mode;
    $form['template'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $setting ? $setting : '',
      '#ajax' => array(
        'callback' => 'catalyst_template_selection_form_ajax',
        'wrapper' => $html_id,
      ),
    );
  }
  if ($setting || ($default && empty($parent_defaults))) {
    $form['edit_template'] = array(
      '#title' => t('Edit template'),
      '#type' => 'link',
      '#href' => sprintf('admin/catalyst/template/%d/edit', $default->id),
      '#prefix' => '&nbsp;',
      '#options' => array('query' => drupal_get_destination()),
      //'#attributes' => array('target' => '_blank'),
    );
  }
  else {
    $query = array('entity_type' => $entity_type);
    if ($bundle) $query['bundle'] = $bundle;
    if ($view_mode) $query['view_mode'] = $view_mode;
    $form['add_template'] = array(
      '#title' => t('Add template'),
      '#type' => 'link',
      '#href' => 'admin/catalyst/template/add',
      '#options' => array(
        'query' => $query + drupal_get_destination(),
      ),
    );
  }
  return catalyst_form($form, 'page', 'template_assignment');
}
function catalyst_template_selection_form_ajax($form, &$form_state) {
  if (empty($form_state['values']['template'])) {
    catalyst_template_setting_del($form['#entity_type'], $form['#bundle'], $form['#view_mode']);
  }
  else {
    catalyst_template_setting_set($form_state['values']['template'], $form['#entity_type'], $form['#bundle'], $form['#view_mode']);
  }
  return $form;
}
function catalyst_template_selection_reset_form($form, &$form_state, $entity_type = NULL) {
  $form['#entity_type'] = $entity_type;
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => !$entity_type ? t('Reset all to defaults') : t('Reset @entity_type to defaults', array('@entity_type' => $entity_type)),
  );
  return catalyst_form($form, 'page', 'template_assignment');
}
function catalyst_template_selection_reset_form_submit($form, &$form_state) {
  if ($form['#entity_type']) {
    $entity_info = array(entity_get_info($form['#entity_type']));
  }
  else {
    $entity_info = entity_get_info();
  }
  foreach ($entity_info AS $entity_type => $entity_type_info) {
    catalyst_template_setting_del($entity_type);
    foreach (array_keys($entity_type_info['bundles']) AS $bundle) {
      catalyst_template_setting_del($entity_type, $bundle);
      foreach (array_keys($entity_type_info['view modes']) AS $view_mode) {
        catalyst_template_setting_del($entity_type, $bundle, $view_mode);
      }
    }
    drupal_set_message(t('Reset template settings for @entity_type entities.', array('@entity_type' => $entity_type)));
  }
}