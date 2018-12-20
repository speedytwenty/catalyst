<?php

/**
 * @file
 */

class CatalystEntityAPIController extends EntityAPIControllerExportable {
  public function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);
    foreach ($entities AS &$entity) {
      $entity->machine = $entity->wrapper()->field__machine->machine->value();
      $entity->internal = (bool)$entity->wrapper()->field__internal->value();
      $entity->admin_notes = entity_valval($entity->wrapper()->field__admin_notes);
      //$entity->component = catalyst_registry_entry($entity->type, $entity->machine);
      if (!empty($entity->field__package)) {
        $entity->package = $entity->wrapper()->field__package->value();
      }
      if (!empty($entity->field__data)) {
        $entity->data = entity_valval($entity->wrapper()->field__data);
        if ($entity->type == 'package' && !empty($entity->data['module'])) {
          $entity->module = $entity->data['module'];
          $entity->subdir = $entity->data['subdir'];
        }
      }
    }
    return $entities;
  }

  public function create(array $values = array()) {
    $entity = parent::create($values);
    if (!empty($values['machine'])) {
      $entity->wrapper()->field__machine->set(array('machine' => $values['machine']));
    }
    return $entity;
  }

  public function normalize($entity) {
    $vars = get_object_vars($entity);
    unset($vars[$this->statusKey], $vars[$this->moduleKey], $vars['is_new']);
    if ($this->nameKey != $this->idKey) {
      unset($vars[$this->idKey]);
    }
    if (!empty($vars['field__internal'])) {
      $vars['internal'] = $entity->wrapper()->field__internal->value();
    }
    unset($vars['field__internal']);
    if (!empty($vars['field__debug'])) {
      $vars['debug'] = $entity->wrapper()->field__debug->value();
    }
    unset($vars['field__debug']);
    if (!empty($vars['field__drupal_processing'])) {
      $vars['drupal_processing'] = $entity->wrapper()->field__drupal_processing->value();
    }
    unset($vars['field__drupal_processing']);
    if (!empty($vars['field__admin_notes'])) {
      $vars['admin_notes'] = entity_valval($entity->wrapper()->field__admin_notes);
    }
    unset($vars['field__admin_notes']);
    if (!empty($vars['field__body'])) {
      $vars['body'] = entity_valval($entity->wrapper()->field__body);
    }
    unset($vars['field__body']);
    if (!empty($vars['field__html_head'])) {
      $vars['html_head'] = entity_valval($entity->wrapper()->field__html_head);
    }
    unset($vars['field__html_head']);
    if (!empty($vars['field__preprocess'])) {
      $vars['preprocess'] = entity_valval($entity->wrapper()->field__preprocess);
    }
    unset($vars['field__preprocess']);
    if (!empty($entity->package) && !is_array($entity->package)) {
      $vars['package'] = $entity->package->normalize();
    }
    unset($vars['field__package']);
    unset($vars['field__machine']);
    drupal_alter('entity_export', $vars, $entity, $this->entityType);
    return $vars;
  }

  public function export($entity, $prefix = '') {
    $vars = $this->normalize($entity);
    return entity_var_json_export($vars, $prefix);
  }

  public function view($entities, $view_mode = 'template', $langcode = NULL, $page = NULL) {
    if ($view_mode != 'template') {
      return parent::view($entities, $view_mode, $langcode, $page);
    }
    $view = array();
    $entities = entity_key_array_by_property($entities, $this->idKey);
    foreach ($entities AS $entity) {
      $build = array(
        //'#theme' => $entity->type,
        '#entity_type' => $this->entityType,
        '#entity' => $entity,
        '#bundle' => $entity->type,
        '#page' => $page,
      );
      $entity->setVariable($entity->type, $entity);
      ctools_include('plugins');
      $plugins = ctools_get_plugins('catalyst', 'plugin');
      foreach ($plugins AS $plugin_name => $plugin) {
        if ($func = ctools_plugin_get_function($plugin, 'entity build')) {
          $func($build);
        }
      }
      $key = isset($entity->{$this->idKey}) ? $entity->{$this->idKey} : NULL;
      $view[$this->entityType][$key] = $build;
    }
    return $view;
  }

  /**
   * Implements EntityAPIControllerInterface.
   *
   * @param $transaction
   *   Optionally a DatabaseTransaction object to use. Allows overrides to pass
   *   in their transaction object.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $transaction = isset($transaction) ? $transaction : db_transaction();
    try {
      // Load the stored entity, if any.
      if (!empty($entity->{$this->idKey}) && !isset($entity->original)) {
        // In order to properly work in case of name changes, load the original
        // entity using the id key if it is available.
        $entity->original = entity_load_unchanged($this->entityType, $entity->{$this->idKey});
      }
      $entity->is_new = !empty($entity->is_new) || empty($entity->{$this->idKey});
      ctools_include('plugins');
      $plugins = ctools_get_plugins('catalyst', 'plugin');
      foreach ($plugins AS $plugin_name => $plugin) {
        if ($func = ctools_plugin_get_function($plugin, 'entity save')) {
          $func($this->entityType, $entity);
        }
      }
      return parent::save($entity, $transaction);
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }

}
