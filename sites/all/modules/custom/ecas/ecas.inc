<?php
// $Id$
/**
 * @file
 * This file embeds the actual code of the ecas module.
 */

/**
 * Implementation of hook_init().
 * Traps a page load to see if authentication is required.
 */
function ecas_init() {
  ecas_login_check();
}

/**
 * Private function for hook_menu().
 */
function _ecas_menu(&$items) {
  $items['ecas'] = array(
    'path' => 'ecas',
    'title' => t('ECAS Login'),
    'page callback' => 'ecas_login_page',
    'access callback' => 'ecas_menu_check',
    'type' => MENU_SUGGESTED_ITEM,
  );

  $items['ecaslogout'] = array(
    'title' => t('ECAS Logout'),
    'page callback' => 'ecas_logout',
    'access callback' => 'ecas_menu_logout_check',
    'type' => MENU_SUGGESTED_ITEM,
  );
  $items['ecasfulllogout'] = array(
    'title' => t('ECAS Full Logout'),
    'page callback' => 'ecas_logout',
    'page arguments' => array(TRUE),
    'access callback' => 'ecas_menu_logout_check',
    'type' => MENU_SUGGESTED_ITEM,
  );

  $items['account_request'] = array(
    'title' => 'Create an ECAS account',
    'page callback' => 'account_request',
    'access callback' => 'ecas_menu_check',
    'type' => MENU_SUGGESTED_ITEM,
  );

  $items['ecas_warning_page'] = array(
    'title' => 'Ecas warning',
    'page callback' => 'ecas_warning_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );

  return $items;
}


function ecas_menu_check() {
  global $user;
  $access = FALSE;
  if ($user->uid == 0) {// access and display ecas page if anonymous
    $access=TRUE;
  }
  if (strpos($_GET['q'], 'admin/build/menu') !== FALSE) { // access and display ecas page if go to menu admin interface
    $access=TRUE;
  }
  return $access;
}

function account_request() {
  $account_request_url = variable_get('ecas_account_request_url', ECAS_DEFAULT_ACCOUNT_REQUEST_URL);
  $return_url = url('ecas', array('absolute' => TRUE));
  $account_request_url = str_replace('%local_ecas_url%', $return_url, $account_request_url);
  drupal_goto($account_request_url);
}

function ecas_login_page() {
  global $user;

  $destination = variable_get('site_frontpage', 'node');

  // If it is the user's first CAS login and initial login redirection is enabled, go to the set page
  if ($_SESSION['ecas_goto']) {
    $destination = $_SESSION['ecas_goto'];
    unset($_SESSION['ecas_goto']);
  }

  drupal_goto($destination);
}

/**
 * Logs a user out of drupal
 * @param $full_logout TRUE to also log out from ECAS itself, FALSE to log out only from Drupal
 */
function ecas_logout($full_logout = FALSE) {
  global $user;

  watchdog('user', 'Session closed for %name.', array('%name' => theme('placeholder', $user->name)));

  // Destroy the current session:
  session_destroy();
  $user = drupal_anonymous_user();
  module_invoke_all('user', 'logout', NULL, $user);

  // We have to use $GLOBALS to unset a global variable:
  $user = user_load(array('uid' => 0));

  // disable auto-authentication
  $_SESSION['phpECAS_logout'] = 'true';

  unset($_SESSION['ecas_goto']);

  if ($full_logout) {
    _ecas_init_phpcas_client();
    $params = array(
      'service' => variable_get('site_name', 'ecas'),
      'url' => url('front', array('absolute' => TRUE))
    );
    drupal_alter('ecas_full_logout_parameters', $params);
    phpCAS::logout($params);
  }

  // Go to the constructed logout destination
  drupal_goto();
}

/**
 * Saves the page that the user was on when login was requested or required.
 */
function ecas_save_page() {
  if (!$_SESSION['ecas_goto']) {
    if (arg(0) == 'ecas') {
      //we're were destined to the CAS login page, so set
      //the page to the referrer.
      $_SESSION['ecas_goto'] = $_SERVER['HTTP_REFERER']; // http_referer doesn't work
    }
    else {
      //We're destined for another page, so save the group.
      $_SESSION['ecas_goto'] = $_GET['q'];
    }
  }
}

/**
 * Update the value of a given profile field for a given user
 * @param $uid      Uid of the given user
 * @param $category Category of the field to update
 * @param $field    Title of the field to update
 * @param $value    New value for the field
 */
function _ecas_update_profile_info($uid, $category, $field, $value) {
  // does not perform the update if the field is empty
  if (!strlen(trim($field))) return;
  return (
    db_query(
      "REPLACE INTO {profile_values} (fid, uid, value)
      SELECT MAX(fid), %d, '%s'
      FROM {profile_fields}
      WHERE category = '%s'
      AND title = '%s'",
      $uid,
      $value,
      $category,
      $field
    )
  );
}

/**
 * Update the profile of a given user
 * @see ecas_sync_user_info()
 */
function ecas_sync_user_profile(&$user, $user_info) {
  // retrieve the configuration variables related to the integration with the Profile module
  $firstname_profile_category = trim(variable_get('ecas_profile_firstname_category', ECAS_PROFILE_DEFAULT_CATEGORY));
  $firstname_profile_field    = trim(variable_get('ecas_profile_firstname_field',    ECAS_PROFILE_DEFAULT_FIRSTNAME_FIELD));
  $lastname_profile_category  = trim(variable_get('ecas_profile_lastname_category',  ECAS_PROFILE_DEFAULT_CATEGORY));
  $lastname_profile_field     = trim(variable_get('ecas_profile_lastname_field',     ECAS_PROFILE_DEFAULT_LASTNAME_FIELD));
  $ecasmail_profile_category  = trim(variable_get('ecas_profile_ecas_mail_category', ECAS_PROFILE_DEFAULT_CATEGORY));
  $ecasmail_profile_field     = trim(variable_get('ecas_profile_ecas_mail_field',    ECAS_PROFILE_DEFAULT_ECAS_MAIL_FIELD));

  _ecas_update_profile_info($user->uid, $firstname_profile_category, $firstname_profile_field, $user_info['givenname']);
  _ecas_update_profile_info($user->uid, $lastname_profile_category,  $lastname_profile_field,  $user_info['sn']);
  _ecas_update_profile_info($user->uid, $ecasmail_profile_category,  $ecasmail_profile_field,  $user_info['mail']);
}

/**
 * Update the Content Profile of a given user
 * @see ecas_sync_user_info()
 */
function ecas_sync_user_content_profile(&$user, $user_info) {
  $content_profile_type = variable_get('ecas_content_profile_type', 'profile');

  $firstname_content_profile_field = trim(variable_get('ecas_content_profile_firstname_field', 'field_firstname'));
  $lastname_content_profile_field  = trim(variable_get('ecas_content_profile_lastname_field',  'field_lastname' ));
  $mail_content_profile_field      = trim(variable_get('ecas_content_profile_mail_field',      'field_ecas_mail'));

  // create a content profile for this user if needed
  $profile_node = new stdClass();

  // we just need to set the type to use content_profile_profile_exists
  $profile_node->type = $content_profile_type;
  if (!content_profile_profile_exists($profile_node, $user->uid)) {
    $profile_node->title  = $user->name;
    $profile_node->uid    = $user->uid;
    $profile_node->status = 1;
  }
  else {
    $profile_node = content_profile_load($content_profile_type, $user->uid, '', TRUE);
  }

  // set the values for this user
  if (drupal_strlen($firstname_content_profile_field)) {
    $profile_node->$firstname_content_profile_field = array(0 => array('value' => $user_info['givenname']));
  }
  if (drupal_strlen($lastname_content_profile_field)) {
    $profile_node->$lastname_content_profile_field  = array(0 => array('value' => $user_info['sn']));
  }
  if (drupal_strlen($mail_content_profile_field)) {
    $profile_node->$mail_content_profile_field      = array(0 => array('email' => $user_info['mail']));
  }

  // save the content profile
  node_save($profile_node);
}

/**
 * Sync the roles of a given user based on LDAP informations,
 * using the group_sync module
 * @param $user A user object
 * @return false if sync failed, true otherwise
 */
function ecas_sync_user_group_sync(&$user, $user_info) {
  /* synchronization with LDAP */
  require_once(drupal_get_path('module', 'group_sync') .'/LDAPInterface.inc');
  $result = group_sync_account($user->name);
  if ($result) {
    watchdog('php', 'User roles synchronized with LDAP');
  }
  else {
    watchdog('php', 'User roles not synchronized with LDAP');
  }
  return $result;
}

/**
 * Update various informations of a given user: core mail address, profile,
 * Content Profile, roles, ...
 * When all informations have been synced, this function invokes the
 * info_ecas_update hook in all enabled modules that implement it.
 * @param $user A user object
 * @param $user_info array with the following interesting keys:
 *  - mail: mail address
 *  - givenname: first name
 *  - sn: last name
 *  These values will be used to fill fields/profiles/...
 * @param $args Extra parameters, not used directly in this function but passed
 * to the info_ecas_update hook.
 */
function ecas_sync_user_info(&$user, $user_info, $args) {
  // update the user mail in the users table
  if (variable_get('ecas_update_mail_address', TRUE)) {
    user_save($user, array('mail' => $user_info['mail']));
    $user->mail = $user_info['mail'];
  }

  // update the user profile if available and enabled
  if (module_exists('profile') && variable_get('ecas_profile_enabled', FALSE)) {
    ecas_sync_user_profile($user, $user_info);
  }

  // update the user Content Profile if available and enabled
  if (module_exists('content_profile') && variable_get('ecas_content_profile_enabled', FALSE)) {
    ecas_sync_user_content_profile($user, $user_info);
  }

  // sync the roles of the user based on LDAP informations, using the group_sync module
  if (module_exists('group_sync') && variable_get('ecas_group_sync_enabled', FALSE)) {
    ecas_sync_user_group_sync($user);
  }

  module_invoke_all('info_ecas_update', $user, $user_info, $args);
}

/**
 * Uses ECAS to log in the user. Also updates her informations.
 */
function ecas_login_check() {
  global $user, $account;
  $force_login = _ecas_force_login();
  if ($user->uid) { // the user has an uid, and it is > 0 (which is anonymous user's uid)
    // do nothing because user is already logged into Drupal
  }
  elseif ($force_login != ECAS_NO_LOGIN) {
    $ecas_sync_user_info_args = array();

    ecas_save_page();
    $ecas_logout = $_SESSION['phpECAS_logout'];
    if ($force_login === ECAS_GATEWAY && ($ecas_logout == NULL || $ecas_logout == 'false')) {
      if ($_SERVER['QUERY_STRING'] == '' && strpos($_SERVER['PHP_SELF'], '?q=') === FALSE) {
        $_SERVER['PHP_SELF'] .= '?q=' . $GLOBALS['_GET']['q'];
      }
    }

    _ecas_init_phpcas_client();

    // Adds an optional "domain" parameter to the login URL - this allows Drupal
    // admins to specify the default ecas domain to be displayed on the login
    // page when none could be found in the cookies sent by the browser.
    $ecas_domain = (string)variable_get('ecas_domain', '');
    if (drupal_strlen($ecas_domain)) {
      $initial_server_login_url = phpCAS::getServerLoginURL();
      $custom_server_login_url = sprintf('%s&domain=%s', $initial_server_login_url, urlencode($ecas_domain));
      phpCAS::setServerLoginURL($custom_server_login_url);
    }

    if ($force_login === ECAS_LOGIN) {
      phpCAS::forceAuthentication();
    }

    if (phpCAS::isAuthenticated() && (($force_login === ECAS_GATEWAY && ($ecas_logout == NULL || $ecas_logout == 'false')) || ($force_login === ECAS_LOGIN))) {
      $ecas_name = phpCAS::getUser();
      // try to log into Drupal
      $user = user_load(array('name' => $ecas_name));
    }
    else {
      // these variables will be checked by later conditions
      $user = NULL;
      $ecas_name = NULL;
    }

    // If we don't have a user register them.
    if (!$user->uid && ($ecas_name != NULL || $ecas_name != '')) {
      $user_default = array(
        'name' => $ecas_name,
        'pass' => user_password(),
        'init' => $ecas_name,
        'status' => variable_get('ecas_account_option', 1),
        'access' => time(),
        'auth_ecas' => 'ecas_' . $ecas_name,
      );

      $user_default['mail'] = variable_get('ecas_default_mail_address', ECAS_DEFAULT_MAIL_ADDRESS);

      // Become user 1 to be able to save profile information
      session_save_session(FALSE);
      $admin = array('uid' => 1);
      $user = user_load($admin);

      // now save the user
      $user = user_save('', $user_default);

      session_save_session(true);
      watchdog('user', 'new user: %n (ECAS)', array('%n' => $user->name), WATCHDOG_NOTICE, l(t('edit user'), sprintf('admin/user/edit/%d', $user->uid)));
      if (($user->uid) && ($user->uid > 0) && $cas_authmap) {
        module_invoke_all('user', 'login', NULL, $user);
        //unset($_SESSION['ecas_goto']);
        watchdog('user', 'Session opened for %name.', array('%name' => $user->name));

        drupal_goto(sprintf('user/%d/edit', $user->uid));
      }

      // Set a session variable to denote this the initial login
      $_SESSION['ecas_first_login'] = TRUE;

      // also set an extra parameter for ecas_sync_user_info() -- this allows
      // other modules to detect a user creation
      $ecas_sync_user_info_args['ecas_user_creation'] = TRUE;
    }

    // final check to make sure we have a good user
    if ($user->uid && $user->uid > 0) {
      // activate auto-authentication
      $_SESSION['phpECAS_logout'] = 'false';

      // avoid calling ldap_* functions if they are not available
      if (function_exists('ldap_connect')) {
        // retrieve informations about the user through LDAP
        $user_info = getLdapUserInfo($user->name, array('sn', 'givenname', 'dg'));

        // load the user as an object
        $user = user_load(array('name' => $user->name));
        // update her informations
        if (!empty($user_info)) {
          ecas_sync_user_info($user, $user_info, $ecas_sync_user_info_args);
        }
        else {
          drupal_set_message(
            t('Warning: no information could be found for username :username'),
            array(':username' => $user->name)
          );
        }
      }

      if ($user->status == 0) { // case when account is blocked
        session_destroy();
        $user = drupal_anonymous_user();
        // since the user is blocked, we absolutely want to redirect the user
        // to the ecas warning page - thus, we unset any previously set destination
        if (isset($_REQUEST['destination'])) {
          unset($_REQUEST['destination']);
        }
        if (isset($_REQUEST['edit']['destination'])) {
          unset($_REQUEST['edit']['destination']);
        }
        drupal_goto('ecas_warning_page');
      }
      else {
        module_invoke_all('user', 'login', NULL, $user);
        drupal_set_message(t(variable_get('ecas_login_message', ECAS_DEFAULT_LOGIN_MESSAGE), array('%ecas_username' => $user->name)));
        watchdog('user', 'Session opened for %name.', array('%name' => $user->name));
        ecas_login_page();
      }
    } // if we have a good user
    else {
      $user = drupal_anonymous_user();
    }
  } // End if user is already logged in else
}

/**
 * Check to see if we need to display the logout menu.
 * @return boolean TRUE if the user is logged via ECAS, FALSE otherwise
 */
function ecas_menu_logout_check() {
  global $user;
  $access = FALSE;
  if ($user->uid) {
    // we provide access to this menu entry only if we are logged via ecas
    $access = ($_SESSION['phpCAS']['user'] === $user->name);
  }
  return $access;
}

/**
 * Implementation of hook_block().
 * Provides login blog that only shows up when the user logs in.
 */
function ecas_block($op = 'list', $delta = 0, $edit = array()) {
  global $user;
  if ($op == 'list') {
    $blocks[0]['info'] = t('ECAS User login');
    return $blocks;
  }
  elseif ($op == 'view') {
    $block = array();

    switch ($delta) {
      case 0:
        // For usability's sake, avoid showing two login forms on one page.
        if (!$user->uid && !(arg(0) == 'user' && !is_numeric(arg(1)))) {
          $edit = $_POST['edit'];

          $output = '<div class="user-login-block">'."\n";

          // NOTE: special care needs to be taken because on pages with forms,
          // such as node and comment submission pages, the $edit variable
          // might already be set.
          $output .= l(t('Login'), 'ecas');
          $output .= '</div>'."\n";
          $block['subject'] = t('User Login');
          $block['content'] = $output;
        }
        else {
          $edit = $_POST['edit'];

          $output = '<div class="user-login-block">'."\n";

          // NOTE: special care needs to be taken because on pages with forms,
          // such as node and comment submission pages, the $edit variable
          // might already be set.
          $output .= l(t('Logout'), 'ecaslogout');
          $output .= '</div>'."\n";
          $block['subject'] = t('User Login');
          $block['content'] = $output;
        }
        return $block;
    }
  }
}

/**
 * Determines whether cas login should be enforced for this page load.
 * This is done based on the redirection settings for this module.
 */
function _ecas_force_login() {

  list($arg0) = split('/', $_GET['q']);

  // Don't even do the test if we're hitting the cas page
  if ($arg0 == 'ecas' || $arg0 == 'ecaslogout' ) {
    return ECAS_LOGIN;
  }

  // Don't even do the test if cron.php or xmlrpc.php is invoked.  Don't require login.
  if (base_path() . 'cron.php' == $_SERVER['PHP_SELF'] || base_path() . 'xmlrpc.php' == $_SERVER['PHP_SELF']) {
    return ECAS_NO_LOGIN;
  }

  // Don't even do the test if it's a RSS feed
  $args = split('/', $_GET['q']);
  if ($args[count($args)-1] == 'feed')
    return ECAS_NO_LOGIN;

  $pages = variable_get('ecas_pages', '');
  // This common page matching logic used throughout drupal.
  if ($pages) {
    $path = drupal_get_path_alias($_GET['q']);
    $regexp = '/^('. preg_replace(array('/(\r\n?|\n)/', '/\\\\\*/', '/(^|\|)\\\\<front\\\\>($|\|)/'), array('|', '.*', '\1'. variable_get('site_frontpage', 'node') .'\2'), preg_quote($pages, '/')) .')$/';
    $path_match = preg_match($regexp, $path);

    // Alter the default
    if ($path_match) {
      return ECAS_LOGIN;
    }
  }

  return ECAS_GATEWAY;
}

/**
 * Generate the 'ecas_warning_page' page.
 */
function ecas_warning_page() {
  $output = '';

  $output .= '<h2>' . t('Account blocked') . '</h2>';
  $output .= '<p>' . variable_get('ecas_warning_message', t('Your account is not yet approved')) . '</p>';

  return $output;
}

/**
 * Initializes the phpCas client
 */
function _ecas_init_phpcas_client() {
  $server_version     = (string)variable_get('cas_version', '2.0');
  $server_ecas_server = FPFIS_ECAS_URL;
  $server_port        = FPFIS_ECAS_PORT;
  $server_uri         = FPFIS_ECAS_URI;
  $start_session      = (boolean)FALSE; // Drupal takes care of its own session
  $assurance_level    = variable_get('ecas_assurance_level', constant('ECAS_DEFAULT_ASSURANCE_LEVEL'));

  // Before using the phpCas client, we optionally set it in debug mode
  if (variable_get('ecas_phpcas_debug', FALSE)) {
    $logpath = variable_get('ecas_phpcas_debug_logpath', constant('ECAS_DEFAULT_DEBUG_LOGPATH'));
    // as specified in ecas_admin_settings(), we do not check whether the logpath is writable or not
    if (drupal_strlen($logpath)) {
      $GLOBALS['PHPCAS_DEBUG']['filename'] = $logpath;
      $GLOBALS['PHPCAS_DEBUG']['indent'] = 2; // arbitrarily set to Drupal indent width
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
    phpCas::setExtraCurlOption($key, $value);
  }
}
