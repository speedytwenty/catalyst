<?php
function catalyst_template_list_form($form, &$form_state) {
  $values = empty($form_state['values']['filters']) ? array() : $form_state['values']['filters'];
  $values += array(
    'title' => empty($_REQUEST['title']) ? NULL : $_REQUEST['title'],
    'machine' => empty($_REQUEST['machine']) ? NULL : $_REQUEST['machine'],
    'entity_type' => empty($_REQUEST['entity_type']) ? NULL : $_REQUEST['entity_type'],
    'bundle' => empty($_REQUEST['bundle']) ? NULL : $_REQUEST['bundle'],
    'view_mode' => empty($_REQUEST['view_mode']) ? NULL : $_REQUEST['view_mode'],
    'internal' => isset($_REQUEST['internal']) ? $_REQUEST['internal'] : '',
  );
  $html_id = drupal_html_id(__FUNCTION__);
  $form['#prefix'] = sprintf('<div id="%s">', $html_id);
  $form['#suffix'] = '</div>';
  $ajax = array(
    'callback' => 'catalyst_template_list_form_ajax',
    'wrapper' => $html_id,
  );
  $form['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
    '#tree' => TRUE,
  );
  $form['filters']['title'] = array(
    '#title' => t('Label:'),
    '#type' => 'textfield',
    '#default_value' => $values['title'],
    '#size' => 12,
    '#ajax' => $ajax,
  );
  $form['filters']['machine'] = array(
    '#title' => t('Machine:'),
    '#type' => 'textfield',
    '#default_value' => $values['machine'],
    '#size' => 12,
    '#ajax' => $ajax,
  );
  $form['filters']['entity_type'] = array(
    '#type' => 'select',
    '#title' => t('Entity type:'),
    '#options' => array('' => t('-- any --')) + catalyst_template_entity_type_options(),
    '#default_value' => $values['entity_type'],
    '#ajax' => $ajax,
  );
  if (!empty($values['entity_type'])) {
    $form['filters']['bundle'] = array(
      '#type' => 'select',
      '#title' => t('Bundle'),
      '#options' => array('' => t('- any -')) + catalyst_template_bundle_options($values['entity_type']),
      '#default_value' => $values['bundle'],
      '#ajax' => $ajax,
    );
    $form['filters']['view_mode'] = array(
      '#type' => 'select',
      '#title' => t('View mode'),
      '#options' => array('' => t('- any -')) + catalyst_template_view_mode_options($values['entity_type']),
      '#default_value' => $values['view_mode'],
      '#ajax' => $ajax,
    );
    $form['filters']['internal'] = array(
      '#title' => t('Realm'),
      '#type' => 'select',
      '#options' => array(
        '' => t('- any -'),
        0 => t('Site'),
        1 => t('System'),
      ),
      '#default_value' => $values['internal'],
      '#ajax' => $ajax,
    );
  }
  $form['list'] = array(
    '#theme' => 'table',
    '#header' => array(t('All'), t('ID'), t('Label'), t('Entity type'), t('Bundles'), t('View modes'), t('Modified'), t('Actions')),
    '#rows' => array(),
  );
  $templates = catalyst_template_query($values);
  foreach ($templates AS $template) {
    $actions = 'edit';
    $checkbox = array(
      '#type' => 'checkbox',
      '#name' => sprintf('ids[%d]', $template->id),
      '#return_value' => $template->id,
    );
    $text = t('@label (@machine)', array(
      '@label' => $template->label,
      '@machine' => $template->machine,
    ));
    dsm(entity_uri('catalyst', $template->entity));
    $uri = entity_uri('catalyst', $template->entity);
    $form['list']['#rows'][] = array(
      $checkbox,
      $template->id,
      l($text, $uri['path']),
      $template->template['entity_type'],
      empty($template->template['bundles']) ? '-' : implode(', ', $template->template['bundles']),
      empty($template->template['view_modes']) ? '-' : implode(', ', $template->template['view_modes']),
      date(DATE_RFC2822, $template->wrapper->changed->value()),
      $actions
    );
  }
  $form['pager'] = array('#theme' => 'pager');
  return catalyst_form($form, 'page', 'catalyst_admin_template_list');
}

function catalyst_template_query($values = array(), $options = array()) {
  $options += array(
    'limit' => 2,
  );
  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'catalyst')
    ->entityCondition('bundle', 'template');
  if ($values['title']) {
    $query->propertyCondition('title', '%'.db_like($values['title']).'%', 'like');
  }
  if ($values['machine']) {
    $query->propertyCondition('title', '%'.db_like($values['machine']).'%', 'like');
  }
  if ($values['entity_type']) {
    $like = '%{s:11:\"entity_type\";s:'.strlen($values['entity_type']).':\"'.$values['entity_type'].'\";%';
    $query->fieldCondition('field__data', 'value_serialized', $like, 'like');
    if ($values['bundle']) {
      $like = '%s:7:\"bundles\";a:%s:'.strlen($values['bundle']).':\"'.$values['bundle'].'\";%';
      $query->fieldCondition('field__data', 'value_serialized', $like, 'like');
    }
    if ($values['view_mode']) {
      $like = '%s:10:\"view_modes\";a:%s:'.strlen($values['view_mode']).':\"'.$values['view_mode'].'\";%';
      $query->fieldCondition('field__data', 'value_serialized', $like, 'like');
    }
    if ($values['internal'] != '') {
      $query->fieldCondition('field__internal', 'value', (int)$values['internal'], '=');
    }
  }
  
  $query->pager($options['limit']);
  $result = $query->execute();
  if (!empty($result['catalyst'])) {
    return catalyst_load('template', array_keys($result['catalyst']));
  }
}
function catalyst_template_list_form_ajax($form, &$form_state) {
  return $form;
}