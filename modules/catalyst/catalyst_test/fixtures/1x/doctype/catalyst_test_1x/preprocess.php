<?php
$variables['test_doctype_var'] = 'doctype var value';
// Variable to check to see that doctype preprocessing occurred before this preprocessing
$variables['preprocessing_results'] = array();
$testvars = array(
  'head_title' => 'is_string',
  'head_title_array' => 'is_array',
  'page' => 'is_array',
  'drupal_processing' => 'is_bool',
  'doctype' => 'is_object',
  'layout' => 'is_array',
  // drupal vars
  'zebra' => 'is_string',
  'id' => 'is_int',
  'classes_array' => 'is_array',
  'rdf_namespaces' => 'is_string',
  'grddl_profile' => 'is_string',
  'language' => 'is_object',
);
foreach ($testvars AS $testvar => $expected) {
  $missing = !isset($variables[$testvar]);
  if ($expected != 'empty') {
    $variables['preprocessing_results'][] = array(
      'result' => !$missing,
      'expected' => TRUE,
      'actual' => FALSE,
      'message' => format_string('The @varname is present in prepreocessing.', array(
        '@varname' => $testvar,
      )),
    );
  }
  $variables['preprocessing_results'][] = array(
    'result' => !$missing && $expected($variables[$testvar]),
    'expected' => TRUE,
    'actual' => FALSE,
    'message' => format_string('The @varname @type in prepreocessing.', array(
      '@varname' => $testvar,
      '@type' => $expected,
    )),
  );
}
drupal_set_message('Message from doctype preprocessing.');
dsm($variables);