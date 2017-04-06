<?php
/**
 * @file
 * Callbacks used by the administration area.
 */

/**
 * Generates the cache purge rule editing form.
 */
function nexteuropa_varnish_admin_settings_form($form, $form_state) {

  if (!empty($form_state['value'])) {
    nexteuropa_varnish_purge_all_form($form, $form_state);
  }

  $form['purge_cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Purge caches'),
    '#description' => t('Flush all caches (Drupal & Varnish)'),
  );

  $form['purge_cache']['purge'] = array(
    '#type' => 'submit',
    '#value' => t('Purge all caches'),
    '#submit' => array('nexteuropa_varnish_purge_all_confirm'),
  );

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );

  $form['settings']['nexteuropa_varnish_default_purge_rule'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the default purge rule'),
    '#description' => t('Activates the default purge rule for all content types.
      The rule invalidates the Varnish cache entries whenever content changes
      are having an impact on the published/unpublished state.'),
    '#default_value' => variable_get('nexteuropa_varnish_default_purge_rule', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Redirect the user from "General" page to the "purge all" confirmation form.
 */
function nexteuropa_varnish_purge_all_confirm($form, &$form_state) {
  $form_state['redirect'] = 'admin/config/system/nexteuropa-varnish/purge_all';
}

/**
 * Generates the form allowing triggering the full cache purge.
 */
function nexteuropa_varnish_purge_all_form($form, &$form_state) {
  $description = t("The action you are about to perform has a deep impact on the site's performance!");
  $confirm_message = t("Are you sure you want to purge all site's caches (Varnish included)?");
  return confirm_form($form,
    $confirm_message,
    'admin/config/system/nexteuropa-varnish/general',
    $description,
    t('Continue'),
    t('Cancel')
  );
}

/**
 * Processes the full flush cache triggered by the "Purge all caches" button.
 *
 * @see nexteuropa_varnish_admin_settings_form()
 */
function nexteuropa_varnish_purge_all_form_submit($form, &$form_state) {
  $confirm_message = t('The Drupal and Varnish caches have been fully flushed.');
  $message_level = 'status';
  // First clear the actual backend cache (usually DrupalDatabaseCache).
  // Otherwise the web frontend cache will receive again outdated cached
  // versions of pages.
  drupal_flush_all_caches();

  // Treating Varnish flushing (inspired by "flexibe_purge" contrib module).
  $send_success = _nexteuropa_varnish_varnish_requests_send();
  if (!$send_success) {
    $confirm_message = t('The Varnish caches have not been purged correctly. Please consult logs for more information.');
    $message_level = 'error';
  }

  drupal_set_message($confirm_message, $message_level);
  $form_state['redirect'] = 'admin/config/system/nexteuropa-varnish/general';
}

/**
 * Implements hook_FORM_ID_form_validate().
 */
function nexteuropa_varnish_admin_settings_form_validate($form, &$form_state) {
  $rule_state = $form_state['values']['nexteuropa_varnish_default_purge_rule'];
  if ($rule_state && _nexteuropa_varnish_check_node_rules()) {
    form_set_error(
      'settings',
      t('You can not enable the default purge rule while "Purge rules" of type "node" exist.')
    );
  }
}

/**
 * Checks if rules type of node exist.
 *
 * @return bool
 *   TRUE / FALSE depends on the results of the query.
 */
function _nexteuropa_varnish_check_node_rules() {
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'nexteuropa_varnish_cache_purge_rule')
    ->propertyCondition('paths', '');

  $result = $query->execute();

  return isset($result['nexteuropa_varnish_cache_purge_rule']);
}
