<?php
/**
 * @file
 * nexteuropa_news.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_news_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ne_news_content|node|nexteuropa_news|form';
  $field_group->group_name = 'group_ne_news_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_background_information',
      2 => 'field_description',
      3 => 'field_introduction',
      4 => 'field_long_title',
      5 => 'title_field',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ne-news-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ne_news_content|node|nexteuropa_news|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ne_news_metadata|node|nexteuropa_news|form';
  $field_group->group_name = 'group_ne_news_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '1',
    'children' => array(
      0 => 'field_sources',
      1 => 'group_content_access',
      2 => 'og_group_ref',
      3 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ne-news-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ne_news_metadata|node|nexteuropa_news|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Metadata');

  return $field_groups;
}
