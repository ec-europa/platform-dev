<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_laco\LanguageCoverageServiceInterface.
 */

namespace Drupal\nexteuropa_laco;

/**
 * Interface LanguageCoverageServiceInterface.
 *
 * @package Drupal\nexteuropa_laco
 */
interface LanguageCoverageServiceInterface {

  /**
   * Deliver response based on current path's language coverage.
   *
   * This method sets proper HTTP status codes and exits.
   */
  public function deliverResponse();

  /**
   * Check if current HTTP request should be handled service.
   *
   * @return bool
   *    TRUE if current HTTP request can be handled, FALSE otherwise.
   */
  static public function isServiceRequest();

  /**
   * Factory method.
   *
   * @return \Drupal\nexteuropa_laco\LanguageCoverageServiceInterface
   *    Instantiate new object.
   */
  static public function getInstance();

}
