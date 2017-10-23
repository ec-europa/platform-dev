<?php

/**
 * @file
 * Page callbacks for the mocked Poetry server.
 */

use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;

/**
 * A page callback which simulate poetry webservice.
 */
function _tmgmt_poetry_mock_soap_server() {
  $poetry_wsdl = _tmgmt_poetry_mock_get_poetry_service_wsdl();
  $options = ['uri' => _tmgmt_poetry_mock_get_poetry_service_endpoint()];
  $server = new \SoapServer($poetry_wsdl, $options);
  $server->setClass(PoetryMock::class);
  $server->handle();
}

/**
 * Generate mock wsdl to simulate poetry.
 */
function _tmgmt_poetry_mock_wsdl() {
  $uri = _tmgmt_poetry_mock_get_poetry_service_endpoint();
  $wsdl = theme('poetry_wsdl', ['uri' => $uri]);
  drupal_add_http_header('Content-Type', 'application/xml; utf-8');
  print $wsdl;
  drupal_exit();
}
