<?php

/**
 * @file
 * nuts_regions.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function nuts_regions_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'nuts_regions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'NUTS regions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'NUTS regions';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '75';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nuts_id' => 'nuts_id',
    'name' => 'name',
    'nuts_code' => 'nuts_code',
    'nuts_level' => 'nuts_level',
    'nuts_country' => 'nuts_country',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nuts_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nuts_code' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nuts_level' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nuts_country' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Field: Taxonomy term: Code (ID) */
  $handler->display->display_options['fields']['nuts_id']['id'] = 'nuts_id';
  $handler->display->display_options['fields']['nuts_id']['table'] = 'field_data_nuts_id';
  $handler->display->display_options['fields']['nuts_id']['field'] = 'nuts_id';
  $handler->display->display_options['fields']['nuts_id']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: NUTS Code */
  $handler->display->display_options['fields']['nuts_code']['id'] = 'nuts_code';
  $handler->display->display_options['fields']['nuts_code']['table'] = 'field_data_nuts_code';
  $handler->display->display_options['fields']['nuts_code']['field'] = 'nuts_code';
  /* Field: Taxonomy term: Level */
  $handler->display->display_options['fields']['nuts_level']['id'] = 'nuts_level';
  $handler->display->display_options['fields']['nuts_level']['table'] = 'field_data_nuts_level';
  $handler->display->display_options['fields']['nuts_level']['field'] = 'nuts_level';
  /* Field: Taxonomy term: NUTS Country */
  $handler->display->display_options['fields']['nuts_country']['id'] = 'nuts_country';
  $handler->display->display_options['fields']['nuts_country']['table'] = 'field_data_nuts_country';
  $handler->display->display_options['fields']['nuts_country']['field'] = 'nuts_country';
  /* Filter criterion: Taxonomy term: Level (nuts_level) */
  $handler->display->display_options['filters']['nuts_level_value']['id'] = 'nuts_level_value';
  $handler->display->display_options['filters']['nuts_level_value']['table'] = 'field_data_nuts_level';
  $handler->display->display_options['filters']['nuts_level_value']['field'] = 'nuts_level_value';
  $handler->display->display_options['filters']['nuts_level_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['nuts_level_value']['expose']['operator_id'] = 'nuts_level_value_op';
  $handler->display->display_options['filters']['nuts_level_value']['expose']['label'] = 'Level';
  $handler->display->display_options['filters']['nuts_level_value']['expose']['operator'] = 'nuts_level_value_op';
  $handler->display->display_options['filters']['nuts_level_value']['expose']['identifier'] = 'nuts_level_value';
  $handler->display->display_options['filters']['nuts_level_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Taxonomy term: NUTS Country (nuts_country) */
  $handler->display->display_options['filters']['nuts_country_value']['id'] = 'nuts_country_value';
  $handler->display->display_options['filters']['nuts_country_value']['table'] = 'field_data_nuts_country';
  $handler->display->display_options['filters']['nuts_country_value']['field'] = 'nuts_country_value';
  $handler->display->display_options['filters']['nuts_country_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['nuts_country_value']['expose']['operator_id'] = 'nuts_country_value_op';
  $handler->display->display_options['filters']['nuts_country_value']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['nuts_country_value']['expose']['operator'] = 'nuts_country_value_op';
  $handler->display->display_options['filters']['nuts_country_value']['expose']['identifier'] = 'nuts_country_value';
  $handler->display->display_options['filters']['nuts_country_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['nuts_country_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['nuts_country_value']['group_info']['label'] = 'Country';
  $handler->display->display_options['filters']['nuts_country_value']['group_info']['identifier'] = 'nuts_country_value';
  // @todo complete list of country filter options;
  $handler->display->display_options['filters']['nuts_country_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Belgium',
      'operator' => '=',
      'value' => 'BE',
    ),
    2 => array(
      'title' => 'The Netherlands',
      'operator' => '=',
      'value' => 'NL',
    ),
    3 => array(
      'title' => 'Germany',
      'operator' => '=',
      'value' => 'DE',
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'nuts-regions';

  $export['nuts_regions'] = $view;

  return $export;
}
