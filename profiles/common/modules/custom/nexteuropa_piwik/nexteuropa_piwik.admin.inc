<?php

/**
 * @file
 * Administrative page callbacks for the nexteuropa_piwik module.
 */

/**
 * Implements hook_admin_settings().
 */
function nexteuropa_piwik_admin_settings_form($form_state) {
  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );

  $form['account']['nexteuropa_piwik_site_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Piwik site ID'),
    '#default_value' => variable_get('nexteuropa_piwik_site_id', ''),
    '#size' => 15,
    '#maxlength' => 20,
    '#required' => TRUE,
    '#description' => t('The user account number is unique to the websites domain. Click the <strong>Settings</strong> link in your Piwik account, then the <strong>Websites</strong> tab and enter the appropriate site <strong>ID</strong> into this field.'),
  );
  $form['account']['nexteuropa_piwik_smartloader_prurl'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarloader Protocol-Relative URL'),
    '#default_value' => variable_get('nexteuropa_piwik_smartloader_prurl', '//europa.eu/webtools/load.js'),
    '#size' => 80,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t("The URL of the default webtools smartloader is '//europa.eu/webtools/load.js'"),
  );

  $instance_options = array(
    "europa.eu" => t("europa.eu"),
    "ec.europa.eu" => t("ec.europa.eu"),
    "testing" => t("Test instance"),
  );
  $form['account']['nexteuropa_piwik_site_instance'] = array(
    '#type' => 'select',
    '#title' => t('Piwik instance'),
    '#options' => $instance_options,
    '#default_value' => variable_get('nexteuropa_piwik_site_instance', 'ec.europa.eu'),
    '#required' => TRUE,
    '#description' => t("Define the Piwik instance"),
  );
  $utility_options = array(
    "piwik" => t("Piwik"),
    "piwiktest" => t("Piwiktest"),
  );
  $form['account']['nexteuropa_piwik_utility'] = array(
    '#type' => 'select',
    '#title' => t('Piwik utility'),
    '#options' => $utility_options,
    '#default_value' => variable_get('nexteuropa_piwik_utility', 'piwik'),
    '#required' => TRUE,
    '#description' => t("Use Piwik as default value for production sites, and only change to Piwiktest in case there of testing mode for new webtools smart loader versions"),
  );

  // Visibility settings.
  $form['tracking_title'] = array(
    '#type' => 'item',
    '#title' => t('Tracking scope'),
  );
  $form['tracking'] = array(
    '#type' => 'vertical_tabs',
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'nexteuropa_piwik') . '/nexteuropa_piwik.admin.js'),
    ),
  );

  // Page specific visibility configurations.
  $php_access = user_access('use PHP for tracking visibility');
  $visibility = variable_get('nexteuropa_piwik_visibility_pages', 0);
  $pages = variable_get('nexteuropa_piwik_pages', NEXTEUROPA_PIWIK_PAGES);

  // Site paths.
  $form['tracking']['site_path'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site paths'),
  );

  $form['tracking']['site_path']['nexteuropa_piwik_site_path'] = array(
    '#type' => 'textarea',
    '#title' => t('Site paths'),
    '#default_value' => variable_get('nexteuropa_piwik_site_path', ''),
    '#required' => TRUE,
    '#description' => t("Specify site paths to be tracked in Piwik. Add paths by using their domain name e.g. <strong>ec.europa.eu/agriculture</strong>. Enter one path per line."),
    '#rows' => 10,
  );

  // Site setion.
  $form['tracking']['site_section'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site section'),
  );

  $form['tracking']['site_section']['nexteuropa_piwik_site_section'] = array(
    '#type' => 'textfield',
    '#title' => t('Site section'),
    '#default_value' => variable_get('nexteuropa_piwik_site_section', ''),
    '#size' => 80,
    '#maxlength' => 255,
    '#required' => FALSE,
    '#description' => t("Allows you to refine your statistics by indicating a category or section of your site"),
  );

  // Search result pages.
  $form['tracking']['search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search'),
  );

  $site_search_dependencies = '<div class="admin-requirements">';
  $site_search_dependencies .= t('Requires: !module-list',
    array(
      '!module-list' => (module_exists('search') ? t('@module (<span class="admin-enabled">enabled</span>)',
        array('@module' => 'Search')) : t('@module (<span class="admin-disabled">disabled</span>)',
        array('@module' => 'Search'))),
    )
  );
  $site_search_dependencies .= '</div>';

  $form['tracking']['search']['nexteuropa_piwik_site_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Track internal search'),
    '#description' => t('If checked, internal search keywords are tracked.') . $site_search_dependencies,
    '#default_value' => variable_get('nexteuropa_piwik_site_search', TRUE),
    '#disabled' => (module_exists('search') ? FALSE : TRUE),
  );

  // Pages visibility settings.
  $form['tracking']['page_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  if ($visibility == 2 && !$php_access) {
    $form['tracking']['page_vis_settings'] = array();
    $form['tracking']['page_vis_settings']['nexteuropa_piwik_visibility_pages'] = array('#type' => 'value', '#value' => 2);
    $form['tracking']['page_vis_settings']['nexteuropa_piwik_pages'] = array('#type' => 'value', '#value' => $pages);
  }
  else {
    $options = array(
      t('Every page except the listed pages'),
      t('The listed pages only'),
    );
    $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
      '%blog' => 'blog',
      '%blog-wildcard' => 'blog/*',
      '%front' => '<front>',
    ));

    if (module_exists('php') && $php_access) {
      $options[] = t('Pages on which this PHP code returns <code>TRUE</code> (experts only)');
      $title = t('Pages or PHP code');
      $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    else {
      $title = t('Pages');
    }
    $form['tracking']['page_vis_settings']['nexteuropa_piwik_visibility_pages'] = array(
      '#type' => 'radios',
      '#title' => t('Add tracking to specific pages'),
      '#options' => $options,
      '#default_value' => $visibility,
    );
    $form['tracking']['page_vis_settings']['nexteuropa_piwik_pages'] = array(
      '#type' => 'textarea',
      '#title' => $title,
      '#title_display' => 'invisible',
      '#default_value' => $pages,
      '#description' => $description,
      '#rows' => 10,
    );
  }

  // Render the role overview.
  $form['tracking']['role_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Roles'),
  );

  $form['tracking']['role_vis_settings']['nexteuropa_piwik_visibility_roles'] = array(
    '#type' => 'radios',
    '#title' => t('Add tracking for specific roles'),
    '#options' => array(
      t('Add to the selected roles only'),
      t('Add to every role except the selected ones'),
    ),
    '#default_value' => variable_get('nexteuropa_piwik_visibility_roles', 1),
  );

  $role_options = array_map('check_plain', user_roles());
  $form['tracking']['role_vis_settings']['nexteuropa_piwik_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#default_value' => variable_get('nexteuropa_piwik_roles', array()),
    '#options' => $role_options,
    '#description' => t('If none of the roles are selected, all users will be tracked. If a user has any of the roles checked, that user will be tracked (or excluded, depending on the setting above).'),
  );

  // Render the advanced PIWIK rules.
  $form['tracking']['advanced_rules'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced PIWIK rules'),
  );

  $form['tracking']['advanced_rules']['nexteuropa_piwik_rules_state'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable advanced PIWIK rules'),
    '#description' => t('Activates the "Advanced PIWIK rules" configuration tab.'),
    '#default_value' => variable_get('nexteuropa_piwik_rules_state', FALSE),
  );

  $form = system_settings_form($form);
  array_unshift($form['#submit'], '_nexteuropa_piwik_rules_state_check');

  return $form;
}

