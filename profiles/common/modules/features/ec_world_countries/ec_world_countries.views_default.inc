<?php

/**
 * @file
 * ec_world_countries.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ec_world_countries_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ec_world_countries';
  $view->description = 'List of European Commission world countries as defined in the ec_world_countries module';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'European Commission world countries';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'EC world countries';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer taxonomy';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '55';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'iso_3166_1_alpha_2_code' => 'iso_3166_1_alpha_2_code',
    'name_1' => 'name_1',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'iso_3166_1_alpha_2_code' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Taxonomy term: Parent term */
  $handler->display->display_options['relationships']['parent']['id'] = 'parent';
  $handler->display->display_options['relationships']['parent']['table'] = 'taxonomy_term_hierarchy';
  $handler->display->display_options['relationships']['parent']['field'] = 'parent';
  $handler->display->display_options['relationships']['parent']['required'] = TRUE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: ISO 3166-1 alpha-2 code */
  $handler->display->display_options['fields']['iso_3166_1_alpha_2_code']['id'] = 'iso_3166_1_alpha_2_code';
  $handler->display->display_options['fields']['iso_3166_1_alpha_2_code']['table'] = 'field_data_iso_3166_1_alpha_2_code';
  $handler->display->display_options['fields']['iso_3166_1_alpha_2_code']['field'] = 'iso_3166_1_alpha_2_code';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'parent';
  $handler->display->display_options['fields']['name_1']['label'] = 'Continent';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'ec_world_countries' => 'ec_world_countries',
  );
  /* Filter criterion: Taxonomy term: ISO 3166-1 alpha-2 code (iso_3166_1_alpha_2_code) */
  $handler->display->display_options['filters']['iso_3166_1_alpha_2_code_value']['id'] = 'iso_3166_1_alpha_2_code_value';
  $handler->display->display_options['filters']['iso_3166_1_alpha_2_code_value']['table'] = 'field_data_iso_3166_1_alpha_2_code';
  $handler->display->display_options['filters']['iso_3166_1_alpha_2_code_value']['field'] = 'iso_3166_1_alpha_2_code_value';
  $handler->display->display_options['filters']['iso_3166_1_alpha_2_code_value']['operator'] = 'not empty';
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'parent';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Continent';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    16 => 0,
    14 => 0,
    5 => 0,
    18 => 0,
    15 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    12 => 0,
    13 => 0,
    17 => 0,
    20 => 0,
    21 => 0,
    22 => 0,
    23 => 0,
    24 => 0,
  );
  $handler->display->display_options['filters']['name']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['name']['group_info']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['group_info']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Africa',
      'operator' => '=',
      'value' => 'Africa',
    ),
    2 => array(
      'title' => 'Asia',
      'operator' => '=',
      'value' => 'Asia',
    ),
    3 => array(
      'title' => 'Europe',
      'operator' => '=',
      'value' => 'Europe',
    ),
    4 => array(
      'title' => 'North America',
      'operator' => '=',
      'value' => 'North America',
    ),
    5 => array(
      'title' => 'Oceania',
      'operator' => '=',
      'value' => 'Oceania',
    ),
    6 => array(
      'title' => 'South America',
      'operator' => '=',
      'value' => 'South America',
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ec-world-countries';
  $translatables['ec_world_countries'] = array(
    t('Master'),
    t('EC world countries'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Parent'),
    t('Name'),
    t('ISO 3166-1 alpha-2 code'),
    t('Continent'),
    t('Page'),
  );
  $export['ec_world_countries'] = $view;

  return $export;
}
