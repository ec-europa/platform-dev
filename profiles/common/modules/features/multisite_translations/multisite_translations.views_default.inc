<?php

/**
 * @file
 * multisite_translations.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function multisite_translations_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'translation_jobs';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'tmgmt_job';
  $view->human_name = 'translation jobs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'translation jobs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'accept translation jobs';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Translation Management Job: Label */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  /* Field: Translation Management Job: Source_language */
  $handler->display->display_options['fields']['source_language']['id'] = 'source_language';
  $handler->display->display_options['fields']['source_language']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['source_language']['field'] = 'source_language';
  /* Field: Translation Management Job: Target_language */
  $handler->display->display_options['fields']['target_language']['id'] = 'target_language';
  $handler->display->display_options['fields']['target_language']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['target_language']['field'] = 'target_language';
  /* Field: Translation Management Job: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  /* Field: Translation Management Job: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'views_entity_tmgmt_job';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['link_to_entity'] = 0;
  /* Field: Translation Management Job: Translation management job ID */
  $handler->display->display_options['fields']['tjid']['id'] = 'tjid';
  $handler->display->display_options['fields']['tjid']['table'] = 'tmgmt_job';
  $handler->display->display_options['fields']['tjid']['field'] = 'tjid';
  $handler->display->display_options['fields']['tjid']['label'] = 'ID';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/workbench/translation-jobs';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Translation jobs';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  $export['translation_jobs'] = $view;

  return $export;
}
