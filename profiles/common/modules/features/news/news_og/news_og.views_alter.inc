<?php
/**
 * @file
 * Code for the News views alter file.
 */

/**
 * Implements hook_views_default_views_alter().
 */
function news_og_views_default_views_alter(&$views) {
  if (array_key_exists('news', $views)) {
    $view = $views['news'];

    /* Display: Defaults */
    $handler = $view->display['default']->handler;
    /* Relationship: OG membership: OG membership from Node */
    $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
    $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';

    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'og_context';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
    );

    $handler = $view->display['page']->handler;
    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
    );
    $handler->display->display_options['defaults']['filters'] = FALSE;

    /* Display: Community Top news */
    $handler = $view->display['top_news']->handler;

    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Top News';
    $handler->display->display_options['defaults']['pager'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['pager']['options']['items_per_page'] = '5';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Nid */
    $handler->display->display_options['fields']['nid']['id'] = 'nid';
    $handler->display->display_options['fields']['nid']['table'] = 'node';
    $handler->display->display_options['fields']['nid']['field'] = 'nid';
    $handler->display->display_options['fields']['nid']['label'] = '';
    $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
    $handler->display->display_options['fields']['nid']['alter']['text'] = '<div class="news" id="news[nid]">';
    $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['text'] = '<h3>[title]</h3>';
    $handler->display->display_options['fields']['title']['element_type'] = 'h3';
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
    /* Field: Content: Body */
    $handler->display->display_options['fields']['body']['id'] = 'body';
    $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
    $handler->display->display_options['fields']['body']['field'] = 'body';
    $handler->display->display_options['fields']['body']['label'] = '';
    $handler->display->display_options['fields']['body']['alter']['max_length'] = '500';
    $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
    $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
    $handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
    $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
    /* Field: Content: Nid */
    $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
    $handler->display->display_options['fields']['nid_1']['table'] = 'node';
    $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
    $handler->display->display_options['fields']['nid_1']['label'] = '';
    $handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = TRUE;
    $handler->display->display_options['fields']['nid_1']['alter']['text'] = '</div>';
    $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['nid_1']['element_default_classes'] = FALSE;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
      3 => 'OR',
    );
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'news' => 'news',
    );
    $handler->display->display_options['filters']['type']['group'] = 1;
    /* Filter criterion: Content: It is a Top News (field_top_news) */
    $handler->display->display_options['filters']['field_top_news_value']['id'] = 'field_top_news_value';
    $handler->display->display_options['filters']['field_top_news_value']['table'] = 'field_data_field_top_news';
    $handler->display->display_options['filters']['field_top_news_value']['field'] = 'field_top_news_value';
    $handler->display->display_options['filters']['field_top_news_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['field_top_news_value']['group'] = 1;
    /* Filter criterion: Workbench Moderation: Published */
    $handler->display->display_options['filters']['published']['id'] = 'published';
    $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['published']['field'] = 'published';
    $handler->display->display_options['filters']['published']['value'] = '1';
    $handler->display->display_options['filters']['published']['group'] = 1;

    /* Filter criterion: Content: Group content visibility (group_content_access) */
    $handler->display->display_options['filters']['group_content_access_value']['id'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['table'] = 'field_data_group_content_access';
    $handler->display->display_options['filters']['group_content_access_value']['field'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['group_content_access_value']['group'] = 3;
    /* Filter criterion: Content: Groups audience (og_group_ref) */
    $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
    $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
    $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 3;

    /* Display: Top news Attachment */
    $handler = $view->display['attachment_1']->handler;

    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['pager']['options']['items_per_page'] = '5';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'list';
    $handler->display->display_options['style_options']['class'] = 'news_list nav nav-tabs ';
    $handler->display->display_options['style_options']['wrapper_class'] = '';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Nid */
    $handler->display->display_options['fields']['nid']['id'] = 'nid';
    $handler->display->display_options['fields']['nid']['table'] = 'node';
    $handler->display->display_options['fields']['nid']['field'] = 'nid';
    $handler->display->display_options['fields']['nid']['label'] = '';
    $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
    $handler->display->display_options['fields']['title']['alter']['path'] = '#news[nid] ';
    $handler->display->display_options['fields']['title']['alter']['absolute'] = TRUE;
    $handler->display->display_options['fields']['title']['alter']['max_length'] = '50';
    $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
      3 => 'OR',
    );
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'news' => 'news',
    );
    $handler->display->display_options['filters']['type']['group'] = 1;
    /* Filter criterion: Content: It is a Top News (field_top_news) */
    $handler->display->display_options['filters']['field_top_news_value']['id'] = 'field_top_news_value';
    $handler->display->display_options['filters']['field_top_news_value']['table'] = 'field_data_field_top_news';
    $handler->display->display_options['filters']['field_top_news_value']['field'] = 'field_top_news_value';
    $handler->display->display_options['filters']['field_top_news_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['field_top_news_value']['group'] = 1;
    /* Filter criterion: Workbench Moderation: Published */
    $handler->display->display_options['filters']['published']['id'] = 'published';
    $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['published']['field'] = 'published';
    $handler->display->display_options['filters']['published']['value'] = '1';
    $handler->display->display_options['filters']['published']['group'] = 1;

    /* Filter criterion: Content: Group content visibility (group_content_access) */
    $handler->display->display_options['filters']['group_content_access_value']['id'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['table'] = 'field_data_group_content_access';
    $handler->display->display_options['filters']['group_content_access_value']['field'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['group_content_access_value']['group'] = 3;
    /* Filter criterion: Content: Groups audience (og_group_ref) */
    $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
    $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
    $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 3;

    /* Display: news_public */
    $handler = $view->new_display('page', 'news_public', 'page_1');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'grid';
    $handler->display->display_options['style_options']['columns'] = '3';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;

    $handler->display->display_options['defaults']['empty'] = FALSE;
    /* No results behavior: Global: Text area */
    $handler->display->display_options['empty']['area']['id'] = 'area';
    $handler->display->display_options['empty']['area']['table'] = 'views';
    $handler->display->display_options['empty']['area']['field'] = 'area';
    $handler->display->display_options['empty']['area']['empty'] = TRUE;
    $handler->display->display_options['empty']['area']['content'] = 'No content found.';
    $handler->display->display_options['empty']['area']['format'] = 'full_html';
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['element_type'] = 'h3';
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    /* Field: Content: Post date */
    $handler->display->display_options['fields']['created']['id'] = 'created';
    $handler->display->display_options['fields']['created']['table'] = 'node';
    $handler->display->display_options['fields']['created']['field'] = 'created';
    $handler->display->display_options['fields']['created']['label'] = '';
    $handler->display->display_options['fields']['created']['alter']['text'] = '<small>[created]</small>';
    $handler->display->display_options['fields']['created']['element_class'] = 'label label-default label-small';
    $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['created']['date_format'] = 'short';
    /* Field: Content: Body */
    $handler->display->display_options['fields']['body']['id'] = 'body';
    $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
    $handler->display->display_options['fields']['body']['field'] = 'body';
    $handler->display->display_options['fields']['body']['label'] = '';
    $handler->display->display_options['fields']['body']['alter']['max_length'] = '600';
    $handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
    $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['body']['element_wrapper_class'] = 'fieldset clearfix';
    $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
    $handler->display->display_options['fields']['body']['settings'] = array(
      'trim_length' => '600',
    );
    /* Field: Content: link */
    $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
    $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
    $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
    $handler->display->display_options['fields']['field_link']['label'] = 'Related link';
    $handler->display->display_options['fields']['field_link']['element_type'] = '0';
    $handler->display->display_options['fields']['field_link']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['field_link']['hide_empty'] = TRUE;
    $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
    $handler->display->display_options['fields']['field_link']['delta_offset'] = '0';
    /* Field: Content: Groups audience */
    $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
    $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
    $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
    $handler->display->display_options['fields']['og_group_ref']['label'] = 'Group';
    $handler->display->display_options['fields']['og_group_ref']['hide_empty'] = TRUE;
    $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
      'link' => 1,
    );
    $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
      3 => 'OR',
    );
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'news' => 'news',
    );
    $handler->display->display_options['filters']['type']['group'] = 1;
    /* Filter criterion: Workbench Moderation: Published */
    $handler->display->display_options['filters']['published']['id'] = 'published';
    $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['published']['field'] = 'published';
    $handler->display->display_options['filters']['published']['value'] = '1';
    $handler->display->display_options['filters']['published']['group'] = 1;

    /* Filter criterion: Content: Group content visibility (group_content_access) */
    $handler->display->display_options['filters']['group_content_access_value']['id'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['table'] = 'field_data_group_content_access';
    $handler->display->display_options['filters']['group_content_access_value']['field'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['group_content_access_value']['group'] = 3;
    /* Filter criterion: Content: Groups audience (og_group_ref) */
    $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
    $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
    $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 3;
    $handler->display->display_options['path'] = 'news_public';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'News';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;

    /* Display: highlight */
    $handler = $view->new_display('block', 'highlight', 'highlight');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Highlighted news';
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    /* Field: Content: Body */
    $handler->display->display_options['fields']['body']['id'] = 'body';
    $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
    $handler->display->display_options['fields']['body']['field'] = 'body';
    $handler->display->display_options['fields']['body']['label'] = '';
    $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
    );
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'news' => 'news',
    );
    $handler->display->display_options['filters']['type']['group'] = 1;

    /* Filter criterion: Workbench Moderation: Published */
    $handler->display->display_options['filters']['published']['id'] = 'published';
    $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['published']['field'] = 'published';
    $handler->display->display_options['filters']['published']['value'] = '1';
    /* Filter criterion: Content: Highlighted (field_highlighted) */
    $handler->display->display_options['filters']['field_highlighted_value']['id'] = 'field_highlighted_value';
    $handler->display->display_options['filters']['field_highlighted_value']['table'] = 'field_data_field_highlighted';
    $handler->display->display_options['filters']['field_highlighted_value']['field'] = 'field_highlighted_value';
    $handler->display->display_options['filters']['field_highlighted_value']['value'] = array(
      1 => '1',
    );

  }
}
