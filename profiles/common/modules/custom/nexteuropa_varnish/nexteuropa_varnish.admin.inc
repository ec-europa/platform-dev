<?php
/**
 * @file
 * Callbacks used by the administration area.
 */

/**
 * Generates the cache purge rule editing form.
 */
function nexteuropa_varnish_admin_settings_form($form, $form_state) {

  // Render the advanced PIWIK rules.
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

  $form = system_settings_form($form);
  array_unshift($form['#submit'], '_nexteuropa_varnish_default_rule_state_check');

  return system_settings_form($form);

}

/**
 * Implements hook_FORM_ID_form_validate().
 */
function nexteuropa_varnish_admin_settings_form_validate($form, &$form_state) {
  $rule_state = $form_state['values']['nexteuropa_varnish_default_purge_rule'];
  if ($rule_state && _nexteuropa_varnish_check_node_rules()) {
    form_set_error(
      'settings',
      t('You can not enable the default purge rule while "Purge rules" type of node exist.')
    );
  }
}

/**
 * Helper submit function for checking the PIWIK advanced rules state.
 */
function _nexteuropa_varnish_default_rule_state_check($form, &$form_state) {
  // Checking the state of the default purge rule checkbox.
  $rule_state = $form_state['values']['nexteuropa_varnish_default_purge_rule'];
  $rule_state_var = variable_get('nexteuropa_varnish_default_purge_rule', FALSE);

  switch ($rule_state) {
    case 0:
      $state = t('off');
      break;

    case 1:
      $state = t('on');
      break;
  }

  if ($rule_state != $rule_state_var) {
    variable_set('nexteuropa_varnish_default_purge_rule', $rule_state);
    drupal_set_message(t('The default purge rule is turned @state.', array('@state' => $state)));
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

  if (isset($result['nexteuropa_varnish_cache_purge_rule'])) {
    return TRUE;
  }

  return FALSE;
}
