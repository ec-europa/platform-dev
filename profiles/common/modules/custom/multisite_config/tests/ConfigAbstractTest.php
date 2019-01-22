<?php

namespace Drupal\multisite_config\Tests;

/**
 * Class ConfigAbstractTest.
 *
 * @package Drupal\multisite_config\Tests
 */
abstract class ConfigAbstractTest extends \PHPUnit_Framework_TestCase {

  const CONTENT_TYPE_WITH_FIELDS = 'test_with_fields';
  const CONTENT_TYPE_WITHOUT_FIELDS = 'test_without_fields';

  /**
   * Service object instance as returned by multisite_config_service().
   *
   * @var object
   */
  protected $service;

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    if (!module_exists('multisite_config_test')) {
      throw new \Exception('multisite_config_test feature must be enabled.');
    }
  }

}
