<?php
/**
 * @file
 * Page callbacks for the mocked Poetry server.
 */

/**
 * A page callback which simulate poetry webservice.
 */
function _tmgmt_poetry_mock_soap_server() {
  if (_check_poetry_service_variable()) {
    $poetry_service = variable_get('poetry_service');
    $poetry_wsdl = $poetry_service['address'];
    $options = ['uri' => $poetry_service['poetry_endpoint']];
    $server = new \SoapServer($poetry_wsdl, $options);
    $server->setClass(\Drupal\tmgmt_poetry_mock\Mock\PoetryMock::class);
    $server->handle();
  }
  else {
    return FALSE;
  }
}

/**
 * Generate mock wsdl to simulate poetry.
 */
function _tmgmt_poetry_mock_wsdl() {
  $uri = url('tmgmt_poetry_mock/soap_server', ['absolute' => TRUE, 'language' => (object) ['language' => FALSE]]);
  $wsdl = theme('poetry_wsdl', ['uri' => $uri]);
  drupal_add_http_header('Content-Type', 'application/xml; utf-8');
  print $wsdl;
  drupal_exit();
}
