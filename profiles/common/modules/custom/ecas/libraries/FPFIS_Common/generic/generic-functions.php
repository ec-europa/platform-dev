<?php

/***************************************************************************
 *                            generic-functions.php
*                            -------------------
*   author            :    DIGIT FPFIS SUPPORT
*   email                : DIGIT-FPFIS-SUPPORT@ec.europa.eu
*   Revisions
*     - See sources repository
*
***************************************************************************/

/*
 Generic functions used by several applications for common or specific purposes
*/

/*
 * Used to catch the warnings the ldap library throws at us,
 * and redirect those warnings to Drupal in a more user friendly way
 */
function ldapErrorHandler($errno, $errstr, $errfile, $errline)
{  
  if($errno==2){
    if(strpos($errstr, 'Adminlimit exceeded') !== FALSE) {
      $message = t('The search returned only a partial search result because the search result limit was exceeded. Adjust you search criteria or contact your LDAP server administrator.');
      drupal_set_message("<i>Notice:</i> " . $message, 'status');
      return;
    } else if(strpos($errstr, 'Unable to bind to server: No such object') !== FALSE){
      // Error is handled in code itself
      return;
    }
  }
    
  $message = "[$errno] $errstr<br />\n (line $errline of $errfile)";
    
  switch ($errno) {
    default:
    case E_USER_ERROR:
      drupal_set_message("<i>Error:</i> " . $message, 'error');
      break;
    case E_USER_WARNING:
    case E_WARNING:
      drupal_set_message("<i>Warning:</i> " . $message, 'warning');
      break;
    case E_USER_NOTICE:
    case E_NOTICE:      
      drupal_set_message("<i>Notice:</i> " . $message, 'status');
      break;
  }
}


/*
 Hack to record the real IP address of the visitor when the application is mapped behind a proxy
WARNING: HTTP_CLIENT_IP is a custom header added by BlueCoat proxies
*/

if (!function_exists('getRemoteAddrBehindProxy'))
{
  function getRemoteAddrBehindProxy()
  {
    $remote_addr = '';
    if ( !empty($_SERVER['REMOTE_ADDR']) )
      $remote_addr = $_SERVER['REMOTE_ADDR'];
    if ( !empty($_SERVER['HTTP_X_FORWARDED_FOR']) )
      $remote_addr = $_SERVER['HTTP_X_FORWARDED_FOR'];
    if ( !empty($_SERVER['HTTP_CLIENT_IP']) )
      $remote_addr = $_SERVER['HTTP_CLIENT_IP'];
    return $remote_addr;
  }
}

/*
 function getLdapUserInfo
Return on information recorded in the directory bases on the user uid
parameters :
- $uid : user account id
- $extra : array of extra parameters that the function must return, example : array('dg','sn','givenname')
*/
if (!function_exists('getLdapUserInfo'))
{
  function getLdapUserInfo($uid, $extra = null)
  {
    set_error_handler('ldapErrorHandler');

    $ldap = '';
    $result = false;

    if (defined('FPFIS_LDAP_SERVER_PORT') && FPFIS_LDAP_SERVER_PORT)
    {
      $ldap = ldap_connect(FPFIS_LDAP_SERVER_NAME, FPFIS_LDAP_SERVER_PORT);
    }
    else
    {
      $ldap = ldap_connect(FPFIS_LDAP_SERVER_NAME);
    }

    ldap_set_option($ldap, LDAP_OPT_PROTOCOL_VERSION, 3);
    ldap_set_option($ldap, LDAP_OPT_REFERRALS, 0);

    if (FPFIS_LDAP_USER_DN || FPFIS_LDAP_PASSWORD)
    {
      if(!ldap_bind($ldap, FPFIS_LDAP_USER_DN, FPFIS_LDAP_PASSWORD)){
        trigger_error('Could not connect with the LDAP server. Please check your settings.', E_USER_ERROR);
        ldap_close($ldap);
        restore_error_handler();
        return false;            
      }
    }

    $search = ldap_search($ldap, FPFIS_LDAP_BASE_DN, FPFIS_LDAP_UID."=$uid");
    $ldap_result = ldap_get_entries($ldap, $search);

    if ($ldap_result['count'] != 0)
    {
      $result['uid'] = $ldap_result[0][FPFIS_LDAP_UID][0];
      $result['cn'] = $ldap_result[0][FPFIS_LDAP_CN][0];
      $result['mail'] = $ldap_result[0][FPFIS_LDAP_MAIL][0];

      if($extra != null)
      {
        foreach($extra as $extra_value)
			  {
				  $result[$extra_value] = (isset($ldap_result[0][$extra_value]) ? $ldap_result[0][$extra_value][0] : '');
			  }
      }
    }

    unset($ldap_result);

    ldap_close($ldap);

    restore_error_handler();

    return $result;
  }
}

