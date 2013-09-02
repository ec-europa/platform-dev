<?php
// -------------------------------------------------------------------------------
// Proxy configuration
// -------------------------------------------------------------------------------
$conf['proxy_server'] = '158.169.9.13';
$conf['proxy_port'] = 8012;
$conf['proxy_username'] = 'j50l033';
$conf['proxy_password'] = 'cU2M>!:7';
$conf['proxy_user_agent'] = 'Drupal Multisite (msp0)';
$conf['proxy_exceptions'] = array(php_uname('n'), 'fpfis-dev.net1.cec.eu.int','intragate.ec.europa.eu', 'ec.europa.eu', 'fpfis-dev', '127.0.0.1', 'localhost', 'biguonia.cc.cec.eu.int', '158.167.39.277', 'dbprod-dmrz.jrc.org', '139.191.254.129','intragate.acceptance.ec.europa.eu');

// Proxy configuration as read by the chr (Curl HTTP Request) module
$conf['drupal_http_request_function'] = 'curl_http_request';
$conf['https_proxy'] = $conf['http_proxy'] = array(
  'server' => '158.169.9.13', // pslux.ec.europa.eu
  'port' => '8012',
  'username' => 'j50l033',
  'password' => 'cU2M>!:7',
  'exceptions' => array(php_uname('n'), 'fpfis-dev.net1.cec.eu.int','intragate.ec.europa.eu', 'ec.europa.eu', 'fpfis-dev', '127.0.0.1', 'localhost', 'biguonia.cc.cec.eu.int', '158.167.39.2
77', 'dbprod-dmrz.jrc.org', '139.191.254.129', 'intragate.acceptance.ec.europa.eu'),
);
