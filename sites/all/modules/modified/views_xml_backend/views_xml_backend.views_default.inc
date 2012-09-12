<?php
/**
 * @file
 * Default example view.
 */

/**
 * Implements hook_views_default_views().
 */
function views_xml_backend_views_default_views() {
  $views = array();
  // Export code begin.

  $view = new view;
  $view->name = 'views_project_releases';
  $view->description = 'Releases for a project by API compatability version';
  $view->tag = 'default';
  $view->base_table = 'xml';
  $view->human_name = 'Views project releases';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Views project releases';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['xml_file'] = 'http://updates.drupal.org/release-history/views/6.x';
  $handler->display->display_options['query']['options']['row_xpath'] = '/project/releases/release';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'text' => 'text',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'text' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: download_link: Text */
  $handler->display->display_options['fields']['text_1']['id'] = 'text_1';
  $handler->display->display_options['fields']['text_1']['table'] = 'xml';
  $handler->display->display_options['fields']['text_1']['field'] = 'text';
  $handler->display->display_options['fields']['text_1']['label'] = 'Download URL';
  $handler->display->display_options['fields']['text_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['text_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_1']['xpath_selector'] = 'download_link';
  /* Field: name: Text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'xml';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['text']['alter']['path'] = '[text_1] ';
  $handler->display->display_options['fields']['text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text']['alter']['external'] = 1;
  $handler->display->display_options['fields']['text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text']['xpath_selector'] = 'name';
  /* Field: mdhash: Text */
  $handler->display->display_options['fields']['text_2']['id'] = 'text_2';
  $handler->display->display_options['fields']['text_2']['table'] = 'xml';
  $handler->display->display_options['fields']['text_2']['field'] = 'text';
  $handler->display->display_options['fields']['text_2']['label'] = 'MD5 Hash';
  $handler->display->display_options['fields']['text_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_2']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_2']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_2']['xpath_selector'] = 'mdhash';
  /* Field: version_major: Text */
  $handler->display->display_options['fields']['text_4']['id'] = 'text_4';
  $handler->display->display_options['fields']['text_4']['table'] = 'xml';
  $handler->display->display_options['fields']['text_4']['field'] = 'text';
  $handler->display->display_options['fields']['text_4']['label'] = 'Version major';
  $handler->display->display_options['fields']['text_4']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_4']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_4']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_4']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_4']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_4']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_4']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_4']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_4']['xpath_selector'] = 'version_major';
  $handler->display->display_options['fields']['text_4']['multiple'] = 0;
  /* Field: terms/term/value: Text */
  $handler->display->display_options['fields']['text_3']['id'] = 'text_3';
  $handler->display->display_options['fields']['text_3']['table'] = 'xml';
  $handler->display->display_options['fields']['text_3']['field'] = 'text';
  $handler->display->display_options['fields']['text_3']['label'] = 'Release type';
  $handler->display->display_options['fields']['text_3']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_3']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_3']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_3']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_3']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_3']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_3']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_3']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_3']['xpath_selector'] = 'terms/term/value';
  $handler->display->display_options['fields']['text_3']['multiple'] = 1;
  /* Filter criterion: version_major: Numeric */
  $handler->display->display_options['filters']['numeric']['id'] = 'numeric';
  $handler->display->display_options['filters']['numeric']['table'] = 'xml';
  $handler->display->display_options['filters']['numeric']['field'] = 'numeric';
  $handler->display->display_options['filters']['numeric']['exposed'] = TRUE;
  $handler->display->display_options['filters']['numeric']['expose']['operator_id'] = 'numeric_op';
  $handler->display->display_options['filters']['numeric']['expose']['label'] = 'Major Version';
  $handler->display->display_options['filters']['numeric']['expose']['operator'] = 'numeric_op';
  $handler->display->display_options['filters']['numeric']['expose']['identifier'] = 'numeric';
  $handler->display->display_options['filters']['numeric']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['numeric']['xpath_selector'] = 'version_major';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'views-project-releases';

  // Export code end.
  $views[$view->name] = $view;

