<?php
/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\PoetryFactoryInterface.
 */

namespace Drupal\tmgmt_poetry\Services;

/**
 * Interface PoetryFactoryInterface.
 *
 * @package Drupal\tmgmt_poetry\Services
 */
interface PoetryFactoryInterface {

  /**
   * Factory method.
   *
   * @return PoetryFactoryInterface
   *    Object instance.
   */
  static public function getInstance();

}
