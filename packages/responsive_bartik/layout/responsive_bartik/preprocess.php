<?php
$variables['main_menu'] = theme('links__system_main_menu', array(
  'links' => menu_main_menu(),
  'attributes' => array(
    'id' => 'main-menu-links',
    'class' => array('links', 'clearfix'),
  ),
  'heading' => array(
    'text' => t('Main menu'),
    'level' => 'h2',
    'class' => array('element-invisible'),
  ),
));
$variables['secondary_menu'] = theme('links__system_secondary_menu', array(
  'links' => menu_secondary_menu(),
  'attributes' => array(
    'id' => 'secondary-menu-links',
    'class' => array('links', 'inline', 'clearfix'),
  ),
  'heading' => array(
    'text' => t('Secondary menu'),
    'level' => 'h2',
    'class' => array('element-invisible'),
  ),
));