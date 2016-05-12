<?php
/**
 * @file
 * nexteuropa_faq.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_faq_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ne_faq_content|node|nexteuropa_faq|form';
  $field_group->group_name = 'group_ne_faq_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_faq';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'title_field',
      1 => 'field_ne_body',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ne-faq-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ne_faq_content|node|nexteuropa_faq|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ne_faq_metadata|node|nexteuropa_faq|form';
  $field_group->group_name = 'group_ne_faq_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_faq';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '2',
    'children' => array(
      0 => 'field_ne_faq_categories',
      1 => 'field_tags',
      2 => 'group_content_access',
      3 => 'og_group_ref',
      4 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ne-faq-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ne_faq_metadata|node|nexteuropa_faq|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Metadata');

  return $field_groups;
}
