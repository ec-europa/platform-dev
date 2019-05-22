<?php

/**
 * @file
 * Code for the newsletters module.
 */

/**
 * Soft configure simplenews content type.
 */
function _newsletters_set_simplenews_content_type() {
  $t = get_t();

  // Use soft config for simplenews comment form location.
  multisite_config_service('comment')->setReplyFormCommentForContentType('simplenews', 1);
  // Use soft config to allow comments from authenticated users.
  multisite_config_service('comment')->setDefaultCommentForContentType('simplenews', 'closed');
  // Use soft config to allow simplenews comment threading.
  multisite_config_service('comment')->setThreadingCommentForContentType('simplenews', 1);
  // Use soft config for simplenews comment title.
  multisite_config_service('comment')->setTitleCommentForContentType('simplenews', 1);
  // Use soft config for preview simplenews comment.
  multisite_config_service('comment')->setPreviewCommentForContentType('simplenews', 1);
  // Use soft config to set number of comments per page.
  multisite_config_service('comment')->setNumberCommentForContentType('simplenews', '50');

  $field_group_content_children = array(
    0 => 'body',
    1 => 'field_simplenews_term',
    2 => 'title',
  );

  // Attach fields to content type.
  // Data taken from newsletters.features.field_instance.inc.
  $field_instances = array();

  // Activate "entity translation" for simplenews content type if enabled;
  // otherwise, fall back to "content translation" if enabled.
  // This is needed because newsletter can be used in the standard profile
  // where "entity translation" is enabled but in the communities profiles as
  // well where "entity translation" is disabled.
  if (module_exists('entity_translation')) {
    variable_set('language_content_type_simplenews', ENTITY_TRANSLATION_ENABLED);
    // Create the title_field if it does not exist yet.
    multisite_config_service('field')->createTitleField();

    // Exported field_instance: 'node-simplenews-title_field'.
    $field_instances['node-simplenews-title_field'] = array(
      'bundle' => 'simplenews',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
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
      ),
      'entity_type' => 'node',
      'field_name' => 'title_field',
      'label' => $t('Title'),
      'required' => TRUE,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'hide_label' => array(
          'entity' => FALSE,
          'page' => FALSE,
        ),
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => -5,
      ),
    );

    $field_group_content_children[3] = 'title_field';
  }
  else {
    variable_set('language_content_type_simplenews', TRANSLATION_ENABLED);
  }

  // Create new fields.
  // Data taken from newsletters.features.field_base.inc.
  $fields = array(
    'field_related_contents'  => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_related_contents',
      'foreign keys' => array(
        'node' => array(
          'columns' => array(
            'target_id' => 'nid',
          ),
          'table' => 'node',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'direction' => 'ASC',
            'field' => 'body:value',
            'property' => 'nid',
            'type' => 'none',
          ),
          'target_bundles' => array(
            'article' => 'article',
            'page' => 'page',
          ),
        ),
        'handler_submit' => 'Change handler',
        'referenceable_types' => array(
          'article' => 'article',
          'page' => 'page',
        ),
        'target_type' => 'node',
      ),
      'translatable' => 0,
      'type' => 'entityreference',
    ),
  );
  foreach ($fields as $field) {
    field_create_field($field);
  }

  // Exported field_instance: 'node-simplenews-field_related_contents'.
  $field_instances['node-simplenews-field_related_contents'] = array(
    'bundle' => 'simplenews',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_related_contents',
    'label' => $t('related contents'),
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 130,
    ),
  );

  // Exported field_instance: 'node-simplenews-field_tags'.
  $field_instances['node-simplenews-field_tags'] = array(
    'bundle' => 'simplenews',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_tags',
    'label' => $t('Tags'),
    'required' => 0,
    'settings' => array(
      'user_field_privacy' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 120,
    ),
  );

  foreach ($field_instances as $instance) {
    field_create_instance($instance);
  }

  // Add field groups.
  // Stage field group configuration for page content type.
  $service = multisite_config_service('field_group');
  // Data taken from newsletters.features.field_group.inc.
  $service->createFieldGroup('Content', 'group_simplenews', 'node', 'simplenews')
    ->setChildren($field_group_content_children)
    ->setType('tab')->setFormatter('closed')->setWeight(0)
    ->setInstanceSetting('classes', 'group-newsletter-content field-group-tab')
    ->save();

  $service->createFieldGroup('Metadata', 'group_newsletter_metadata', 'node', 'simplenews')
    ->setChildren(array(
      0 => 'field_related_contents',
      1 => 'field_tags',
      2 => 'language',
    ))
    ->setType('tab')->setFormatter('closed')->setWeight(10)
    ->setInstanceSetting('classes', 'group-newsletter-metadata field-group-tab')
    ->save();
}
