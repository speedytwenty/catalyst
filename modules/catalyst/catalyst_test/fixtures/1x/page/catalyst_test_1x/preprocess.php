<?php
$variables['test_page_var'] = 'preprocess var val';

$account = (object) array(
  'created' => time(),
  'name' => 'John Doe',
);
$variables['content'] = user_view($account, 'catalyst_test');