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
  /* Field: Cart bundle: Target languages */
  $handler->display->display_options['fields']['target_languages']['id'] = 'target_languages';
  $handler->display->display_options['fields']['target_languages']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['target_languages']['field'] = 'target_languages';
  $handler->display->display_options['fields']['target_languages']['label'] = 'Target Languages';
  /* Field: Cart bundle: Bundle items */
  $handler->display->display_options['fields']['cart_bundle_items']['id'] = 'cart_bundle_items';
  $handler->display->display_options['fields']['cart_bundle_items']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_items']['field'] = 'cart_bundle_items';
  $handler->display->display_options['fields']['cart_bundle_items']['label'] = '';
  $handler->display->display_options['fields']['cart_bundle_items']['element_label_colon'] = FALSE;
  /* Field: Cart bundle: Bundle actions */
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['id'] = 'cart_bundle_items_form_link';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['field'] = 'cart_bundle_items_form_link';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['label'] = '';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';
  /* Filter criterion: Cart bundle: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cart_bundle';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'OPEN';

  /* Display: Cart Bundle | Page */
  $handler = $view->new_display('page', 'Cart Bundle | Page', 'cart_page_view');
  $handler->display->display_options['display_description'] = 'Page view for the Cart Bundle entities';
  $handler->display->display_options['path'] = 'admin/dgt_connector/cart';

  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'bundle_items';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'cart_item';
  $view->human_name = 'Bundle items';
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
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'ciid' => 'ciid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'ciid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Cart Item: Entity title */
  $handler->display->display_options['fields']['entity_title']['id'] = 'entity_title';
  $handler->display->display_options['fields']['entity_title']['table'] = 'cart_item';
  $handler->display->display_options['fields']['entity_title']['field'] = 'entity_title';
  $handler->display->display_options['fields']['entity_title']['label'] = 'Item title';
  /* Field: Cart Item: Entity type */
  $handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['table'] = 'cart_item';
  $handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['label'] = 'Item type';
  /* Field: Cart Item: Changed date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'cart_item';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Item added on';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'd/m/Y G:i:s';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Sort criterion: Cart Item: Changed date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'cart_item';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Contextual filter: cbid */
  $handler->display->display_options['arguments']['cbid']['id'] = 'cbid';
  $handler->display->display_options['arguments']['cbid']['table'] = 'cart_item';
  $handler->display->display_options['arguments']['cbid']['field'] = 'cbid';
  $handler->display->display_options['arguments']['cbid']['ui_name'] = 'cbid';
  $handler->display->display_options['arguments']['cbid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['cbid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['cbid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['cbid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['cbid']['summary_options']['items_per_page'] = '25';

  $views[$view->name] = $view;
  return $views;
}
