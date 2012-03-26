<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function mediagallery_core_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('multisite_standard', $views)) {
    $view=$views['multisite_standard'];
	
    /* Display: Latest content block */
    $handler = $view->display['block']->handler;

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
    
  }
}

