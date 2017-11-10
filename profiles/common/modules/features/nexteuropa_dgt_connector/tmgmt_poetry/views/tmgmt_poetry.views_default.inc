<?php

/**
 * @file
 * Exported views specific for TMGMT Poetry module.
 */

/**
 * Implements hook_views_default_views().
 */
function tmgmt_poetry_views_default_views() {
  // View which displays all job items that belong to a job for tmgmt_poetry.
  $view = new view();
  $view->name = 'tmgmt_poetry_translation_job_items';
  $view->description = 'Displays all job items that belong to a job.';
  $view->tag = 'Translation Management';
  $view->base_table = 'tmgmt_job_item';
  $view->human_name = 'TMGMT Poetry Translation Job Items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Job Items';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'tmgmt_views_job_access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'label' => 'label',
    'plugin' => 'plugin',
    'state' => 'state',
    'changed' => 'changed',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'label' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'plugin' => array(
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
  $handler->display->display_options['empty']['area']['content'] = 'There are no items attached to this translation job.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Translation Management Job Item: Tjid */
  $handler->display->display_options['relationships']['tjid']['id'] = 'tjid';
  $handler->display->display_options['relationships']['tjid']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['relationships']['tjid']['field'] = 'tjid';
  /* Field: Label */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  $handler->display->display_options['fields']['label']['ui_name'] = 'Label';
  /* Field: Translation Management Job Item: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['ui_name'] = 'State';
  /* Field: Progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['ui_name'] = 'Progress';
  /* Field: Translation Management Job Item: Word count */
  $handler->display->display_options['fields']['word_count_1']['id'] = 'word_count_1';
  $handler->display->display_options['fields']['word_count_1']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['word_count_1']['field'] = 'word_count';
  /* Field: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['ui_name'] = 'Changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['ui_name'] = 'Operations';
  $handler->display->display_options['fields']['operations']['element_label_colon'] = FALSE;
  /* Contextual filter: Job Item */
  $handler->display->display_options['arguments']['tjid']['id'] = 'tjid';
  $handler->display->display_options['arguments']['tjid']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['arguments']['tjid']['field'] = 'tjid';
  $handler->display->display_options['arguments']['tjid']['ui_name'] = 'Job Item';
  $handler->display->display_options['arguments']['tjid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['tjid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tjid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tjid']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'reference',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'reference' => 'reference',
    'target_language' => 'target_language',
    'label' => 'label',
    'type' => 'type',
    'state' => 'state',
    'progress' => 'progress',
    'word_count_1' => 'word_count_1',
    'changed' => 'changed',
    'operations' => 'operations',
    'source_language' => 'source_language',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'reference' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'target_language' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'label' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
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
    'progress' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'word_count_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'source_language' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Translation Management Job Item: Tjid */
  $handler->display->display_options['relationships']['tjid']['id'] = 'tjid';
  $handler->display->display_options['relationships']['tjid']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['relationships']['tjid']['field'] = 'tjid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Translation Management Job: Reference */
  $handler->display->display_options['fields']['reference']['id'] = 'reference';
  $handler->display->display_options['fields']['reference']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['reference']['field'] = 'reference';
  $handler->display->display_options['fields']['reference']['relationship'] = 'tjid';
  $handler->display->display_options['fields']['reference']['exclude'] = TRUE;
  /* Field: Translation Management Job: Target_language */
  $handler->display->display_options['fields']['target_language']['id'] = 'target_language';
  $handler->display->display_options['fields']['target_language']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['target_language']['field'] = 'target_language';
  $handler->display->display_options['fields']['target_language']['relationship'] = 'tjid';
  $handler->display->display_options['fields']['target_language']['label'] = 'Language';
  /* Field: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['ui_name'] = 'State';
  /* Field: Progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['ui_name'] = 'Progress';
  $handler->display->display_options['fields']['progress']['label'] = 'Fields progress';
  /* Field: Translation Management Job Item: Word count */
  $handler->display->display_options['fields']['word_count_1']['id'] = 'word_count_1';
  $handler->display->display_options['fields']['word_count_1']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['word_count_1']['field'] = 'word_count';
  /* Field: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['ui_name'] = 'Changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'tmgmt_job_item';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['ui_name'] = 'Operations';
  $handler->display->display_options['fields']['operations']['element_label_colon'] = FALSE;

  $views[$view->name] = $view;
  return $views;
}
