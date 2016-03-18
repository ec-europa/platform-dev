<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_laco\Tests\LanguageCoverageServiceTest.
 */

namespace Drupal\nexteuropa_laco\Tests;

use Drupal\nexteuropa_laco\LanguageCoverageService;

/**
 * Class LanguageCoverageServiceTest.
 *
 * @package Drupal\nexteuropa_laco\Tests
 */
class LanguageCoverageServiceTest extends \PHPUnit_Framework_TestCase {

  /**
   * Smoke test.
   */
  public function testSmoke() {
    $this->assertEquals(LanguageCoverageService::HTTP_METHOD, 'HEAD');
  }

}
