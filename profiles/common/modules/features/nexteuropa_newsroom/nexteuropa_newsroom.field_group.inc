<?php
/**
 * @file
 * nexteuropa_newsroom.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_newsroom_field_group_info() {
  $field_groups = array();

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
      3 => 'field_newsroom_organiser',
      4 => 'field_newsroom_project',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Event information',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-event-info field-group-div section',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_event_info|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_info|node|newsroom_item|event';
  $field_group->group_name = 'group_event_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'event';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Event information',
    'weight' => '1',
    'children' => array(
      0 => 'field_newsroom_item_date',
      1 => 'field_newsroom_organiser',
      2 => 'field_newsroom_item_venue',
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
  $field_groups['group_event_info|node|newsroom_item|event'] = $field_group;

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
    'weight' => '0',
    'children' => array(
      0 => 'field_illustrative_image',
      1 => 'field_newsroom_item_type',
      2 => 'field_teaser',
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
  $field_groups['group_lead|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_lead|node|newsroom_item|event';
  $field_group->group_name = 'group_lead';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'event';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Lead',
    'weight' => '2',
    'children' => array(
      0 => 'field_teaser',
      1 => 'field_illustrative_image',
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
  $field_groups['group_lead|node|newsroom_item|event'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_additional_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_additional_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_item_form_section';
  $field_group->data = array(
    'label' => 'Additional information',
    'weight' => '9',
    'children' => array(
      0 => 'field_newsroom_author',
      1 => 'field_newsroom_item_contact_mail',
      2 => 'field_newsroom_item_contact_text',
      3 => 'field_newsroom_item_type',
      4 => 'field_newsroom_organiser',
      5 => 'field_newsroom_project',
      6 => 'field_nr_project_coordinator',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-additional-info field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_additional_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_basic_info|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_item_form_section';
  $field_group->data = array(
    'label' => 'Basic Information',
    'weight' => '6',
    'children' => array(
      0 => 'field_newsletter_only',
      1 => 'field_newsroom_item_date',
      2 => 'field_newsroom_item_main_link',
      3 => 'field_newsroom_item_rapid_pr',
      4 => 'field_newsroom_item_short_title',
      5 => 'field_newsroom_parent_content',
      6 => 'field_newsroom_short_item',
      7 => 'field_newsroom_teaser_only',
      8 => 'field_related_content',
      9 => 'field_teaser',
      10 => 'title_field',
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
  $field_groups['group_newsroom_item_basic_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_contact|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact',
    'weight' => '5',
    'children' => array(
      0 => 'field_newsroom_item_contact_mail',
      1 => 'field_newsroom_item_contact_text',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-contact field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_contact|node|newsroom_item|default'] = $field_group;

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
  $field_groups['group_newsroom_item_context_info|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_files|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '6',
    'children' => array(
      0 => 'field_newsroom_documents',
      1 => 'field_newsroom_files',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-files field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_files|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_form_section|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_form_section';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Section',
    'weight' => '0',
    'children' => array(
      0 => 'group_newsroom_additional_info',
      1 => 'group_newsroom_item_basic_info',
      2 => 'group_newsroom_item_full_content',
      3 => 'group_newsroom_topics',
      4 => 'group_newsroom_item_language',
      5 => 'group_newsroom_item_technical',
      6 => 'group_newsroom_items_link',
      7 => 'group_newsroom_items_attachments',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-newsroom-item-form-section field-group-tabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_form_section|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_full_content|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_full_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_item_form_section';
  $field_group->data = array(
    'label' => 'Full Content',
    'weight' => '7',
    'children' => array(
      0 => 'body',
      1 => 'field_illustrative_image',
      2 => 'field_newsroom_item_image',
      3 => 'field_newsroom_item_linked_obj',
      4 => 'field_newsroom_item_pre_title',
      5 => 'field_newsroom_item_quote_box',
      6 => 'field_newsroom_item_speaker',
      7 => 'field_newsroom_item_venue',
      8 => 'field_newsroom_location',
      9 => 'field_newsroom_slide',
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
  $field_groups['group_newsroom_item_full_content|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_links|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '3',
    'children' => array(
      0 => 'field_eur_lex_link',
      1 => 'field_newsroom_item_main_link',
      2 => 'field_newsroom_project_website',
      3 => 'field_newsroom_registration_link',
      4 => 'field_ted_link',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-links field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_links|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_main|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_main';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Main content',
    'weight' => '2',
    'children' => array(
      0 => 'body',
      1 => 'field_newsroom_author',
      2 => 'field_newsroom_item_image',
      3 => 'field_newsroom_item_quote_box',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-main field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_main|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_project|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_project';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Project',
    'weight' => '4',
    'children' => array(
      0 => 'field_newsroom_project_acr',
      1 => 'field_nr_project_coordinator',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-project field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_project|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_slide|node|newsroom_item|default';
  $field_group->group_name = 'group_newsroom_item_slide';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Slide',
    'weight' => '8',
    'children' => array(
      0 => 'field_newsroom_slide',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => 'group-newsroom-item-slide field-group-div',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_newsroom_item_slide|node|newsroom_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_item_technical|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_item_technical';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_item_form_section';
  $field_group->data = array(
    'label' => 'Technical fields',
    'weight' => '13',
    'children' => array(
      0 => 'field_newsroom_ec_content',
      1 => 'field_newsroom_item_id',
      2 => 'field_newsroom_project_acr',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-item-technical field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_item_technical|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_items_attachments|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_items_attachments';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_item_form_section';
  $field_group->data = array(
    'label' => 'Attachments',
    'weight' => '12',
    'children' => array(
      0 => 'field_newsroom_documents',
      1 => 'field_newsroom_files',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-items-attachments field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_items_attachments|node|newsroom_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_items_link|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_items_link';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_item_form_section';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '11',
    'children' => array(
      0 => 'field_eur_lex_link',
      1 => 'field_newsroom_item_other_link',
      2 => 'field_newsroom_project_website',
      3 => 'field_newsroom_registration_link',
      4 => 'field_ted_link',
      5 => 'path',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsroom-items-link field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_newsroom_items_link|node|newsroom_item|form'] = $field_group;

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
  $field_groups['group_newsroom_technical|taxonomy_term|newsroom_item_type|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_topics|node|newsroom_item|form';
  $field_group->group_name = 'group_newsroom_topics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_newsroom_item_form_section';
  $field_group->data = array(
    'label' => 'Topics',
    'weight' => '8',
    'children' => array(
      0 => 'field_highlighted_newsroom_topic',
      1 => 'field_newsroom_topics',
      2 => 'field_primary_topic',
      3 => 'field_tags',
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
  $field_groups['group_newsroom_topics|node|newsroom_item|form'] = $field_group;

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
  $field_groups['group_ns_technical|taxonomy_term|newsroom_service|form'] = $field_group;

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
    'label' => 'Technical Newsroom Fields',
    'weight' => '3',
    'children' => array(
      0 => 'field_newsroom_import_name',
      1 => 'field_newsroom_type',
      2 => 'field_newsroom_date_label',
      3 => 'field_newsroom_display_date',
      4 => 'field_newsroom_type_id',
      5 => 'field_newsroom_direct_link',
      6 => 'field_newsroom_highlighted',
      7 => 'field_newsroom_read_more_text',
      8 => 'field_newsroom_resp_person_label',
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
  $export['group_newsroom_technical|taxonomy_term|newsroom_item_type|form'] = $field_group;

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
  $field_groups['group_ntop_technical|taxonomy_term|newsroom_category|form'] = $field_group;

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
    'label' => 'Technical Newsroom Fields',
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
  $export['group_newsroom_technical|taxonomy_term|newsroom_topic|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsroom_event_info|node|newsroom_item|event';
  $field_group->group_name = 'group_newsroom_event_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'newsroom_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Recommended reading',
    'weight' => '7',
    'children' => array(
      0 => 'field_newsroom_item_other_link',
      1 => 'field_newsroom_item_rapid_pr',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-event-info field-group-div',
        'description' => '',
        'classes' => '',
        'id' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_recommended_reading|node|newsroom_item|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional information');
  t('Attachments');
  t('Basic Information');
  t('Contact');
  t('Context Information');
  t('Event information');
  t('Files');
  t('Full Content');
  t('Lead');
  t('Links');
  t('Main content');
  t('Project');
  t('Recommended reading');
  t('Section');
  t('Slide');
  t('Technical Fields');
  t('Technical fields');
  t('Topics');

  return $export;
}
