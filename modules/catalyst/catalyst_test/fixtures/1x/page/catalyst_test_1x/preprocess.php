<?php
$variables['test_page_var'] = 'preprocess var val';

$account = (object) array(
  'created' => time(),
  'name' => 'John Doe',
  'uid' => 0,
);
$variables['content'] = user_view($account, 'catalyst_test');
drupal_set_message('Message from page preprocessing.');