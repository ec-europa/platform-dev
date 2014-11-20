<?php
// Are we coming from the proxy?
$using_proxy = isset($_SERVER['HTTP_CLIENT_IP']);
$using_drush = ($_SERVER['HTTP_HOST'] == 'default' || (isset($multisite_subsite) && $_SERVER['HTTP_HOST'] == $multisite_subsite));
if ($using_proxy || $using_drush) {
  $base_base_url = 'https://webgate.ec.europa.eu';
  $_SERVER['HTTPS'] = 'on';
  $_SERVER['SERVER_PORT'] = '';
  $_SERVER['REMOTE_ADDR'] = $_SERVER['HTTP_CLIENT_IP'];
} else {
  $base_base_url = 'http://' . $_SERVER['HTTP_HOST'];
}
$base_base_path = '/multisite';

$multisite_subsite = trim(@$multisite_subsite);
if (strlen($multisite_subsite)) {
  $base_url = $base_base_url . $base_base_path . '/' . $multisite_subsite;
  ini_set('session.cookie_path', $base_base_path . '/' . $multisite_subsite);
  // $conf['site_frontpage'] = 'content/welcome-your-site';
  $conf['file_public_path']  = sprintf('sites/%s/files', $multisite_subsite);
  $conf['file_private_path'] = sprintf('%s/private_files', $conf['file_public_path']);
} else {
  $base_url = $base_base_url . $base_base_path;
  ini_set('session.cookie_path', $base_base_path);
}

$conf['error_level'] = 1; // 0 is ERROR_REPORTING_HIDE, 1 is ERROR_REPORTING_DISPLAY_SOME, 2 is ERROR_REPORTING_DISPLAY_ALL
$conf['apachesolr_attachments_java'] = realpath(dirname(__FILE__) . '/../../../util/java/current/bin/java');
$conf['apachesolr_attachments_tika_path'] = realpath(dirname(__FILE__) . '/../../../util/tika');
$conf['apachesolr_attachments_tika_jar'] = 'tika-app-1.1.jar';
$conf['file_chmod_directory'] = 02775;
$conf['video_cron'] = FALSE;

// adjust path so ffmpeg is found on both web servers and management machine
$web_path = realpath(dirname(__FILE__) . '/../../../util/ffmpeg');
$mgmt_path = '/ec/local/home/fpfis/util/ffmpeg';
putenv('PATH=' . $web_path . PATH_SEPARATOR . getenv('PATH') . PATH_SEPARATOR . $mgmt_path);
$conf['video_ffmpeg_path'] = 'ffmpeg';

// -------------------------------------------------------------------------------
// Ecas configuration
// -------------------------------------------------------------------------------
define('FPFIS_COMMON_LIBRARIES_PATH', realpath(dirname(__FILE__) . '/../../../util'));
define('FPFIS_ECAS_PATH',             realpath(dirname(__FILE__) . '/../../../util/phpcas/CAS.php'));
if ($_SERVER['HTTP_HOST'] == 'webgate.ec.europa.eu') {
  define('FPFIS_ECAS_URL', 'webgate.ec.europa.eu');
  define('FPFIS_ECAS_PORT', 443);
  define('FPFIS_ECAS_URI', '/cas');
}
else if ($_SERVER['HTTP_HOST'] == 'ec.europa.eu') {
  define('FPFIS_ECAS_URL', 'ecas.ec.europa.eu');
  define('FPFIS_ECAS_PORT', 443);
  define('FPFIS_ECAS_URI', '/cas');
}
else {
  define('FPFIS_ECAS_URL', 'ecas.cc.cec.eu.int');
  define('FPFIS_ECAS_PORT', 7002);
  define('FPFIS_ECAS_URI', '/cas');
}
define('FPFIS_LDAP_SERVER_NAME', 'cedprod.cec.eu.int');
define('FPFIS_LDAP_SERVER_PORT', '10389');
define('FPFIS_LDAP_BASE_DN', 'ou=People,o=cec.eu.int');
define('FPFIS_LDAP_BASE_DN_DG', 'ou=Groups,o=cec.eu.int');
define('FPFIS_LDAP_USER_DN', 'uid=iwt,ou=TrustedApps,o=cec.eu.int');
define('FPFIS_LDAP_PASSWORD', 'F45§g!33');
$conf['ecas_force_proto'] = 'https';

