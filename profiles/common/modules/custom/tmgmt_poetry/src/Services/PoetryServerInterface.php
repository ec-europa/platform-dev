<?php
/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\PoetryServerInterface.
 */

namespace Drupal\tmgmt_poetry\Services;

/**
 * Interface PoetryServerInterface.
 *
 * @package Drupal\tmgmt_poetry\Services
 */
interface PoetryServerInterface extends PoetryFactoryInterface {

  /**
   * Process request coming from Poetry Service.
   */
  public function process();

}
