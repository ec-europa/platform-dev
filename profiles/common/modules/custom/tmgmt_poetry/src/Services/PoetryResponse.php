<?php
/**
 * @file
 * Contains \Drupal\tmgmt_poetry\Services\PoetryResponse.
 */

namespace Drupal\tmgmt_poetry\Services;

/**
 * Class PoetryResponse.
 *
 * @package Drupal\tmgmt_poetry\Services
 */
class PoetryResponse implements PoetryResponseInterface {

  /**
   * Factory method.
   *
   * @return PoetryResponse
   *    Object instance.
   */
  static public function getInstance() {
    // TODO: Implement getInstance() method.
    return new self();
  }

  /**
   * {@inheritdoc}
   */
  public function build($settings) {
    // TODO: Implement build() method.
  }

}
