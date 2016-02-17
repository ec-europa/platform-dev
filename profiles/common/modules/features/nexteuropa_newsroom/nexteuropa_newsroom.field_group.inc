<?php
/**
 * @file
 * nexteuropa_newsroom.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_newsroom_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_info|node|newsroom_item|default';
  $field_group->group_name = 'group_event_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Event information',
    'weight' => '1',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'field_newsroom_item_speaker',
      2 => 'field_newsroom_item_venue',
      3 => 'field_newsroom_project',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Event information',
      'instance_settings' => array(
        'classes' => 'group-event-info field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_event_info|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_lead|node|newsroom_item|default';
  $field_group->group_name = 'group_lead';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Lead',
    'weight' => '2',
    'children' => array(
      0 => 'field_illustrative_image',
      1 => 'field_teaser',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Lead',
      'instance_settings' => array(
        'classes' => 'group-lead field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_lead|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsrom_item_basic_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsrom_item_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic Information',
    'weight' => '7',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-newsrom-item-basic-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsrom_item_basic_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_additional_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_additional_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional information',
    'weight' => '45',
    'children' => array(
      0 => 'field_newsroom_item_contact_mail',
      1 => 'field_newsroom_item_contact_text',
      2 => 'field_newsroom_item_other_link',
      3 => 'field_newsroom_project',
      4 => 'field_newsroom_project_acr',
      5 => 'field_newsroom_project_website',
      6 => 'field_nr_project_coordinator',
      7 => 'field_newsroom_ec_content',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-additional-info field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsroom_additional_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_basic_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic Information',
    'weight' => '5',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'field_newsroom_item_main_link',
      2 => 'field_newsroom_item_rapid_pr',
      3 => 'field_newsletter_only',
      4 => 'field_newsroom_short_item',
      5 => 'field_newsroom_teaser_only',
      6 => 'field_related_content',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsroom_item_basic_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_context_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_context_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Context Information',
    'weight' => '8',
    'children' => array(
      0 => 'field_newsroom_item_id',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-newsroom-item-context-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsroom_item_context_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_full_content|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_full_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Full Content',
    'weight' => '4',
    'children' => array(
      0 => 'body',
      1 => 'field_newsroom_item_image',
      2 => 'field_newsroom_item_linked_obj',
      3 => 'field_newsroom_item_pre_title',
      4 => 'field_newsroom_item_quote_box',
      5 => 'field_newsroom_item_short_title',
      6 => 'field_newsroom_item_speaker',
      7 => 'field_newsroom_item_venue',
      8 => 'field_newsroom_documents',
      9 => 'field_newsroom_files',
      10 => 'field_illustrative_image',
      11 => 'field_newsroom_slide',
      12 => 'field_teaser',
      13 => 'field_newsroom_location',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsroom_item_full_content|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_technical|taxonomy_term|newsroom_item_type|form';
  $field_group->group_name = 'group_newsroom_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_item_type';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '4',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-newsroom-technical field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsroom_technical|taxonomy_term|newsroom_item_type|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_topics|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_topics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Topics',
    'weight' => '3',
    'children' => array(
      0 => 'field_tags',
      1 => 'field_highlighted_newsroom_topic',
      2 => 'field_newsroom_topics',
      3 => 'field_primary_topic',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-topics field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsroom_topics|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ns_technical|taxonomy_term|newsroom_service|form';
  $field_group->group_name = 'group_ns_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_service';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '2',
    'children' => array(
      0 => 'field_newsroom_service_id',
      1 => 'field_service_active',
      2 => 'field_service_type',
      3 => 'field_newsroom_topic',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_ns_technical|taxonomy_term|newsroom_service|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_nt_technical|taxonomy_term|newsroom_item_type|form';
  $field_group->group_name = 'group_nt_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_item_type';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '3',
    'children' => array(
      0 => 'field_newsroom_import_name',
      1 => 'field_newsroom_type',
      2 => 'field_date_label',
      3 => 'field_display_date',
      4 => 'field_newsroom_type_id',
      5 => 'field_direct_link_if_teaser_only',
      6 => 'field_newsroom_highlighted',
      7 => 'field_read_more_text',
      8 => 'field_responsible_person_label',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-nt-technical field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_nt_technical|taxonomy_term|newsroom_item_type|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ntop_technical|taxonomy_term|newsroom_category|form';
  $field_group->group_name = 'group_ntop_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_category';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '2',
    'children' => array(
      0 => 'field_newsroom_category_id',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ntop-technical field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ntop_technical|taxonomy_term|newsroom_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ntop_technical|taxonomy_term|newsroom_topic|form';
  $field_group->group_name = 'group_ntop_technical';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'newsroom_topic';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Fields',
    'weight' => '2',
    'children' => array(
      0 => 'field_newsroom_topic_id',
      1 => 'field_newsroom_category_domain',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ntop-technical field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ntop_technical|taxonomy_term|newsroom_topic|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_recommended_reading|node|newsroom_item|default';
  $field_group->group_name = 'group_recommended_reading';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Recommended reading',
    'weight' => '15',
    'children' => array(),
    'format_type' => 'hidden',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(),
    ),
  );
  $export['group_recommended_reading|node|newsroom_item|default'] = $field_group;

  return $export;
}
