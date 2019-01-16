<?php

/**
 * @file
 * Show module configuration info.
 */

/**
 * Build the admin settings form.
 */
function nexteuropa_scheduler_message_settings() {
  $form = array();
  $form['nexteuropa_scheduler_message_text'] = array(
    '#type' => 'item',
    "#disabled" => TRUE,
    '#title' => t('Message text'),
    '#markup' => _nexteuropa_scheduler_message_replace(),
    '#description' => t('This is the message to show when scheduling the publication of a node or revision. The text %date_to_check will be replaced by the date value from the field below and the text %date_to_publish will be replaced by the publication date of the node or the revision.'),
  );
  $form['nexteuropa_scheduler_message_time'] = array(
    '#type' => 'item',
    "#disabled" => TRUE,
    '#title' => t('Limit date'),
    '#markup' => _nexteuropa_scheduler_message_get_time()->format('r'),
    '#description' => t('This is the limit date to check. Any node or revision set to be published after this date, will show the previous message.'),
  );
  return $form;
}