/**
 * Implements hook_FORM_ID_form_validate().
 */
function nexteuropa_piwik_admin_settings_form_validate($form, &$form_state) {
  // Trim some text area values.
  $form_state['values']['nexteuropa_piwik_site_id'] = trim($form_state['values']['nexteuropa_piwik_site_id']);
  $form_state['values']['nexteuropa_piwik_pages'] = trim($form_state['values']['nexteuropa_piwik_pages']);

  if (!preg_match('/^\d{1,}$/', $form_state['values']['nexteuropa_piwik_site_id'])) {
    form_set_error('nexteuropa_piwik_site_id', t('A valid Piwik site ID is an integer only.'));
  }
}

/**
 * Validate a form element that should have tokens in it.
 *
 * For example:
 * @code
 * $form['my_node_text_element'] = array(
 *   '#type' => 'textfield',
 *   '#title' => t('Some text to token-ize that has a node context.'),
 *   '#default_value' => 'The title of this node is [node:title].',
 *   '#element_validate' => array('nexteuropa_piwik_token_element_validate'),
 * );
 * @endcode
 */
function nexteuropa_piwik_token_element_validate(&$element, &$form_state) {
  $value = isset($element['#value']) ? $element['#value'] : $element['#default_value'];

  if (!drupal_strlen($value)) {
    // Empty value needs no further validation since the element should depend
    // on using the '#required' FAPI property.
    return $element;
  }

  $tokens = token_scan($value);
  $invalid_tokens = _nexteuropa_piwik_get_forbidden_tokens($tokens);
  if ($invalid_tokens) {
    form_error($element, t('The %element-title is using the following forbidden tokens with personal identifying information: @invalid-tokens.', array(
      '%element-title' => $element['#title'],
      '@invalid-tokens' => implode(', ', $invalid_tokens),
    )));
  }

  return $element;
}

