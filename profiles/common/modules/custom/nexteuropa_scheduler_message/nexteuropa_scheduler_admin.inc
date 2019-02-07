<?php

/**
 * @file
 * Show module configuration info.
 */

/**
 * Build the admin settings form.
 */
function nexteuropa_scheduler_message_settings() {
  // The platform forces the language of the admin pages, like node/%/edit,
  // to be able to translage, we need to pass the language from the url
  // to the t() function.
  global $language_url;
  $options = array('langcode' => $language_url->language);
  $seconds_to_check = _nexteuropa_scheduler_message_get_time()->format('U');
  $form = array();
  $form['nexteuropa_scheduler_message_text'] = array(
    '#type' => 'item',
    "#disabled" => TRUE,
    '#title' => t('Message text'),
    '#markup' => _nexteuropa_scheduler_message_replace(),
    '#description' => t('This is the message to show when scheduling the publication of a node or revision. The text %date_to_check will be replaced by the date value from the field below and the text %date_to_publish will be replaced by the publication date of the node or the revision.'),
  );
  $on = t("on", array(), $options);
  $form['nexteuropa_scheduler_message_time'] = array(
    '#type' => 'item',
    "#disabled" => TRUE,
    '#title' => t('Limit date'),
    '#markup' => format_date($seconds_to_check, 'custom', 'H:i:s') . " CET " . $on . " " . format_date($seconds_to_check, 'custom', 'd F Y', NULL, $language_url->language),
    '#description' => t('This is the limit date to check. Any node or revision set to be published after this date, will show the previous message.'),
  );
  return $form;
}
