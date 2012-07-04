<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function gallerymedia_core_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('multisite_settings_core', $views)) {
    $view=$views['multisite_settings_core'];
	
    /* Display: Latest content block */
   // $handler = $view->display['block_latest']->handler;

    // /* Field: Content: Description */
    // $handler->display->display_options['fields']['media_gallery_description']['id'] = 'media_gallery_description';
    // $handler->display->display_options['fields']['media_gallery_description']['table'] = 'field_data_media_gallery_description';
    // $handler->display->display_options['fields']['media_gallery_description']['field'] = 'media_gallery_description';
    // $handler->display->display_options['fields']['media_gallery_description']['label'] = '';
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['alter_text'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['make_link'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['absolute'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['external'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['replace_spaces'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['trim_whitespace'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['nl2br'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['max_length'] = '150';
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['word_boundary'] = 1;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['ellipsis'] = 1;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['strip_tags'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['trim'] = 1;
    // $handler->display->display_options['fields']['media_gallery_description']['alter']['html'] = 1;
    // $handler->display->display_options['fields']['media_gallery_description']['element_label_colon'] = FALSE;
    // $handler->display->display_options['fields']['media_gallery_description']['element_default_classes'] = 1;
    // $handler->display->display_options['fields']['media_gallery_description']['hide_empty'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['empty_zero'] = 0;
    // $handler->display->display_options['fields']['media_gallery_description']['hide_alter_empty'] = 1;
    // $handler->display->display_options['fields']['media_gallery_description']['field_api_classes'] = 0;
    // $handler->display->display_options['defaults']['filters'] = FALSE;

        


/* Display: Latest Media block */
$handler = $view->new_display('block', 'Latest Media block', 'block_m');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['style_options']['row_class'] = 'item';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['row_options']['hide_empty'] = 0;
$handler->display->display_options['row_options']['default_field_elements'] = 0;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title']['alter']['external'] = 0;
$handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title']['alter']['html'] = 0;
$handler->display->display_options['fields']['title']['element_type'] = 'p';
$handler->display->display_options['fields']['title']['element_class'] = 'carousel-caption';
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['element_default_classes'] = 0;
$handler->display->display_options['fields']['title']['hide_empty'] = 0;
$handler->display->display_options['fields']['title']['empty_zero'] = 0;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['title']['link_to_node'] = 1;
/* Field: Content: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['nid']['alter']['external'] = 0;
$handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
$handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
$handler->display->display_options['fields']['nid']['alter']['html'] = 0;
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nid']['element_default_classes'] = 0;
$handler->display->display_options['fields']['nid']['hide_empty'] = 0;
$handler->display->display_options['fields']['nid']['empty_zero'] = 0;
$handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['nid']['link_to_node'] = 0;
/* Field: Content: Picture upload */
$handler->display->display_options['fields']['field_picture_upload']['id'] = 'field_picture_upload';
$handler->display->display_options['fields']['field_picture_upload']['table'] = 'field_data_field_picture_upload';
$handler->display->display_options['fields']['field_picture_upload']['field'] = 'field_picture_upload';
$handler->display->display_options['fields']['field_picture_upload']['label'] = '';
$handler->display->display_options['fields']['field_picture_upload']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_picture_upload']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['external'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['field_picture_upload']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['field_picture_upload']['alter']['more_link'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['trim'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['alter']['html'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_picture_upload']['element_default_classes'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['empty'] = '[Empty_gallery]';
$handler->display->display_options['fields']['field_picture_upload']['hide_empty'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['empty_zero'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['field_picture_upload']['click_sort_column'] = 'fid';
$handler->display->display_options['fields']['field_picture_upload']['settings'] = array(
  'image_style' => 'landscape',
  'image_link' => 'content',
);
$handler->display->display_options['fields']['field_picture_upload']['group_rows'] = 1;
$handler->display->display_options['fields']['field_picture_upload']['delta_limit'] = '1';
$handler->display->display_options['fields']['field_picture_upload']['delta_offset'] = '0';
$handler->display->display_options['fields']['field_picture_upload']['delta_reversed'] = 1;
$handler->display->display_options['fields']['field_picture_upload']['delta_first_last'] = 0;
$handler->display->display_options['fields']['field_picture_upload']['field_api_classes'] = 0;
/* Field: Content: Video upload */
$handler->display->display_options['fields']['field_video_upload']['id'] = 'field_video_upload';
$handler->display->display_options['fields']['field_video_upload']['table'] = 'field_data_field_video_upload';
$handler->display->display_options['fields']['field_video_upload']['field'] = 'field_video_upload';
$handler->display->display_options['fields']['field_video_upload']['label'] = '';
$handler->display->display_options['fields']['field_video_upload']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_video_upload']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['external'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['field_video_upload']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['field_video_upload']['alter']['more_link'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['trim'] = 0;
$handler->display->display_options['fields']['field_video_upload']['alter']['html'] = 0;
$handler->display->display_options['fields']['field_video_upload']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_video_upload']['element_default_classes'] = 1;
$handler->display->display_options['fields']['field_video_upload']['empty'] = '[Empty_gallery]';
$handler->display->display_options['fields']['field_video_upload']['hide_empty'] = 0;
$handler->display->display_options['fields']['field_video_upload']['empty_zero'] = 0;
$handler->display->display_options['fields']['field_video_upload']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['field_video_upload']['click_sort_column'] = 'fid';
$handler->display->display_options['fields']['field_video_upload']['type'] = 'video_formatter_thumbnail';
$handler->display->display_options['fields']['field_video_upload']['settings'] = array(
  'image_style' => 'landscape',
  'image_link' => 'content',
);
$handler->display->display_options['fields']['field_video_upload']['group_rows'] = 1;
$handler->display->display_options['fields']['field_video_upload']['delta_limit'] = '1';
$handler->display->display_options['fields']['field_video_upload']['delta_offset'] = '0';
$handler->display->display_options['fields']['field_video_upload']['delta_reversed'] = 0;
$handler->display->display_options['fields']['field_video_upload']['delta_first_last'] = 0;
$handler->display->display_options['fields']['field_video_upload']['field_api_classes'] = 0;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_picture_upload][field_video_upload]';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
$handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
$handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
$handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'gallerymedia' => 'gallerymedia',
);
$handler->display->display_options['filters']['type']['group'] = 1;
$translatables['multisite_standard'] = array(
  t('Master'),
  t('Latest Content'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Latest Content block'),
  t('Site wide block displaying latest content.'),
  t(' <i class="icon-[type]"></i>[title]'),
  t('Latest Media block'),
  t('[Empty_gallery]'),
  t('[field_picture_upload][field_video_upload]'),
);

}
}