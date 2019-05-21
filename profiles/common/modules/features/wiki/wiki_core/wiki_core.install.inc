<?php

/**
 * @file
 * Helper functions for installing and uninstalling updates for basic config.
 */

/**
 * Set the field instance settings for the "comment_body" field.
 *
 * It allows "soft" configuring the default settings of the field instance.
 */
function _wiki_core_comment_body_field_instance_add() {
  // Exported field_instance: 'comment-comment_node_wiki-comment_body'.
  $field_instances['comment-comment_node_wiki-comment_body'] = array(
    'bundle' => 'comment_node_wiki',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => 1,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'basic_html' => 'basic_html',
          'filtered_html' => 0,
          'full_html' => 0,
          'plain_text' => 0,
          'wiki' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'basic_html' => array(
              'weight' => 5,
            ),
            'filtered_html' => array(
              'weight' => -9,
            ),
            'full_html' => array(
              'weight' => -10,
            ),
            'plain_text' => array(
              'weight' => -8,
            ),
            'wiki' => array(
              'weight' => 0,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_field_privacy' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  field_create_instance($field_instances['comment-comment_node_wiki-comment_body']);
}
