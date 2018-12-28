<?php

/**
 * @file
 */

class CatalystEntityAPIController extends EntityAPIController {
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
      $entity->internal = (bool)$entity->wrapper()->field__internal->value();
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

  public function machine() {
    return $this->field__machine->machine->value();
  }

  public function create(array $values = array()) {
    $entity = parent::create($values);
    if (!empty($values['machine'])) {
      $entity->machine = $values['machine'];
      $entity->wrapper()->field__machine->set(array('machine' => $values['machine']));
    }
    $internal = isset($values['internal']) ? $values['internal'] : 0;
    $entity->wrapper()->field__internal->set($internal);
    $this->catalyst_invoke('entity create', $entity, $values);
    return $entity;
  }

  /**
   * Custom import.
   *
   * @see EntityAPIControllerExportable::import()
   */
  public function import($export) {
    if (is_array($export)) {
      $entity = $this->create($export);
      if (!empty($export['package'])) {
        $package = $this->ensureStub($entity, 'package', $export['package']);
        $entity->wrapper()->field__package->set($package);
      }
      $this->catalyst_invoke('entity import', $entity, $export);
      return $entity;
    }
    return FALSE;
  }

  public function ensureStub(CatalystEntity $entity, $bundle, $machine) {
    if ($item = catalyst_load_single($bundle, $machine)) {
      return $item->entity;
    }
    $stub = entity_create($this->entityType, array(
      'title' => t('Stub for: @title', array('@tite' => $entity->wrapper()->label())),
      'machine' => $machine,
      'type' => $bundle,
    ));
    $stub->save();
    return $stub;
  }

  public function export($entity, $prefix = '') {
    $export = get_object_vars($entity);
    unset($export['is_new']);
    if ($prefix && !empty($export['machine'])) {
      $export['machine'] = $prefix.$export['machine'];
    }
    $export['internal'] = empty($entity->field__internal) ? FALSE : (bool)$entity->wrapper()->field__internal->value();
    $handler = $entity->handler();
    if ($func = ctools_plugin_get_function($handler, 'entity export')) {
      $func($entity, $export, $prefix, $handler);
    }
    foreach ($handler['plugins'] AS $plugin_name => $plugin) {
      if ($func = ctools_plugin_get_function($plugin, 'entity export')) {
        $func($entity, $export, $prefix, $plugin, $handler);
      }
    }
    foreach (array_keys($export) AS $k) {
      if (strpos($k, 'field__') === 0) unset($export[$k]);
    }
    return $export;
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
        if (!empty($this->nameKey) && !empty($entity->{$this->nameKey})) {
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
