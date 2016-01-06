<?php

/**
 * @file
 */

class CatalystBlockMigration extends CatalystEntityMigration {
  protected $entityBundle = 'block';
  protected $machineField = 'field__machine';
  protected $machineKey = 'field__machine';
  protected $sourceIDField = 'id';

  protected function sourceFields() {
    return array(
      'machine_name' => t('Machine name'),
      'content' => t('Block content'),
      'css_custom' => t('Custom CSS'),
      'css_includes' => t('CSS Includes'),
      'js_custom' => t('Custom JS'),
      'js_includes' => t('JS Includes'),
      'files_custom' => t('Custom Files'),
      'files_shared' => t('Shared Files'),
      'preprocess_php' => t('Preprocess PHP'),
      'block_placements' => t('Block placements'),
      'block_placement_layout_ids' => t('Block placement layout IDs'),
    ) + parent::sourceFields();
  }
  //*/

  protected function mapFields() {
    parent::mapFields();
    $this->addFieldMapping('field__machine', 'machine_name');
    // Block placements
    $this->addFieldMapping('field__blockplacements__block', 'block_placements');
    $this->addReferenceFieldMapping('field__blockplacements__block:layout_id', 'block_placement_layout_ids', 'layout');
    // Reference field mapping
    $this->addReferenceFieldMapping('field__media_stylesheets', 'css_includes', 'stylesheet');
    $this->addReferenceFieldMapping('field__media_javascripts', 'js_includes', 'javascript');
    $this->addReferenceFieldMapping('field__media_files', 'files_shared', 'file');
    // Mappings for formatted fields
    $this->addFormattedFieldMapping('field__body', 'content', 'cpage_html');
    $this->addFormattedFieldMapping('field__preprocess', 'preprocess_php', 'php');
    $this->addFormattedFieldMapping('field__css', 'css_custom', 'css');
    $this->addFormattedFieldMapping('field__js', 'js_custom', 'js');
    // File field mapping
    $this->addFileFieldMapping('field__files', 'files_custom');
  }
}