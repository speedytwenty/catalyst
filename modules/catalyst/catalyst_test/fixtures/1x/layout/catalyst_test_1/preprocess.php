<?php
$variables['test_layout_var'] = 'preprocess var val';
$variables['expected_page_title'] = sprintf('%s <> TEST <> %s', strip_tags(drupal_get_title()), check_plain(variable_get('site_name', 'Drupal')));

drupal_set_message('Message from layout preprocessing.');