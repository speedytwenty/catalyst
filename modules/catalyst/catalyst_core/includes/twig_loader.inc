<?php

/**
 * @file
 */

class Twig_Loader_Catalyst_Entity implements Twig_LoaderInterface {
  protected $entity_type;
  protected $entity;
  public function __construct($entity_type = NULL, CatalystEntity $entity = NULL) {
    $this->setEntity($entity_type, $entity);
  }

  public function setEntity($entity_type = NULL, CatalystEntity $entity = NULL) {
    $this->entity_type = $entity_type;
    $this->entity = $entity;
  }

  public function getEntityFileInfo($name) {
    $this->checkEntity();
    catalyst_include('code');
    if ($file_info = catalyst_code_entity_file_info($this->entity, $name)) {
      return $file_info;
    }
    else {
      trigger_error(t('Missing twig template file information for:@filename (@entity_type:@bundle:@machine)', array(
        '@filename' => $name,
        '@entity_type' => $this->entity_type,
        '@bundle' => $this->entity->wrapper()->getBundle(),
        '@machine' => $this->entity->machine,
      )));
    }
  }

  public function getSource($name) {
    return file_get_contents($this->getEntityFileInfo($name)['filepath']);
  }

  public function getCacheKey($name) {
    $this->checkEntity();
    return format_string('@entity_type:@bundle:@machine:@name', array(
      '@entity_type' => $this->entity_type,
      '@bundle' => $this->entity->wrapper()->getBundle(),
      '@machine' => $this->entity->machine,
      '@name' => $name,
    ));
  }

  public function exists($name) {
    if ($file_info = $this->getEntityFileInfo($name)) {
      return file_exists($file_info['filepath']);
    }
  }

  public function isFresh($name, $time) {
    $file_info = $this->getEntityFileInfo($name);
    return filemtime($file_info['filepath']) <= $time;
  }
  protected function checkEntity() {
    if (!isset($this->entity)) {
      throw new Exception('Attempting to load catalyst entity twig template before setting an entity.');
    }
  }

  protected function normalize($name) {
    return preg_replace('#/{2,}#', '/', str_replace('\\', '/', (string) $name));
  }
}
