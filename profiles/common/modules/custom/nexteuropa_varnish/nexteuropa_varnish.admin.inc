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
    '#title' => t('Enable the default purge rule.'),
    '#description' => t('Activates the default purge rule for all content types.
      The rule invalidates the Varnish cache entries whenever content changes
      are having an impact on the published/unpublished state.'),
    '#default_value' => variable_get('nexteuropa_varnish_default_purge_rule', FALSE),
  );

  return system_settings_form($form);

}
