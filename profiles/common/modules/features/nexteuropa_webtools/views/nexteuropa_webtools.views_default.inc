<?php
/**
 * @file
 * Default views for NextEuropa Token CKEditor.
 */

/**
 * Implements hook_views_default_views().
 */
function nexteuropa_webtools_views_default_views() {
  $views = array();

  // Export code begin.
  $view = new view();
  $view->name = 'nexteuropa_webtools_filter_view';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'bean';
  $view->human_name = 'NextEuropa Token CKEditor: Filter view for webtools.';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'label' => 'label',
    'delta' => 'delta',
    'nexteuropa_webtools_widget_selection' => 'nexteuropa_webtools_widget_selection',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'label' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delta' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nexteuropa_webtools_widget_selection' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Block: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'bean';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Block: descripiton */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'bean';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  /* Field: Block: Block Delta */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'bean';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  /* Field: CKEditor selection: Content */
  $handler->display->display_options['fields']['nexteuropa_webtools_widget_selection']['id'] = 'nexteuropa_webtools_widget_selection';
  $handler->display->display_options['fields']['nexteuropa_webtools_widget_selection']['table'] = 'bean';
  $handler->display->display_options['fields']['nexteuropa_webtools_widget_selection']['field'] = 'nexteuropa_webtools_widget_selection';
  $handler->display->display_options['fields']['nexteuropa_webtools_widget_selection']['label'] = 'Insert as';
  $handler->display->display_options['fields']['nexteuropa_webtools_widget_selection']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nexteuropa_webtools_widget_selection']['label_field'] = 'title';
  $handler->display->display_options['fields']['nexteuropa_webtools_widget_selection']['view_modes'] = array(
    'full' => 'full',
    'teaser' => 'teaser',
    'rss' => 0,
    'search_index' => 0,
    'search_result' => 0,
    'diff_standard' => 0,
    'print' => 0,
    'token' => 0,
  );

  /* Filter criterion: Block: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'bean';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array('webtools');
  $handler->display->display_options['filters']['type']['exposed'] = FALSE;
  /* Filter criterion: Block: title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'bean';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  /* Filter criterion: Block: Label */
  $handler->display->display_options['filters']['label']['id'] = 'label';
  $handler->display->display_options['filters']['label']['table'] = 'bean';
  $handler->display->display_options['filters']['label']['field'] = 'label';
  $handler->display->display_options['filters']['label']['operator'] = 'contains';
  $handler->display->display_options['filters']['label']['exposed'] = TRUE;
  $handler->display->display_options['filters']['label']['expose']['operator_id'] = 'label_op';
  $handler->display->display_options['filters']['label']['expose']['label'] = 'Label';
  $handler->display->display_options['filters']['label']['expose']['operator'] = 'label_op';
  $handler->display->display_options['filters']['label']['expose']['identifier'] = 'label';

  $views[$view->name] = $view;

  return $views;
}
