<?php

/**
 * @file
 * Class \Drupal\multisite_config\Tests\NextEuropaDataExportAbstractTest.
 */

namespace Drupal\multisite_config\Tests;

/**
 * Class ConfigAbstractTest.
 *
 * @package Drupal\multisite_config\Tests
 */
class ConfigBaseTest extends ConfigAbstractTest {

  /**
   * Test Multisite Service container.
   */
  public function testServiceContainer() {

    $service = multisite_config_service('not_existing_module');
    $this->assertEquals('Drupal\multisite_config\ConfigBase', get_class($service));

    $paths = glob(drupal_get_path('module', 'multisite_config') . '/lib/Drupal/*' , GLOB_ONLYDIR);
    foreach ($paths as $path) {
      $name = basename($path);
      $service = multisite_config_service($name);
      $this->assertEquals("Drupal\\$name\\Config", get_class($service));
    }
  }

}
