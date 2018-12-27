<?php

/**
 * @file
 */

class CatalystEntityAPIController extends EntityAPIControllerExportable {
  public function bundleHandler($bundle) {
    catalyst_include('plugins');
    return catalyst_get_plugins('bundle', $bundle);
  }

  public function bundlePlugins($bundle, $plugin = NULL) {
    $plugins = $this->bundleHandler($bundle)['plugins'];
    return $plugin ? $plugins[$plugin] : $plugins;
  }

  public function bundleHandlerPluginSettings($bundle, $plugin_name) {
    $handler = $this->bundleHandler($bundle);
    if (isset($handler['plugins'][$plugin_name])) {
      return $handler['plugins'][$plugin_name]['settings'];
    }
    return array();
  }

  public function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);
    foreach ($entities AS &$entity) {
      $entity->machine = $entity->wrapper()->field__machine->machine->value();
      //$entity->internal = (bool)$entity->wrapper()->field__internal->value();
      //$entity->admin_notes = entity_valval($entity->wrapper()->field__admin_notes);
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
      $this->catalyst_invoke('entity load', $entity);
    }
    return $entities;
  }

  public function create(array $values = array()) {
    $entity = parent::create($values);
    if (!empty($values['machine'])) {
      $entity->wrapper()->field__machine->set(array('machine' => $values['machine']));
    }
    else {
      if ($entity->wrapper()->label()) {
        $entity->machine = preg_replace('/[^a-z0-9_]+/', '', $entity->label);
        $entity->wrapper()->field__machine->set(array('machine' => $entity->machine));
      }
    }
    $this->catalyst_invoke('entity create', $entity, $values);
    //$entity->internal = isset($values['internal']) && $values['internal'];
    //$entity->wrapper()->field__internal->set($entity->internal);
    return $entity;
  }

  public function normalize($entity) {
    $normalized = (object)get_object_vars($entity);
    $unset = array($this->statusKey, $this->moduleKey, 'is_new');
    foreach ($unset AS $k) {
      if (isset($normalized->{$k})) unset($normalized->{$k});
    }
    if ($this->nameKey != $this->idKey) {
      unset($vars->{$this->idKey});
    }
    if (!empty($entity->field__internal)) {
      $normalized->internal = $entity->wrapper()->field__internal->value();
    }
    if (!empty($entity->field__debug)) {
      $normalized->debug = $entity->wrapper()->field__debug->value();
    }
    if (!empty($entity->field__drupal_processing)) {
      $normalized->drupal_processing = (bool)$entity->wrapper()->field__drupal_processing->value();
    }
    if (!empty($entity->field__admin_notes)) {
      $normalized->admin_notes = entity_valval($entity->wrapper()->field__admin_notes);
    }
    if (!empty($entity->field__body)) {
      $normalized->body = entity_valval($entity->wrapper()->field__body);
    }
    if (!empty($entity->field__html_head)) {
      $normalized->html_head = entity_valval($entity->wrapper()->field__html_head);
    }
    if (!empty($entity->field__preprocess)) {
      $normalized->preprocess = entity_valval($entity->wrapper()->field__preprocess);
    }
    if (!empty($entity->field__package)) {
      $normalized->package = $entity->package->normalize();
    }
    $this->catalyst_invoke('entity normalize', $entity, $normalized);
    foreach (array_keys(get_object_vars($normalized)) AS $k) {
      if (strpos($k, 'field__') === 0) unset($normalized->{$k});
    }
    return $normalized;
  }

  public function display(CatalystEntity $entity, $page = NULL) {
    catalyst_include('plugins');
    $this->catalyst_invoke('prepare display', $entity, $page);
    $entity->setVariable('entity', $entity);
    $entity->content = array(
      '#entity_type' => $this->entityType,
      '#bundle' => $entity->wrapper()->getBundle(),
      '#entity' => $entity,
      '#page' => $page,
    );
    $this->catalyst_invoke('entity display', $entity, $page);
    return $entity->content;
  }

  /**
   * Implements EntityAPIControllerInterface.
   *
   * @return
   *   A serialized string in JSON format suitable for the import() method.
   */
  public function export($entity, $prefix = '') {
    $vars = get_object_vars($this->normalize($entity));
    $this->catalyst_invoke('entity export', $entity, $prefix);
    return entity_var_json_export($vars, $prefix);
  }

  /**
   */
  public function catalyst_invoke($hook, $entity) {
    catalyst_include('plugins');
    $args = func_get_args();
    $args[0] = $this->entityType;
    $args[1] = $entity;
    $result = array();
    $handler = $entity->handler();
    if ($func = ctools_plugin_get_function($handler, $hook)) {
      $call_args = $args;
      $call_args[] = $handler;
      $result = call_user_func_array($func, $call_args);
    }
    if (!empty($handler['plugins'])) {
      foreach ($handler['plugins'] AS $plugin_name => $plugin) {
        if ($func = ctools_plugin_get_function($plugin, $hook)) {
          $call_args = $args;
          $call_args[] = $plugin;
          $call_args[] = $handler;
          $call_args[] = $this->bundleHandlerPluginSettings($entity->wrapper()->getBundle(), $plugin_name);
          if ($merge = call_user_func_array($func, $call_args)) {
            $result = array_merge_recursive($result, $merge);
          }
        }
      }
    }
    return $result;
  }

  /**
   * Implements EntityAPIControllerInterface.
   *
   * @param $transaction
   *   Optionally a DatabaseTransaction object to use. Allows overrides to pass
   *   in their transaction object.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    try {
      if (!isset($entity->original)) {
        if (!empty($entity->{$this->nameKey})) {
          $entity->original = entity_load_unchanged($this->entityType, $entity->{$this->nameKey});
        }
        elseif (!empty($entity->{$this->idKey})) {
          $entity->original = entity_load_unchanged($this->entityType, $entity->{$this->idKey});
        }
      }
      $this->catalyst_invoke('entity save', $entity, $transaction);
      $entity->is_new = !empty($entity->is_new) || empty($entity->{$this->idKey});
      $return = parent::save($entity, $transaction);

      //unset($entity->force_overwrite);
      unset($entity->original);
      unset($entity->is_new);
      unset($entity->preprocessed);
      return $return;
    }
    catch (Exception $e) {
      if ($transaction) $transaction->rollback();
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }

}
