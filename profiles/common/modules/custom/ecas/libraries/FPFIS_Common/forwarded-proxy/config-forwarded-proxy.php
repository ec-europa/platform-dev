<?php

/*
Configuration file to include in the application where the proxy hack is required
Indicate hostname where the script is hosted: 'www.cc.cec', 'feeds.ec.europa.eu', 'webtools.ec.europa.eu', etc.
Without http:// and without trailing slash /
*/
if ( !defined('FPFIS_SERVER_HOSTNAME') ) define('FPFIS_SERVER_HOSTNAME','webgate.ec.europa.eu');
if ( !defined('FPFIS_SERVER_PORT') ) define('FPFIS_SERVER_PORT','');
if ( !defined('FPFIS_COMMON_LIBRARIES_PATH') ) define('FPFIS_COMMON_LIBRARIES_PATH','');

if ( strlen(FPFIS_SERVER_HOSTNAME) ){ $_SERVER["HTTP_X_FORWARDED_HOST"] = FPFIS_SERVER_HOSTNAME; }

if ( is_file(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/forwarded-proxy/forwarded-proxy.php') )
	include_once(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/forwarded-proxy/forwarded-proxy.php');

?>