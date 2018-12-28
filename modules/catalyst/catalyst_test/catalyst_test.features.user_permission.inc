<?php
/**
 * @file
 * catalyst_test.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function catalyst_test_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'eck add catalyst core_test entities'.
  $permissions['eck add catalyst core_test entities'] = array(
    'name' => 'eck add catalyst core_test entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: 'eck administer catalyst core_test entities'.
  $permissions['eck administer catalyst core_test entities'] = array(
    'name' => 'eck administer catalyst core_test entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: 'eck delete catalyst core_test entities'.
  $permissions['eck delete catalyst core_test entities'] = array(
    'name' => 'eck delete catalyst core_test entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: 'eck edit catalyst core_test entities'.
  $permissions['eck edit catalyst core_test entities'] = array(
    'name' => 'eck edit catalyst core_test entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: 'eck list catalyst core_test entities'.
  $permissions['eck list catalyst core_test entities'] = array(
    'name' => 'eck list catalyst core_test entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: 'eck view catalyst core_test entities'.
  $permissions['eck view catalyst core_test entities'] = array(
    'name' => 'eck view catalyst core_test entities',
    'roles' => array(),
    'module' => 'eck',
  );

  return $permissions;
}