$view = new view;
$view->name = 'rss';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'xml';
$view->human_name = 'Drupal Planet';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Drupal Planet';
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['xml_file'] = 'http://drupal.org/planet/rss.xml';
$handler->display->display_options['query']['options']['row_xpath'] = '//item';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['row_options']['inline'] = array(
  'text_1' => 'text_1',
  'text' => 'text',
);
$handler->display->display_options['row_options']['hide_empty'] = 0;
$handler->display->display_options['row_options']['default_field_elements'] = 1;
/* Field: link: Text */
$handler->display->display_options['fields']['text_1']['id'] = 'text_1';
$handler->display->display_options['fields']['text_1']['table'] = 'xml';
$handler->display->display_options['fields']['text_1']['field'] = 'text';
$handler->display->display_options['fields']['text_1']['label'] = '';
$handler->display->display_options['fields']['text_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['text_1']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['external'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['text_1']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['text_1']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['trim'] = 0;
$handler->display->display_options['fields']['text_1']['alter']['html'] = 0;
$handler->display->display_options['fields']['text_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['text_1']['element_default_classes'] = 1;
$handler->display->display_options['fields']['text_1']['hide_empty'] = 0;
$handler->display->display_options['fields']['text_1']['empty_zero'] = 0;
$handler->display->display_options['fields']['text_1']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['text_1']['xpath_selector'] = 'link';
/* Field: title: Text */
$handler->display->display_options['fields']['text']['id'] = 'text';
$handler->display->display_options['fields']['text']['table'] = 'xml';
$handler->display->display_options['fields']['text']['field'] = 'text';
$handler->display->display_options['fields']['text']['label'] = '';
$handler->display->display_options['fields']['text']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['text']['alter']['make_link'] = 1;
$handler->display->display_options['fields']['text']['alter']['path'] = '[text_1]';
$handler->display->display_options['fields']['text']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['text']['alter']['external'] = 0;
$handler->display->display_options['fields']['text']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['text']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['text']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['text']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['text']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['text']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['text']['alter']['trim'] = 0;
$handler->display->display_options['fields']['text']['alter']['html'] = 0;
$handler->display->display_options['fields']['text']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['text']['element_default_classes'] = 1;
$handler->display->display_options['fields']['text']['hide_empty'] = 0;
$handler->display->display_options['fields']['text']['empty_zero'] = 0;
$handler->display->display_options['fields']['text']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['text']['xpath_selector'] = 'title';
/* Field: pubDate: Text */
$handler->display->display_options['fields']['text_3']['id'] = 'text_3';
$handler->display->display_options['fields']['text_3']['table'] = 'xml';
$handler->display->display_options['fields']['text_3']['field'] = 'text';
$handler->display->display_options['fields']['text_3']['label'] = '';
$handler->display->display_options['fields']['text_3']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['external'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['text_3']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['text_3']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['trim'] = 0;
$handler->display->display_options['fields']['text_3']['alter']['html'] = 0;
$handler->display->display_options['fields']['text_3']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['text_3']['element_default_classes'] = 1;
$handler->display->display_options['fields']['text_3']['hide_empty'] = 0;
$handler->display->display_options['fields']['text_3']['empty_zero'] = 0;
$handler->display->display_options['fields']['text_3']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['text_3']['xpath_selector'] = 'pubDate';
/* Field: description: Text */
$handler->display->display_options['fields']['text_2']['id'] = 'text_2';
$handler->display->display_options['fields']['text_2']['table'] = 'xml';
$handler->display->display_options['fields']['text_2']['field'] = 'text';
$handler->display->display_options['fields']['text_2']['label'] = '';
$handler->display->display_options['fields']['text_2']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['external'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['text_2']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['text_2']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['trim'] = 0;
$handler->display->display_options['fields']['text_2']['alter']['html'] = 0;
$handler->display->display_options['fields']['text_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['text_2']['element_default_classes'] = 1;
$handler->display->display_options['fields']['text_2']['hide_empty'] = 0;
$handler->display->display_options['fields']['text_2']['empty_zero'] = 0;
$handler->display->display_options['fields']['text_2']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['text_2']['xpath_selector'] = 'description';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'drupal-planet';

  $views[$view->name] = $view;

  return $views;
}
