<?php

/**
 * @file
 * Code for the multisite_notifications_core settgins page.
 */

/**
 * Render API callback: General settings for notifications.
 */
function multisite_notifications_core_general_settings() {

  // Subscription.
  $form['subscription_block_settings'] = array(
    '#title' => t('Subscribe block settings'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['subscription_block_settings']['subscribe_confirmation'] = array(
    '#title' => t('Subscribe confirmation mail'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Subject.
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['subscribe_confirmation']['multisite_notifications_core_subscribe_subject_' . $language->language] = array(
      '#title' => t('Subscribe mail subject: @name', array('@name' => $language->name)),
      '#type' => 'textfield',
      '#default_value' => variable_get('multisite_notifications_core_subscribe_subject_' . $language->language, ''),
    );
  }

  // Body.
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['subscribe_confirmation']['multisite_notifications_core_subscribe_message_' . $language->language] = array(
      '#title' => t('Subscribe mail body: @name', array('@name' => $language->name)),
      '#type' => 'textarea',
      '#default_value' => variable_get('multisite_notifications_core_subscribe_message_' . $language->language, ''),
    );
  }

  // Unsubscription.
  $form['subscription_block_settings']['unsubscribe_confirmation'] = array(
    '#title' => t('Unsubscribe confirmation mail'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Subject.
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['unsubscribe_confirmation']['multisite_notifications_core_unsubscribe_subject_' . $language->language] = array(
      '#title' => t('Unsubscribe mail subject: @name', array('@name' => $language->name)),
      '#type' => 'textfield',
      '#default_value' => variable_get('multisite_notifications_core_unsubscribe_subject_' . $language->language, ''),
    );
  }

  // Body.
  foreach ($languages = language_list() as $language) {
    $form['subscription_block_settings']['unsubscribe_confirmation']['multisite_notifications_core_unsubscribe_message_' . $language->language] = array(
      '#title' => t('Unsubscribe mail body: @name', array('@name' => $language->name)),
      '#type' => 'textarea',
      '#default_value' => variable_get('multisite_notifications_core_unsubscribe_message_' . $language->language, ''),
    );
  }

  return system_settings_form($form);

}

/**
 * Mail template.
 *
 * @return \stdClass
 *   The content of mail(subject, body, comment).
 */
function _multisite_notifications_core_mail_template() {
  $template = new stdClass();
  $template->subject = '[site:name] updates : [node:title]';
  $template->body = '{{MAIL@ Dear {{[current-user:roles:last] == subscriber?subscriber:[current-user:name]}}.

Your subscription on [site:name] notifies you of {{[subs:is-new]==0?:a new post:}}{{[subs:is-updated]#an updated post:}}{{[subs:is-old]#new comments on:
}}
}}{{![subs:is-published]#| ***** This post is unpublished! *****
}}{{![subs:category:tid]?:{{[subs:category:tid]==[subs:forum:tid]?:| Category: [subs:category:name]
}}}}{{![subs:forum:tid]?:| Forum: [subs:forum:name]
}}

--------------------------------------------------------------------------------------------
[node:title]
{{![node:author:name]?:by: [node:author:name]}}
--------------------------------------------------------------------------------------------
{{![subs:has-distinct-summary]?&nbsp;[node:body]:Summary:&nbsp;[node:summary]}}

| Online version: [node:url]
{{![subs:is-old]#{{!![subs:files:field_files:count]#| Attached files:
{{[subs:files:field_files:count]#| [subs:files:field_files:index:#0:url]
}}}}}}{{![subs:comments:count]?| ---------------------------------------------------
:|
| Comments: [subs:comments:count]
| ---------------------------------------------------
[subs:comments:join:
]
}}| Direct unsubscribe link ([subs:type]):
| [subs:unsubscribe-url]
{{MAIL@| This is an automated message. Please do NOT reply to the sender address!
{{[current-user:roles:last] == subscriber? :"To manage your subscriptions go to: [subs:manage-url]"}}

}}';
  $template->comment = '| {{[subs:is-new]?New:Updated}} {{[subs:is-published]?:UNPUBLISHED }}comment:
| Author: [comment:author:name]
| Title: [comment:title]
&nbsp;
[comment:body]
| Link: [comment:url]
{{!![subs:files:field_files:count]#| Attached files:
{{[subs:files:field_files:count]#| [subs:files:field_files:index:#0:url]
}}}}| ---------------------------------------------------';

  return $template;
}
