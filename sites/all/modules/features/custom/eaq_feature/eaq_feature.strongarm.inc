<?php
/**
 * @file
 * eaq_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function eaq_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_ask_a_question';
  $strongarm->value = '0';
  $export['comment_anonymous_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_ask_a_question';
  $strongarm->value = '1';
  $export['comment_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_ask_a_question';
  $strongarm->value = 1;
  $export['comment_default_mode_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_ask_a_question';
  $strongarm->value = '50';
  $export['comment_default_per_page_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_ask_a_question';
  $strongarm->value = 1;
  $export['comment_form_location_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_ask_a_question';
  $strongarm->value = '1';
  $export['comment_preview_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_ask_a_question';
  $strongarm->value = 1;
  $export['comment_subject_field_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_sync_node_type_ask_a_question';
  $strongarm->value = array();
  $export['i18n_sync_node_type_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_ask_a_question';
  $strongarm->value = '0';
  $export['language_content_type_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_ask_a_question';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_ask_a_question';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_ask_a_question';
  $strongarm->value = array();
  $export['node_options_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_ask_a_question';
  $strongarm->value = '0';
  $export['node_preview_ask_a_question'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_ask_a_question';
  $strongarm->value = 0;
  $export['node_submitted_ask_a_question'] = $strongarm;

  return $export;
}
