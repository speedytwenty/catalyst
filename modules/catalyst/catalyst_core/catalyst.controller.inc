<?php

/**
 * @file
 */

class CatalystEntityAPIController extends EntityAPIControllerExportable {
  public function bundleHandler($bundle) {
    catalyst_include('plugins');
    return catalyst_get_plugins('bundle', $bundle);
  }

  public function bundlePlugins($bundle) {
    return $this->bundleHandler($bundle)['plugins'];
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
    //$entity->internal = isset($values['internal']) && $values['internal'];
    //$entity->wrapper()->field__internal->set($entity->internal);
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
        if (!empty($entity->{$this->nameKey})) {
          $entity->original = entity_load_unchanged($this->entityType, $entity->{$this->nameKey});
        }
        elseif (!empty($entity->{$this->idKey})) {
          $entity->original = entity_load_unchanged($this->entityType, $entity->{$this->idKey});
        }
      }
      $entity->is_new = !empty($entity->is_new) || empty($entity->{$this->idKey});
      $this->catalyst_invoke('entity save', $entity, $transaction);
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
