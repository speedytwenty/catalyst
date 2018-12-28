<?php
function catalyst_template_list_form($form, &$form_state) {
  $values = empty($form_state['values']['filters']) ? array() : $form_state['values']['filters'];
  $values += array(
    'title' => empty($_REQUEST['title']) ? NULL : $_REQUEST['title'],
    'machine' => empty($_REQUEST['title']) ? NULL : $_REQUEST['machine'],
    'package' => empty($_REQUEST['package']) ? NULL : $_REQUEST['package'],
    'entity_type' => empty($_REQUEST['entity_type']) ? NULL : $_REQUEST['entity_type'],
    'bundle' => empty($_REQUEST['bundle']) ? NULL : $_REQUEST['bundle'],
    'view_mode' => empty($_REQUEST['view_mode']) ? NULL : $_REQUEST['view_mode'],
    'realm' => isset($_REQUEST['realm']) ? $_REQUEST['realm'] : NULL,
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
      '#title' => t('Bundle:'),
      '#options' => array('' => t('- any -')) + catalyst_template_bundle_options($values['entity_type']),
      '#default_value' => $values['bundle'],
      '#ajax' => $ajax,
    );
    $form['filters']['view_mode'] = array(
      '#type' => 'select',
      '#title' => t('View mode:'),
      '#options' => array('' => t('- any -')) + catalyst_template_view_mode_options($values['entity_type']),
      '#default_value' => $values['view_mode'],
      '#ajax' => $ajax,
    );
  }
  $package_options = array();
  if ($packages = catalyst_load('package')) {
    foreach ($packages AS $package) {
      if (!empty($package->entries['template'])) {
        $package_options[$package->machine] = filter_xss_admin($package->label);
      }
    }
    if (!empty($package_options)) {
      $form['filters']['package'] = array(
        '#type' => 'select',
        '#title' => t('Package:'),
        '#options' => array('' => t('- any -')) + $package_options,
        '#default_value' => $values['package'],
        '#ajax' => $ajax,
      );
    }
  }
  $form['filters']['realm'] = array(
    '#title' => t('Realm'),
    '#type' => 'select',
    '#options' => array(
      '' => t('- any -'),
      'site' => t('Site'),
      'system' => t('System'),
    ),
    '#default_value' => $values['realm'],
    '#ajax' => $ajax,
  );
  if ($query = array_filter($values)) {
    $form['filters']['deep_link'] = array(
      '#type' => 'link',
      '#title' => t('Deeplink »'),
      '#href' => 'admin/catalyst/template/list',
      '#options' => array('query' => $query),
    );
  }
  $form['filters']['reset'] = array(
    '#type' => 'submit',
    '#executes_submit_callback' => FALSE,
    '#submit' => array('catalyst_template_list_form_reset'),
    '#value' => t('Reset'),
  );
  $form['list'] = array(
    '#theme' => 'table',
    '#header' => array(
      t('All'),
      array('data' => t('ID'), 'field' => 'id', 'specifier' => 'id', 'type' => 'property'),
      array('data' => t('Label'), 'field' => 'title', 'specifier' => 'title', 'type' => 'property'),
      t('Entity type'),
      t('Bundles'),
      t('View modes'),
      array(
        'data' => t('Package'),
        'type' => 'field',
        'specifier' => array(
          'field' => 'field__package',
          'column' => 'target_id',
        ),
        'field' => '',
      ),
      array('data' => t('Modified'), 'field' => 'changed', 'specifier' => 'changed', 'type' => 'property'),
      t('Actions')
    ),
    '#rows' => array(),
  );
  if ($templates = catalyst_template_query($values, array(), $form['list']['#header'])) {
    dsm($templates);
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
      $uri = entity_uri('catalyst', $template->entity);
      $form['list']['#rows'][] = array(
        drupal_render($checkbox),
        $template->id,
        l($text, $uri['path']),
        $template->template['entity_type'],
        empty($template->template['bundles']) ? '-' : implode(', ', $template->template['bundles']),
        empty($template->template['view_modes']) ? '-' : implode(', ', $template->template['view_modes']),
        empty($template->package) ? '-' : $template->package,
        date(DATE_RFC2822, $template->wrapper->changed->value()),
        $actions
      );
    }
  }
  else {
    $form['list']['#rows'] = array(array(
      array('data' => t('No results'), 'colspan' => count($form['list']['#header'])),
    ));
  }
  $form['footer'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('admin-list-footer')),
  );
  $form['footer']['pager'] = array('#theme' => 'pager');
  $form['footer']['bulk_action'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'admin-list-bulk-action')),
  );
  $form['footer']['bulk_action']['action'] = array(
    '#type' => 'select',
    '#title' => t('Action:'),
    '#options' => array(
      '' => '',
      'delete' => t('Delete template(s)'),
    ),
  );
  $form['footer']['bulk_action']['submit_action'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return catalyst_form($form, 'page', 'catalyst_admin_template_list');
}

function catalyst_template_query($values = array(), $options = array(), $header = array()) {
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
  }
  if (!empty($values['package']) && $pid = catalyst_lookup_entity('package', check_plain($values['package']))) {
    $query->fieldCondition('field__package', 'target_id', $pid, '=');
  }
  if (!empty($values['realm']) && in_array($values['realm'], array('site', 'system'))) {
    $query->fieldCondition('field__internal', 'value',  $values['realm'] == 'system' ? 1 : 0, '=');
  }
  
  $query->pager($options['limit']);
  if ($header) $query->tableSort($header);
  $result = $query->execute();
  if (!empty($result['catalyst'])) {
    return catalyst_load('template', array_keys($result['catalyst']));
  }
}
function catalyst_template_list_form_ajax($form, &$form_state) {
  return $form;
}

function catalyst_template_list_form_reset() {
  drupal_goto('admin/catalyst/template/list');
}