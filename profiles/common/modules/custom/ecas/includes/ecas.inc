<?php

/**
 * @file
 * This file embeds the actual code of the ecas module.
 */

/**
 * Checks if the given user is an ECAS user.
 *
 * @param object $user
 *   The user object to check.
 *
 * @return bool
 *   TRUE if the given user is an ECAS user, FALSE otherwise.
 */
function _is_ecas_user($user) {
  if ($authmap_res = db_query('SELECT module FROM {authmap} WHERE uid = :uid', array('uid' => $user->uid))) {
    if ($first_record = $authmap_res->fetchAssoc()) {
      if ($first_record['module'] == 'ecas') {
        return TRUE;
      }
    }
  }

  return FALSE;
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Remove the possibility to edit all the info synchronized from ecas.
 */
function ecas_form_user_profile_form_alter(&$form, &$form_state, $form_id) {
  $user = user_load($form['#user']->uid);
  // Load the user related to the profile.
  if (_is_ecas_user($user)) {
    // Remove the "Current password".
    $form['account']['current_pass']['#access'] = FALSE;

    // Remove the "Password" and "Confirm password"  fields from the
    // 'user/%/edit' page.
    $form['account']['pass']['#access'] = FALSE;
    if (!empty($user->mail)) {
      $form['account']['mail']['#disabled'] = TRUE;
    }

    // Disable the firstname and lastname fields.
    $form['field_firstname']['#disabled'] = TRUE;
    $form['field_lastname']['#disabled'] = TRUE;

    // Disable the creator field.
    $form['field_creator']['#disabled'] = TRUE;

    // Disable the name field.
    $form['account']['name']['#disabled'] = TRUE;

    $ecas_ch_pw_url = variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL);
    $form['account']['ecas_information_label'] = array(
      '#markup' => sprintf(
        t('This account is managed by EU Login. Its password can be changed using %s.'),
        l(t('the EU Login change password page'), $ecas_ch_pw_url)
      ),
      '#weight' => -10,
    );
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Add a warning for users trying to recover their password.
 */
function ecas_form_user_pass_alter(&$form, &$form_state, $form_id) {
  array_unshift($form['#validate'], '_ecas_user_pass_validate');
}

/**
 * Warn users trying to recover EU login password from Drupal at user/password.
 *
 * If the given user is an ECAS user, provide an ECAS-related URL instead of
 * sending a mail with erroneous instructions.
 */
function _ecas_user_pass_validate($form, &$form_state) {
  $name = trim($form_state['values']['name']);

  // Try to load by email.
  $account = user_load_by_mail($name);
  if (!$account) {
    // No success, try to load by name.
    $account = user_load_by_name($name);
  }
  if ($account) {
    if (_is_ecas_user($account)) {
      $ecas_ch_pw_url = variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL);
      $ecas_ch_pw_link = l($ecas_ch_pw_url, $ecas_ch_pw_url);
      $message = t('This user appears to be an EU Login user -- you can not recover his password using this form. Please visit %s instead');
      $displayed_message = sprintf($message, $ecas_ch_pw_link);
      form_set_error('name', $displayed_message);
      return;
    }
  }
}

/**
 * Private function for hook_menu().
 *
 * @param array $items
 *   An array of menu items.
 *
 * @return array
 *   An array of menu items.
 *
 * @todo It doesn't make sense to pass in data by reference and then returning
 *   the altered data. It should be either but not both.
 */
function _ecas_menu(array &$items) {
  $items['ecas'] = array(
    'path' => 'ecas',
    'title' => 'EU Login',
    'page callback' => 'ecas_login_page',
    'access callback' => 'ecas_menu_check',
    'type' => MENU_SUGGESTED_ITEM,
  );

  $items['ecaslogout'] = array(
    'title' => 'EU Login - Logout',
    'page callback' => 'ecas_logout',
    'access callback' => 'ecas_menu_logout_check',
    'type' => MENU_SUGGESTED_ITEM,
  );
  $items['ecasfulllogout'] = array(
    'title' => 'EU Login - Full Logout',
    'page callback' => 'ecas_logout',
    'page arguments' => array(TRUE),
    'access callback' => 'ecas_menu_logout_check',
    'type' => MENU_SUGGESTED_ITEM,
  );

  // NEPT-520: the use of eu login in the path has 2 goals:
  // The first is to give a path value aligned with the new official name of
  // the European SSO tool.
  // The second is avoiding to complicate the suffix based language negotiation
  // process by adding an new exception in the "ecas" path exception in the
  // process.
  // see nexteuropa_multilingual_language_negotiation_url_rewrite_callback().
  $items['eulogin_warning/%'] = array(
    'title' => 'EU Login warning',
    'page callback' => 'ecas_warning_page',
    'page arguments' => array(1),
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );

  return $items;
}

/**
 * Implements hook_theme().
 */
function ecas_theme() {
  return array(
    'ecas_profile_warning_page' => array(
      'variables' =>
       array(
         'warning_title' => NULL,
         'warning_text' => NULL,
       ),
      'template' => 'theme/templates/ecas-profile-warning-page',
    ),
  );
}

/**
 * Implements hook_user_logout().
 *
 * Apply ECAS logout logic when logging out because of autologout rules.
 */
function ecas_user_logout($account) {
  if (isset($_GET['q']) && $_GET['q'] == 'autologout_ahah_logout/alt') {
    if (ecas_menu_logout_check()) {
      ecas_logout(TRUE, FALSE);
    }
    elseif (variable_get('autologout_use_alt_logout_method', TRUE)) {
      _ecas_session_end();
      drupal_goto(variable_get('site_frontpage', 'node'));
    }
  }
}

/**
 * Checks the menu access.
 *
 * @return bool
 *   TRUE when the user is anonymous, or when the path of the displayed page
 *   correspond to 'ecas' or 'account_request'.
 *
 * @see ecas_login_page()
 */
function ecas_menu_check() {
  if (user_is_anonymous()) {
    // Access and display ECAS page if anonymous.
    return TRUE;
  }

  // If the user is already logged, then return FALSE only if the displayed
  // page does not correspond to one of the path listed below.
  $limited_acess_paths = array(
    'ecas',
    'account_request',
  );

  return in_array(current_path(), $limited_acess_paths);
}

/**
 * Redirects the user to the ECAS login page.
 */
function ecas_login_page() {
  try {
    ecas_login_check();
  }
  catch (Exception $e) {
    watchdog_exception('user', $e);
    _ecas_warning_goto(ECAS_WARNING_REASON_UNKNOWN, NULL, 'The EU login connection failed.');
  }

  $destination = variable_get('site_frontpage', 'node');

  // If it is the user's first CAS login and initial login redirection is
  // enabled, go to the set page.
  if (!empty($_SESSION['ecas_goto'])) {
    $destination = $_SESSION['ecas_goto'];
    unset($_SESSION['ecas_goto']);
  }

  $force_proto = variable_get('ecas_force_proto', FALSE);
  if (drupal_strlen($force_proto)) {
    $destination = preg_replace('/^(https?:\/\/)/', $force_proto . '://', $destination);
  }

  drupal_goto($destination);
}

/**
 * Logs a user out of Drupal.
 *
 * @param bool $full_logout
 *   TRUE to also log out from ECAS itself, FALSE to log out only from Drupal.
 * @param bool $call_hook_user_logout
 *   TRUE to call the hook_user_logout.
 */
function ecas_logout($full_logout = TRUE, $call_hook_user_logout = TRUE) {
  global $user;

  watchdog('user', 'Session closed for %name.', array('%name' => format_username($user)));

  // Destroy the current session.
  session_destroy();
  $user = drupal_anonymous_user();

  if ($call_hook_user_logout) {
    module_invoke_all('user_logout', $user);
  }

  // We have to use $GLOBALS to unset a global variable.
  $user = user_load(0);

  unset($_SESSION['ecas_goto']);
  // Removes the optional sticky cookie.
  $http_cookie_name = variable_get('ecas_sticky_cookie_name', 'drupal_stick_to_https');
  if (drupal_strlen($http_cookie_name)) {
    global $base_path;
    setcookie($http_cookie_name, 'deleted', time() - 86400, $base_path, '.' . $_SERVER['HTTP_HOST'], FALSE, TRUE);
  }

  if ($full_logout) {
    _ecas_init_phpcas_client();
    $params = array(
      'url' => url('<front>', array('absolute' => TRUE)),
    );
    drupal_alter('ecas_full_logout_parameters', $params);
    phpCAS::logout($params);
  }

  // Go to the constructed logout destination.
  drupal_goto();
}

/**
 * Saves the page that the user was on when login was requested or required.
 */
function ecas_save_page() {
  // The page is saved only if it is not done already.
  if (isset($_SESSION['ecas_goto'])) {
    return;
  }

  if (arg(0) == 'ecas') {
    // Saving the ECAS page does not make sense, use HTTP referer (absolute
    // URL) instead.
    $referer = (isset($_GET['referer'])) ? $_GET['referer'] : $_SERVER['HTTP_REFERER'];
    $_SESSION['ecas_goto'] = $referer;

    return;
  }

  // Save the Drupal path (i.e. not an absolute URL).
  $_SESSION['ecas_goto'] = $_GET['q'];
}

/**
 * Updates the extra core user fields of a given user.
 *
 * @param object $user
 *   The user object to update.
 * @param array $user_info
 *   An associative array with the following keys:
 *   - cas:email: mail address.
 *   - cas:firstName: first name.
 *   - cas:lastName: last name.
 *   - cas:domain: the domain, e.g. eu.europa.ec or external.
 *   - cas:departmentNumber: the department, e.g. DIGIT.A.3.
 * @param array $edit
 *   The array containing user properties and field values to edit at saving
 *   time.
 *   It is the same array structure as in the user_save().
 *
 * @see ecas_sync_drupal_user_with_ecas_info()
 */
function ecas_sync_profile_core(&$user, array $user_info, array &$edit = array()) {
  $field_firstname = trim(variable_get('ecas_profile_core_firstname_field', 'field_firstname'));
  $field_lastname = trim(variable_get('ecas_profile_core_lastname_field', 'field_lastname'));
  $field_ecasmail = trim(variable_get('ecas_profile_core_ecas_email_field', 'field_ecas_mail'));
  $field_ecascreator = trim(variable_get('ecas_profile_core_ecas_creator_field', 'field_creator'));
  $user_fields = field_info_instances('user', 'user');

  // You can now access the fields without knowing the language.
  if (!empty($field_firstname) && isset($user_fields[$field_firstname])) {
    $edit[$field_firstname][LANGUAGE_NONE][0]['value'] = $user_info['cas:firstName'];
  }
  if (!empty($field_lastname) && isset($user_fields[$field_lastname])) {
    $edit[$field_lastname][LANGUAGE_NONE][0]['value'] = $user_info['cas:lastName'];
  }
  if (!empty($field_ecasmail) && isset($user_fields[$field_ecasmail])) {
    $edit[$field_ecasmail][LANGUAGE_NONE][0]['value'] = $user_info['cas:email'];
  }
  if (!empty($field_ecascreator) && isset($user_fields[$field_ecascreator])) {
    if ($user_info['cas:domain'] == 'external') {
      $edit[$field_ecascreator][LANGUAGE_NONE][0]['value'] = $user_info['cas:domain'];
    }
    else {
      $edit[$field_ecascreator][LANGUAGE_NONE][0]['value'] = $user_info['cas:domain'] . '/' . $user_info['cas:departmentNumber'];
    }
  }
}

/**
 * Update various information of a given user and save them.
 *
 * Update information: core mail address, profile, Content Profile, roles, ...
 * When all information has been synced, this function invokes the
 * info_ecas_update() hook in all enabled modules that implement it.
 *
 * @param object $user
 *   A user object.
 * @param array $user_info
 *   An associative array with the following interesting keys:
 *   - mail: mail address.
 *   - givenname: first name.
 *   - sn: last name.
 *   These values will be used to fill fields/profiles/...
 * @param array $args
 *   Extra parameters, not used directly in this function but passed to the
 *   info_ecas_update() hook.
 *
 * @deprecated
 *   Use the combination of ecas_sync_drupal_user_on_ecas_info() and
 *   ecas_save_user() instead.
 */
function ecas_sync_user_info(&$user, array $user_info, array $args) {
  $account_edit = ecas_sync_drupal_user_on_ecas_info($user, $user_info, $args);
  ecas_save_user($user, $account_edit, $user_info, $args);
}

/**
 * Synchronizes the Drupal user with the Ecas data.
 *
 * Update information: core mail address, profile, Content Profile, roles, ...
 *
 * When all information has been synced, this function invokes the
 * hook_ecas_sync_user_info() and hook_ecas_user_roles_alter() hooks.
 *
 * The function does not save the synchronized user object. That must be done
 * later through ecas_save_user().
 *
 * @param object $user
 *   A user object.
 * @param array $user_info
 *   An associative array with the following interesting keys:
 *   - mail: mail address.
 *   - givenname: first name.
 *   - sn: last name.
 *   These values will be used to fill fields/profiles/...
 * @param array $args
 *   Extra parameters, not used directly in this function but passed to the
 *   ecas_sync_user_info() and ecas_user_roles_alter() hooks.
 *
 * @return array
 *   An array of fields and values to save like user_save() uses.
 *   For example array('name' => 'My name').
 *   Key / value pairs added to the $edit['data'] will be serialized and
 *   saved in the {users.data} column.
 *
 * @see ecas_save_user()
 */
function ecas_sync_drupal_user_with_ecas_info(&$user, array $user_info, array $args) {
  $edit = (array) $user;

  // Update the user mail in the users table.
  if (variable_get('ecas_update_mail_address', TRUE)) {
    $edit['mail'] = (isset($user_info['cas:email'])) ? $user_info['cas:email'] : '';
  }

  // Update extra core user fields.
  if (variable_get('ecas_profile_core_enabled', FALSE)) {
    ecas_sync_profile_core($user, $user_info, $edit);
  }

  // Call "hook_ecas_sync_user_info" implementation with $edit passed by
  // reference as parameter.
  foreach (module_implements('ecas_sync_user_info') as $module) {
    $function = $module . '_ecas_sync_user_info';
    $function($user, $user_info, $edit, $args);
  }

  // Let the opportunity to modules to alter user roles.
  drupal_alter('ecas_user_roles', $edit['roles'], $user, $user_info, $args);

  return $edit;
}

/**
 * Implements hook_ecas_sync_user_info().
 *
 * Assign the "CEM" role assigned to the user if they belong to the COMM_CEM.
 */
function ecas_ecas_sync_user_info($user, array $user_info, array &$edit, array $args) {
  $user_cas_groups = array();
  if (!empty($user_info['cas:groups']) && !empty($user_info['cas:groups']['cas:group'])) {
    $user_cas_groups = (array) $user_info['cas:groups']['cas:group'];
  }
  $administrator_role = user_role_load_by_name("administrator");
  $cem_role = user_role_load_by_name(CCE_BASIC_CONFIG_CEM_ROLE_NAME);
  $user_roles = (isset($user->roles)) ? $user->roles : array();
  // When a user logs using ecas, if they have the cem role on the site, we
  // remove cem and administrator roles from their profiles and keep the rest.
  if (isset($user_roles[$cem_role->rid])) {
    unset($user_roles[$cem_role->rid]);
    if (isset($user_roles[$administrator_role->rid])) {
      unset($user_roles[$administrator_role->rid]);
    }
  }
  if (in_array(ECAS_CEM_ECAS_GROUP, $user_cas_groups)) {
    $user_roles[$cem_role->rid] = $cem_role->name;
    $user_roles[$administrator_role->rid] = $administrator_role->name;
    watchdog(
      'ecas',
      'User "%name" has received the "%role_1" and "%role_2" roles.',
      array(
        '%name' => $user->name,
        '%role_1' => $administrator_role->name,
        '%role_2' => $cem_role->name,
      ),
      WATCHDOG_INFO,
      l(t('edit user'), sprintf('admin/user/edit/%d', $user->uid))
    );
  }

  $edit['roles'] = $user_roles;
}

/**
 * Uses ECAS to log in the user. Also updates her information.
 */
function ecas_login_check() {
  global $user;

  if ($user->uid) {
    // The user has an uid, and it is > 0 (which is anonymous user's uid) do
    // nothing because user is already logged into Drupal.
    drupal_set_message(t('You are already logged, dear %ecas_username.', array('%ecas_username' => $user->name)));
    return;
  }

  $force_login = _ecas_force_login();
  if ($force_login == ECAS_NO_LOGIN) {
    return;
  }

  $ecas_sync_user_info_args = array();

  // Start a new Drupal session.
  drupal_session_start();

  ecas_save_page();

  _ecas_init_phpcas_client();
  _ecas_prepare_phpcas_url();

  if ($force_login === ECAS_LOGIN) {
    phpCAS::forceAuthentication();
  }

  // Check the user is authenticated by ecas.
  // if not, we stop here with a warning message page.
  if (!phpCAS::isAuthenticated()) {
    _ecas_warning_goto(
      ECAS_WARNING_REASON_UNKNOWN,
      NULL,
      'ECAS authentication failed for unexpected reasons.'
    );
  }

  // Get ecas user data.
  $ecas_name = phpCAS::getUser();
  $ecas_attributes = phpCAS::getAttributes();

  // If no ecas attribute are available, we cannot achieve the user login.
  // We stop the process and redirect the user to the warning page.
  if (empty($ecas_attributes) || empty($ecas_name)) {
    _ecas_warning_goto(
      ECAS_WARNING_REASON_INCOMPLETE_USER,
      NULL,
      'Login process failed for "%ecas_name" because of an EU login user with missing required attributes.',
      array(
        '%ecas_name' => !empty($ecas_name) ? $ecas_name : 'Unknown user name',
      )
    );
  }

  $ecas_social_login = $ecas_attributes['cas:employeeType'];
  $ecas_user_language = ecas_get_ecas_user_language($ecas_attributes);

  // Let's check after an existing Drupal account.
  $account = user_load_by_name($ecas_name);
  // Check if the mail is in use.
  if (!$account &&  $ecas_social_login != 'v') {
    $account = user_load_by_mail($ecas_attributes['cas:email']);
  }
  // Let's already give the chance to other module to alter the
  // account structure.
  drupal_alter('ecas_extra_filter', $ecas_name, $account, $_SESSION['ecas_goto']);

  // Prepare the Drupal user object.
  $account = ecas_prepare_drupal_user($ecas_name, $account, $ecas_attributes);

  // Check if the user has not been logged in and arrives in this process by
  // mistake.
  // If it happens, we redirect him to the front page and ask him to log out
  // and log in again.
  if (
    isset($account->data['ecas_login_date']) &&
    ($account->data['ecas_login_date'] == $ecas_attributes['cas:loginDate'])
  ) {

    $msg = 'Rejected ECAS reused login: %n (ECAS)';
    watchdog('user', $msg, array('%n' => $account->name), WATCHDOG_NOTICE);

    _ecas_session_end();

    $url = phpCAS::getServerLogoutURL() . '?url=' . _ecas_get_site_frontpage_full_url();
    $msg = t(
      'Your EU Login session needs to be renewed. For security reasons, please <a href="@url">logout and login again</a>.',
      array('@url' => $url)
    );
    drupal_set_message($msg, 'error');
    // No need to continue, redirect the user to the front page.
    drupal_goto('<front>');
  }

  // Also set an extra parameter for ecas_sync_user_info() -- this allows
  // other modules to detect a user creation.
  $ecas_sync_user_info_args['ecas_user_creation'] = $_SESSION['ecas_first_login'];

  // Synchronize data between Drupal user object and Ecas ones according to the
  // site specificity.
  // There is no save inside, that will be do after further validations.
  $account_edit = ecas_sync_drupal_user_with_ecas_info($account, $ecas_attributes, $ecas_sync_user_info_args);

  // Before saving and as we gave a last chance to other modules to change the
  // user data, check the validity of the user that must be saved.
  // The ecas user must have a defined e-mail; otherwise the drupal
  // authentication is denied.
  if (empty($account_edit['mail'])) {
    _ecas_warning_goto(
      ECAS_WARNING_REASON_NO_EMAIL,
      $ecas_user_language,
      'Login denied for %ecas_name because it has no e-mail defined.',
      array(
        '%ecas_name' => $ecas_name,
      )
    );
  }

  // Check that the email is not used for another account; otherwise the drupal
  // authentication is denied.
  if ($ecas_social_login == 'v' && ecas_is_email_already_used($account_edit['mail'], $account)) {
    _ecas_warning_goto(
      ECAS_WARNING_REASON_EXISTING_EMAIL,
      $ecas_user_language,
      'Login denied for %ecas_name because the e-mail is already used by another account.',
      array(
        '%ecas_name' => $ecas_name,
      )
    );
  }

  // Check that social login user has authenticated role only.
  $authenticated_role = user_role_load_by_name('authenticated user');

  if ($ecas_social_login == 'v' && (user_has_role($authenticated_role->rid, $account) && count($account->roles) > 1)) {
    _ecas_warning_goto(
      ECAS_WARNING_REASON_SOCIAL,
      $ecas_user_language,
      'Login denied for %ecas_name because the account has more then authenticated role.',
      array(
        '%ecas_name' => $ecas_name,
      )
    );
  }

  // Time to save the user.
  $saved_account = ecas_save_user($account, $account_edit, $ecas_attributes, $ecas_sync_user_info_args);

  if (empty($saved_account->status)) {
    _ecas_warning_goto(
      ECAS_WARNING_REASON_BLOCKED,
      $ecas_user_language,
      'Login denied for %ecas_name because the account is not active yet.',
      array(
        '%ecas_name' => $ecas_name,
      )
    );
  }

  // Finalize the user login.
  $user = $saved_account;
  user_login_finalize();

  // Optionally set a non-secure cookie meaning "the user has logged in
  // using HTTPS and should not use HTTP for the duration of this
  // session".
  $http_cookie_name = variable_get('ecas_sticky_cookie_name', 'drupal_stick_to_https');
  if (drupal_strlen($http_cookie_name)) {
    global $base_path;
    setcookie($http_cookie_name, variable_get('ecas_sticky_cookie_value', 'y'), 0, $base_path, '.' . $_SERVER['HTTP_HOST'], FALSE, TRUE);
  }

  // Check if it is the first login, if yes, redirect the user to user edit
  // form.
  if (!empty($_SESSION['ecas_first_login'])) {
    $_SESSION['ecas_goto'] = sprintf('user/%d/edit', $user->uid);
  }

  // Before ending, display the login success message.
  $message = variable_get(ECAS_LOGIN_MESSAGE, _ecas_get_default_login_message());
  $message = format_string(
    $message,
    array('%ecas_username' => $user->name)
  );
  drupal_set_message(filter_xss($message));
}

/**
 * Check to see if we need to display the logout menu.
 *
 * @return bool
 *   TRUE if the user is logged via ECAS,
 *   FALSE otherwise.
 */
function ecas_menu_logout_check() {
  global $user;

  if (!user_is_logged_in()) {
    return FALSE;
  }

  // We provide access to this menu entry only if we are logged via ECAS.
  if (isset($_SESSION['phpCAS']) && isset($user->name)) {
    if ($_SESSION['phpCAS']['user'] === $user->name) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Implements hook_block_view().
 *
 * Provides login block that only shows up when the user logs in.
 */
function ecas_block_view($delta = '') {
  global $user;

  $block = array();

  switch ($delta) {
    case 'ecas':
      if (!$user->uid) {
        $output = '<div class="user-login-block">' . "\n";

        $output .= l(t('Login'), 'ecas');
        $output .= '</div>' . "\n";
        $block['subject'] = t('User Login');
        $block['content'] = $output;
      }
      else {
        $output = '<div class="user-login-block">' . "\n";

        $output .= l(t('Logout'), 'ecaslogout');
        $output .= '</div>' . "\n";
        $block['subject'] = t('User Login');
        $block['content'] = $output;
      }
      return $block;
  }
}

/**
 * Implements hook_block_info().
 */
function ecas_block_info() {
  $blocks['ecas'] = array(
    'info' => t('EU Login'),
  );

  return $blocks;
}

/**
 * Page callback; displays the 'ecas_warning_page' page.
 *
 * @param string $reason
 *   The id of the warning reason.
 *
 * @return string
 *   The themed warning page display.
 */
function ecas_warning_page($reason) {
  $theme_variables = array('warning_title' => t("Your site's account cannot be created"));

  switch ($reason) {
    case ECAS_WARNING_REASON_SOCIAL:
      $theme_variables['warning_title'] = t("Your social network account does not allow you to login.");
      $message_key = ECAS_WARNING_MESSAGE_SOCIAL;
      break;

    case ECAS_WARNING_REASON_BLOCKED:
      $theme_variables['warning_title'] = t("Your site's account is currently blocked");
      $message_key = ECAS_WARNING_MESSAGE;
      break;

    case ECAS_WARNING_REASON_NO_EMAIL:
      $message_key = ECAS_WARNING_MESSAGE_NO_EMAIL;
      break;

    case ECAS_WARNING_REASON_EXISTING_EMAIL:
      $message_key = ECAS_WARNING_MESSAGE_EXISTING_EMAIL;
      break;

    case ECAS_WARNING_REASON_NOT_CREATED:
      $message_key = ECAS_WARNING_MESSAGE_NOT_CREATED;
      break;

    case ECAS_WARNING_REASON_INCOMPLETE_USER:
      $message_key = ECAS_WARNING_MESSAGE_INCOMPLETE_USER;
      break;

    default:
      $theme_variables['warning_text'] = t("The reason is unknown. Please contact the site's administrator.");

      return theme('ecas_profile_warning_page', $theme_variables);

  }

  $message = variable_get($message_key, _ecas_get_default_warning_message($message_key));
  // NEPT-520: Fallback process for sites that have set the ecas variable values
  // before the i18n variable integration in the ecas module.
  if (!is_array($message)) {
    watchdog(
      'user',
      'The %message_key value is not updated to set the text filter to apply on it. Please update the ECAS settings.',
      array('%message_key' => $message_key),
      WATCHDOG_WARNING
    );
    $message = array('value' => $message);
  }
  $theme_variables['warning_text'] = _ecas_filter_variable_text($message);

  return theme('ecas_profile_warning_page', $theme_variables);
}

/**
 * Creates an ECAS user.
 *
 * @param string $ecas_name
 *   The ECAS name of the user.
 * @param array $defaults
 *   An array of user fields and properties to save on the user object.
 *
 * @return false|\stdClass
 *   The user object, or FALSE if the user could not be created.
 */
function ecas_create_user($ecas_name, $defaults = array()) {
  $user_default = array_merge(array(
    'name' => $ecas_name,
    'pass' => user_password(),
    'init' => $ecas_name,
    'status' => variable_get('ecas_account_option', 1),
    'access' => REQUEST_TIME,
    'auth_ecas' => 'ecas_' . $ecas_name,
    'mail' => variable_get('ecas_default_mail_address', ECAS_DEFAULT_MAIL_ADDRESS),
  ), $defaults);

  // Now save the user.
  $account = user_save(drupal_anonymous_user(), $user_default);

  // Register the user has ECAS authentication.
  db_insert('authmap')
    ->fields(array(
      'authname' => $ecas_name,
      'uid' => $account->uid,
      'module' => 'ecas',
    ))
    ->execute();

  watchdog('user', 'new user: %n (ECAS)', array('%n' => $account->name), WATCHDOG_NOTICE, l(t('edit user'), sprintf('admin/user/edit/%d', $account->uid)));

  if ($account) {
    $account = user_load_by_name($account->name);
  }

  return $account;
}

/**
 * Saves the Drupal user object from ecas synchronized data.
 *
 * @param object $account
 *   The Drupal user object on which the saving action is done.
 * @param array $edit
 *   An array of fields and values to save.
 * @param array $ecas_user_info
 *   Associative array with the user related ecas attributes.
 * @param array $args
 *   Extra parameters, not used directly in this function but passed to the
 *   info_ecas_update() hook.
 *
 * @return bool|Object
 *   A fully-loaded $user object upon successful save or FALSE if the
 *   save failed.
 *
 * @see user_save()
 */
function ecas_save_user($account, $edit, array $ecas_user_info, array $args = array()) {
  // Fix : save file object replaced by fid by user_save function.
  // See at the end of the function.
  if (isset($account->picture)) {
    $picture = $account->picture;
  }

  // Store the user name first to use it in watchdog in case of failure and
  // $account loses it during the saving operation.
  $name = 'Unknown user';
  if (isset($account->name)) {
    $name = $account->name;
  }

  // Set the ecas_login_date user attribute based on 'cas:loginDate' value.
  if (isset($ecas_user_info['cas:loginDate'])) {
    $edit['data']['ecas_login_date'] = $ecas_user_info['cas:loginDate'];
    $account->access = REQUEST_TIME;
  }

  $account = user_save($account, $edit);

  // Check to make sure we have a good Drupal user.
  if (!$account || $account->uid == 0) {
    watchdog(
      'user',
      'Drupal user save failed for %name.',
      array('%name' => $name),
      WATCHDOG_ERROR
    );

    return FALSE;
  }

  if (!empty($_SESSION['ecas_first_login'])) {
    // Register the user has ECAS authentication.
    db_insert('authmap')
      ->fields(array(
        'authname' => $account->name,
        'uid' => $account->uid,
        'module' => 'ecas',
      ))
      ->execute();

    watchdog(
      'user',
      'new user: %n (ECAS)',
      array('%n' => $account->name),
      WATCHDOG_NOTICE,
      l(t('edit user'), sprintf('admin/user/edit/%d', $account->uid))
    );
  }

  // Ensure the the picture is correctly set in the account object
  // before passing to the hook_info_ecas_update().
  if (isset($picture)) {
    $account->picture = $picture;
  }
  // Old hook implementation. we keep it for backward compatibility.
  module_invoke_all('info_ecas_update', $account, $ecas_user_info, $args);

  // Load the user account and update realname, to ensure the safe_value of
  // fields are updated.
  cache_clear_all();
  $update_account = user_load($account->uid, TRUE);
  realname_update($update_account);
  return $account;
}

/**
 * Gets the user's department structure.
 *
 * @param array $user_info
 *   The user's attributes retrieved from the LDAP.
 *
 * @return array
 *   The service to which the user belongs:
 *    - 'dg': User's DG Acronym or FALSE if not given;
 *    - 'directorate': User's directorate name or FALSE if not given;
 *    - 'unit': User's unit name or FALSE if not given;
 *    - 'sub_unit': User's sub-unit name or FALSE if not given;
 *    - 'full_name": The full name of the user's department.
 *
 * @see phpCAS::getAttributes()
 */
function ecas_get_user_department($user_info) {
  if (!empty($user_info['cas:departmentNumber'])) {
    $department = array('full_name' => $user_info['cas:departmentNumber']);
    $organizations = explode('.', $user_info['cas:departmentNumber']);

    $department += array(
      'dg' => (!empty($organizations[0])) ? $organizations[0] : FALSE,
      'directorate' => (!empty($organizations[1])) ? $organizations[1] : FALSE,
      'unit' => (!empty($organizations[2])) ? $organizations[2] : FALSE,
      'sub_unit' => (!empty($organizations[3])) ? $organizations[3] : FALSE,
    );

    return $department;
  }

  return array();
}

/**
 * Gets the user language code for a specified ecas user.
 *
 * @param array $user_info
 *   Associative array with the user data coming from ecas.
 *   All array keys are prefixed by 'cas:'.
 *
 * @return object|bool
 *   The drupal language object associated to the ecas user language or FALSE
 *   if not found.
 */
function ecas_get_ecas_user_language(array $user_info = array()) {
  if (empty($user_info['cas:locale'])) {
    return FALSE;
  }

  $user_locale = $user_info['cas:locale'];
  $enabled_language_list = language_list('enabled');
  $enabled_language_list = reset($enabled_language_list);

  return isset($enabled_language_list[$user_locale]) ? $enabled_language_list[$user_locale] : FALSE;
}

/**
 * Checks if the e-mail address is not already used by a user.
 *
 * It does not use "user_load_by_mail" because this function is case sensitive
 * with some DB types.
 *
 * @param string $email
 *   The e-mail to control.
 * @param object $account
 *   (optional) An account to exclude from the control.
 *
 * @return bool
 *   True if the e-mail is already used by a user; otherwise FALSE.
 *
 * @see user_load_by_mail()
 * @see user_account_form_validate()
 */
function ecas_is_email_already_used($email, $account = NULL) {
  $email = trim($email);

  $query = db_select('users')
    ->fields('users', array('uid'))
    ->condition('mail', db_like($email), 'LIKE')
    ->range(0, 1);

  if (!empty($account) && !empty($account->uid)) {
    $query->condition('uid', $account->uid, '<>');
  }

  return (bool) $query->execute()->fetchField();
}

/**
 * Prepares the Drupal user based on the ECAS user data.
 *
 * @param string $ecas_name
 *   The Ecas user name.
 * @param object $account
 *   An already existing Drupal user account linked to the Ecas user.
 * @param array $ecas_user_attributes
 *   The Ecas user attributes.
 *
 * @return object
 *   The Drupal user object as already registered or a default object with the
 *   minimum properties needed for validity checks: name, new, init, password,
 *   status, auth_ecas, mail, access.
 */
function ecas_prepare_drupal_user($ecas_name, $account = NULL, array $ecas_user_attributes = array()) {
  if ($account) {
    // Set a session variable to denote this is an initial login (uid = 0) or
    // not.
    $_SESSION['ecas_first_login'] = empty($account->uid);

    return $account;
  }

  // Prepare the account object to use the same validity check mechanism
  // for known and unknown users.
  // Logic based on an initial set to anonymous user is taken from user module.
  $account = drupal_anonymous_user();
  $account->name = $ecas_name;
  $account->pass = user_password();
  $account->init = $ecas_name;
  $account->status = variable_get('ecas_account_option', 1);
  $account->auth_ecas = 'ecas_' . $ecas_name;
  $account->timezone = variable_get('date_default_timezone', @date_default_timezone_get());
  $account->is_new = 1;
  // Leave email uncontrolled yet, the control on the email value
  // will be done later, after giving the opportunity to other modules to
  // implement their own check or email setting.
  if (!empty($ecas_user_attributes['cas:email'])) {
    $account->mail = $ecas_user_attributes['cas:email'];
  }

  // Set a session variable to denote this is the initial login.
  $_SESSION['ecas_first_login'] = TRUE;

  return $account;
}

/**
 * Initializes the phpCas client.
 */
function _ecas_init_phpcas_client() {
  $server_version     = (string) variable_get('cas_version', '2.0');
  $server_ecas_server = FPFIS_ECAS_URL;
  $server_port        = FPFIS_ECAS_PORT;
  $server_uri         = FPFIS_ECAS_URI;
  $start_session      = (boolean) FALSE;

  // Drupal takes care of its own session.
  $assurance_level = variable_get('ecas_assurance_level', constant('ECAS_DEFAULT_ASSURANCE_LEVEL'));

  // Before using the phpCas client, we optionally set it in debug mode.
  if (variable_get('ecas_phpcas_debug', FALSE)) {
    $logpath = variable_get('ecas_phpcas_debug_logpath', constant('ECAS_DEFAULT_DEBUG_LOGPATH'));
    // As specified in ecas_admin_settings(), we do not check whether the
    // logpath is writable or not.
    if (drupal_strlen($logpath)) {
      phpCAS::setDebug($logpath);
    }
  }

  phpCAS::client(
    $server_version,
    $server_ecas_server,
    $server_port,
    $server_uri,
    $start_session,
    $assurance_level
  );
  phpCAS::setNoCasServerValidation();

  foreach (variable_get('ecas_curl_options', array()) as $key => $value) {
    phpCAS::setExtraCurlOption($key, $value);
  }
}

/**
 * Sets the URL used by the phpCas client.
 */
function _ecas_prepare_phpcas_url() {
  // Adds an optional "domain" parameter to the login URL - this allows Drupal
  // admins to specify the default ecas domain to be displayed on the login
  // page when none could be found in the cookies sent by the browser.
  $ecas_domain = (string) variable_get('ecas_domain', '');
  if (drupal_strlen($ecas_domain)) {
    $initial_server_login_url = phpCAS::getServerLoginURL();
    $custom_server_login_url = sprintf('%s&domain=%s', $initial_server_login_url, urlencode($ecas_domain));
    phpCAS::setServerLoginURL($custom_server_login_url);
  }

  // Preparing validation URL to retrieve attributes as well :
  $assurance_level = variable_get('ecas_assurance_level', constant('ECAS_DEFAULT_ASSURANCE_LEVEL'));
  $validate_server_url = 'https://' . FPFIS_ECAS_URL . ':' . FPFIS_ECAS_PORT;
  $validate_server_url .= FPFIS_ECAS_URI . '/TicketValidationService?assuranceLevel=' . $assurance_level . '&ticketTypes=SERVICE,PROXY&userDetails=true&groups=*';
  phpCAS::setServerServiceValidateURL($validate_server_url);
}

/**
 * Determines whether cas login should be enforced for this page load.
 *
 * This is done based on the redirection settings for this module.
 *
 * @return int
 *   An ECAS status constant, either ECAS_LOGIN or ECAS_GATEWAY.
 */
function _ecas_force_login() {
  list($arg0) = explode('/', $_GET['q']);

  // Don't even do the test if we're hitting the cas page.
  if ($arg0 == 'ecas' || $arg0 == 'ecaslogout') {
    return ECAS_LOGIN;
  }

  // Allow users to access the drupal login page.
  if ($arg0 == 'user') {
    return ECAS_NO_LOGIN;
  }

  // Don't even do the test if cron.php or xmlrpc.php is invoked. Don't
  // require login.
  if (base_path() . 'cron.php' == $_SERVER['PHP_SELF'] || base_path() . 'xmlrpc.php' == $_SERVER['PHP_SELF']) {
    return ECAS_NO_LOGIN;
  }

  // Don't even do the test if it's a RSS feed.
  $args = explode('/', $_GET['q']);
  if ($args[count($args) - 1] == 'feed') {
    return ECAS_NO_LOGIN;
  }

  $method = variable_get('ecas_pages_method', 0);
  $pages = variable_get('ecas_pages', '');

  // This common page matching logic used throughout Drupal.
  if ($pages) {
    $path = drupal_get_path_alias($_GET['q']);

    $pattern = array(
      '/(\r\n?|\n)/',
      '/\\\\\*/',
      '/(^|\|)\\\\<front\\\\>($|\|)/',
    );
    $replacement = array(
      '|',
      '.*',
      '\1' . variable_get('site_frontpage', 'node') . '\2',
    );
    $regexp = '/^(' . preg_replace($pattern, $replacement, preg_quote($pages, '/')) . ')$/';
    $path_match = preg_match($regexp, $path);

    if ($method == ECAS_LOGIN_EXLUDE_PAGES) {
      if ($path_match) {
        // Current page matches pattern given, so we need to exclude this
        // page from ecas login.
        return ECAS_GATEWAY;
      }
      else {
        return ECAS_LOGIN;
      }
    }
    else {
      // ECAS_LOGIN_INCLUDE_PAGES.
      if ($path_match) {
        // Current page matches pattern given, so we need to include this
        // page for ECAS login.
        return ECAS_LOGIN;
      }
      else {
        return ECAS_GATEWAY;
      }
    }
  }
  else {
    if ($method == ECAS_LOGIN_EXLUDE_PAGES) {
      return ECAS_LOGIN;
    }
    else {
      // ECAS_LOGIN_INCLUDE_PAGES only on listed pages, but no pages listed,
      // so no login on any page.
      return ECAS_GATEWAY;
    }
  }

  return ECAS_GATEWAY;
}

/**
 * End session and set global variable $user to anonymous.
 */
function _ecas_session_end() {
  global $user;

  session_destroy();

  $user = drupal_anonymous_user();
}

/**
 * Get the full URL of the homepage of the site.
 *
 * @return string
 *   The full URL of the homepage of the site.
 */
function _ecas_get_site_frontpage_full_url() {
  return url('<front>', ['absolute' => TRUE]);
}

/**
 * Triggers the redirection to the ecas warning page with the right parameters.
 *
 * @param string $path_page_argument
 *   The warning page argument to use for the redirection.
 * @param object $language
 *   The language to append to the path used in the redirection.
 * @param string $message
 *   (Optional) A message to use in order to log the redirection event.
 * @param array $message_args
 *   (Optional) Array of variables to replace in the log message on display or
 *   NULL if message is already translated or not possible to
 *   translate.
 *
 * @see drupal_goto()
 */
function _ecas_warning_goto($path_page_argument, $language = NULL, $message = NULL, array $message_args = array()) {
  if (!empty($message)) {
    watchdog('user', $message, $message_args, WATCHDOG_ERROR);
  }

  if (empty($language)) {
    $language = language_default();
  }

  _ecas_session_end();

  // Ensure that the user is correctly redirected to warning page because
  // if drupal_goto() detects an internal path in destination parameter, it
  // will use it instead of the submitted parameters, see function code.
  if (isset($_REQUEST['destination'])) {
    unset($_REQUEST['destination']);
  }
  if (isset($_REQUEST['edit']['destination'])) {
    unset($_REQUEST['edit']['destination']);
  }

  drupal_goto('eulogin_warning/' . $path_page_argument, array('language' => $language));
}

/**
 * Filters a variable text value.
 *
 * @param array $raw_text_parameters
 *   Associative array of data required by the filter process:
 *   - 'value': The text value to filter.
 *   - 'format': (optional) The filter id to be used during the process.
 *
 * @return string
 *   The filtered variable value.
 */
function _ecas_filter_variable_text(array $raw_text_parameters) {
  if (!empty($raw_text_parameters['format'])) {
    return check_markup($raw_text_parameters['value'], $raw_text_parameters['format']);
  }

  return check_markup($raw_text_parameters['value']);
}

/**
 * Gets the default value of a message linked to a specific warning.
 *
 * @param string $related_variable_name
 *   The name of the variable related to the default value to retrieve.
 *
 * @return array
 *   The default message value and the format to apply on it.
 *
 * @see ecas_warning_page()
 * @see ecas_variable_info()
 * @see ecas_admin_settings()
 */
function _ecas_get_default_warning_message($related_variable_name) {
  switch ($related_variable_name) {
    case ECAS_WARNING_MESSAGE:
      $value = 'Your account is not yet approved';
      break;

    case ECAS_WARNING_MESSAGE_SOCIAL:
      $value = 'please use <a href="https://ecas.ec.europa.eu/cas/logout">EU login</a>.';
      break;

    case ECAS_WARNING_MESSAGE_NO_EMAIL:
      $value = <<< EOF
      We cannot log you in without a valid email.<br />
      Please complete your EU-Login account or contact <a href="https://ecas.ec.europa.eu/cas/contact.html">EU-Login support</a>.
EOF;
      break;

    case ECAS_WARNING_MESSAGE_EXISTING_EMAIL:
      $value = <<< EOF
      We cannot log you in as the e-mail of your EU Login is already used by another account.<br /> 
      Please log in with this existing account.
EOF;
      break;

    case ECAS_WARNING_MESSAGE_NOT_CREATED:
      $value = <<< EOF
      An error occurred that prevent us to create your account.
EOF;
      break;

    case ECAS_WARNING_MESSAGE_INCOMPLETE_USER:
      $value = <<< EOF
      We do not receive all required data of your EU Login. That prevent us to create your account.<br /> 
      Please complete your EU-Login account or contact <a href="https://ecas.ec.europa.eu/cas/contact.html">EU-Login support</a>.
EOF;
      break;

    default:
      $value = "The reason is unknown. Please contact the site's administrator.";
      break;
  }

  return array(
    'value' => $value,
    'format' => 'filtered_html',
  );
}

/**
 * Gets the default value of a login message variable.
 *
 * @return string
 *   The default message value.
 *
 * @see ecas_warning_page()
 * @see ecas_variable_info()
 * @see ecas_admin_settings()
 */
function _ecas_get_default_login_message() {
  return 'Logged in via EU Login as %ecas_username.';
}
