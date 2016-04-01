<?php

/**
 * @file
 * Contains \NextEuropaLacoSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\TableNode;
use Drupal\nexteuropa_laco\LanguageCoverageService as Service;

/**
 * Behat step definitions for the NextEuropa Multilingual module.
 */
class NextEuropaLacoSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * {@inheritdoc}
   */
  protected $drupal;

  /**
   * Constructs a NextEuropaLacoSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Assert language coverage on a specific path.
   *
   * @param string $code
   *    Expected response code.
   * @param string $language
   *    Language to be queried.
   * @param string $path
   *    Path to determined the language coverage for.
   *
   * @Then I should get a :code for :language language coverage on the :path path
   */
  public function assertLanguageCoverage($code, $language, $path) {
    global $base_url;

    $client = new \GuzzleHttp\Client([
      'headers' => [
        Service::HTTP_HEADER_SERVICE_NAME => Service::HTTP_HEADER_SERVICE_VALUE,
        Service::HTTP_HEADER_LANGUAGE_NAME => $language,
      ],
      'http_errors' => FALSE,
    ]);
    $actual = $client->request(Service::HTTP_METHOD, $base_url . '/' . $path)->getStatusCode();
    if ($actual != $code) {
      throw new \InvalidArgumentException("Language coverage for '$language' on '$path' returned '$actual' instead of '$code'.");
    }
  }

}
