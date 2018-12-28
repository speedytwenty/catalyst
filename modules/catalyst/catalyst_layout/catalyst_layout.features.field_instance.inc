<?php
/**
 * @file
 * catalyst_layout.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function catalyst_layout_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'catalyst-doctype-field__admin_notes'.
  $field_instances['catalyst-doctype-field__admin_notes'] = array(
    'bundle' => 'doctype',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__admin_notes',
    'label' => 'Help/Instructions',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 'catalyst_doc',
          'catalyst_html' => 0,
          'catalyst_js' => 0,
          'catalyst_php' => 0,
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 28,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__body'.
  $field_instances['catalyst-doctype-field__body'] = array(
    'bundle' => 'doctype',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
      'template' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__body',
    'label' => 'Content',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 0,
          'catalyst_html' => 'catalyst_html',
          'catalyst_js' => 0,
          'catalyst_php' => 0,
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__data'.
  $field_instances['catalyst-doctype-field__data'] = array(
    'bundle' => 'doctype',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__data',
    'label' => 'Data',
    'required' => 0,
    'settings' => array(
      'namespace' => 1,
      'serialization' => 'json_encode',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'serialized_field',
      'settings' => array(),
      'type' => 'serialized_hidden',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__doctype_charset'.
  $field_instances['catalyst-doctype-field__doctype_charset'] = array(
    'bundle' => 'doctype',
    'default_value' => array(
      0 => array(
        'value' => 'utf-8',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__doctype_charset',
    'label' => 'Character Set',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'select_or_other',
      'settings' => array(
        'available_options' => 'utf-8
',
        'available_options_php' => '',
        'markup_available_options_php' => '&lt;none&gt;',
        'other' => 'Other',
        'other_size' => 30,
        'other_title' => '',
        'other_unknown_defaults' => 'other',
        'sort_options' => 0,
      ),
      'type' => 'select_or_other',
      'weight' => 24,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__doctype_content_type'.
  $field_instances['catalyst-doctype-field__doctype_content_type'] = array(
    'bundle' => 'doctype',
    'default_value' => array(
      0 => array(
        'value' => 'text/html',
      ),
    ),
    'deleted' => 0,
    'description' => '<p><em>For a complete list of content types goto <a href="http://www.freeformatter.com/mime-types-list.html" target="_blank">http://www.freeformatter.com/mime-types-list.html</a>.</em></p>',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__doctype_content_type',
    'label' => 'HTTP Content-Type',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'select_or_other',
      'settings' => array(
        'available_options' => 'application/json|application/json
application/xml|application/xml
application/xhtml+xml|application/xhtml+xml
text/html|text/html',
        'available_options_php' => '',
        'markup_available_options_php' => '&lt;none&gt;',
        'other' => 'Other',
        'other_size' => 60,
        'other_title' => '',
        'other_unknown_defaults' => 'other',
        'sort_options' => 0,
      ),
      'type' => 'select_or_other',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__drupal_processing'.
  $field_instances['catalyst-doctype-field__drupal_processing'] = array(
    'bundle' => 'doctype',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 3,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__drupal_processing',
    'label' => 'Enable Drupal processing',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__internal'.
  $field_instances['catalyst-doctype-field__internal'] = array(
    'bundle' => 'doctype',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_key',
        'weight' => 6,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__internal',
    'label' => 'Internal',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 27,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__machine'.
  $field_instances['catalyst-doctype-field__machine'] = array(
    'bundle' => 'doctype',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'machine',
        'settings' => array(),
        'type' => 'machine_default',
        'weight' => 1,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__machine',
    'label' => 'Machine name',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'machine',
      'settings' => array(
        'editable' => 0,
        'field_size' => 60,
        'machine_field_label' => 'Machine name',
        'machine_replace_pattern' => '[^a-z0-9_]+',
        'machine_replace_with' => '_',
      ),
      'type' => 'machine_from_title_widget',
      'weight' => 22,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__package'.
  $field_instances['catalyst-doctype-field__package'] = array(
    'bundle' => 'doctype',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__package',
    'label' => 'Package',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'entityreference_autocreate' => array(
          'active' => 1,
          'author' => '',
          'author_current_user' => 1,
          'status' => -1,
        ),
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 26,
    ),
  );

  // Exported field_instance: 'catalyst-doctype-field__preprocess'.
  $field_instances['catalyst-doctype-field__preprocess'] = array(
    'bundle' => 'doctype',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__preprocess',
    'label' => 'Preprocessing',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 0,
          'catalyst_html' => 0,
          'catalyst_js' => 0,
          'catalyst_php' => 'catalyst_php',
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 24,
    ),
  );

  // Exported field_instance: 'catalyst-file-field__data'.
  $field_instances['catalyst-file-field__data'] = array(
    'bundle' => 'file',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__data',
    'label' => 'Data',
    'required' => 0,
    'settings' => array(
      'namespace' => 1,
      'serialization' => 'json_encode',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'serialized_field',
      'settings' => array(),
      'type' => 'serialized_hidden',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'catalyst-javascript-field__data'.
  $field_instances['catalyst-javascript-field__data'] = array(
    'bundle' => 'javascript',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__data',
    'label' => 'Data',
    'required' => 0,
    'settings' => array(
      'namespace' => 1,
      'serialization' => 'json_encode',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'serialized_field',
      'settings' => array(),
      'type' => 'serialized_hidden',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__admin_notes'.
  $field_instances['catalyst-layout-field__admin_notes'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 22,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__admin_notes',
    'label' => 'Help/Instructions',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 'catalyst_doc',
          'catalyst_html' => 0,
          'catalyst_js' => 0,
          'catalyst_php' => 0,
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 27,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__blockplacements__layout'.
  $field_instances['catalyst-layout-field__blockplacements__layout'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__blockplacements__layout',
    'label' => 'Blocks',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'catalyst_field_api',
      'settings' => array(),
      'type' => 'block_placement_layout_widget',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__blocks_related'.
  $field_instances['catalyst-layout-field__blocks_related'] = array(
    'bundle' => 'layout',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__blocks_related',
    'label' => 'Add Blocks',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_clone' => 0,
          'allow_existing' => 1,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'blocks',
          'label_singular' => 'block',
          'match_operator' => 'CONTAINS',
          'override_labels' => 1,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__body'.
  $field_instances['catalyst-layout-field__body'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'template' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__body',
    'label' => 'Content',
    'required' => 1,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 0,
          'catalyst_html' => 'catalyst_html',
          'catalyst_js' => 0,
          'catalyst_php' => 0,
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__css__layout'.
  $field_instances['catalyst-layout-field__css__layout'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__css__layout',
    'label' => 'Custom CSS',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 'catalyst_css',
          'catalyst_doc' => 0,
          'catalyst_html' => 0,
          'catalyst_js' => 0,
          'catalyst_php' => 0,
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__data'.
  $field_instances['catalyst-layout-field__data'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__data',
    'label' => 'Data',
    'required' => 0,
    'settings' => array(
      'namespace' => 1,
      'serialization' => 'json_encode',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'serialized_field',
      'settings' => array(),
      'type' => 'serialized_hidden',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__doctype'.
  $field_instances['catalyst-layout-field__doctype'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__doctype',
    'label' => 'Doctype',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'test_instance_behavior' => array(
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__drupal_processing'.
  $field_instances['catalyst-layout-field__drupal_processing'] = array(
    'bundle' => 'layout',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__drupal_processing',
    'label' => 'Enable Drupal processing',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 18,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__files'.
  $field_instances['catalyst-layout-field__files'] = array(
    'bundle' => 'layout',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 15,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__files',
    'label' => 'Custom Files',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'gif jpg jpeg png svg doc docx rtf txt wpd wps cvs dat pps ppt pptx sdf vcf xml m3u m4a mid mp3 wma wav 3gp avi flv mov mp4 mpg wmv',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 1,
          ),
          'value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 1,
          ),
          'value' => 'media/layout/[catalyst:field--machine:machine]',
        ),
        'redirect' => FALSE,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'bar',
      ),
      'type' => 'file_generic',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__html_head'.
  $field_instances['catalyst-layout-field__html_head'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 14,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__html_head',
    'label' => 'Custom HTML Head',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 0,
          'catalyst_html' => 'catalyst_html',
          'catalyst_js' => 0,
          'catalyst_php' => 0,
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 10,
      ),
      'type' => 'text_textarea',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__internal'.
  $field_instances['catalyst-layout-field__internal'] = array(
    'bundle' => 'layout',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 20,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__internal',
    'label' => 'Internal',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__js__layout'.
  $field_instances['catalyst-layout-field__js__layout'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Custom javascript specific to this layout.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__js__layout',
    'label' => 'Custom Javascript',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 0,
          'catalyst_html' => 0,
          'catalyst_js' => 'catalyst_js',
          'catalyst_php' => 0,
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__layout_drupal_css'.
  $field_instances['catalyst-layout-field__layout_drupal_css'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 19,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__layout_drupal_css',
    'label' => 'Drupal Stylesheets',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 21,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__layout_drupal_js'.
  $field_instances['catalyst-layout-field__layout_drupal_js'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__layout_drupal_js',
    'label' => 'Drupal Javascript',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 22,
    ),
  );

  // Exported field_instance:
  // 'catalyst-layout-field__layout_page_title_pattern'.
  $field_instances['catalyst-layout-field__layout_page_title_pattern'] = array(
    'bundle' => 'layout',
    'default_value' => array(
      0 => array(
        'value' => '{%if title %}{{ title }} | {% endif %}{{ name }}',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__layout_page_title_pattern',
    'label' => 'Page title pattern',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__layout_regions'.
  $field_instances['catalyst-layout-field__layout_regions'] = array(
    'bundle' => 'layout',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 18,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__layout_regions',
    'label' => 'Regions',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'machine',
      'settings' => array(
        'editable' => 1,
        'field_size' => 60,
        'machine_field_label' => 'Region key',
        'machine_replace_pattern' => '[^a-z0-9_]+',
        'machine_replace_with' => '_',
        'text_field_label' => 'Region text',
      ),
      'type' => 'machine_with_text_widget',
      'weight' => 25,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__layout_show_messages'.
  $field_instances['catalyst-layout-field__layout_show_messages'] = array(
    'bundle' => 'layout',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__layout_show_messages',
    'label' => 'Show messages',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__machine'.
  $field_instances['catalyst-layout-field__machine'] = array(
    'bundle' => 'layout',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__machine',
    'label' => 'Machine name',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'machine',
      'settings' => array(
        'editable' => 0,
        'field_size' => 60,
        'machine_field_label' => 'Machine name',
        'machine_replace_pattern' => '[^a-z0-9_]+',
        'machine_replace_with' => '_',
      ),
      'type' => 'machine_from_title_widget',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__media_files'.
  $field_instances['catalyst-layout-field__media_files'] = array(
    'bundle' => 'layout',
    'deleted' => 0,
    'description' => 'Adding files here allows them to used easily in other places.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__media_files',
    'label' => 'Shared Files',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_existing' => 1,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'files',
          'label_singular' => 'file',
          'match_operator' => 'CONTAINS',
          'override_labels' => 1,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 24,
    ),
  );

  // Exported field_instance:
  // 'catalyst-layout-field__media_javascripts__layout'.
  $field_instances['catalyst-layout-field__media_javascripts__layout'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__media_javascripts__layout',
    'label' => 'Javascript Includes',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_clone' => 0,
          'allow_existing' => 1,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'javascripts',
          'label_singular' => 'javascript',
          'match_operator' => 'CONTAINS',
          'override_labels' => 1,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 7,
    ),
  );

  // Exported field_instance:
  // 'catalyst-layout-field__media_stylesheets__layout'.
  $field_instances['catalyst-layout-field__media_stylesheets__layout'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__media_stylesheets__layout',
    'label' => 'Stylesheet Includes',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'inline_entity_form',
      'settings' => array(
        'fields' => array(),
        'type_settings' => array(
          'allow_clone' => 0,
          'allow_existing' => 1,
          'allow_new' => 1,
          'delete_references' => 0,
          'label_plural' => 'stylesheets',
          'label_singular' => 'stylesheet',
          'match_operator' => 'CONTAINS',
          'override_labels' => 1,
        ),
      ),
      'type' => 'inline_entity_form',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__package'.
  $field_instances['catalyst-layout-field__package'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 21,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__package',
    'label' => 'Package',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'entityreference_autocreate' => array(
          'active' => 1,
          'author' => '',
          'author_current_user' => 1,
          'status' => -1,
        ),
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'catalyst-layout-field__preprocess'.
  $field_instances['catalyst-layout-field__preprocess'] = array(
    'bundle' => 'layout',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'template' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__preprocess',
    'label' => 'Preprocessing',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'catalyst_css' => 0,
          'catalyst_doc' => 0,
          'catalyst_html' => 0,
          'catalyst_js' => 0,
          'catalyst_php' => 'catalyst_php',
          'plain_text' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'catalyst_css' => array(
              'weight' => 0,
            ),
            'catalyst_doc' => array(
              'weight' => 0,
            ),
            'catalyst_html' => array(
              'weight' => 0,
            ),
            'catalyst_js' => array(
              'weight' => 0,
            ),
            'catalyst_php' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 30,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'catalyst-stylesheet-field__data'.
  $field_instances['catalyst-stylesheet-field__data'] = array(
    'bundle' => 'stylesheet',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'catalyst',
    'field_name' => 'field__data',
    'label' => 'Data',
    'required' => 0,
    'settings' => array(
      'namespace' => 1,
      'serialization' => 'json_encode',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'serialized_field',
      'settings' => array(),
      'type' => 'serialized_hidden',
      'weight' => 17,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<p><em>For a complete list of content types goto <a href="http://www.freeformatter.com/mime-types-list.html" target="_blank">http://www.freeformatter.com/mime-types-list.html</a>.</em></p>');
  t('Add Blocks');
  t('Adding files here allows them to used easily in other places.');
  t('Blocks');
  t('Character Set');
  t('Content');
  t('Custom CSS');
  t('Custom Files');
  t('Custom HTML Head');
  t('Custom Javascript');
  t('Custom javascript specific to this layout.');
  t('Data');
  t('Doctype');
  t('Drupal Javascript');
  t('Drupal Stylesheets');
  t('Enable Drupal processing');
  t('HTTP Content-Type');
  t('Help/Instructions');
  t('Internal');
  t('Javascript Includes');
  t('Machine name');
  t('Package');
  t('Page title pattern');
  t('Preprocessing');
  t('Regions');
  t('Shared Files');
  t('Show messages');
  t('Stylesheet Includes');

  return $field_instances;
}
