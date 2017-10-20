<?php

namespace Drupal\nexteuropa_varnish\Tests;

/**
 * Class HelperMethodsTest.
 *
 * It tests the different helper functions the modules uses.
 *
 * @package Drupal\nexteuropa_varnish\Tests
 */
class HelperMethodsTest extends \PHPUnit_Framework_TestCase {

  /**
   * Tests the helper function _nexteuropa_varnish_trim_base_path().
   *
   * @param string $testedPath
   *   The original path to test the trimming process.
   * @param string $expectedPath
   *   The end path expected after the trimming process.
   * @param string $testedBasePath
   *   The base path to use in the test of trimming process.
   * @param string $testedCase
   *   The label of the tested case for the test of trimming process.
   *
   * @dataProvider trimmingPathDataProvider
   */
  public function testTrimmingPath($testedPath, $expectedPath, $testedBasePath, $testedCase) {
    // Charge the file as the tested function is not in a class and in order to
    // test it without a Drupal stack.
    require_once __DIR__ . '/../../nexteuropa_varnish.module';

    $resultPath = _nexteuropa_varnish_trim_base_path($testedPath, $testedBasePath);

    $this->assertEquals($expectedPath, $resultPath, sprintf('The %s case fails. it receives %s instead of %s!', $testedCase, $resultPath, $expectedPath));
  }

  /**
   * Provides test data for testTrimmingPath().
   *
   * @return array
   *  The test data.
   */
  public function trimmingPathDataProvider() {
    return array(
      array(
        'nexteuropa/varnish/de/press/news/170925',
        'de/press/news/170925',
        'nexteuropa/varnish/',
        'with slashes',
      ),
      array(
        '/de/press/news/170925',
        'de/press/news/170925',
        '/',
        'with a simple slash',
      ),
      array(
        'de/press/news/170925',
        'de/press/news/170925',
        '',
        'without slash',
      ),
      array(
        'de/press/news/170925',
        'de/press/news/170925',
        'nexteuropa/varnish/',
        'without the base path',
      ),
    );
  }

}
