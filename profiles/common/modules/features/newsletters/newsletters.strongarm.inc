<?php

/**
 * @file
 * newsletters.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function newsletters_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bounce_error_on_password_reset_message';
  $strongarm->value = 'You cannot reset your password. The email address associated with your account been blocked from receiving further mails due to failed delivery of past mail.';
  $export['bounce_error_on_password_reset_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bounce_error_on_registration_message';
  $strongarm->value = 'You cannot register with the provided email address: it has been blocked from receiving further mails due to failed delivery of past mail.';
  $export['bounce_error_on_registration_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bounce_notify_user_message';
  $strongarm->value = 'Please update your email address: it has been blocked from receiving further mails due to failed delivery of past mail.';
  $export['bounce_notify_user_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_format';
  $strongarm->value = 'full_html';
  $export['mimemail_format'] = $strongarm;
  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_format';
  $strongarm->value = 'html';
  $export['simplenews_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_from_address';
  $strongarm->value = 'EC-FP-INTERNET-SERVICES-DO-NOT-REPLY@ec.europa.eu';
  $export['simplenews_from_address'] = $strongarm;

  return $export;
}
