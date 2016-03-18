<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_laco\Tests\LanguageCoverageServiceTest.
 */

namespace Drupal\nexteuropa_laco\Tests;

use Drupal\nexteuropa_laco\LanguageCoverageService as Service;


/**
 * Class LanguageCoverageServiceTest.
 *
 * @package Drupal\nexteuropa_laco\Tests
 */
class LanguageCoverageServiceTest extends \PHPUnit_Framework_TestCase {

  /**
   * Test factory method.
   */
  public function testFactoryMethod() {
    $instance = Service::getInstance();
    $reflection = new \ReflectionClass($instance);
    $this->assertEquals('Drupal\nexteuropa_laco\LanguageCoverageService', $reflection->getName());
  }

  /**
   * Test HTTP request.
   */
  public function testHttpRequest() {
    $client = $this->getClient();
    $response = $client->request(Service::HTTP_METHOD, $this->getUri('user'));
    $this->assertEquals(200, $response->getStatusCode());
    return;
  }

  /**
   * Returns Drupal full path.
   *
   * @param string $path
   *    Relative Drupal path.
   *
   * @return string
   *    Full URI.
   */
  protected function getUri($path) {
    return BASE_URL . '/' . $path;
  }

  /**
   * Returns Guzzle client object.
   *
   * @return \GuzzleHttp\Client
   *    Properly configured client.
   */
  protected function getClient() {
    return new \GuzzleHttp\Client([
      'headers' => [Service::HTTP_HEADER_SERVICE_NAME => Service::HTTP_HEADER_SERVICE_VALUE],
    ]);
  }

}
