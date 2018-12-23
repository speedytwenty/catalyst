<?php

/**
 * @file
 */

class CatalystEntity extends Entity {
  protected $dependencies = array();
  protected $access;
  protected $variables = array();
  public $internal;

  public function dependencies() {
  }

  public function access() {
    if (!isset($this->access)) {
      $this->access = TRUE;
      if (!empty($this->field__access)) {
        $this->access = (bool)catalyst_component_php($this, 'access');
      }
    }
    return $this->access;
  }

  public function variables() {
    return $this->variables;
  }

  public function setVariable($key, $val) {
    $this->variables[$key] = $val;
    return $this;
  }

  public function unsetVariable($key) {
    unset($this->variables[$key]);
    return $this;
  }

  public function setVariables(array $vars) {
    foreach ($vars AS $k => $v) {
      $this->setVariable($k, $v);
    }
  }

  public function getVariable($key) {
    return isset($this->variables[$key]) ? $this->variables[$key] : NULL;
  }

  public function normalize() {
    return entity_get_controller($this->entityType)->normalize($this);
  }

  public function getDataValue($key) {
    $data = entity_valval($this->wrapper()->field__data);
    return isset($data[$key]) ? $data[$key] : NULL;
  }

  public function setDataValue($key, $value) {
    $data = $this->wrapper()->field__data->value();
    $data['value'][$key] = $value;
    $this->wrapper()->field__data->set($data);
    return $this;
  }

  public function handler() {
    return entity_get_controller($this->entityType)->bundleHandler($this->wrapper()->getBundle());
  }

  public function plugins() {
    return entity_get_controller($this->entityType)->bundlePlugins($this->wrapper()->getBundle());
  }

  public function display($page = NULL) {
    return entity_get_controller($this->entityType)->display($this, $page);
  }
}
