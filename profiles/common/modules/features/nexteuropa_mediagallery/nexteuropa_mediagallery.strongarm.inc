<?php

/**
 * @file
 * nexteuropa_mediagallery.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nexteuropa_mediagallery_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_nexteuropa_mediagallery';
  $strongarm->value = 'edit-workflow';
  $export['additional_settings__active_tab_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['autosave_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_nexteuropa_mediagallery';
  $strongarm->value = '0';
  $export['comment_anonymous_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['comment_default_mode_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_nexteuropa_mediagallery';
  $strongarm->value = '10';
  $export['comment_default_per_page_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['comment_form_location_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_nexteuropa_mediagallery';
  $strongarm->value = '0';
  $export['comment_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_nexteuropa_mediagallery';
  $strongarm->value = '0';
  $export['comment_preview_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['comment_subject_field_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_nexteuropa_mediagallery';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_translation_comment_filter_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['entity_translation_comment_filter_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_translation_hide_translation_links_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['entity_translation_hide_translation_links_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_translation_node_metadata_nexteuropa_mediagallery';
  $strongarm->value = '0';
  $export['entity_translation_node_metadata_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__nexteuropa_mediagallery';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'print' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'media_gallery_colorbox' => array(
        'custom_settings' => FALSE,
      ),
      'media_gallery_page' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'language' => array(
          'weight' => '11',
        ),
        'path' => array(
          'weight' => '4',
        ),
      ),
      'display' => array(
        'language' => array(
          'default' => array(
            'weight' => '0',
            'visible' => FALSE,
          ),
          'media_gallery_colorbox' => array(
            'weight' => '0',
            'visible' => FALSE,
          ),
          'media_gallery_page' => array(
            'weight' => '0',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_extended_nexteuropa_mediagallery';
  $strongarm->value = '1';
  $export['i18n_node_extended_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_options_nexteuropa_mediagallery';
  $strongarm->value = array();
  $export['i18n_node_options_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_sync_node_type_nexteuropa_mediagallery';
  $strongarm->value = array();
  $export['i18n_sync_node_type_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_nexteuropa_mediagallery';
  $strongarm->value = '4';
  $export['language_content_type_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_nexteuropa_mediagallery';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_nexteuropa_mediagallery';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_nexteuropa_mediagallery';
  $strongarm->value = array(
    0 => 'moderation',
    1 => 'revision',
  );
  $export['node_options_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_nexteuropa_mediagallery';
  $strongarm->value = '0';
  $export['node_preview_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['node_submitted_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_display_comment_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['print_html_display_comment_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_display_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['print_html_display_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_display_urllist_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['print_html_display_urllist_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_mail_display_comment_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['print_mail_display_comment_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_mail_display_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['print_mail_display_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_mail_display_urllist_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['print_mail_display_urllist_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_display_comment_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['print_pdf_display_comment_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_display_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['print_pdf_display_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_display_urllist_nexteuropa_mediagallery';
  $strongarm->value = 1;
  $export['print_pdf_display_urllist_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_orientation_nexteuropa_mediagallery';
  $strongarm->value = '';
  $export['print_pdf_orientation_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_size_nexteuropa_mediagallery';
  $strongarm->value = '';
  $export['print_pdf_size_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_nexteuropa_mediagallery';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_expand_fieldset_nexteuropa_mediagallery';
  $strongarm->value = '0';
  $export['scheduler_expand_fieldset_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['scheduler_publish_enable_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_moderation_state_nexteuropa_mediagallery';
  $strongarm->value = 'published';
  $export['scheduler_publish_moderation_state_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_past_date_nexteuropa_mediagallery';
  $strongarm->value = 'error';
  $export['scheduler_publish_past_date_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_required_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['scheduler_publish_required_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_revision_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['scheduler_publish_revision_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_touch_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['scheduler_publish_touch_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_default_time_nexteuropa_mediagallery';
  $strongarm->value = '';
  $export['scheduler_unpublish_default_time_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['scheduler_unpublish_enable_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_moderation_state_nexteuropa_mediagallery';
  $strongarm->value = 'draft';
  $export['scheduler_unpublish_moderation_state_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_required_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['scheduler_unpublish_required_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_revision_nexteuropa_mediagallery';
  $strongarm->value = 0;
  $export['scheduler_unpublish_revision_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_use_vertical_tabs_nexteuropa_mediagallery';
  $strongarm->value = '1';
  $export['scheduler_use_vertical_tabs_nexteuropa_mediagallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_moderation_default_state_nexteuropa_mediagallery';
  $strongarm->value = 'draft';
  $export['workbench_moderation_default_state_nexteuropa_mediagallery'] = $strongarm;

  return $export;
}
