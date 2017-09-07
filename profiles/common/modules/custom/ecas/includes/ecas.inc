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
 */
function ecas_form_user_pass_alter(&$form, &$form_state, $form_id) {
  array_unshift($form['#validate'], '_ecas_user_pass_validate');
}

/**
 * Validate the user/password form.
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

  $items['account_request'] = array(
    'title' => 'Create an EU Login account',
    'page callback' => 'account_request',
    'access callback' => 'ecas_menu_check',
    'type' => MENU_SUGGESTED_ITEM,
  );

  $items['ecas_warning_page'] = array(
    'title' => 'EU Login warning',
    'page callback' => 'ecas_warning_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );

  return $items;
}

/**
 * Checks the menu.
 *
 * @return bool
 *   TRUE when the user is anonymous, or when the path does not start with the
 *   string 'admin/structure/menu'.
 */
function ecas_menu_check() {
  global $user;
  $access = FALSE;
  if ($user->uid == 0) {
    // Access and display ECAS page if anonymous.
    $access = TRUE;
  }
  if (strpos($_GET['q'], 'admin/structure/menu') !== FALSE) {
    // Access and display ECAS page if go to menu admin interface.
    $access = TRUE;
  }
  return $access;
}

/**
 * Redirects the user to the account request page.
 */
function account_request() {
  $account_request_url = variable_get('ecas_account_request_url', ECAS_DEFAULT_ACCOUNT_REQUEST_URL);
  $return_url = url('ecas', array('absolute' => TRUE));
  $account_request_url = str_replace('%local_ecas_url%', $return_url, $account_request_url);
  drupal_goto($account_request_url);
}

/**
 * Redirects the user to the ECAS login page.
 */
