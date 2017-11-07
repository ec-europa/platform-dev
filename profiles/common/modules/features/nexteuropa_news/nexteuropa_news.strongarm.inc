<?php

/**
 * @file
 * nexteuropa_news.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nexteuropa_news_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_nexteuropa_news';
  $strongarm->value = '0';
  $export['comment_anonymous_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_nexteuropa_news';
  $strongarm->value = 1;
  $export['comment_default_mode_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_nexteuropa_news';
  $strongarm->value = '50';
  $export['comment_default_per_page_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_nexteuropa_news';
  $strongarm->value = 1;
  $export['comment_form_location_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_nexteuropa_news';
  $strongarm->value = '1';
  $export['comment_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_nexteuropa_news';
  $strongarm->value = '1';
  $export['comment_preview_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_nexteuropa_news';
  $strongarm->value = 1;
  $export['comment_subject_field_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__nexteuropa_news';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'path' => array(
          'weight' => '5',
        ),
        'language' => array(
          'weight' => '27',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_nexteuropa_news';
  $strongarm->value = '4';
  $export['language_content_type_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_nexteuropa_news';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_nexteuropa_news';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_nexteuropa_news';
  $strongarm->value = array(
    0 => 'moderation',
    1 => 'revision',
  );
  $export['node_options_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_nexteuropa_news';
  $strongarm->value = '1';
  $export['node_preview_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_nexteuropa_news';
  $strongarm->value = 1;
  $export['node_submitted_nexteuropa_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_nexteuropa_news_en_pattern';
  $strongarm->value = '';
  $export['pathauto_node_nexteuropa_news_en_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_nexteuropa_news_pattern';
  $strongarm->value = 'news/[node:source:title]';
  $export['pathauto_node_nexteuropa_news_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_nexteuropa_news_und_pattern';
  $strongarm->value = '';
  $export['pathauto_node_nexteuropa_news_und_pattern'] = $strongarm;

  return $export;
}
