<?php

/**
 * @file
 * Helper functions for module install.
 */

/**
 * Gets the default pop-up and consent default settings.
 *
 * @return array
 *   Associative array containing the default value for
 *   'eu_cookie_compliance' variable.
 */
function _multisite_eu_cookie_compliance_get_eu_cookie_compliance_default_settings() {
  return array(
    'popup_enabled' => 1,
    'method' => 'opt_in',
    'disabled_javascripts' => '',
    'whitelisted_cookies' => 'Drupal.toolbar.collapsed
Drupal.tableDrag.showWeight
Drupal.toolbar.collapsed
has_js
',
    'consent_storage_method' => 'do_not_store',
    'popup_clicking_confirmation' => FALSE,
    'popup_info' => array(
      'value' => '<h2 class="ecl-heading ecl-heading--h2" style="line-height: 20px;">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px;">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'use_mobile_message' => 0,
    'mobile_popup_info' => array(
      'value' => '',
      'format' => 'full_html',
    ),
    'mobile_breakpoint' => '768',
    'popup_agree_button_message' => 'OK, I agree',
    'show_disagree_button' => TRUE,
    'popup_disagree_button_message' => 'More info',
    'disagree_button_label' => 'Decline',
    'withdraw_enabled' => 0,
    'withdraw_message' => array(
      'value' => '<h2 class="ecl-heading ecl-heading--h2" style="line-height: 20px;">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px;">You have given your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'withdraw_tab_button_label' => 'Privacy settings',
    'withdraw_action_button_label' => 'Withdraw consent',
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => '<h2 class="ecl-heading ecl-heading--h2" style="line-height: 20px;">Thank you for accepting cookies</h2><p style="font-size: 13px; line-height: 20px;">You can now hide this message or find out more about cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_find_more_button_message' => 'More info',
    'popup_hide_button_message' => 'Hide',
    'popup_link' => 'https://ec.europa.eu/info/cookies_en',
    'popup_link_new_window' => 0,
    'popup_position' => FALSE,
    'use_bare_css' => 0,
    'popup_text_hex' => 'ffffff',
    'popup_bg_hex' => '0779BF',
    'popup_height' => '60',
    'popup_width' => '100%',
    'fixed_top_position' => 1,
    'popup_delay' => '1000',
    'disagree_do_not_show_popup' => 0,
    'reload_page' => 0,
    'popup_scrolling_confirmation' => FALSE,
    'cookie_name' => 'multisite.eu.cookie.compliance.agree',
    'domains_option' => '1',
    'domains_list' => '',
    'exclude_paths' => '',
    'exclude_admin_pages' => 1,
    'exclude_uid_1' => 1,
    'script_scope' => 'footer',
    'better_support_for_screen_readers' => 0,
    'cookie_session' => 0,
  );
}
