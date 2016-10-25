<?php
/**
 * @file
 * cce_basic_config.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cce_basic_config_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'clean_url';
  $strongarm->value = TRUE;
  $export['clean_url'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_article';
  $strongarm->value = '0';
  $export['comment_anonymous_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_article';
  $strongarm->value = '2';
  $export['comment_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_article';
  $strongarm->value = 1;
  $export['comment_default_mode_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_article';
  $strongarm->value = 50;
  $export['comment_default_per_page_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_article';
  $strongarm->value = 1;
  $export['comment_form_location_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_article';
  $strongarm->value = '1';
  $export['comment_preview_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_article';
  $strongarm->value = 1;
  $export['comment_subject_field_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'date_api_version';
  $strongarm->value = '7.2';
  $export['date_api_version'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'date_default_timezone';
  $strongarm->value = 'Europe/Berlin';
  $export['date_default_timezone'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'date_first_day';
  $strongarm->value = '0';
  $export['date_first_day'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_long';
  $strongarm->value = 'l, j F, Y - H:i';
  $export['date_format_long'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_medium';
  $strongarm->value = 'D, d/m/Y - H:i';
  $export['date_format_medium'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_short';
  $strongarm->value = 'd/m/Y - H:i';
  $export['date_format_short'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'drupal_http_request_function';
  $strongarm->value = 'chr_curl_http_request';
  $export['drupal_http_request_function'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'file_private_path';
  $strongarm->value = 'sites/default/files/private_files';
  $export['file_private_path'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'filter_fallback_format';
  $strongarm->value = 'plain_text';
  $export['filter_fallback_format'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_select_nodes';
  $strongarm->value = 0;
  $export['i18n_select_nodes'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_string_allowed_formats';
  $strongarm->value = array(
    'full_html' => 'full_html',
    'plain_text' => 'plain_text',
    'filtered_html' => 0,
    'basic_html' => 0,
  );
  $export['i18n_string_allowed_formats'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'image_captcha_bilinear_interpolation';
  $strongarm->value = 1;
  $export['image_captcha_bilinear_interpolation'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_compression_type';
  $strongarm->value = 'min';
  $export['jquery_update_compression_type'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_admin_version';
  $strongarm->value = '1.7';
  $export['jquery_update_jquery_admin_version'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_cdn';
  $strongarm->value = 'none';
  $export['jquery_update_jquery_cdn'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_version';
  $strongarm->value = '1.10';
  $export['jquery_update_jquery_version'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_article';
  $strongarm->value = '2';
  $export['language_content_type_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negociation_views';
  $strongarm->value = 1;
  $export['language_negociation_views'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_check_links_interval';
  $strongarm->value = '2419200';
  $export['linkchecker_check_links_interval'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_check_links_types';
  $strongarm->value = 0;
  $export['linkchecker_check_links_types'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_disable_link_check_for_urls';
  $strongarm->value = 'example.com
example.net
example.org';
  $export['linkchecker_disable_link_check_for_urls'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_extract_from_a';
  $strongarm->value = 1;
  $export['linkchecker_extract_from_a'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_extract_from_img';
  $strongarm->value = 1;
  $export['linkchecker_extract_from_img'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_ignore_response_codes';
  $strongarm->value = '200
206
302
304
401
301
403';
  $export['linkchecker_ignore_response_codes'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_scan_blocks';
  $strongarm->value = 0;
  $export['linkchecker_scan_blocks'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_scan_comments';
  $strongarm->value = 0;
  $export['linkchecker_scan_comments'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'linkchecker_scan_nodetypes';
  $strongarm->value = array(
    'article' => 'article',
    'page' => 'page',
  );
  $export['linkchecker_scan_nodetypes'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'media__file_extensions';
  $strongarm->value = 'jpg jpeg gif png doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv wmv ico';
  $export['media__file_extensions'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'media__wysiwyg_allowed_types';
  $strongarm->value = array(
    0 => 'image',
    1 => 'video',
    2 => 'audio',
    3 => 'document',
  );
  $export['media__wysiwyg_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'media__wysiwyg_browser_plugins';
  $strongarm->value = array(
    0 => 'upload',
    1 => 'media_default--media_browser_1',
    2 => 'media_default--media_browser_my_files',
  );
  $export['media__wysiwyg_browser_plugins'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'media__wysiwyg_upload_directory';
  $strongarm->value = '';
  $export['media__wysiwyg_upload_directory'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_article';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_article';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'multisite_version';
  $strongarm->value = '2.2';
  $export['multisite_version'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_admin_theme';
  $strongarm->value = '0';
  $export['node_admin_theme'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_article';
  $strongarm->value = array(
    0 => 'promote',
    1 => 'moderation',
    2 => 'revision',
  );
  $export['node_options_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_article';
  $strongarm->value = '1';
  $export['node_preview_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_article';
  $strongarm->value = 1;
  $export['node_submitted_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_community_pattern';
  $strongarm->value = 'community/[node:title]';
  $export['pathauto_node_community_pattern'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_link_class';
  $strongarm->value = 'print-page';
  $export['print_html_link_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_link_pos';
  $strongarm->value = array(
    'block' => 'block',
    'link' => 0,
    'corner' => 0,
    'help' => 0,
  );
  $export['print_html_link_pos'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_show_link';
  $strongarm->value = '2';
  $export['print_html_show_link'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_mail_link_pos';
  $strongarm->value = array(
    'block' => 'block',
    'link' => 0,
    'corner' => 0,
    'help' => 0,
  );
  $export['print_mail_link_pos'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_mail_show_link';
  $strongarm->value = '2';
  $export['print_mail_show_link'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_autoconfig';
  $strongarm->value = 1;
  $export['print_pdf_autoconfig'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_book_link';
  $strongarm->value = '1';
  $export['print_pdf_book_link'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_content_disposition';
  $strongarm->value = '2';
  $export['print_pdf_content_disposition'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_display_sys_urllist';
  $strongarm->value = 0;
  $export['print_pdf_display_sys_urllist'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_dompdf_unicode';
  $strongarm->value = 0;
  $export['print_pdf_dompdf_unicode'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_filename';
  $strongarm->value = '[site:name] - [node:title] - [node:changed:custom:Y-m-d]';
  $export['print_pdf_filename'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_font_family';
  $strongarm->value = 'dejavusans';
  $export['print_pdf_font_family'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_font_size';
  $strongarm->value = '10';
  $export['print_pdf_font_size'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_font_subsetting';
  $strongarm->value = 0;
  $export['print_pdf_font_subsetting'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_images_via_file';
  $strongarm->value = 0;
  $export['print_pdf_images_via_file'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_link_class';
  $strongarm->value = 'print-pdf';
  $export['print_pdf_link_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_link_pos';
  $strongarm->value = array(
    'block' => 'block',
    'link' => 0,
    'corner' => 0,
    'help' => 0,
  );
  $export['print_pdf_link_pos'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_link_teaser';
  $strongarm->value = 0;
  $export['print_pdf_link_teaser'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_link_use_alias';
  $strongarm->value = 0;
  $export['print_pdf_link_use_alias'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_node_link_pages';
  $strongarm->value = '';
  $export['print_pdf_node_link_pages'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_node_link_visibility';
  $strongarm->value = '0';
  $export['print_pdf_node_link_visibility'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_page_orientation';
  $strongarm->value = 'portrait';
  $export['print_pdf_page_orientation'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_paper_size';
  $strongarm->value = 'A4';
  $export['print_pdf_paper_size'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_show_link';
  $strongarm->value = '2';
  $export['print_pdf_show_link'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_sys_link_pages';
  $strongarm->value = '';
  $export['print_pdf_sys_link_pages'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_sys_link_visibility';
  $strongarm->value = '1';
  $export['print_pdf_sys_link_visibility'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_wkhtmltopdf_options';
  $strongarm->value = '--footer-font-size 7 --footer-right \'[page]\'';
  $export['print_pdf_wkhtmltopdf_options'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'search_active_modules';
  $strongarm->value = array(
    'apachesolr_search' => 'apachesolr_search',
    'user' => 'user',
    'node' => 0,
  );
  $export['search_active_modules'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'search_default_module';
  $strongarm->value = 'apachesolr_search';
  $export['search_default_module'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'security_allowed_tags';
  $strongarm->value = 'a
abbr
area
audio
b
base
blockquote
br
button
canvas
caption
center
cite
code
col
colgroup
dd
div
dl
em
embed
fieldset
figcaption
figure
font
form
h2
h3
h4
h5
h6
hr
i
iframe
img
input
label
legend
li
map
mark
ol
option
p
pre
q
rp
rt
s
section
select
small
source
span
strike
strong
style
sub
summary
sup
table
tbody
td
textarea
tfoot
th
thead
time
tr
track
tt
u
ul
video
';
  $export['security_allowed_tags'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'node';
  $export['site_frontpage'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_autobuffering';
  $strongarm->value = 1;
  $export['video_autobuffering'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_autoplay';
  $strongarm->value = 0;
  $export['video_autoplay'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_bypass_conversion';
  $strongarm->value = 0;
  $export['video_bypass_conversion'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_convertor';
  $strongarm->value = 'TranscoderAbstractionFactoryFfmpeg';
  $export['video_convertor'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_convert_on_save';
  $strongarm->value = 1;
  $export['video_convert_on_save'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_cron';
  $strongarm->value = 0;
  $export['video_cron'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_dimensions';
  $strongarm->value = '320x180
320x240
384x216
384x288
400x225
400x300
432x243
432x324
480x200
480x270
480x360
512x288
560x315
560x420
640x360
640x480
648x486
720x405
720x480
720x486
720x540
720x576
768x576
852x480
864x486
960x400
960x540
960x720
1024x576
1280x720
1280x960
1280x1080
1440x1080
1920x800
1920x1080';
  $export['video_dimensions'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_ffmpeg_instances';
  $strongarm->value = '5';
  $export['video_ffmpeg_instances'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_ffmpeg_path';
  $strongarm->value = '/ec/prod/app/webroot/flex_home/reference-sources/util/ffmpeg.new/current/bin/ffmpeg';
  $export['video_ffmpeg_path'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_preset';
  $strongarm->value = array(
    0 => 'default_flash_conversion',
  );
  $export['video_preset'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_publish_on_complete';
  $strongarm->value = FALSE;
  $export['video_publish_on_complete'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_queue_timeout';
  $strongarm->value = '900';
  $export['video_queue_timeout'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_thumbnail_count';
  $strongarm->value = '3';
  $export['video_thumbnail_count'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_thumbnail_path';
  $strongarm->value = 'videos/thumbnails';
  $export['video_thumbnail_path'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_transcode_timeout';
  $strongarm->value = '10';
  $export['video_transcode_timeout'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_use_default_thumb';
  $strongarm->value = 0;
  $export['video_use_default_thumb'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'video_use_preset_wxh';
  $strongarm->value = 1;
  $export['video_use_preset_wxh'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_moderation_default_state_article';
  $strongarm->value = 'draft';
  $export['workbench_moderation_default_state_article'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-capitalizator_mode';
  $strongarm->value = 'ucfirst';
  $export['easy_breadcrumb-capitalizator_mode'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-include_home_segment';
  $strongarm->value = 0;
  $export['easy_breadcrumb-include_home_segment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-include_invalid_paths';
  $strongarm->value = 0;
  $export['easy_breadcrumb-include_invalid_paths'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-segments_separator';
  $strongarm->value = '>';
  $export['easy_breadcrumb-segments_separator'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'cce_basic_config_admin_pages';
  $strongarm->value = array(
    0 => 'admin/structure/feature-set',
    1 => 'admin/workbench',
    2 => 'admin/content/comment',
    3 => 'admin/content/media',
    4 => 'admin/content/webform',
    5 => 'admin/structure/block',
    6 => 'admin/help',
  );
  $export['cce_basic_config_admin_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_captcha_distortion_amplitude';
  $strongarm->value = '5';
  $export['image_captcha_distortion_amplitude'] = $strongarm;

  return $export;
}
