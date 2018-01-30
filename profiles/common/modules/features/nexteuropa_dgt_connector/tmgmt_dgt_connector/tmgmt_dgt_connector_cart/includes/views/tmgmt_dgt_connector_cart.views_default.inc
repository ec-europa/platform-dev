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
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'target_languages',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'cbid' => 'cbid',
    'target_languages' => 'target_languages',
    'created' => 'created',
    'changed' => 'changed',
    'tjid' => 'tjid',
    'status' => 'status',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'cbid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'target_languages' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
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
    'tjid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h3>No bundles were found.</h3>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Bulk operations: Cart bundle */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = 'Bundle';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::tmgmt_dgt_connector_cart_discard_cart_bundles' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::tmgmt_dgt_connector_cart_send_cart_bundles' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Cart bundle: Label */
  $handler->display->display_options['fields']['cbid']['id'] = 'cbid';
  $handler->display->display_options['fields']['cbid']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cbid']['field'] = 'cbid';
  $handler->display->display_options['fields']['cbid']['label'] = 'Bundle ID';
  $handler->display->display_options['fields']['cbid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['cbid']['separator'] = '';
  /* Field: Cart bundle: Bundle items titles */
  $handler->display->display_options['fields']['cart_bundle_items_titles']['id'] = 'cart_bundle_items_titles';
  $handler->display->display_options['fields']['cart_bundle_items_titles']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_items_titles']['field'] = 'cart_bundle_items_titles';
  /* Field: Cart bundle: Translation job ID */
  $handler->display->display_options['fields']['tjid']['id'] = 'tjid';
  $handler->display->display_options['fields']['tjid']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['tjid']['field'] = 'tjid';
  /* Field: Cart bundle: Creation date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Cart bundle: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Cart bundle: Bundle items link */
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['id'] = 'cart_bundle_items_form_link';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['field'] = 'cart_bundle_items_form_link';
  $handler->display->display_options['fields']['cart_bundle_items_form_link']['label'] = 'Bundle items';
  /* Field: Cart bundle: Target languages */
  $handler->display->display_options['fields']['target_languages']['id'] = 'target_languages';
  $handler->display->display_options['fields']['target_languages']['table'] = 'cart_bundle';
  $handler->display->display_options['fields']['target_languages']['field'] = 'target_languages';
  $handler->display->display_options['fields']['target_languages']['label'] = 'Languages';
  $handler->display->display_options['fields']['target_languages']['exclude'] = TRUE;
  /* Sort criterion: Cart bundle: Changed */
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
  $handler->display->display_options['arguments']['uid']['limit'] = '0';
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

  return $views;
}
