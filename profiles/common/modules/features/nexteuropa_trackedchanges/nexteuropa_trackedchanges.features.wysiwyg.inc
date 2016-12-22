<?php
/**
 * @file
 * nexteuropa_trackedchanges.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function nexteuropa_trackedchanges_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: full_html_track.
  $profiles['full_html_track'] = array(
    'format' => 'full_html_track',
    'editor' => 'ckeditor',
    'settings' => array(
      'default' => TRUE,
      'user_choose' => FALSE,
      'show_toggle' => TRUE,
      'theme' => 'advanced',
      'language' => 'en',
      'access' => 1,
      'access_pages' => 'node/*
user/*
comment/*',
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'Italic' => 1,
          'Underline' => 1,
          'JustifyLeft' => 1,
          'JustifyCenter' => 1,
          'JustifyRight' => 1,
          'JustifyBlock' => 1,
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Outdent' => 1,
          'Indent' => 1,
          'Undo' => 1,
          'Link' => 1,
          'Unlink' => 1,
          'Anchor' => 1,
          'TextColor' => 1,
          'BGColor' => 1,
          'Blockquote' => 1,
          'Source' => 1,
          'HorizontalRule' => 1,
          'PasteFromWord' => 1,
          'ShowBlocks' => 1,
          'Format' => 1,
          'Font' => 1,
          'FontSize' => 1,
          'Styles' => 1,
          'Table' => 1,
          'Smiley' => 1,
          'Maximize' => 1,
        ),
        'drupal_path' => array(
          'Link' => 1,
        ),
        'drupal' => array(
          'media' => 1,
          'break' => 1,
        ),
        'nexteuropa_token_ckeditor' => array(
          'NextEuropaToken' => 1,
        ),
        'multisite_wysiwyg_link_hreflang' => array(
          'Link' => 1,
        ),
        'lite' => array(
          'lite_AcceptAll' => 1,
          'lite_RejectAll' => 1,
          'lite_AcceptOne' => 1,
          'lite_RejectOne' => 1,
          'lite_ToggleShow' => 1,
          'lite_ToggleTracking' => 1,
        ),
      ),
      'toolbar_loc' => 'top',
      'toolbar_align' => 'left',
      'path_loc' => 'bottom',
      'resizing' => TRUE,
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'verify_html' => TRUE,
      'preformatted' => FALSE,
      'convert_fonts_to_spans' => TRUE,
      'remove_linebreaks' => TRUE,
      'apply_source_formatting' => FALSE,
      'paste_auto_cleanup_on_paste' => FALSE,
      'css_setting' => 'theme',
      'css_path' => NULL,
      'css_classes' => NULL,
    ),
    'entity_type' => 'wysiwyg_profile',
    'rdf_mapping' => array(),
  );

  return $profiles;
}
