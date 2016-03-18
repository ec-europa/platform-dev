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
  static public function isServiceRequest() {
    $header = self::getHeaderKey(self::HTTP_HEADER_SERVICE_NAME);
    $result = isset($_SERVER['REQUEST_METHOD']) && ($_SERVER['REQUEST_METHOD'] == self::HTTP_METHOD);
    $result = $result && isset($_SERVER[$header]) && ($_SERVER[$header] == self::HTTP_HEADER_SERVICE_VALUE);
    return $result;
  }

  /**
   * {@inheritdoc}
   */
  static public function getInstance() {
    return new static();
  }

  /**
   * {@inheritdoc}
   */
  public function deliverResponse() {
    $this->buildResponse();
    drupal_exit();
  }

  /**
   * {@inheritdoc}
   */
  public function buildResponse() {
    $language = $this->getRequestedLanguage();
    if (!$language) {
      $this->setStatus('400 Bad request');
    }
    elseif (!$this->isValidLanguage($language)) {
      $this->setStatus('404 Not found');
    }
    else {
      $this->setStatus('200 OK');
    }

    $this->setHeader('Content-Length', '0');
  }

  /**
   * Check whereas the given language is enabled on the current site.
   *
   * @param string $language
   *    Language code.
   *
   * @return bool
   *    TRUE for a valid language, FALSE otherwise.
   */
  public function isValidLanguage($language) {
    return (bool) db_select('languages', 'l')
      ->fields('l', ['language'])
      ->condition('l.language', $language)
      ->condition('l.enabled', 1)
      ->execute()
      ->fetchAssoc();
  }

  /**
   * Set HTTP response status code.
   */
  public function setStatus($status) {
    $this->setHeader('Status', $status);
  }

  /**
   * Set HTTP response header.
   *
   * @param string $name
   *    Header name.
   * @param string $value
   *    Header value.
   */
  public function setHeader($name, $value) {
    drupal_add_http_header($name, $value);
  }

  /**
   * Get requested language.
   *
   * @return string|FALSE
   *    The requested language, FALSE if none found.
   */
  public function getRequestedLanguage() {
    $header = self::getHeaderKey(self::HTTP_HEADER_LANGUAGE_NAME);
    if (isset($_SERVER[$header]) && !empty($_SERVER[$header])) {
      return $_SERVER[$header];
    }
    return FALSE;
  }

  /**
   * Remove language portion from the end of the URL, if any.
   *
   * @param string $url
   *    Requested URL.
   * @param string $language
   *    Requested language.
   *
   * @return string
   *    Sanitized URL.
   */
  public function sanitizeUrl($url, $language) {
    return preg_replace("/_$language$/i", '', $url);
  }

  /**
   * Convert HTTP header name into $_SERVER array key.
   *
   * @param string $header
   *    Header name as provided by the HTTP request.
   *
   * @return string
   *    Header name as a $_SERVER array key.
   */
  static public function getHeaderKey($header) {
    $header = 'HTTP_' . strtoupper($header);
    return str_replace('-', '_', $header);
  }

}
