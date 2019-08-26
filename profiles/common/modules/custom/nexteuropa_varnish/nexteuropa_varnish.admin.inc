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
    '#description' => t('The operation will clear Varnish cache.
    Click the checkbox to also clear Drupal cache.'),
  );

  // If the purge mechanism is prevented to work, then the button must be
  // disabled and a warning message must be displayed.
  $disabled = _nexteuropa_varnish_temporary_message();

  $form['purge_cache']['purge_drupal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Clear drupal cache as well'),
    '#return_value' => 1,
    '#default_value' => 0,
  );

  $form['purge_cache']['purge'] = array(
    '#type' => 'submit',
    '#value' => t('Purge caches'),
    '#submit' => array('nexteuropa_varnish_purge_all_confirm'),
    '#disabled' => $disabled,
  );

  $form['watchdog_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Watchdog settings'),
    '#description' => t('Set varnish watchdog logging granularity.'),
  );

  $form['watchdog_settings']['nexteuropa_varnish-granularity'] = array(
    '#type' => 'radios',
    '#title' => t('Granularity'),
    '#default_value' => variable_get('nexteuropa_varnish-granularity', 2),
    '#options' => array(0 => t('None'), 1 => t('Only errors'), 2 => t('All')),
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

  $form['#submit'][] = 'nexteuropa_varnish_admin_settings_cache_clear_submit';
  return system_settings_form($form);
}

/**
 * Submit callback for clearing the purge rules cache table.
 *
 * @see nexteuropa_varnish_admin_settings_form()
 */
function nexteuropa_varnish_admin_settings_cache_clear_submit($form, &$form_state) {
  cache_clear_all('*', NEXTEUROPA_VARNISH_CACHE_TABLE, TRUE);
}

/**
 * Redirect the user from "General" page to the "purge all" confirmation form.
 */
function nexteuropa_varnish_purge_all_confirm($form, &$form_state) {
  if ($form_state['values']['purge_drupal']) {
    $form_state['redirect'] = 'admin/config/system/nexteuropa-varnish/purge/all';
  }
  else {
    $form_state['redirect'] = 'admin/config/system/nexteuropa-varnish/purge/varnish';
  }
}

/**
 * Generates the form allowing triggering the full cache purge.
 */
function nexteuropa_varnish_purge_all_form($form, &$form_state, $arg) {
  $description = t("The action you are about to perform has a deep impact on the site's performance!");
  $arg == 'all' ? $type = "Varnish and Drupal" : $type = "Varnish";
  $confirm_message = t("Are you sure you want to purge !type cache ?", array('!type' => $type));
  return confirm_form($form,
    $confirm_message,
    'admin/config/system/nexteuropa-varnish/general',
    $description,
    t('Continue'),
    t('Cancel')
  );
}

/**
 * Processes the flush cache triggered by the "Purge caches" button.
 *
 * @see nexteuropa_varnish_admin_settings_form()
 */
function nexteuropa_varnish_purge_all_form_submit($form, &$form_state) {
  $arg = $form_state['build_info']['args'][0];
  $arg == 'all' ? $type = "Drupal and Varnish" : $type = "Varnish";
  $confirm_message = t('The !type caches have been fully flushed.', array('!type' => $type));
  $message_level = 'status';
  // First clear the actual backend cache (usually DrupalDatabaseCache).
  // Otherwise the web frontend cache will receive again outdated cached
  // versions of pages.
  if ($arg == 'all') {
    drupal_flush_all_caches();
  }

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
