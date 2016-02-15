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
    '#default_value' => variable_get('nexteuropa_piwik_smartloader_prurl', ''),
    '#size' => 80,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t("The URL of the webtools smartloader script. e.g. '//example.com/load.js'"),
  );
  $form['account']['nexteuropa_piwik_site_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Site path'),
    '#default_value' => variable_get('nexteuropa_piwik_site_path', ''),
    '#size' => 80,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t("Current sites path to be tracked in piwik.e.g. 'ec.europa.eu/agriculture'"),
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
    '#default_value' => "testing",
    '#required' => TRUE,
    '#description' => t("Define the Piwik instance"),
  );

  $form['account']['nexteuropa_piwik_site_section'] = array(
    '#type' => 'textfield',
    '#title' => t('Site section'),
    '#default_value' => variable_get('nexteuropa_piwik_site_section', ''),
    '#size' => 80,
    '#maxlength' => 255,
    '#required' => FALSE,
    '#description' => t("Allows you to refine your statistics by indicating a category or section of your site"),
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
  $pages = variable_get('nexteuropa_piwik_pages', PIWIK_PAGES);

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
    '#default_value' => variable_get('nexteuropa_piwik_visibility_roles', 0),
  );

  $role_options = array_map('check_plain', user_roles());
  $form['tracking']['role_vis_settings']['nexteuropa_piwik_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#default_value' => variable_get('nexteuropa_piwik_roles', array()),
    '#options' => $role_options,
    '#description' => t('If none of the roles are selected, all users will be tracked. If a user has any of the roles checked, that user will be tracked (or excluded, depending on the setting above).'),
  );

  return system_settings_form($form);
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

  $nexteuropa_piwik_site_path = $form_state['values']['nexteuropa_piwik_site_path'];
  $result = drupal_http_request($nexteuropa_piwik_site_path);
  if ($result->code != 200 && $form_state['values']['nexteuropa_piwik_url_skiperror'] == FALSE) {
    form_set_error('nexteuropa_piwik_site_path', t('The validation of "@url" failed with error "@error" (HTTP code @code).', array(
        '@url' => check_url($nexteuropa_piwik_site_path),
        '@error' => $result->error,
        '@code' => $result->code,
        )));
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

  foreach ($value_tokens as $type => $tokens) {
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
    // addressfield_tokens.module
    ':first-name]',
    ':last-name]',
    ':name-line]',
    ':mc-address]',
    ':thoroughfare]',
    ':premise]',
    // realname.module
    ':name-raw]',
    // token.module
    ':ip-address]',
  );

  return preg_match('/' . implode('|', array_map('preg_quote', $token_blacklist)) . '/i', $token_string);
}
