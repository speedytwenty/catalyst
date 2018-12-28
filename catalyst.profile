<?php
/**
 * @file
 * Enables modules and site configuration for a catalyst site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Alter the "configure" installation step
 */
function catalyst_form_install_configure_form_alter(&$form, $form_state) {
  form_load_include($form_state, 'install', 'catalyst');
  _catalyst_form_install_configure_form_alter($form, $form_state);
}

