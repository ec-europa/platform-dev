<?php

/**
 * @file
 * Hooks for nexteuropa_trackedchanges admin interfaces.
 */

/**
 * NextEuropa LACO settings form.
 */
function nexteuropa_laco_settings_form($form, &$form_state) {
  $description = t('Enable the insertion of the Webtools LACO icons with content hyperlinks.');
  if (module_exists('nexteuropa_metatags')) {
    $description .= '<br/><strong>For a better performance of the LACO icon feature, please enable the "Nexteuropa Metatags" module (nexteuropa_metatags)!</strong>';
  }
  $form['nexteuropa_laco_enable_laco_icon_feature'] = array(
    '#title' => t('Enable the Language Coverage icon feature'),
    '#type' => 'checkbox',
    '#description' => $description,
    '#default_value' => variable_get('nexteuropa_laco_enable_laco_icon_feature'),
  );

  $form['nexteuropa_laco_icon_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webtools LACO icon settings'),
    '#description' => t('For more information about the different parameters below, please consult the Webtools Language Coverage documentation'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="nexteuropa_laco_enable_laco_icon_feature"]' => array(
          'checked' => TRUE,
        ),
      ),
    ),
  );

  $form['nexteuropa_laco_icon_settings']['nexteuropa_laco_smartloader_prurl'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarloader Protocol-Relative URL'),
    '#default_value' => variable_get('nexteuropa_laco_smartloader_prurl', '//europa.eu/webtools/load.js'),
    '#size' => 80,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t("The URL of the default webtools smartloader is '//europa.eu/webtools/load.js'"),
  );

  $raw_default_value = variable_get(
    'nexteuropa_laco_icon_include',
    array(
      '#block-system-main',
      '#sidebar-left',
      '#sidebar-right',
      '.page-content aside',
    )
  );
  $form['nexteuropa_laco_icon_settings']['nexteuropa_laco_icon_include'] = array(
    '#type' => 'textarea',
    '#title' => t('Containers to be included for the icon generation'),
    '#default_value' => implode("\r\n", $raw_default_value),
    '#required' => TRUE,
    '#description' => t(
      'Use any CSS selector 2.1 value to specify which links or containers are eligible. Set one selector per line.'
    ),
    '#rows' => 10,
  );

  $raw_default_value = variable_get('nexteuropa_laco_icon_exclude', array());
  $form['nexteuropa_laco_icon_settings']['nexteuropa_laco_icon_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Containers to be excluded for the icon generation'),
    '#default_value' => implode("\r\n", $raw_default_value),
    '#description' => t(
      'Use any CSS selector 2.1 value to specify which links or containers are eligible. Set one selector per line'
    ),
    '#rows' => 10,
  );

  $options = array(
    'any' => t('Any'),
    'other' => t('Other'),
    'false' => t('None (False)'),
  );
  $form['nexteuropa_laco_icon_settings']['nexteuropa_laco_icon_document_coverage'] = array(
    '#type' => 'select',
    '#title' => t('LACO icons behaviours for documents'),
    '#default_value' => variable_get('nexteuropa_laco_icon_document_coverage', 'any'),
    '#options' => $options,
    '#description' => t('Defines how the LACO icon must be displayed beside files links.'),
  );

  $form['nexteuropa_laco_icon_settings']['nexteuropa_laco_icon_page_coverage'] = array(
    '#type' => 'select',
    '#title' => t('LACO icons behaviours for pages'),
    '#default_value' => variable_get('nexteuropa_laco_icon_page_coverage', 'any'),
    '#options' => $options,
    '#description' => t('Defines how the LACO icon must be displayed beside HTML page links.'),
  );

  $form['nexteuropa_laco_icon_settings']['nexteuropa_laco_icon_language_coverage'] = array(
    '#type' => 'select',
    '#title' => t('Languages covered by the LACO icon'),
    '#default_value' => variable_get('nexteuropa_laco_icon_language_coverage', 'eu'),
    '#options' => array(
      'eu' => t('Official EU languages only'),
      'All' => t('Official EU languages + non-official ones supported by LACO'),
    ),
    '#description' => t(
      'Defines which languages are covered with the LACO icon. The supported non-official languages are SQ, AR, HY, BE, HE, HI, IS, JA, NO, MK, RU, TR, UR, VI, ZH.'
    ),
  );

  $form['nexteuropa_laco_icon_settings']['nexteuropa_laco_icon_type'] = array(
    '#type' => 'select',
    '#title' => t('LACO icon type'),
    '#default_value' => variable_get('nexteuropa_laco_icon_type', 'dot'),
    '#options' => array(
      'dot' => t('Display only 3 dots icon ( ••• )'),
      'all' => t('Display the current language (iso code) of the link following by 3 dots icons ( FR | ••• )'),
    ),
    '#description' => t(
      'Defines the type of LACO that will be used in the icon display.'
    ),
  );

  // Pages visibility settings.
  $form['nexteuropa_laco_icon_settings']['page_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages where the LACO icon feature must be active'),
  );
  $options = array(
    t('Every page except the listed pages'),
    t('The listed pages only'),
  );
  $form['nexteuropa_laco_icon_settings']['page_vis_settings']['nexteuropa_laco_visibility_pages'] = array(
    '#type' => 'radios',
    '#title' => t('Add tracking to specific pages'),
    '#options' => $options,
    '#default_value' => variable_get('nexteuropa_laco_visibility_pages', 0),
  );

  $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
    '%blog' => 'blog',
    '%blog-wildcard' => 'blog/*',
    '%front' => '<front>',
  ));
  $form['nexteuropa_laco_icon_settings']['page_vis_settings']['nexteuropa_laco_excluded_paths'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('nexteuropa_laco_excluded_paths', NEXTEUROPA_LACO_PAGES),
    '#description' => $description,
  );

  $form = system_settings_form($form);

  return $form;
}

/**
 * Validation callback for the NextEuropa LACO settings form.
 *
 * @see nexteuropa_laco_settings_form()
 */
function nexteuropa_laco_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  $values['nexteuropa_laco_icon_include'] = explode("\r\n", $values['nexteuropa_laco_icon_include']);
  $values['nexteuropa_laco_icon_exclude'] = explode("\r\n", $values['nexteuropa_laco_icon_exclude']);
}
