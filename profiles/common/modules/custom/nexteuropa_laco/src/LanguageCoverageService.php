<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_laco\LanguageCoverageService.
 */

namespace Drupal\nexteuropa_laco;

/**
 * Class LanguageCoverageService.
 *
 * @package Drupal\nexteuropa_laco
 */
class LanguageCoverageService implements LanguageCoverageServiceInterface {

  /**
   * HTTP method the service will be reacting to.
   */
  const HTTP_METHOD = 'HEAD';

  /**
   * Custom HTTP Header name for requesting service.
   */
  const HTTP_HEADER_SERVICE_NAME = 'EC-Requester-Service';

  /**
   * Custom HTTP Header value idendifying the requesting service.
   */
  const HTTP_HEADER_SERVICE_VALUE = 'WEBTOOLS LACO';

  /**
   * Custom HTTP Header name for requested language.
   */
  const HTTP_HEADER_LANGUAGE_NAME = 'EC-LACO-lang';

  /**
   * {@inheritdoc}
   */
  public function deliverResponse() {
    drupal_add_http_header('Status', '200 OK');
    drupal_add_http_header('Content-Length', '0');
    drupal_exit();
  }

  /**
   * Factory method.
   *
   * @return \Drupal\nexteuropa_laco\LanguageCoverageServiceInterface
   */
  static public function getInstance() {
    return new static();
  }

  /**
   * {@inheritdoc}
   */
  static public function isServiceRequest() {
    $service_header = 'HTTP_' . strtoupper(self::HTTP_HEADER_SERVICE_NAME);
    $service_header = str_replace('-', '_', $service_header);
    $result = isset($_SERVER['REQUEST_METHOD']) && ($_SERVER['REQUEST_METHOD'] == self::HTTP_METHOD);
    $result = $result && isset($_SERVER[$service_header]) && ($_SERVER[$service_header] == self::HTTP_HEADER_SERVICE_VALUE);
    return $result;
  }

}
