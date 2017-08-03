<?php

namespace Drupal\nexteuropa_laco\Tests;

use GuzzleHttp\Client;
use Drupal\nexteuropa_laco\LanguageCoverageService as Service;

/**
 * Class LanguageCoverageServiceTest.
 *
 * @package Drupal\nexteuropa_laco\Tests
 */
class LanguageCoverageServiceTest extends \PHPUnit_Framework_TestCase {

  /**
   * Test HTTP request.
   */
  public function testHttpRequest() {

    // If language is set then return a 200.
    $response = $this->request('user', 'en');
    $this->assertEquals(200, $response->getStatusCode());

    // If language is not enabled then return a 404.
    $response = $this->request('user', 'pl');
    $this->assertEquals(404, $response->getStatusCode());

    // If language is not set then return a 400.
    $response = $this->request('user', NULL);
    $this->assertEquals(400, $response->getStatusCode());
  }

  /**
   * Test factory method.
   */
  public function testFactoryMethod() {
    $instance = Service::getInstance();
    $reflection = new \ReflectionClass($instance);
    $this->assertEquals('Drupal\nexteuropa_laco\LanguageCoverageService', $reflection->getName());
  }

  /**
   * Perform language coverage request on the given path for the given language.
   *
   * @param string $path
   *   Relative Drupal path.
   * @param string $language
   *   Language to check coverage for.
   *
   * @return \Psr\Http\Message\ResponseInterface
   *   Response object instance.
   */
  protected function request($path, $language = 'en') {
    $client = new Client([
      'headers' => [
        Service::HTTP_HEADER_SERVICE_NAME => Service::HTTP_HEADER_SERVICE_VALUE,
        Service::HTTP_HEADER_LANGUAGE_NAME => $language,
      ],
      'http_errors' => FALSE,
    ]);
    return $client->request(Service::HTTP_METHOD, BASE_URL . '/' . $path);
  }

}
