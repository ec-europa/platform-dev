<?php

/**
 * @file
 * Views for the translation cart functionality.
 */

/**
 * Implements hook_views_default_views().
 */
function tmgmt_dgt_connector_cart_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'tmgmt_dgt_connector_bundle';
  $view->description = 'TMGMT DGT Connector Cart View.';
  $view->tag = 'default';
  $view->base_table = 'cart_bundle';
  $view->human_name = 'TMGMT DGT Connector Bundle';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Translations Cart';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access to the dgt connector cart';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table_rowspan';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'cart_bundle_info',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
    1 => array(
      'field' => 'cart_bundle_items_form_link',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'cart_bundle_info' => 'cart_bundle_info',
    'entity_title' => 'entity_title',
    'changed' => 'changed',
    'entity_type' => 'entity_type',
    'cart_bundle_items_form_link' => 'cart_bundle_items_form_link',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'cart_bundle_info' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'cart_bundle_items_form_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['rowspan'] = 1;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h3>No bundles were found.</h3>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Cart bundle: Cart Item */
  $handler->display->display_options['relationships']['cart_item']['id'] = 'cart_item';
  $handler->display->display_options['relationships']['cart_item']['table'] = 'cart_bundle';
  $handler->display->display_options['relationships']['cart_item']['field'] = 'cart_item';
  /* Field: Cart bundle: Bundle information */
  $handler->display->display_options['fields']['cart_bundle_info']['id'] = 'cart_bundle_info';
  $handler->display->display_options['fields']['cart_bundle_info']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_info']['field'] = 'cart_bundle_info';
  $handler->display->display_options['fields']['cart_bundle_info']['label'] = 'Bundle details';
  /* Field: Cart Item: Entity title */
  $handler->display->display_options['fields']['entity_title']['id'] = 'entity_title';
  $handler->display->display_options['fields']['entity_title']['table'] = 'cart_item';
  $handler->display->display_options['fields']['entity_title']['field'] = 'entity_title';
  $handler->display->display_options['fields']['entity_title']['relationship'] = 'cart_item';
  $handler->display->display_options['fields']['entity_title']['label'] = 'Bundle item';
  /* Field: Cart Item: Entity type */
  $handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['table'] = 'cart_item';
  $handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['relationship'] = 'cart_item';
  $handler->display->display_options['fields']['entity_type']['label'] = 'Item type';
  /* Field: Cart Item: Changed date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'cart_item';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['relationship'] = 'cart_item';
  $handler->display->display_options['fields']['changed']['label'] = 'Added on';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'd/m/Y G:i:s';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Cart bundle: Bundle actions */
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['id'] = 'cart_bundle_items_form_link';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['field'] = 'cart_bundle_items_form_link';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['label'] = 'Actions';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['element_label_colon'] = FALSE;
  /* Sort criterion: Cart bundle: Changed date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'cart_bundle';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Contextual filter: Cart bundle: Cart Bundle ID */
  $handler->display->display_options['arguments']['cbid']['id'] = 'cbid';
  $handler->display->display_options['arguments']['cbid']['table'] = 'cart_bundle';
  $handler->display->display_options['arguments']['cbid']['field'] = 'cbid';
  $handler->display->display_options['arguments']['cbid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['cbid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['cbid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['cbid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['cbid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['cbid']['limit'] = '0';
  /* Filter criterion: Cart bundle: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cart_bundle';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'OPEN';

  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'tmgmt_dgt_connector_bundle_info';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'cart_bundle';
  $view->human_name = 'TMGMT DGT Connector Bundle Info';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Cart bundle: Cart Bundle ID */
  $handler->display->display_options['fields']['cbid']['id'] = 'cbid';
  $handler->display->display_options['fields']['cbid']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cbid']['field'] = 'cbid';
  $handler->display->display_options['fields']['cbid']['label'] = 'ID';
  /* Field: Cart bundle: Target languages */
  $handler->display->display_options['fields']['target_languages']['id'] = 'target_languages';
  $handler->display->display_options['fields']['target_languages']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['target_languages']['field'] = 'target_languages';
  /* Field: Cart bundle: Bundle items character count */
  $handler->display->display_options['fields']['cart_bundle_items_count']['id'] = 'cart_bundle_items_count';
  $handler->display->display_options['fields']['cart_bundle_items_count']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_items_count']['field'] = 'cart_bundle_items_count';
  $handler->display->display_options['fields']['cart_bundle_items_count']['label'] = 'Character count';
  /* Field: Cart bundle: Creation date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'd/m/Y G:i:s';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Contextual filter: Cart bundle: Cart Bundle ID */
  $handler->display->display_options['arguments']['cbid']['id'] = 'cbid';
  $handler->display->display_options['arguments']['cbid']['table'] = 'cart_bundle';
  $handler->display->display_options['arguments']['cbid']['field'] = 'cbid';
  $handler->display->display_options['arguments']['cbid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['cbid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['cbid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['cbid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['cbid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['cbid']['limit'] = '0';

  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'dgt_connector_cart_view';
  $view->description = 'TMGMT DGT Connector Cart View.';
  $view->tag = 'default';
  $view->base_table = 'cart_bundle';
  $view->human_name = 'TMGMT DGT Connector Cart View';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Translations Cart';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access to the dgt connector cart';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h3>No bundles were found.</h3>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Cart bundle: Bundle table */
  $handler->display->display_options['fields']['cart_bundle_table']['id'] = 'cart_bundle_table';
  $handler->display->display_options['fields']['cart_bundle_table']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_table']['field'] = 'cart_bundle_table';
  $handler->display->display_options['fields']['cart_bundle_table']['label'] = '';
  $handler->display->display_options['fields']['cart_bundle_table']['element_label_colon'] = FALSE;
  /* Sort criterion: Cart bundle: Changed date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'cart_bundle';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Contextual filter: Cart bundle: User ID */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'cart_bundle';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Cart bundle: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cart_bundle';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'OPEN';

  /* Display: Cart Bundle | Page */
  $handler = $view->new_display('page', 'Cart Bundle | Page', 'cart_page_view');
  $handler->display->display_options['display_description'] = 'Page view for the Cart Bundle entities';
  $handler->display->display_options['path'] = 'admin/tmgmt/dgt_cart';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Small Jobs Cart';
  $handler->display->display_options['menu']['weight'] = '21';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;

  return $views;
}