/**
 * Returns array of invalid tokens.
 */
function _nexteuropa_piwik_get_forbidden_tokens($value) {
  $invalid_tokens = array();
  $value_tokens = is_string($value) ? token_scan($value) : $value;

  foreach ($value_tokens as $tokens) {
    if (array_filter($tokens, '_nexteuropa_piwik_contains_forbidden_token')) {
      $invalid_tokens = array_merge($invalid_tokens, array_values($tokens));
    }
  }

  array_unique($invalid_tokens);
  return $invalid_tokens;
}

/**
 * Validate if a string contains forbidden tokens not allowed by privacy rules.
 *
 * @param string $token_string
 *   A string with one or more tokens to be validated.
 *
 * @return bool
 *   TRUE if blacklisted token has been found, otherwise FALSE.
 */
function _nexteuropa_piwik_contains_forbidden_token($token_string) {
  // List of strings in tokens with personal identifying information not allowed
  // for privacy reasons. See section 8.1 of the Google Analytics terms of use
  // for more detailed information.
  //
  // This list can never ever be complete. For this reason it tries to use a
  // regex and may kill a few other valid tokens, but it's the only way to
  // protect users as much as possible from admins with illegal ideas.
  //
  // User tokens are not prefixed with colon to catch 'current-user' and 'user'.
  //
  // TODO: If someone have better ideas, share them, please!
  $token_blacklist = array(
    ':author]',
    ':author:edit-url]',
    ':author:url]',
    ':author:path]',
    ':current-user]',
    ':current-user:original]',
    ':fid]',
    ':mail]',
    ':name]',
    ':uid]',
    ':one-time-login-url]',
    ':owner]',
    ':owner:cancel-url]',
    ':owner:edit-url]',
    ':owner:url]',
    ':owner:path]',
    'user:cancel-url]',
    'user:edit-url]',
    'user:url]',
    'user:path]',
    'user:picture]',
    // addressfield_tokens.module.
    ':first-name]',
    ':last-name]',
    ':name-line]',
    ':mc-address]',
    ':thoroughfare]',
    ':premise]',
    // realname.module.
    ':name-raw]',
    // token.module.
    ':ip-address]',
  );

  return preg_match('/' . implode('|', array_map('preg_quote', $token_blacklist)) . '/i', $token_string);
}

/**
 * Helper submit function for checking the PIWIK advanced rules state.
 */
function _nexteuropa_piwik_rules_state_check($form, &$form_state) {
  // Checking the state of the advanced rules checkbox.
  $rule_state = $form_state['values']['nexteuropa_piwik_rules_state'];
  $rule_state_var = variable_get('nexteuropa_piwik_rules_state', FALSE);

  switch ($rule_state) {
    case 0:
      $state = t('off');
      break;

    case 1:
      $state = t('on');
      break;
  }

  // Presenting the message resetting the entity cache info and rebuilding menu.
  // Runs only if the advanced PIWIK rules state has changed.
  if ($rule_state != $rule_state_var) {
    variable_set('nexteuropa_piwik_rules_state', $rule_state);
    drupal_set_message(t('The PIWIK advanced rules are turned @state.', array('@state' => $state)));
    entity_info_cache_clear();
    menu_rebuild();
  }
}
