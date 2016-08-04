<?php
/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\PoetryResponseInterface.
 */

namespace Drupal\tmgmt_poetry\Services;

/**
 * Interface PoetryResponseInterface.
 *
 * @package Drupal\tmgmt_poetry\Services
 */
interface PoetryResponseInterface extends PoetryFactoryInterface {

  /**
   * Build response.
   */
  public function build();

}
