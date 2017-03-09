<?php
/**
 * @file
 * nexteuropa_multilingual.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function nexteuropa_multilingual_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'multilingual_recent_translation_job_overview';
  $view->description = 'Gives a bulk operation overview of translation jobs in the system.';
  $view->tag = 'Translation Management';
  $view->base_table = 'tmgmt_job';
  $view->human_name = 'Multilingual: Recent Translation Job Overview';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent translation jobs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'tmgmt_views_job_access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'tjid' => 'tjid',
    'reference' => 'reference',
    'label' => 'label',
    'source_language' => 'source_language',
    'target_language' => 'target_language',
    'state' => 'state',
    'changed' => 'changed',
    'message' => 'message',
    'type' => 'type',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'tjid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'reference' => array(
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
    'source_language' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'target_language' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
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
  $handler->display->display_options['empty']['area']['content'] = 'There are no translation jobs that match the specified filter criteria.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Translator */
  $handler->display->display_options['relationships']['translator']['id'] = 'translator';
  $handler->display->display_options['relationships']['translator']['table'] = 'tmgmt_job';
  $handler->display->display_options['relationships']['translator']['field'] = 'translator';
  $handler->display->display_options['relationships']['translator']['ui_name'] = 'Translator';
  $handler->display->display_options['relationships']['translator']['label'] = 'Translator';
  /* Relationship: Translation Management Job: Job items */
  $handler->display->display_options['relationships']['job_item']['id'] = 'job_item';
  $handler->display->display_options['relationships']['job_item']['table'] = 'tmgmt_job';
  $handler->display->display_options['relationships']['job_item']['field'] = 'job_item';
  /* Relationship: Translation Management Job Item: Translation Management Message */
  $handler->display->display_options['relationships']['tmgmt_message']['id'] = 'tmgmt_message';
  $handler->display->display_options['relationships']['tmgmt_message']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['relationships']['tmgmt_message']['field'] = 'tmgmt_message';
  $handler->display->display_options['relationships']['tmgmt_message']['relationship'] = 'job_item';
  /* Relationship: Content by NID */
  $handler->display->display_options['relationships']['job_item_to_node_by_nid']['id'] = 'job_item_to_node_by_nid';
  $handler->display->display_options['relationships']['job_item_to_node_by_nid']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['relationships']['job_item_to_node_by_nid']['field'] = 'job_item_to_node_by_nid';
  $handler->display->display_options['relationships']['job_item_to_node_by_nid']['relationship'] = 'job_item';
  $handler->display->display_options['relationships']['job_item_to_node_by_nid']['ui_name'] = 'Content by NID';
  /* Field: Translation Management Job: Translation management job ID */
  $handler->display->display_options['fields']['tjid']['id'] = 'tjid';
  $handler->display->display_options['fields']['tjid']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['tjid']['field'] = 'tjid';
  $handler->display->display_options['fields']['tjid']['label'] = '';
  $handler->display->display_options['fields']['tjid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['tjid']['alter']['text'] = 'View';
  $handler->display->display_options['fields']['tjid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['tjid']['alter']['path'] = 'admin/tmgmt/jobs/[tjid]';
  $handler->display->display_options['fields']['tjid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tjid']['separator'] = '';
  /* Field: Translation Management Job: Reference */
  $handler->display->display_options['fields']['reference']['id'] = 'reference';
  $handler->display->display_options['fields']['reference']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['reference']['field'] = 'reference';
  /* Field: Label */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  $handler->display->display_options['fields']['label']['ui_name'] = 'Label';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type_1']['id'] = 'type_1';
  $handler->display->display_options['fields']['type_1']['table'] = 'node';
  $handler->display->display_options['fields']['type_1']['field'] = 'type';
  $handler->display->display_options['fields']['type_1']['relationship'] = 'job_item_to_node_by_nid';
  /* Field: From */
  $handler->display->display_options['fields']['source_language']['id'] = 'source_language';
  $handler->display->display_options['fields']['source_language']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['source_language']['field'] = 'source_language';
  $handler->display->display_options['fields']['source_language']['ui_name'] = 'From';
  $handler->display->display_options['fields']['source_language']['label'] = 'From';
  /* Field: To */
  $handler->display->display_options['fields']['target_language']['id'] = 'target_language';
  $handler->display->display_options['fields']['target_language']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['target_language']['field'] = 'target_language';
  $handler->display->display_options['fields']['target_language']['ui_name'] = 'To';
  $handler->display->display_options['fields']['target_language']['label'] = 'To';
  /* Field: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['ui_name'] = 'State';
  /* Field: Translation Management Job: Progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  /* Field: Translation Management Message: Message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'tmgmt_message';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['relationship'] = 'tmgmt_message';
  /* Field: Translation Management Message: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'tmgmt_message';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['relationship'] = 'tmgmt_message';
  $handler->display->display_options['fields']['type']['label'] = 'Message type';
  /* Field: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['ui_name'] = 'Changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Job updated on';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Sort criterion: Changed */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'tmgmt_job';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['ui_name'] = 'Changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Filter criterion: Translation Management Job: Reference */
  $handler->display->display_options['filters']['reference']['id'] = 'reference';
  $handler->display->display_options['filters']['reference']['table'] = 'tmgmt_job';
  $handler->display->display_options['filters']['reference']['field'] = 'reference';
  $handler->display->display_options['filters']['reference']['operator'] = 'contains';
  $handler->display->display_options['filters']['reference']['group'] = 1;
  $handler->display->display_options['filters']['reference']['exposed'] = TRUE;
  $handler->display->display_options['filters']['reference']['expose']['operator_id'] = 'reference_op';
  $handler->display->display_options['filters']['reference']['expose']['label'] = 'Reference';
  $handler->display->display_options['filters']['reference']['expose']['operator'] = 'reference_op';
  $handler->display->display_options['filters']['reference']['expose']['identifier'] = 'reference';
  $handler->display->display_options['filters']['reference']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Translation Management Job: Label */
  $handler->display->display_options['filters']['label']['id'] = 'label';
  $handler->display->display_options['filters']['label']['table'] = 'tmgmt_job';
  $handler->display->display_options['filters']['label']['field'] = 'label';
  $handler->display->display_options['filters']['label']['operator'] = 'contains';
  $handler->display->display_options['filters']['label']['group'] = 1;
  $handler->display->display_options['filters']['label']['exposed'] = TRUE;
  $handler->display->display_options['filters']['label']['expose']['operator_id'] = 'label_op';
  $handler->display->display_options['filters']['label']['expose']['label'] = 'Label';
  $handler->display->display_options['filters']['label']['expose']['operator'] = 'label_op';
  $handler->display->display_options['filters']['label']['expose']['identifier'] = 'label';
  $handler->display->display_options['filters']['label']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: From */
  $handler->display->display_options['filters']['source_language']['id'] = 'source_language';
  $handler->display->display_options['filters']['source_language']['table'] = 'tmgmt_job';
  $handler->display->display_options['filters']['source_language']['field'] = 'source_language';
  $handler->display->display_options['filters']['source_language']['ui_name'] = 'From';
  $handler->display->display_options['filters']['source_language']['group'] = 1;
  $handler->display->display_options['filters']['source_language']['exposed'] = TRUE;
  $handler->display->display_options['filters']['source_language']['expose']['operator_id'] = 'source_language_op';
  $handler->display->display_options['filters']['source_language']['expose']['label'] = 'From';
  $handler->display->display_options['filters']['source_language']['expose']['operator'] = 'source_language_op';
  $handler->display->display_options['filters']['source_language']['expose']['identifier'] = 'from';
  /* Filter criterion: To */
  $handler->display->display_options['filters']['target_language']['id'] = 'target_language';
  $handler->display->display_options['filters']['target_language']['table'] = 'tmgmt_job';
  $handler->display->display_options['filters']['target_language']['field'] = 'target_language';
  $handler->display->display_options['filters']['target_language']['ui_name'] = 'To';
  $handler->display->display_options['filters']['target_language']['group'] = 1;
  $handler->display->display_options['filters']['target_language']['exposed'] = TRUE;
  $handler->display->display_options['filters']['target_language']['expose']['operator_id'] = 'target_language_op';
  $handler->display->display_options['filters']['target_language']['expose']['label'] = 'To';
  $handler->display->display_options['filters']['target_language']['expose']['operator'] = 'target_language_op';
  $handler->display->display_options['filters']['target_language']['expose']['identifier'] = 'to';
  /* Filter criterion: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'tmgmt_job';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['ui_name'] = 'State';
  $handler->display->display_options['filters']['state']['group'] = 1;
  $handler->display->display_options['filters']['state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['label'] = 'State';
  $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
  /* Filter criterion: Translation Management Message: Message */
  $handler->display->display_options['filters']['message']['id'] = 'message';
  $handler->display->display_options['filters']['message']['table'] = 'tmgmt_message';
  $handler->display->display_options['filters']['message']['field'] = 'message';
  $handler->display->display_options['filters']['message']['relationship'] = 'tmgmt_message';
  $handler->display->display_options['filters']['message']['operator'] = 'contains';
  $handler->display->display_options['filters']['message']['group'] = 1;
  $handler->display->display_options['filters']['message']['exposed'] = TRUE;
  $handler->display->display_options['filters']['message']['expose']['operator_id'] = 'message_op';
  $handler->display->display_options['filters']['message']['expose']['label'] = 'Message';
  $handler->display->display_options['filters']['message']['expose']['operator'] = 'message_op';
  $handler->display->display_options['filters']['message']['expose']['identifier'] = 'message';
  $handler->display->display_options['filters']['message']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Translation Management Message: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'tmgmt_message';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'tmgmt_message';
  $handler->display->display_options['filters']['type']['operator'] = 'contains';
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Message type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/tmgmt/recent-changes';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Recent translation jobs';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Translation';
  $handler->display->display_options['tab_options']['description'] = 'Translation overview';
  $handler->display->display_options['tab_options']['weight'] = -9;
  $handler->display->display_options['tab_options']['name'] = 'management';
  $export['multilingual_recent_translation_job_overview'] = $view;

  return $export;
}
