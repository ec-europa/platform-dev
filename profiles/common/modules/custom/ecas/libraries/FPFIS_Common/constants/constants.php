<?php

/*
Default value to avoid notices
*/
if ( !defined('FPFIS_COMMON_LIBRARIES_PATH') ) define('FPFIS_COMMON_LIBRARIES_PATH', '');

/*
ECAS conf
*/
if ( !defined('FPFIS_ECAS_PATH') ) define('FPFIS_ECAS_PATH', FPFIS_COMMON_LIBRARIES_PATH . '/phpcas/CAS.php');
if ( !defined('FPFIS_ECAS_URL') ) define('FPFIS_ECAS_URL', 'ecas.cc.cec.eu.int');
if ( !defined('FPFIS_ECAS_URI') ) define('FPFIS_ECAS_URI', '/cas');
if ( !defined('FPFIS_ECAS_PORT') ) define('FPFIS_ECAS_PORT', 7002);

/*
LDAP conf
*/
if ( !defined('FPFIS_LDAP_SERVER_NAME') ) define('FPFIS_LDAP_SERVER_NAME', 'cedprod.cec.eu.int');
if ( !defined('FPFIS_LDAP_SERVER_PORT') ) define('FPFIS_LDAP_SERVER_PORT', '10389');
if ( !defined('FPFIS_LDAP_BASE_DN') ) define('FPFIS_LDAP_BASE_DN', 'ou=People,o=cec.eu.int');
if ( !defined('FPFIS_LDAP_BASE_DN_DG') ) define('FPFIS_LDAP_BASE_DN_DG', 'ou=Groups,o=cec.eu.int');
if ( !defined('FPFIS_LDAP_USER_DN') ) define('FPFIS_LDAP_USER_DN', 'uid=XXXXX,ou=People,o=cec.eu.int');
if ( !defined('FPFIS_LDAP_PASSWORD') ) define('FPFIS_LDAP_PASSWORD', 'XXXXX');
if ( !defined('FPFIS_LDAP_UID') ) define('FPFIS_LDAP_UID', 'uid');
if ( !defined('FPFIS_LDAP_CN') ) define('FPFIS_LDAP_CN', 'cn');
if ( !defined('FPFIS_LDAP_MAIL') ) define('FPFIS_LDAP_MAIL', 'mail');

/*
PROXY conf
*/
$fpfis_proxy_rules['bypass_proxy'] = array(
	'^http://ec\.europa\.eu',
	'^http://[^/]*\.ec\.europa\.eu',
	'^http://europa\.eu/rapid/',
	'^http://[^/]*cc\.cec',
	'^http://[^/]*\.eu\.int',
	'^http://158\.16[5-9]\.',
);
$fpfis_proxy_rules['blacklist'] = array(
	//'^http://[^/]*news\.yahoo.com/',
);

if ( !defined('FPFIS_PROXY_SCRIPT') ) define('FPFIS_PROXY_SCRIPT', 'http://autoproxy.cec.eu.int:82/proxy.pac');
if ( !defined('FPFIS_PROXY_SCHEME') ) define('FPFIS_PROXY_SCHEME', 'http://');
if ( !defined('FPFIS_PROXY_PROTOCOL') ) define('FPFIS_PROXY_PROTOCOL', 'tcp');
if ( !defined('FPFIS_PROXY_HOST') ) define('FPFIS_PROXY_HOST', '158.169.9.13');
if ( !defined('FPFIS_PROXY_PORT') ) define('FPFIS_PROXY_PORT', '8012');
if ( !defined('FPFIS_PROXY_USER') ) define('FPFIS_PROXY_USER', '');
if ( !defined('FPFIS_PROXY_PASSWORD') ) define('FPFIS_PROXY_PASSWORD', '');
if ( !defined('FPFIS_PROXY_RULES') ) define('FPFIS_PROXY_RULES', serialize($fpfis_proxy_rules));

/*
Other generic vars
*/
if ( !defined('FPFIS_OVERWRITE_REMOTE_ADDR') ) define('FPFIS_OVERWRITE_REMOTE_ADDR', true);
if ( !defined('FPFIS_OVERWRITE_USER_AGENT') )  define('FPFIS_OVERWRITE_USER_AGENT', 'PHP');
