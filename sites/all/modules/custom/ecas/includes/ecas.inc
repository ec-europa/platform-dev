<?php

/**
 * @file
 * This file embeds the actual code of the ecas module.
 */

/**
 * Implements hook_init().
 * Traps a page load to see if authentication is required.
 */
/*MOVED TO THE ecas_login_page() */
/*
function ecas_init() {
  ecas_login_check();
}*/

/**
 * @param $user A user object
 * @return TRUE if the given user is an ECAS user, FALSE otherwose
 */
function _is_ecas_user($user) {
  if ($authmap_res = db_query('SELECT module FROM {authmap} WHERE uid = :uid', array('uid' => $user->uid))) {
    if ($first_record = $authmap_res->fetchAssoc()) {      
      if ($first_record['module'] == 'ecas') {
        return (TRUE);
      }
    }
  }
  return (FALSE);
}

/**
 * Handle any form modification in this module.
 */
function ecas_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'user_profile_form') {
    $user = user_load($form['#user']->uid); // load the user related to the profile
    
    if (_is_ecas_user($user)) {
      // remove the "Current password"
      $form['account']['current_pass']['#access'] = FALSE;
            
      // remove the "Password", "Confirm password" ...
      $form['account']['pass']['#access'] = FALSE;
      // ... and "E-mail address" fields from the 'user/%/edit' page
      
      // $form['account']['mail']['#access'] = FALSE;
      if(!empty($user->mail))
        $form['account']['mail']['#disabled'] = TRUE;
      
      // disable the firstname and lastname fields
      $form['field_firstname']['#disabled'] = TRUE;
      $form['field_lastname']['#disabled'] = TRUE;
      
      // disable the creator field
      $form['field_creator']['#disabled'] = TRUE;
      
       // disable the name field
      $form['account']['name']['#disabled'] = TRUE;

      $ecas_ch_pw_url = variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL);
      $form['account']['ecas_information_label'] = array(
          '#markup' => sprintf(
              t('This account is managed by ECAS. Its password can be changed using %s.'),
              l('the ECAS change password page', $ecas_ch_pw_url)
          ),
          '#weight' => -10
      ); 
    }
  }
  elseif ($form_id == 'user_pass') {
    $form['#validate'] = array('_ecas_user_pass_validate');
  }
}

/**
 * Validate the user/password form: if the given user is an ECAS user,
 * provide an ECAS-related URL instead of sending a mail with erroneous
 * instructions.
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
      $message = t('This user appears to be an ECAS user -- you can not recover his password using this form. Please visit %s instead');
      $displayed_message = sprintf($message, $ecas_ch_pw_link);
      form_set_error('name', $displayed_message);
      return;
    }
  }
  user_pass_validate($form, $form_state);
}

/**
 * Private function for hook_menu().
 */
