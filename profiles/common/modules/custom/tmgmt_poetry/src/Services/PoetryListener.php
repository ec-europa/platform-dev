<?php

/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\PoetryListener.
 */

namespace Drupal\tmgmt_poetry\Services;

/**
 * Class PoetryListener.
 */
class PoetryListener {
  private $wsdlEndpoint;

  /**
   * PoetryListener constructor.
   */
  public function __construct() {
    $this->setWsdlEndpoint();
    $options = [
      'cache_wsdl' => WSDL_CACHE_NONE,
    ];
    $server = new \SoapServer($this->wsdlEndpoint, $options);
    $server->setClass('Drupal\tmgmt_poetry\Services\PoetryCallback');

    try {
      $server->handle();
    }
    catch (Exception $e) {
      // @todo: provide some nice exception handling.
    }
  }

  /**
   * Sets up Poetry listener WSDL endpoint.
   */
  private function setWsdlEndpoint() {
    $this->wsdlEndpoint = url(
      drupal_get_path("module", "tmgmt_poetry")
      . "/wsdl/PoetryIntegration.wsdl",
      [
        'absolute' => TRUE,
        'language' => (object) ['language' => FALSE],
      ]
    );
  }

  /**
   * Returns Poetry listener WSDL endpoint.
   *
   * @return string
   *    Url to Poetry listener WSDL.
   */
  public function getWsdlEndpoint() {
    return $this->wsdlEndpoint;
  }

}
