<?php

/**
 * @file
 * multisite_mediagallery_community.views_alter.inc
 */

/**
 * Implements hook_views_default_views_alter().
 */
function multisite_mediagallery_community_views_default_views_alter(&$views) {
  if (array_key_exists('galleries', $views)) {
    $view = $views['galleries'];

    /* Display: Page */
    $handler = $view->display['page']->handler;
    /* Filter criterion: Content: Group content visibility (group_content_access) */
    $handler->display->display_options['filters']['group_content_access_value']['id'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['table'] = 'field_data_group_content_access';
    $handler->display->display_options['filters']['group_content_access_value']['field'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['group_content_access_value']['group'] = 1;
    /* Filter criterion: Content: Groups audience (og_group_ref) */
    $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
    $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
    $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 1;

    /* Display: Latest Media block */
    $handler = $view->display['medias_block']->handler;
    /* Filter criterion: Content: Groups audience (og_group_ref) */
    $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
    $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
    $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 1;
    /* Filter criterion: Content: Group content visibility (group_content_access) */
    $handler->display->display_options['filters']['group_content_access_value']['id'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['table'] = 'field_data_group_content_access';
    $handler->display->display_options['filters']['group_content_access_value']['field'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['group_content_access_value']['group'] = 1;

    /* Display: Community Galleries */
    $handler = $view->new_display('page', 'Community Galleries', 'galleries_community');
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['defaults']['header'] = FALSE;
    /* Header: Global: Text area */
    $handler->display->display_options['header']['area']['id'] = 'area';
    $handler->display->display_options['header']['area']['table'] = 'views';
    $handler->display->display_options['header']['area']['field'] = 'area';
    $handler->display->display_options['header']['area']['empty'] = TRUE;
    $handler->display->display_options['header']['area']['format'] = 'full_html';
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    /* Relationship: OG membership: OG membership from Node */
    $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
    $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Video upload */
    $handler->display->display_options['fields']['field_video_upload']['id'] = 'field_video_upload';
    $handler->display->display_options['fields']['field_video_upload']['table'] = 'field_data_field_video_upload';
    $handler->display->display_options['fields']['field_video_upload']['field'] = 'field_video_upload';
    $handler->display->display_options['fields']['field_video_upload']['label'] = '';
    $handler->display->display_options['fields']['field_video_upload']['exclude'] = TRUE;
    $handler->display->display_options['fields']['field_video_upload']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['field_video_upload']['empty'] = '[Empty_gallery]';
    $handler->display->display_options['fields']['field_video_upload']['click_sort_column'] = 'fid';
    $handler->display->display_options['fields']['field_video_upload']['type'] = 'video_formatter_thumbnail';
    $handler->display->display_options['fields']['field_video_upload']['settings'] = array(
      'image_style' => 'square_thumbnail',
      'image_link' => 'content',
    );
    $handler->display->display_options['fields']['field_video_upload']['delta_limit'] = '1';
    $handler->display->display_options['fields']['field_video_upload']['delta_offset'] = '0';
    $handler->display->display_options['fields']['field_video_upload']['delta_reversed'] = TRUE;
    /* Field: Content: Picture upload */
    $handler->display->display_options['fields']['field_picture_upload']['id'] = 'field_picture_upload';
    $handler->display->display_options['fields']['field_picture_upload']['table'] = 'field_data_field_picture_upload';
    $handler->display->display_options['fields']['field_picture_upload']['field'] = 'field_picture_upload';
    $handler->display->display_options['fields']['field_picture_upload']['label'] = '';
    $handler->display->display_options['fields']['field_picture_upload']['exclude'] = TRUE;
    $handler->display->display_options['fields']['field_picture_upload']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['field_picture_upload']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['field_picture_upload']['empty'] = '[Empty_gallery]';
    $handler->display->display_options['fields']['field_picture_upload']['click_sort_column'] = 'fid';
    $handler->display->display_options['fields']['field_picture_upload']['settings'] = array(
      'image_style' => 'square_thumbnail',
      'image_link' => 'content',
    );
    $handler->display->display_options['fields']['field_picture_upload']['delta_limit'] = '1';
    $handler->display->display_options['fields']['field_picture_upload']['delta_offset'] = '0';
    $handler->display->display_options['fields']['field_picture_upload']['delta_reversed'] = TRUE;
    /* Field: Global: Custom text */
    $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
    $handler->display->display_options['fields']['nothing']['table'] = 'views';
    $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
    $handler->display->display_options['fields']['nothing']['label'] = '';
    $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="galleries-item-wrapper">
        [field_picture_upload][field_video_upload]
        </div>';
    $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
    $handler->display->display_options['fields']['title']['element_type'] = 'h3';
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
    /* Field: Content: Body */
    $handler->display->display_options['fields']['body']['id'] = 'body';
    $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
    $handler->display->display_options['fields']['body']['field'] = 'body';
    $handler->display->display_options['fields']['body']['label'] = '';
    $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
    $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
    $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
    $handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
    $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
    /* Field: Content: Nid */
    $handler->display->display_options['fields']['nid']['id'] = 'nid';
    $handler->display->display_options['fields']['nid']['table'] = 'node';
    $handler->display->display_options['fields']['nid']['field'] = 'nid';
    $handler->display->display_options['fields']['nid']['label'] = '';
    $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
    $handler->display->display_options['fields']['nid']['alter']['text'] = '<div id="nb_items">[nid]</div>';
    $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
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
    $handler->display->display_options['path'] = 'galleries_community';
    $handler->display->display_options['tab_options']['weight'] = '0';
  }
}
