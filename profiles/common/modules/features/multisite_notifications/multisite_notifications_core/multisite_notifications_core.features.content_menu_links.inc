<?php
/**
 * @file
 * multisite_notifications_core.features.content_menu_links.inc
 */

/**
 * Implements hook_content_menu_links_defaults().
 */
function multisite_notifications_core_content_menu_links_defaults() {
  $menu_links = array();

  // Exported menu link: management:admin/config/system/mail-edit.
  $menu_links['management:admin/config/system/mail-edit'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/mail-edit',
    'router_path' => 'admin/config/system/mail-edit',
    'link_title' => 'Mail templates',
    'options' => array(
      'attributes' => array(
        'title' => 'Edit mails being sent out by Drupal.',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'admin/config/system',
  );
  // Exported menu link: management:admin/config/system/subscriptions.
  $menu_links['management:admin/config/system/subscriptions'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/subscriptions',
    'router_path' => 'admin/config/system/subscriptions',
    'link_title' => 'Subscriptions',
    'options' => array(
      'attributes' => array(
        'title' => 'Site and user default settings for Subscriptions.',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'admin/config/system',
  );
  // Exported menu link: management:
  // admin/config/system/subscriptions/subscription-block.
  $menu_links['management:admin/config/system/subscriptions/subscription-block'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/subscriptions/subscription-block',
    'router_path' => 'admin/config/system/subscriptions/subscription-block',
    'link_title' => 'Subscription Block',
    'options' => array(
      'attributes' => array(
        'title' => 'Configure the subscription block settings.',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-10',
    'parent_path' => 'admin/config/system/subscriptions',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Mail templates');
  t('Subscription Block');
  t('Subscriptions');

  return $menu_links;
}
