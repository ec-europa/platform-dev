<?php
/**
 * @file
 * f_a_q.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function f_a_q_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_f_a_q';
  $strongarm->value = 0;
  $export['comment_anonymous_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_f_a_q';
  $strongarm->value = 1;
  $export['comment_default_mode_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_f_a_q';
  $strongarm->value = '50';
  $export['comment_default_per_page_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_f_a_q';
  $strongarm->value = 0;
  $export['comment_form_location_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_f_a_q';
  $strongarm->value = '2';
  $export['comment_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_f_a_q';
  $strongarm->value = '1';
  $export['comment_preview_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_f_a_q';
  $strongarm->value = 1;
  $export['comment_subject_field_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__f_a_q';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-10',
        ),
        'path' => array(
          'weight' => '32',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_f_a_q';
  $strongarm->value = '2';
  $export['language_content_type_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_f_a_q';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_f_a_q';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_f_a_q';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_f_a_q';
  $strongarm->value = '1';
  $export['node_preview_f_a_q'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_f_a_q';
  $strongarm->value = 1;
  $export['node_submitted_f_a_q'] = $strongarm;

  return $export;
}
