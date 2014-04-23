<?php
/**
 * @file
 * newsletters.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function newsletters_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_newsletter_metadata|node|simplenews|form';
  $field_group->group_name = 'group_newsletter_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'simplenews';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '10',
    'children' => array(
      0 => 'field_related_contents',
      1 => 'field_tags',
      2 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-newsletter-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_newsletter_metadata|node|simplenews|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_simplenews|node|simplenews|form';
  $field_group->group_name = 'group_simplenews';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'simplenews';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_simplenews_term',
      2 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-simplenews field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_simplenews|node|simplenews|form'] = $field_group;

  return $export;
}
