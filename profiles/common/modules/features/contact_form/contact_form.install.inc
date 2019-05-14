<?php

/**
 * @file
 * Install the feature contact_form.
 */

/**
 * Implements hook_form_pre_features_enable_feature().
 *
 * Add menu element and configure the contact form.
 */
function contact_form_pre_features_enable_feature($component) {

  $item = array(
    'link_path' => 'contact',
    'link_title' => t('Contact support'),
    'menu_name' => 'main-menu',
    'weight' => '50',
  );
  menu_link_save($item);
  // Set default contact form.
  $site_mail = variable_get('site_mail', ini_get('sendmail_from'));
  db_update('contact')
    ->fields(array('recipients' => $site_mail))
    ->condition('cid', 1, '=')
    ->execute();
  // Activation message.
  drupal_set_message(t('contact_form feature is now active on your site.'));
}

/**
 * Check if contact module is enbled and enable it if it's not.
 */
function _contact_form_init_feature() {
  if (!module_exists('contact')) {
    module_enable(array('contact'));
    cache_clear_all();
    menu_rebuild();
  }
}
