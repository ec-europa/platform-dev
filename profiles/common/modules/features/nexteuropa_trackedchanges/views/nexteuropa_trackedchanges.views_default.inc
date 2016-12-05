<?php
/**
 * @file
 * Code related to module views.
 */

/**
 * Implements hook_views_default_views().
 */
function nexteuropa_trackedchanges_views_default_views() {
  $view = new view();
  $view->name = 'content_tracked_changes';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'netc_info';
  $view->human_name = 'Content tracked changes';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Content tracked changes';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<div class="messages status">No tracked changes detected in any contents.</div>';
  /* Field: Tracked changes info: Concerned entity id */
  $handler->display->display_options['fields']['rel_entity_id']['id'] = 'rel_entity_id';
  $handler->display->display_options['fields']['rel_entity_id']['table'] = 'netc_info';
  $handler->display->display_options['fields']['rel_entity_id']['field'] = 'rel_entity_id';
  $handler->display->display_options['fields']['rel_entity_id']['label'] = '';
  $handler->display->display_options['fields']['rel_entity_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rel_entity_id']['element_label_colon'] = FALSE;
  /* Field: Tracked changes info: Concerned entity URI */
  $handler->display->display_options['fields']['rel_entity_uri']['id'] = 'rel_entity_uri';
  $handler->display->display_options['fields']['rel_entity_uri']['table'] = 'views_entity_netc_info';
  $handler->display->display_options['fields']['rel_entity_uri']['field'] = 'rel_entity_uri';
  $handler->display->display_options['fields']['rel_entity_uri']['label'] = '';
  $handler->display->display_options['fields']['rel_entity_uri']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rel_entity_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rel_entity_uri']['display_as_link'] = FALSE;
  $handler->display->display_options['fields']['rel_entity_uri']['link_to_entity'] = 0;
  /* Field: Tracked changes info: Concerned entity path */
  $handler->display->display_options['fields']['rel_entity_path']['id'] = 'rel_entity_path';
  $handler->display->display_options['fields']['rel_entity_path']['table'] = 'views_entity_netc_info';
  $handler->display->display_options['fields']['rel_entity_path']['field'] = 'rel_entity_path';
  $handler->display->display_options['fields']['rel_entity_path']['label'] = '';
  $handler->display->display_options['fields']['rel_entity_path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rel_entity_path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rel_entity_path']['link_to_entity'] = 0;
  /* Field: Tracked changes info: Concerned entity label */
  $handler->display->display_options['fields']['rel_entity_label']['id'] = 'rel_entity_label';
  $handler->display->display_options['fields']['rel_entity_label']['table'] = 'views_entity_netc_info';
  $handler->display->display_options['fields']['rel_entity_label']['field'] = 'rel_entity_label';
  $handler->display->display_options['fields']['rel_entity_label']['label'] = 'Content title';
  $handler->display->display_options['fields']['rel_entity_label']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['rel_entity_label']['alter']['path'] = '[rel_entity_uri]';
  $handler->display->display_options['fields']['rel_entity_label']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rel_entity_label']['link_to_entity'] = 0;
  /* Field: Tracked changes info: Concerned entity moderation state human name */
  $handler->display->display_options['fields']['rel_entity_state_human_name']['id'] = 'rel_entity_state_human_name';
  $handler->display->display_options['fields']['rel_entity_state_human_name']['table'] = 'views_entity_netc_info';
  $handler->display->display_options['fields']['rel_entity_state_human_name']['field'] = 'rel_entity_state_human_name';
  $handler->display->display_options['fields']['rel_entity_state_human_name']['label'] = 'Content moderation state';
  $handler->display->display_options['fields']['rel_entity_state_human_name']['link_to_entity'] = 0;
  /* Field: Tracked changes info: field_netc_info_languages */
  $handler->display->display_options['fields']['field_netc_info_languages']['id'] = 'field_netc_info_languages';
  $handler->display->display_options['fields']['field_netc_info_languages']['table'] = 'field_data_field_netc_info_languages';
  $handler->display->display_options['fields']['field_netc_info_languages']['field'] = 'field_netc_info_languages';
  $handler->display->display_options['fields']['field_netc_info_languages']['label'] = 'Translation with tracked changes';
  $handler->display->display_options['fields']['field_netc_info_languages']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_netc_info_languages']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_netc_info_languages']['delta_offset'] = '0';
  /* Field: Tracked changes info: Concerned entity bundle human name */
  $handler->display->display_options['fields']['rel_entity_bundle_name']['id'] = 'rel_entity_bundle_name';
  $handler->display->display_options['fields']['rel_entity_bundle_name']['table'] = 'views_entity_netc_info';
  $handler->display->display_options['fields']['rel_entity_bundle_name']['field'] = 'rel_entity_bundle_name';
  $handler->display->display_options['fields']['rel_entity_bundle_name']['label'] = 'Content bundle';
  $handler->display->display_options['fields']['rel_entity_bundle_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rel_entity_bundle_name']['link_to_entity'] = 0;
  /* Field: Tracked changes info: Concerned entity type human name */
  $handler->display->display_options['fields']['rel_entity_type_name']['id'] = 'rel_entity_type_name';
  $handler->display->display_options['fields']['rel_entity_type_name']['table'] = 'views_entity_netc_info';
  $handler->display->display_options['fields']['rel_entity_type_name']['field'] = 'rel_entity_type_name';
  $handler->display->display_options['fields']['rel_entity_type_name']['label'] = 'Content entity type';
  $handler->display->display_options['fields']['rel_entity_type_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rel_entity_type_name']['link_to_entity'] = 0;
  /* Sort criterion: Tracked changes info: Concerned entity label */
  $handler->display->display_options['sorts']['rel_entity_label']['id'] = 'rel_entity_label';
  $handler->display->display_options['sorts']['rel_entity_label']['table'] = 'netc_info';
  $handler->display->display_options['sorts']['rel_entity_label']['field'] = 'rel_entity_label';
  $handler->display->display_options['sorts']['rel_entity_label']['expose']['label'] = 'Concerned entity label';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['path'] = 'admin/config/content/wysiwyg/tracked_changes/list';
  $handler->display->display_options['menu']['title'] = 'Content tracked changes';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $translatables['content_tracked_changes'] = array(
    t('Content tracked changes'),
    t('Content title'),
    t('Content moderation state'),
    t('Translation with tracked changes'),
    t('Content bundle'),
    t('Content entity type'),
    t('Concerned entity label'),
    t('<div class="messages status">No tracked changes detected in any contents</div>'),
  );

  $views[$view->name] = $view;

  return $views;
}
