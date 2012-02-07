<?php
/**
 * @file
 * wiki.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function wiki_filter_default_formats() {
  $formats = array();

  // Exported format: wiki
  $formats['wiki'] = array(
    'format' => 'wiki',
    'name' => 'wiki',
    'cache' => '1',
    'status' => '1',
    'weight' => '0',
    'filters' => array(
      'freelinking' => array(
        'weight' => '0',
        'status' => '1',
        'settings' => array(),
      ),
      'filter_simplewiki' => array(
        'weight' => '0',
        'status' => '1',
        'settings' => array(
          'autotoc' => 0,
        ),
      ),
      'filter_toc' => array(
        'weight' => '0',
        'status' => '1',
        'settings' => array(
          'tableofcontents' => array(
            'tableofcontents_on_off' => array(
              'tableofcontents_hide_table_wiki' => 0,
              'tableofcontents_automatic_wiki' => '0',
              'tableofcontents_min_limit_wiki' => '5',
              'tableofcontents_remove_teaser_wiki' => 1,
            ),
            'tableofcontents_security_options' => array(
              'tableofcontents_allow_override_wiki' => 1,
              'tableofcontents_safe_title_wiki' => 1,
            ),
            'tableofcontents_box' => array(
              'tableofcontents_title_wiki' => 'Table of Contents',
              'tableofcontents_minlevel_wiki' => '2',
              'tableofcontents_maxlevel_wiki' => '3',
              'tableofcontents_hide_show_wiki' => 1,
              'tableofcontents_collapsed_wiki' => 0,
            ),
            'tableofcontents_header' => array(
              'tableofcontents_id_stripping_wiki' => array(
                'digits' => 0,
                'dashes' => 0,
                'periods' => 0,
                'underscores' => 0,
                'colons' => 0,
              ),
              'tableofcontents_identifier_introducer_wiki' => 'header',
              'tableofcontents_id_separator_wiki' => '-',
              'tableofcontents_id_generator_wiki' => 'title',
              'tableofcontents_allowed_tags_wiki' => '<em> <i> <strong> <b> <u> <del> <ins> <sub> <sup> <cite> <strike> <s> <tt> <span> <font> <abbr> <acronym> <dfn> <q> <bdo> <big> <small>',
            ),
            'tableofcontents_other' => array(
              'tableofcontents_comments_wiki' => 0,
              'tableofcontents_comments_level_wiki' => '3',
            ),
            'tableofcontents_back_to_top' => array(
              'tableofcontents_back_to_top_wiki' => '',
              'tableofcontents_back_to_top_location_wiki' => 'bottom',
              'tableofcontents_back_to_top_minlevel_wiki' => '2',
              'tableofcontents_back_to_top_maxlevel_wiki' => '4',
              'tableofcontents_back_to_top_anchor_wiki' => 'toc',
              'tableofcontents_scroll_back_to_top_wiki' => 0,
            ),
            'tableofcontents_numbering' => array(
              'tableofcontents_numbering_wiki' => '0',
              'tableofcontents_number_headers_wiki' => 0,
              'tableofcontents_number_mode_wiki' => '0',
              'tableofcontents_number_start_letter_wiki' => '',
              'tableofcontents_number_separator_wiki' => '.',
              'tableofcontents_number_end_letter_wiki' => '.',
            ),
          ),
        ),
      ),
    ),
  );

  return $formats;
}