// -------------------------------------------------------------------------------
// Memcached configuration
// -------------------------------------------------------------------------------
$memcached_enabled = TRUE;
if ($memcached_enabled) {
  // Memcached-related options
  $conf['memcache_servers'] = array(
    '158.167.212.50:11211' => 'default', // katalpa.cc.cec.eu.int
    '158.167.212.51:11211' => 'default', // kanianka.cc.cec.eu.int
  );
  $conf['memcache_key_prefix'] = sprintf('ms_p0_%s', isset($multisite_subsite) && strlen($multisite_subsite) ? $multisite_subsite : 'default'); // ms_p0 == MultiSite Production cluster00
  // Memcached client options -- check out http://www.php.net/manual/en/memcached.constants.php for details
  $conf['memcache_options'][Memcached::OPT_BINARY_PROTOCOL] = TRUE;
  $conf['memcache_options'][Memcached::OPT_COMPRESSION] = TRUE;
  $conf['page_compression'] = FALSE; // avoid double compression
  $conf['memcache_options'][Memcached::OPT_CONNECT_TIMEOUT] = 400;
  $conf['memcache_options'][Memcached::OPT_RETRY_TIMEOUT] = 2;
  //$conf['memcache_options'][Memcached::OPT_SEND_TIMEOUT] = 0;
  //$conf['memcache_options'][Memcached::OPT_RECV_TIMEOUT] = 1;
  $conf['memcache_options'][Memcached::OPT_POLL_TIMEOUT] = 150;
  $conf['memcache_options'][Memcached::OPT_SERVER_FAILURE_LIMIT] = 5;
  $conf['memcache_options'][Memcached::OPT_TCP_NODELAY] = TRUE;

  // Cache-related options
  $conf['lock_inc'] = 'sites/all/modules/memcache/memcache-lock.inc';
  $conf['cache_backends'][] = 'sites/all/modules/memcache/memcache.inc';
  $conf['cache_default_class'] = 'MemCacheDrupal';
  // The 'cache_form' bin must be assigned no non-volatile storage.
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
}

// -------------------------------------------------------------------------------
// Varnish configuration
// -------------------------------------------------------------------------------
// The varnish module invalidates pages cached by Varnish instead of
// managing a "cache_page" table or Memcached entries.
$varnish_enabled = TRUE;
if ($varnish_enabled) {
  // This option is taken into account only when the Varnish module is patched adequately.
  $conf['varnish_keep_caching'] = 'MemCacheDrupal';
  // Varnish-related options
  $conf['varnish_flush_cron'] = 0; // disabled
  $conf['varnish_version'] = 3; // 3.x
  $conf['varnish_control_terminal'] = '158.167.154.207:8890 158.167.39.225:8890'; // s-fp-esx-pla02.net1.cec.eu.int and aloe.cc.cec.eu.int
  $conf['varnish_control_key'] = 'cHOuvoUJLuFro3st1uwlejLug'; // see .secret file in Varnish configuration
  $conf['varnish_socket_timeout'] = '300'; // ms
  $conf['varnish_cache_clear'] = 1; // varnish.module:4:define('VARNISH_DEFAULT_CLEAR', 1);
  $conf['varnish_cache_lifetime'] = 1800; // seconds; Cached pages will not be re-created until at least this much time has elapsed.

  // Cache-related options
  $conf['cache_backends'][] = 'sites/all/modules/varnish/varnish.cache.inc';
  $conf['cache_class_cache_page'] = 'VarnishCache';
}

// -------------------------------------------------------------------------------
// Cache configuration
// -------------------------------------------------------------------------------
$conf['page_cache_invoke_hooks'] = FALSE;
$conf['cache'] = 1;
$conf['block_cache'] = 0;
$conf['cache_lifetime'] = 0; // this parameter is rather tricky: its human-readable description in the Drupal admin interface mentions it applies to cache_page, but it is actually taken into account by all bins, which looks like a good way to get weird behaviours
$conf['page_cache_without_database'] = FALSE; // we need to connect to the database in order to get variables, because the invalidation mechanism relies on that.

//$conf['maintenance_mode'] = TRUE;

// -------------------------------------------------------------------------------
// Proxy configuration
// -------------------------------------------------------------------------------
$conf['proxy_server'] = '158.169.9.13';
$conf['proxy_port'] = 8012;
$conf['proxy_username'] = 'j50l033';
$conf['proxy_password'] = 'cU2M>!:7';
$conf['proxy_user_agent'] = 'Drupal Multisite (msp0)';
$conf['proxy_exceptions'] = array('fpfis-dev.net1.cec.eu.int','intragate.ec.europa.eu', '127.0.0.1', 'localhost', 'biguonia.cc.cec.eu.int', '158.167.39.277', 'dbprod-dmrz.jrc.org', '139.191.254.129','intragate.acceptance.ec.europa.eu');

// Make Feeds module to not use cURL
$conf['feeds_never_use_curl'] = true;

// Proxy configuration as read by the chr (Curl HTTP Request) module
$conf['drupal_http_request_function'] = 'chr_curl_http_request';
$conf['https_proxy'] = $conf['http_proxy'] = array(
  'server' => '158.169.9.13', // pslux.ec.europa.eu
  'port' => '8012',
  'username' => 'j50l033',
  'password' => 'cU2M>!:7',
  'exceptions' => array('fpfis-dev.net1.cec.eu.int','intragate.ec.europa.eu', '127.0.0.1', 'localhost', 'biguonia.cc.cec.eu.int', '158.167.39.277', 'dbprod-dmrz.jrc.org', '139.191.254.129', 'intragate.acceptance.ec.europa.eu', 'intragate.ec.europa.eu'),
);


