<?php
$data = array(
  'title' => t('Hello World'),
  'description' => t('The quick brown fox jumps over the lazy dog'),
);
$variables['encoded_json'] = drupal_json_encode($data);