<?php

/**
 * @file
 * This file provides the views that come along with the ecas_extra module.
 */

/**
 * Implements hook_views_default_views().
 */
function ecas_extra_views_default_views() {
  /*
   * View 'blocked_accounts'
   */
  $view = new view();
  $view->name = 'Blocked_accounts';
  $view->description = 'Blocked accounts';
  $view->tag = 'user';
  $view->base_table = 'users';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer users';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'status' => 'status',
    'module' => 'module',
    'mail' => 'mail',
    'user_denied' => 'user_denied',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'module' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'user_denied' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Bulk operations: User */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display
      ->display_options['fields']['views_bulk_operations']['table'] = 'users';
  $handler->display
      ->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display
      ->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['alter_text'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['make_link'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['absolute'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['external'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['replace_spaces'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['trim_whitespace'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['nl2br'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['word_boundary'] = 1;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['ellipsis'] = 1;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['more_link'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['strip_tags'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['trim'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['alter']['html'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['element_default_classes'] = 1;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['hide_empty'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['empty_zero'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = 1;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['vbo']['entity_load_capacity'] = '10';
  $handler->display
      ->display_options['fields']['views_bulk_operations']['vbo']['operations'] = array(
        'action::system_block_ip_action' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::user_block_user_action' => array(
          'selected' => 1,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::views_bulk_operations_delete_item' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::ecas_extra_deny_account_action' => array(
          'selected' => 1,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::system_message_action' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::views_bulk_operations_script_action' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::views_bulk_operations_modify_action' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
          'settings' => array(
            'show_all_tokens' => 1,
            'display_values' => array(
              '_all_' => '_all_',
            ),
          ),
        ),
        'action::views_bulk_operations_user_roles_action' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::views_bulk_operations_argument_selector_action' => array(
          'selected' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
          'settings' => array(
            'url' => '',
          ),
        ),
        'action::system_goto_action' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
        'action::system_send_email_action' => array(
          'selected' => 0,
          'use_queue' => 0,
          'skip_confirmation' => 0,
          'override_label' => 0,
          'label' => '',
        ),
      );
  $handler->display
      ->display_options['fields']['views_bulk_operations']['vbo']['enable_select_all_pages'] = 1;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['vbo']['display_type'] = '0';
  $handler->display
      ->display_options['fields']['views_bulk_operations']['vbo']['display_result'] = 1;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['vbo']['merge_single_action'] = 0;
  $handler->display
      ->display_options['fields']['views_bulk_operations']['vbo']['force_single'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display
      ->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: User: Active */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display
      ->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: User: Authentication module */
  $handler->display->display_options['fields']['module']['id'] = 'module';
  $handler->display->display_options['fields']['module']['table'] = 'authmap';
  $handler->display->display_options['fields']['module']['field'] = 'module';
  $handler->display->display_options['fields']['module']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['module']['alter']['make_link'] = 0;
  $handler->display
      ->display_options['fields']['module']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['module']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['module']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['module']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['module']['alter']['html'] = 0;
  $handler->display->display_options['fields']['module']['hide_empty'] = 0;
  $handler->display->display_options['fields']['module']['empty_zero'] = 0;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  /* Field: User: Denied */
  $handler->display->display_options['fields']['user_denied']['id'] = 'user_denied';
  $handler->display->display_options['fields']['user_denied']['table'] = 'users';
  $handler->display->display_options['fields']['user_denied']['field'] = 'user_denied';
  $handler->display
      ->display_options['fields']['user_denied']['alter']['alter_text'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['make_link'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['absolute'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['external'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['replace_spaces'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['user_denied']['alter']['nl2br'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['word_boundary'] = 1;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['ellipsis'] = 1;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['more_link'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['user_denied']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['user_denied']['alter']['html'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['element_label_colon'] = 1;
  $handler->display
      ->display_options['fields']['user_denied']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['user_denied']['hide_empty'] = 0;
  $handler->display->display_options['fields']['user_denied']['empty_zero'] = 0;
  $handler->display
      ->display_options['fields']['user_denied']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['user_denied']['not'] = 0;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'User: Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['uid']['expose']['reduce'] = 0;
  /* Filter criterion: User: E-mail */
  $handler->display->display_options['filters']['mail']['id'] = 'mail';
  $handler->display->display_options['filters']['mail']['table'] = 'users';
  $handler->display->display_options['filters']['mail']['field'] = 'mail';
  $handler->display->display_options['filters']['mail']['exposed'] = TRUE;
  $handler->display
      ->display_options['filters']['mail']['expose']['operator_id'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['label'] = 'User: E-mail';
  $handler->display->display_options['filters']['mail']['expose']['operator'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['identifier'] = 'mail';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display
      ->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Active';
  $handler->display
      ->display_options['filters']['status']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display
      ->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['multiple'] = FALSE;
  /* Filter criterion: User: Denied */
  $handler->display->display_options['filters']['user_denied']['id'] = 'user_denied';
  $handler->display->display_options['filters']['user_denied']['table'] = 'users';
  $handler->display->display_options['filters']['user_denied']['field'] = 'user_denied';
  $handler->display->display_options['filters']['user_denied']['value'] = '1';
  $handler->display->display_options['filters']['user_denied']['exposed'] = TRUE;
  $handler->display
      ->display_options['filters']['user_denied']['expose']['operator_id'] = '';
  $handler->display
      ->display_options['filters']['user_denied']['expose']['label'] = 'Denied';
  $handler->display
      ->display_options['filters']['user_denied']['expose']['use_operator'] = FALSE;
  $handler->display
      ->display_options['filters']['user_denied']['expose']['operator'] = 'user_denied_op';
  $handler->display
      ->display_options['filters']['user_denied']['expose']['identifier'] = 'user_denied';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/people/blocked_accounts';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Blocked accounts';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Blocked accounts';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  $views[$view->name] = $view;

  return $views;
}
