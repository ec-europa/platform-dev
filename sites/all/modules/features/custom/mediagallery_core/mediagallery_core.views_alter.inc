<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function mediagallery_core_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('multisite_standard', $views)) {
    $view=$views['multisite_standard'];
	
    /* Display: Latest content block */
    $handler = $view->display['block_latest']->handler;

    /* Field: Content: Description */
    $handler->display->display_options['fields']['media_gallery_description']['id'] = 'media_gallery_description';
    $handler->display->display_options['fields']['media_gallery_description']['table'] = 'field_data_media_gallery_description';
    $handler->display->display_options['fields']['media_gallery_description']['field'] = 'media_gallery_description';
    $handler->display->display_options['fields']['media_gallery_description']['label'] = '';
    $handler->display->display_options['fields']['media_gallery_description']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['external'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['max_length'] = '150';
    $handler->display->display_options['fields']['media_gallery_description']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['trim'] = 1;
    $handler->display->display_options['fields']['media_gallery_description']['alter']['html'] = 1;
    $handler->display->display_options['fields']['media_gallery_description']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['media_gallery_description']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['media_gallery_description']['hide_empty'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['empty_zero'] = 0;
    $handler->display->display_options['fields']['media_gallery_description']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['media_gallery_description']['field_api_classes'] = 0;
    $handler->display->display_options['defaults']['filters'] = FALSE;
    

    /* Display: Latest Media block */
    $handler = $view->new_display('block', 'Latest Media block', 'block_latest_media');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Latest Medias';
    $handler->display->display_options['defaults']['pager'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['defaults']['fields'] = FALSE;
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
    $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
    /* Field: Content: Gallery media */
    $handler->display->display_options['fields']['media_gallery_media']['id'] = 'media_gallery_media';
    $handler->display->display_options['fields']['media_gallery_media']['table'] = 'field_data_media_gallery_media';
    $handler->display->display_options['fields']['media_gallery_media']['field'] = 'media_gallery_media';
    $handler->display->display_options['fields']['media_gallery_media']['label'] = '';
    $handler->display->display_options['fields']['media_gallery_media']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['make_link'] = 1;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['path'] = 'node/[nid]';
    $handler->display->display_options['fields']['media_gallery_media']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['external'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['alter']['html'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['media_gallery_media']['element_default_classes'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['hide_empty'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['empty_zero'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['media_gallery_media']['click_sort_column'] = 'fid';
    $handler->display->display_options['fields']['media_gallery_media']['type'] = 'media';
    $handler->display->display_options['fields']['media_gallery_media']['settings'] = array(
      'file_view_mode' => 'media_preview',
    );
    $handler->display->display_options['fields']['media_gallery_media']['group_rows'] = 1;
    $handler->display->display_options['fields']['media_gallery_media']['delta_limit'] = '1';
    $handler->display->display_options['fields']['media_gallery_media']['delta_offset'] = '0';
    $handler->display->display_options['fields']['media_gallery_media']['delta_reversed'] = 1;
    $handler->display->display_options['fields']['media_gallery_media']['delta_first_last'] = 0;
    $handler->display->display_options['fields']['media_gallery_media']['multi_type'] = 'ul';
    $handler->display->display_options['fields']['media_gallery_media']['field_api_classes'] = 0;
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
      'media_gallery' => 'media_gallery',
    );
    
    
        //Add block in context
  _add_block_context('homepage','block_latest_media','views','block_latest_media', 'content_top');
  
  }
}

