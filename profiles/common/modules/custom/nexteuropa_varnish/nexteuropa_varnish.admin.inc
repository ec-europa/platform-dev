<?php
/**
 * @file
 * Callbacks used by the administration area.
 */

/**
 * Generates the cache purge rule editing form.
 */
function nexteuropa_varnish_admin_settings_form($form, $form_state) {
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
