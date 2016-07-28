<?php
/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\PoetryServer.
 */

namespace Drupal\tmgmt_poetry\Services;

/**
 * Class PoetryServer.
 *
 * Wrapper around SoapServer class for further extends and tests.
 *
 * @package Drupal\tmgmt_poetry\Services
 */
class PoetryServer extends \SoapServer implements PoetryServerInterface {

  /**
   * {@inheritdoc}
   */
  public function process() {
    $this->handle();
  }

  /**
   * {@inheritdoc}
   */
  public static function getInstance() {
    // Generate our own SOAP server.
    $wsdl_endpoint = url(
      drupal_get_path("module", "tmgmt_poetry")
      . "/wsdl/PoetryIntegration.wsdl",
      [
        'absolute' => TRUE,
        'language' => (object) ['language' => FALSE],
      ]
    );
    $options = [
      'cache_wsdl' => WSDL_CACHE_NONE,
    ];
    $server = new self($wsdl_endpoint, $options);
    $server->setClass(
      'Drupal\tmgmt_poetry\Services\PoetryCallback',
      variable_get("poetry_service")
    );

    return $server;
  }

}
