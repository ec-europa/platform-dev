<?php

/**
 * @file
 * Code for the newsletters module.
 */

/**
 * Soft configure simplenews content type.
 */
function _newsletters_set_simplenews_content_type() {
  // Use soft config for newsletters comment form location.
  multisite_config_service('comment')->setThreadingCommentForContentType('simplenews', 1);

  $t = get_t();
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

  // Attach fields to content type.
  // Data taken from newsletters.features.field_instance.inc.
  $field_instances = array();

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

  foreach ($field_instances as $instance) {
    field_create_instance($instance);
  }

  // Add field groups.
  // Data taken from newsletters.features.field_group.inc.
  $field_group1 = new stdClass();
  $field_group1->disabled = FALSE;
  $field_group1->api_version = 1;
  $field_group1->identifier = 'group_newsletter_metadata|node|simplenews|form';
  $field_group1->group_name = 'group_newsletter_metadata';
  $field_group1->entity_type = 'node';
  $field_group1->bundle = 'simplenews';
  $field_group1->mode = 'form';
  $field_group1->parent_name = '';
  $field_group1->label = 'Metadata';
  $field_group1->weight = '10';
  $field_group1->children = array(
    0 => 'field_related_contents',
    1 => 'field_tags',
    2 => 'language',
  );
  $field_group1->format_type = 'tab';
  $field_group1->format_settings = array(
    'formatter' => 'closed',
    'instance_settings' => array(
      'description' => '',
      'classes' => 'group-newsletter-metadata field-group-tab',
      'required_fields' => 1,
    ),
  );
  $field_groups = array();
  $field_groups['group_newsletter_metadata|node|simplenews|form'] = $field_group1;

  $field_group2 = new stdClass();
  $field_group2->disabled = FALSE;
  $field_group2->api_version = 1;
  $field_group2->identifier = 'group_simplenews|node|simplenews|form';
  $field_group2->group_name = 'group_simplenews';
  $field_group2->entity_type = 'node';
  $field_group2->bundle = 'simplenews';
  $field_group2->mode = 'form';
  $field_group2->parent_name = '';
  $field_group2->label = 'Content';
  $field_group2->weight = '0';
  $field_group2->children = array(
    0 => 'body',
    1 => 'field_simplenews_term',
    2 => 'title_field',
  );
  $field_group2->format_type = 'tab';
  $field_group2->format_settings = array(
    'formatter' => 'closed',
    'instance_settings' => array(
      'description' => '',
      'classes' => 'group-simplenews field-group-tab',
      'required_fields' => 1,
    ),
  );
  $field_groups['group_simplenews|node|simplenews|form'] = $field_group2;

  foreach ($field_groups as $group) {
    field_group_group_save($group);
  }
}

/**
 * Add title_field to simplenews content type.
 */
function _newsletters_add_title_field_to_simplenews() {
  $t = get_t();

  // Field instance for title_field.
  if (!field_info_instance('node', 'title_field', 'simplenews')) {
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
    field_create_instance($field_instances['node-simplenews-title_field']);
  }
  else {
    $instance_info = field_info_instance('node', 'title_field', 'simplenews');
    $instance_info['label'] = $t('Title');
    field_update_instance($instance_info);
  }

  $service = multisite_config_service('field_group');

  $service->createFieldGroup('Content', 'group_simplenews', 'node', 'simplenews')
    ->setChildren(array(
      'title_field',
      'field_simplenews_term',
      'body',
    ))
    ->setType('tab')->setFormatter('closed')->setWeight(0)
    ->setInstanceSetting('classes', 'group-simplenews field-group-tab')
    ->setInstanceSetting('required_fields', TRUE)
    ->save();

  $service->createFieldGroup('Metadata', 'group_newsletter_metadata', 'node', 'simplenews')
    ->setChildren(array(
      'field_related_contents',
      'language',
      'field_tags',
    ))
    ->setType('tab')->setFormatter('closed')->setWeight(10)
    ->setInstanceSetting('classes', 'group-newsletter-metadata field-group-tab')
    ->setInstanceSetting('required_fields', TRUE)
    ->save();
}

/**
 * Update the fields of simplenews content type for entity translation.
 */
function _newsletters_node_update($row) {
  $t = get_t();
  $node = node_load($row['nid']);
  $node->title = $node->title;

  $fields = field_info_instances('node', 'simplenews');

  foreach ($fields as $field_name => $field_definition) {
    $instance_info = field_info_instance('node', $field_name, 'simplenews');
    $instance_info['label'] = $t($instance_info['label']);
    field_update_instance($instance_info);

    $field_info = field_info_field($field_name);
    if ($field_info['type'] == 'text' || $field_info['type'] == 'text_long' || $field_info['text_with_summary'] || $field_info['type'] == 'link_field') {
      $field_info['translatable'] = 1;
      field_update_field($field_info);
    }
  }

  node_save($node);
  drupal_set_message(t('We processed node @nid', array('@nid' => $node->nid)));
}
