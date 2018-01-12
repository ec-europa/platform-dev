<?php

/**
 * @file
 * cce_basic_config.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cce_basic_config_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_article_content|node|article|form';
  $field_group->group_name = 'group_article_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => 0,
    'children' => array(
      0 => 'body',
      1 => 'field_image',
      2 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => 'group-article-content field-group-tab',
        'required_fields' => TRUE,
      ),
    ),
  );
  $export['group_article_content|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_article_metadata|node|article|form';
  $field_group->group_name = 'group_article_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => 5,
    'children' => array(
      0 => 'scheduler_settings',
      1 => 'field_tags',
      2 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => 'group-metadata-content field-group-tab',
        'required_fields' => TRUE,
      ),
    ),
  );
  $export['group_article_metadata|node|article|form'] = $field_group;

  return $export;
}