/*
 function getLdapEntries
parameters :
- $base_dn
- $filter
- $extra : array of extra parameters that the function must return, example : array('dg','sn','givenname')
*/
if (!function_exists('getLdapEntries'))
{
  function getLdapEntries($base_dn, $filter, $extra = null) {

    set_error_handler('ldapErrorHandler');
    
    $ldap = '';

    if (FPFIS_LDAP_SERVER_PORT)
    {
      $ldap = ldap_connect(FPFIS_LDAP_SERVER_NAME, FPFIS_LDAP_SERVER_PORT);
    }
    else
    {
      $ldap = ldap_connect(FPFIS_LDAP_SERVER_NAME);
    }

    ldap_set_option($ldap, LDAP_OPT_PROTOCOL_VERSION, 3);
    ldap_set_option($ldap, LDAP_OPT_REFERRALS, 0);

    if (FPFIS_LDAP_USER_DN || FPFIS_LDAP_PASSWORD) {
      if(!ldap_bind($ldap, FPFIS_LDAP_USER_DN, FPFIS_LDAP_PASSWORD)){
        trigger_error('Could not connect with the LDAP server. Please check your settings.', E_USER_ERROR);
        ldap_close($ldap);
        restore_error_handler();
        return;
      }
    }

    if (empty($base_dn))
    {
      $base_dn = FPFIS_LDAP_BASE_DN;
    }

    $search = ldap_search($ldap, $base_dn, $filter, $extra);
    $ldap_result = ldap_get_entries($ldap, $search);

    ldap_close($ldap);

    restore_error_handler();
    
    return $ldap_result;
  }
}

/*
 function getCountryList
return an array with the list of the countries in the EU
*/
if (!function_exists('getCountryList'))
{
  function getCountryList() {
    $list_country = array(
        "BE" => "Belgique/België/Belgien",
        "BG" => "България",
        "CZ" => "Česko",
        "DK" => "Danmark",
        "DE" => "Deutschland",
        "EE" => "Eesti",
        "IE" => "Éire/Ireland",
        "GR" => "Eλλας",
        "ES" => "España",
        "FR" => "France",
        "IT" => "Italia",
        "CY" => "Κυπρος/Kıbrıs",
        "LV" => "Latvija",
        "LT" => "Lietuva",
        "LU" => "Luxembourg",
        "HU" => "Magyarország",
        "MT" => "Malta",
        "NL" => "Nederland",
        "AT" => "Österreich",
        "PL" => "Polska",
        "PT" => "Portugal",
        "RO" => "România",
        "SI" => "Slovenija",
        "SK" => "Slovensko",
        "FI" => "Suomi/Finland",
        "SE" => "Sverige",
        "UK" => "United Kingdom",
    );
    return $list_country;
  }
}

/*
 Overload REMOTE_ADDR in ENV vars
*/

if (!function_exists('overwriteRemoteAddr'))
{
  function overwriteRemoteAddr($overwrite = false)
  {
    if ((defined('FPFIS_OVERWRITE_REMOTE_ADDR') && FPFIS_OVERWRITE_REMOTE_ADDR) || $overwrite)
    {
      if (function_exists('getRemoteAddrBehindProxy'))
      {
        $remote_addr = getRemoteAddrBehindProxy();
        $_SERVER['REMOTE_ADDR'] = $remote_addr;
        if (function_exists('putenv'))
        {
          putenv('REMOTE_ADDR='.$_SERVER['REMOTE_ADDR']);
        }
        $_ENV['REMOTE_ADDR'] = $_SERVER['REMOTE_ADDR'];
        if (function_exists('apache_setenv'))
        {
          apache_setenv('REMOTE_ADDR',$_SERVER['REMOTE_ADDR']);
        }
      }
    }
  }
}

/*
 Create a context to get files through a proxy with file_get_contents
*/
if (!function_exists('setProxyContext'))
{
  function setProxyContext($authentication = true)
  {
    $context = null;
    if (
        defined('FPFIS_PROXY_SCHEME') &&
        defined('FPFIS_PROXY_PROTOCOL') &&
        defined('FPFIS_PROXY_HOST') &&
        defined('FPFIS_PROXY_PORT')
    )
    {
      $proxy_scheme = str_replace('://','',FPFIS_PROXY_SCHEME);
      $aContext = array(
          $proxy_scheme => array(
              'proxy' => FPFIS_PROXY_PROTOCOL.'://'.FPFIS_PROXY_HOST.':'.FPFIS_PROXY_PORT,
              'request_fulluri' => True,
              'timeout' => 1
          ),
      );

      if ( $authentication && defined('FPFIS_PROXY_USER') && defined('FPFIS_PROXY_PASSWORD') )
      {
        $aContext[$proxy_scheme]['header'] = sprintf("Proxy-Authorization: Basic %s\r\n",base64_encode(FPFIS_PROXY_USER.':'.FPFIS_PROXY_PASSWORD));
      }

      $context = stream_context_create($aContext);
    }
    return $context;
  }
}

/*
 Return true if the url matches one of the patterns to check
*/
if (!function_exists('checkProxyRules'))
{
  function checkProxyRules($item,$check_type) {
    if (defined('FPFIS_PROXY_RULES')) {
      $fpfis_proxy_rules = unserialize(FPFIS_PROXY_RULES);
      foreach ( $fpfis_proxy_rules[$check_type] as $line) {
        if (preg_match('@'.$line.'@i',$item)) {
          return true;
        }
      }
    }
    return false;
  }
}

?>