function _ecas_menu(&$items) {
  $items['ecas'] = array(
      'path' => 'ecas',
      'title' => 'ECAS Login',
      'page callback' => 'ecas_login_page',
      'access callback' => 'ecas_menu_check',
      'type' => MENU_SUGGESTED_ITEM,
  );

  $items['ecaslogout'] = array(
      'title' => 'ECAS Logout',
      'page callback' => 'ecas_logout',
      'access callback' => 'ecas_menu_logout_check',
      'type' => MENU_SUGGESTED_ITEM,
  );
  $items['ecasfulllogout'] = array(
      'title' => 'ECAS Full Logout',
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
  if (strpos($_GET['q'], 'admin/structure/menu') !== FALSE) { // access and display ecas page if go to menu admin interface
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
  ecas_login_check();
  global $user;

  $destination = variable_get('site_frontpage', 'node');

  // If it is the user's first CAS login and initial login redirection is enabled, go to the set page
  if ($_SESSION['ecas_goto']) {
    $destination = $_SESSION['ecas_goto'];
    unset($_SESSION['ecas_goto']);
  }

  $force_proto = variable_get('ecas_force_proto', FALSE);
  if (strlen($force_proto)) {
    $destination = preg_replace('/^(https?:\/\/)/', $force_proto . '://', $destination);
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
  module_invoke_all('user_logout', $user);

  // We have to use $GLOBALS to unset a global variable:
  $user = user_load(0);

  unset($_SESSION['ecas_goto']);
  // Removes the optional sticky cookie
  $http_cookie_name = variable_get('ecas_sticky_cookie_name', 'drupal_stick_to_https');
  if (strlen($http_cookie_name)) {
    global $base_path;
    setcookie($http_cookie_name, 'deleted', time() - 86400, $base_path , '.' . $_SERVER['HTTP_HOST'], FALSE, TRUE);
  }

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
  // The page is saved only if it is not done already.
  if (!isset($_SESSION['ecas_goto'])) {
    if (arg(0) == 'ecas') {
      // Saving the ecas page does not make sense, use HTTP referer (absolute URL) instead.
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
 * Update the extra core userfields of a given user
 * @see ecas_sync_user_info()
 */
function ecas_sync_profile_core(&$user, $user_info) {

  $field_firstname = trim(variable_get('ecas_profile_core_firstname_field', 'field_firstname'));
  $field_lastname = trim(variable_get('ecas_profile_core_lastname_field',  'field_lastname' ));
  $field_ecasmail = trim(variable_get('ecas_profile_core_ecas_email_field', 'field_ecas_mail'));
  $field_ecascreator = trim(variable_get('ecas_profile_core_ecas_creator_field', 'field_creator'));
  
  // Can be used for all entity types
  $edit = (array) $user;
  
  // You can now access the fields without knowing the language
  if(!empty($field_firstname) && isset($edit[$field_firstname])) {
    $edit[$field_firstname][LANGUAGE_NONE][0]['value'] = $user_info['givenname'];
  }
  if(!empty($field_lastname) && isset($edit[$field_lastname])) {
    $edit[$field_lastname][LANGUAGE_NONE][0]['value'] = $user_info['sn'];
  }
  if(!empty($field_ecasmail) && isset($edit[$field_ecasmail])) {
   $edit[$field_ecasmail][LANGUAGE_NONE][0]['value'] = $user_info['mail'];
  }
  if(!empty($field_ecascreator) && isset($edit[$field_ecascreator])) {
   $edit[$field_ecascreator][LANGUAGE_NONE][0]['value'] = $user_info['sourceorganisation'].'/'.$user_info['departmentnumber'];
  }  
  
  // save changes 
  user_save($user, $edit);
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
    $picture = $user->picture; // fix : save file object replaced by fid by user_save function
    user_save($user, array('mail' => $user_info['mail']));
    $user->mail = $user_info['mail'];
    $user->picture = $picture;
  }

  // update extra core user fields
  if(variable_get('ecas_profile_core_enabled', FALSE)){
    ecas_sync_profile_core($user, $user_info);
  }

  module_invoke_all('info_ecas_update', $user, $user_info, $args);
}

/**
 * Uses ECAS to log in the user. Also updates her informations.
 */
function ecas_login_check() {
  global $user;
  
  $force_login = _ecas_force_login();
  if ($user->uid) { // the user has an uid, and it is > 0 (which is anonymous user's uid)
    // do nothing because user is already logged into Drupal
  }
  elseif ($force_login != ECAS_NO_LOGIN) {
    $ecas_sync_user_info_args = array();

    // Start a new drupal session
    drupal_session_start();
    
    ecas_save_page();

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
      $account = user_load_by_name($ecas_name);
      
      // extra process to filter ecas user
      drupal_alter('ecas_extra_filter', $ecas_name, $account, $_SESSION['ecas_goto']);
    }
    else {
      // these variables will be checked by later conditions
      $account = FALSE;
      $ecas_name = NULL;
    }

    // If we don't have a user register them.
    if (!$account && !empty($ecas_name)) {
      
      $account = ecas_create_user($ecas_name); 
      
/*      $user_default = array(
          'name' => $ecas_name,
          'pass' => user_password(),
          'init' => $ecas_name,
          'status' => variable_get('ecas_account_option', 1),
          'access' => time(),
          'auth_ecas' => 'ecas_' . $ecas_name,
      );

      $user_default['mail'] = variable_get('ecas_default_mail_address', ECAS_DEFAULT_MAIL_ADDRESS);

      // Become user 1 to be able to save profile information
      //drupal_save_session(FALSE);
      //$user = user_load(1);

      // now save the user
      $account = user_save(drupal_anonymous_user(), $user_default);

      // Register the user has ECAS authentication
      $cas_authmap = db_insert('authmap')
        ->fields(array(
          'authname' => $ecas_name,
          'uid' => $account->uid,
          'module' => 'ecas',
        ))
        ->execute();
          
      //drupal_save_session(TRUE);
            
      watchdog('user', 'new user: %n (ECAS)', array('%n' => $account->name), WATCHDOG_NOTICE, l(t('edit user'), sprintf('admin/user/edit/%d', $account->uid)));
*/
      if ($account && $account->uid > 0) {
        /*user_module_invoke('login', $edit = NULL, $user);
        unset($_SESSION['ecas_goto']);        
        watchdog('user', 'Session opened for %name.', array('%name' => $user->name));
*/
        $_SESSION['ecas_goto'] = sprintf('user/%d/edit', $account->uid);
//        drupal_goto(sprintf('user/%d/edit', $account->uid));
      }
      
      // Set a session variable to denote this the initial login
      $_SESSION['ecas_first_login'] = TRUE;

      // also set an extra parameter for ecas_sync_user_info() -- this allows
      // other modules to detect a user creation
      $ecas_sync_user_info_args['ecas_user_creation'] = TRUE;
    }

    // final check to make sure we have a good user
    if ($account && $account->uid > 0) {
      // avoid calling ldap_* functions if they are not available
      if (function_exists('getLdapUserInfo')) {
        // retrieve informations about the user through LDAP
        $LDAP_info = array('sn', 'givenname', 'dg', 'sourceorganisation', 'departmentnumber');
        drupal_alter('ecas_LDAP_info', $LDAP_info);
        $user_info = getLdapUserInfo($account->name, $LDAP_info);

        // update her informations
        if (!empty($user_info)) {
          ecas_sync_user_info($account, $user_info, $ecas_sync_user_info_args);
        }
        else {
          drupal_set_message(
              t('Warning: no information could be found for username :username'),
              array(':username' => $account->name)
          );
        }
      }

      if ($account->status == 0) { // case when account is blocked        
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
        $user = $account;               
        user_login_finalize();        

        // Optionally set a non-secure cookie meaning "the user has logged in
        // using HTTPS and should not use HTTP for the duration of this
        // session".
        $http_cookie_name = variable_get('ecas_sticky_cookie_name', 'drupal_stick_to_https');
        if (strlen($http_cookie_name)) {
          global $base_path;
          setcookie($http_cookie_name, variable_get('ecas_sticky_cookie_value', 'y') /* dummy value */, 0 /* disappear when the browser closes */, $base_path , '.' . $_SERVER['HTTP_HOST'], FALSE, TRUE);
        }

        drupal_set_message(t(variable_get('ecas_login_message', ECAS_DEFAULT_LOGIN_MESSAGE), array('%ecas_username' => $user->name)));
        ecas_login_page();
      }
    } // if we have a good user
    else {
      unset($_SESSION['phpCAS']);
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
    $access = (isset($_SESSION['phpCAS']) && $_SESSION['phpCAS']['user'] === $user->name);
  }
  return $access;
}

/**
 * Implements hook_block_view().
 * Provides login blog that only shows up when the user logs in.
 */
function ecas_block_view($delta = '') {
  global $user;

  $block = array();

  switch ($delta) {
    case 'ecas':
      if (!$user->uid) { // && !(arg(0) == 'user' && !is_numeric(arg(1)) => doesn't make sense, when no user is logged in, you want people to be able to login using ecas, even when they are on the 'user' page 
        $output = '<div class="user-login-block">' . "\n";

        // NOTE: special care needs to be taken because on pages with forms,
        // such as node and comment submission pages, the $edit variable
        // might already be set.
        $output .= l(t('Login'), 'ecas');
        $output .= '</div>' . "\n";
        $block['subject'] = t('User Login');
        $block['content'] = $output;
      }
      else {
        $output = '<div class="user-login-block">' . "\n";

        // NOTE: special care needs to be taken because on pages with forms,
        // such as node and comment submission pages, the $edit variable
        // might already be set.
        $output .= l(t('Logout'), 'ecaslogout');
        $output .= '</div>' . "\n";
        $block['subject'] = t('User Login');
        $block['content'] = $output;
      }
      return $block;
  }
}

/**
 * Implements hook_block_info();
 */
function ecas_block_info() {
  $blocks['ecas'] = array(
      'info' => t('ECAS User login')
  );

  return $blocks;
}

/**
 * Determines whether cas login should be enforced for this page load.
 * This is done based on the redirection settings for this module.
 */
function _ecas_force_login() {

  list($arg0) = explode('/', $_GET['q']);

  // Don't even do the test if we're hitting the cas page
  if ($arg0 == 'ecas' || $arg0 == 'ecaslogout' ) {
    return ECAS_LOGIN;
  }

  // Allow users to access the drupal login page
  if ($arg0 == 'user' && empty($arg1) ) {
    return ECAS_NO_LOGIN;
  }
    
  // Don't even do the test if cron.php or xmlrpc.php is invoked.  Don't require login.
  if (base_path() . 'cron.php' == $_SERVER['PHP_SELF'] || base_path() . 'xmlrpc.php' == $_SERVER['PHP_SELF']) {
    return ECAS_NO_LOGIN;
  }

  // Don't even do the test if it's a RSS feed
  $args = explode('/', $_GET['q']);
  if ($args[count($args)-1] == 'feed')
    return ECAS_NO_LOGIN;

  $method = variable_get('ecas_pages_method', 0);
  $pages = variable_get('ecas_pages', '');

  // This common page matching logic used throughout drupal.
  if ($pages) {
    $path = drupal_get_path_alias($_GET['q']);

    $regexp = '/^(' . preg_replace(array('/(\r\n?|\n)/', '/\\\\\*/', '/(^|\|)\\\\<front\\\\>($|\|)/'), array('|', '.*', '\1' . variable_get('site_frontpage', 'node') . '\2'), preg_quote($pages, '/')) . ')$/';
    $path_match = preg_match($regexp, $path);

    if($method==ECAS_LOGIN_EXLUDE_PAGES){
      if($path_match){
        // current page matches pattern given,
        // so we need to exclude this page from ecas login
        return ECAS_GATEWAY;
      } else {
        return ECAS_LOGIN;
      }
    } else {//ECAS_LOGIN_INCLUDE_PAGES
      if($path_match){
        // current page matches pattern given,
        // so we need to include this page for ecas login
        return ECAS_LOGIN;
      } else {
        return ECAS_GATEWAY;
      }
    }
  } else {
    if($method==ECAS_LOGIN_EXLUDE_PAGES){
      return ECAS_LOGIN;
    } else {//ECAS_LOGIN_INCLUDE_PAGES
      // only on listed pages, but no pages listed,
      // so no login on any page!!
      return ECAS_GATEWAY;
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
    phpCas::setExtraCurlOption($key, $value);
  }
}


function ecas_create_user($ecas_name, $defaults = array()){
  
  $user_default = array_merge(array(
      'name' => $ecas_name,
      'pass' => user_password(),
      'init' => $ecas_name,
      'status' => variable_get('ecas_account_option', 1),
      'access' => time(),
      'auth_ecas' => 'ecas_' . $ecas_name,
      'mail' => variable_get('ecas_default_mail_address', ECAS_DEFAULT_MAIL_ADDRESS)
  ), $defaults);
    
  // Become user 1 to be able to save profile information
  //drupal_save_session(FALSE);
  //$user = user_load(1);
  
  // now save the user
  $account = user_save(drupal_anonymous_user(), $user_default);
  
  // Register the user has ECAS authentication
  $cas_authmap = db_insert('authmap')
  ->fields(array(
      'authname' => $ecas_name,
      'uid' => $account->uid,
      'module' => 'ecas',
  ))
  ->execute();
  
  //drupal_save_session(TRUE);
  
  watchdog('user', 'new user: %n (ECAS)', array('%n' => $account->name), WATCHDOG_NOTICE, l(t('edit user'), sprintf('admin/user/edit/%d', $account->uid)));
  
  if($account){
    $account = user_load_by_name($account->name);
  }
  
  return $account;  
}
