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
   * Test URL sanitization.
   *
   * @param string $url
   *    URL to be tested.
   * @param string $language
   *    Language code.
   * @param string $expected
   *    Expected URL.
   *
   * @dataProvider sanitizeUrlProvider
   */
  public function testSanitizeUrl($url, $language, $expected) {
    $this->assertEquals($expected, Service::getInstance()->sanitizeUrl($url, $language));
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
   *    Relative Drupal path.
   * @param string $language
   *    Language to check coverage for.
   *
   * @return mixed|\Psr\Http\Message\ResponseInterface
   */
  protected function request($path, $language = 'en') {
    $client = new \GuzzleHttp\Client([
      'headers' => [
        Service::HTTP_HEADER_SERVICE_NAME => Service::HTTP_HEADER_SERVICE_VALUE,
        Service::HTTP_HEADER_LANGUAGE_NAME => $language,
      ],
      'http_errors' => FALSE,
    ]);
    return $client->request(Service::HTTP_METHOD, BASE_URL . '/' . $path);
  }

  /**
   * Data provider for URL sanitization.
   *
   * @return array
   *    Test data.
   */
  public function sanitizeUrlProvider() {
    return [
      ['/path_en', 'en', '/path'],
      ['/path_en', 'fr', '/path_en'],
      ['/path_en_fr', 'en', '/path_en_fr'],
      ['/path', 'en', '/path'],
    ];
  }

}
