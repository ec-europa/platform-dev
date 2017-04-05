<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Unit\AbstractUnitTest.
 */

namespace Drupal\nexteuropa\Unit;

use PHPUnit\Framework\TestCase;

/**
 * Class AbstractUnitTest.
 *
 * @package Drupal\nexteuropa\Unit
 */
abstract class AbstractUnitTest extends TestCase {

  /**
   * {@inheritdoc}
   */
  protected function checkRequirements() {
    parent::checkRequirements();

    $reflection = new \ReflectionObject($this);
    $namespace = $reflection->getNamespaceName();
    if (preg_match_all('/^\\\?Drupal\\\(\w+)\\\Tests/', $namespace, $matches)) {
      $module = $matches[1][0];
      if (!module_exists($module)) {
        $this->markTestSkipped("Module '{$module}' is not enabled, test skipped.");
      }
    }
  }

}