function ecas_login_page() {
  ecas_login_check();

  $destination = variable_get('site_frontpage', 'node');

  // If it is the user's first CAS login and initial login redirection is
  // enabled, go to the set page.
  if ($_SESSION['ecas_goto']) {
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
 */
function ecas_logout($full_logout = TRUE) {
  global $user;

  watchdog('user', 'Session closed for %name.', array('%name' => format_username($user)));

  // Destroy the current session.
  session_destroy();
  $user = drupal_anonymous_user();
  module_invoke_all('user_logout', $user);

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
      'service' => variable_get('site_name', 'ecas'),
      'url' => url('front', array('absolute' => TRUE)),
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
  if (!isset($_SESSION['ecas_goto'])) {
    if (arg(0) == 'ecas') {
      // Saving the ECAS page does not make sense, use HTTP referer (absolute
      // URL) instead.
      $referer = (isset($_GET['referer'])) ? $_GET['referer'] : $_SERVER['HTTP_REFERER'];
      $_SESSION['ecas_goto'] = $referer;
    }
    else {
      // Save the Drupal path (i.e. not an absolute URL).
      $_SESSION['ecas_goto'] = $_GET['q'];
    }
  }
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
 *
 * @see ecas_sync_user_info()
 */
function ecas_sync_profile_core(&$user, array $user_info) {
  $field_firstname = trim(variable_get('ecas_profile_core_firstname_field', 'field_firstname'));
  $field_lastname = trim(variable_get('ecas_profile_core_lastname_field', 'field_lastname'));
  $field_ecasmail = trim(variable_get('ecas_profile_core_ecas_email_field', 'field_ecas_mail'));
  $field_ecascreator = trim(variable_get('ecas_profile_core_ecas_creator_field', 'field_creator'));

  // Can be used for all entity types.
  $edit = (array) $user;

  // You can now access the fields without knowing the language.
  if (!empty($field_firstname) && isset($edit[$field_firstname])) {
    $edit[$field_firstname][LANGUAGE_NONE][0]['value'] = $user_info['cas:firstName'];
  }
  if (!empty($field_lastname) && isset($edit[$field_lastname])) {
    $edit[$field_lastname][LANGUAGE_NONE][0]['value'] = $user_info['cas:lastName'];
  }
  if (!empty($field_ecasmail) && isset($edit[$field_ecasmail])) {
    $edit[$field_ecasmail][LANGUAGE_NONE][0]['value'] = $user_info['cas:email'];
  }
  if (!empty($field_ecascreator) && isset($edit[$field_ecascreator])) {
    if ($user_info['cas:domain'] == 'external') {
      $edit[$field_ecascreator][LANGUAGE_NONE][0]['value'] = $user_info['cas:domain'];
    }
    else {
      $edit[$field_ecascreator][LANGUAGE_NONE][0]['value'] = $user_info['cas:domain'] . '/' . $user_info['cas:departmentNumber'];
    }
  }

  // Save changes.
  user_save($user, $edit);
}

/**
 * Update various information of a given user.
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
 */
function ecas_sync_user_info(&$user, array $user_info, array $args) {
  // Update the user mail in the users table.
  if (variable_get('ecas_update_mail_address', TRUE)) {
    $picture = $user->picture;
    // Fix : save file object replaced by fid by user_save function.
    user_save($user, array('mail' => $user_info['cas:email']));
    $user->mail = $user_info['cas:email'];
    $user->picture = $picture;
  }

  // Update extra core user fields.
  if (variable_get('ecas_profile_core_enabled', FALSE)) {
    ecas_sync_profile_core($user, $user_info);
  }

  module_invoke_all('info_ecas_update', $user, $user_info, $args);
}

/**
 * Uses ECAS to log in the user. Also updates her information.
 */
function ecas_login_check() {
  global $user;

  $force_login = _ecas_force_login();
  if ($user->uid) {
    // The user has an uid, and it is > 0 (which is anonymous user's uid) do
    // nothing because user is already logged into Drupal.
  }
  elseif ($force_login != ECAS_NO_LOGIN) {
    $ecas_sync_user_info_args = array();

    // Start a new Drupal session.
    drupal_session_start();

    ecas_save_page();

    _ecas_init_phpcas_client();

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

    if ($force_login === ECAS_LOGIN) {
      phpCAS::forceAuthentication();
    }

    if (phpCAS::isAuthenticated() && (($force_login === ECAS_GATEWAY && ($ecas_logout == NULL || $ecas_logout == 'false')) || ($force_login === ECAS_LOGIN))) {
      $ecas_name = phpCAS::getUser();
      $ecas_attributes = phpCAS::getAttributes();
      $ecas_groups = $ecas_attributes['cas:groups'];
      $ecas_email = $ecas_attributes['cas:email'];

      // Try to log into Drupal.
      $account = user_load_by_name($ecas_name);

      // Extra process to filter ECAS user.
      drupal_alter('ecas_extra_filter', $ecas_name, $account, $_SESSION['ecas_goto']);
    }
    else {
      // These variables will be checked by later conditions.
      $account = FALSE;
      $ecas_name = NULL;
    }

    // If we don't have a user register them.
    if (!$account && !empty($ecas_name)) {

      $account = ecas_create_user($ecas_name);

      if ($account && $account->uid > 0) {
        $_SESSION['ecas_goto'] = sprintf('user/%d/edit', $account->uid);
      }

      // Set a session variable to denote this the initial login.
      $_SESSION['ecas_first_login'] = TRUE;

      // Also set an extra parameter for ecas_sync_user_info() -- this allows
      // other modules to detect a user creation.
      $ecas_sync_user_info_args['ecas_user_creation'] = TRUE;
    }

    // Final check to make sure we have a good user.
    if ($account && $account->uid > 0) {
      // Retrieve information about the user from ECAS attributes.
      $user_info = phpCAS::getAttributes();

      // Update her information.
      if (!empty($user_info)) {
        ecas_sync_user_info($account, $user_info, $ecas_sync_user_info_args);
      }
      else {
        $args = array(':username' => $account->name);
        drupal_set_message(t('Warning: no information could be found for username :username', $args));
      }

      if ($account->status == 0) {
        // Case when account is blocked.
        session_destroy();

        $user = drupal_anonymous_user();

        // Since the user is blocked, we absolutely want to redirect the user
        // to the ECAS warning page - thus, we unset any previously set
        // destination.
        if (isset($_REQUEST['destination'])) {
          unset($_REQUEST['destination']);
        }
        if (isset($_REQUEST['edit']['destination'])) {
          unset($_REQUEST['edit']['destination']);
        }
        drupal_goto('ecas_warning_page');
      }
      else {
        $user = $account;
        user_login_finalize();

        // Optionally set a non-secure cookie meaning "the user has logged in
        // using HTTPS and should not use HTTP for the duration of this
        // session".
        $http_cookie_name = variable_get('ecas_sticky_cookie_name', 'drupal_stick_to_https');
        if (drupal_strlen($http_cookie_name)) {
          global $base_path;
          setcookie($http_cookie_name, variable_get('ecas_sticky_cookie_value', 'y'), 0, $base_path, '.' . $_SERVER['HTTP_HOST'], FALSE, TRUE);
        }

        // @todo It is not possible to reliably translate dynamic content using
        //   the t() function. This should be done using i18n_variable instead.
        // @see https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-3637
        // @codingStandardsIgnoreStart
        drupal_set_message(t(variable_get('ecas_login_message', ECAS_DEFAULT_LOGIN_MESSAGE), array('%ecas_username' => $user->name)));
        // @codingStandardsIgnoreEnd
        ecas_login_page();
      }
    }
    // If we have a good user.
    else {
      unset($_SESSION['phpCAS']);
      $user = drupal_anonymous_user();
    }
  }
}

/**
 * Check to see if we need to display the logout menu.
 *
 * @return bool
 *   TRUE if the user is logged via ECAS, FALSE otherwise.
 */
function ecas_menu_logout_check() {
  global $user;
  $access = FALSE;
  if ($user->uid) {
    // We provide access to this menu entry only if we are logged via ECAS.
    $access = isset($_SESSION['phpCAS']) && $_SESSION['phpCAS']['user'] === $user->name;
  }
  return $access;
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

        // NOTE: special care needs to be taken because on pages with forms,
        // such as node and comment submission pages, the $edit variable might
        // already be set.
        $output .= l(t('Login'), 'ecas');
        $output .= '</div>' . "\n";
        $block['subject'] = t('User Login');
        $block['content'] = $output;
      }
      else {
        $output = '<div class="user-login-block">' . "\n";

        // NOTE: special care needs to be taken because on pages with forms,
        // such as node and comment submission pages, the $edit variable might
        // already be set.
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
  if ($arg0 == 'user' && empty($arg1)) {
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
 * Page callback; displays the 'ecas_warning_page' page.
 */
function ecas_warning_page() {
  $output = '';

  $output .= '<h2 class="ecl-heading ecl-heading--h2">' . t('Account blocked') . '</h2>';
  $output .= '<p>' . variable_get('ecas_warning_message', t('Your account is not yet approved')) . '</p>';

  return $output;
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
    // @todo Use REQUEST_TIME instead of time().
    'access' => time(),
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
