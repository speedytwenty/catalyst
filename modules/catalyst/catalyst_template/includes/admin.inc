<?php

/**
 * @file
 * Catalyst template admin page and form callbacks.
 */

function catalyst_template_admin_list() {
  $entity_info = entity_get_info();
  unset($entity_info['catalyst']);
  $build = array();
  foreach ($entity_info  AS $entity_type => $entity_type_info) {
    if (empty($entity_type_info['view modes'])) {
      continue;
    }
    $build[$entity_type] = array(
      '#theme' => 'table',
      '#header' => array(t('Bundle'), t('Actions')),
      '#rows' => array(),
      '#caption' => $entity_type_info['label'],
    );
    $default = array('__default__' => array('label' => t('Default')));
    $bundles = $default + $entity_type_info['bundles'];
    foreach ($bundles AS $bundle => $bundle_info) {
      $links = array();
      if ($template = catalyst_template_load($entity_type, $bundle, FALSE)) {
        $links['configure'] = array(
          'href' =>  'admin/catalyst/template/' . $template->id . '/edit',
          'title' => t('configure'),
        );
        $links['delete'] = array(
          'href' =>  'admin/catalyst/template/' . $template->id . '/delete',
          'title' => t('delete'),
        );
      }
      else {
        $links['configure'] = array(
          'href' =>  'admin/catalyst/template/add/' . $entity_type . '/' . $bundle,
          'title' => t('setup'),
        );
      }
      $build[$entity_type]['#rows'][] = array(
        $bundle_info['label'],
        theme('links', array('links' => $links, 'attributes' => array('class' => array('inline')))),
      );
    }
  }
  return $build;
}
