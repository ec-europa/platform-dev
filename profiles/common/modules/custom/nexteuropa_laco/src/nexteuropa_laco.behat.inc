<?php

/**
 * @file
 * Contains \NextEuropaLacoSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Drupal\nexteuropa_laco\LanguageCoverageService as Service;
use Behat\Gherkin\Node\TableNode;

/**
 * Behat step definitions for the NextEuropa Multilingual module.
 */
class NextEuropaLacoSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * {@inheritdoc}
   */
  protected $drupal;

  /**
   * Default debug mode value.
   *
   * @var bool
   */
  protected $debug;

  /**
   * Constructs a NextEuropaLacoSubContext object.
   *
   * @param Drupal\DrupalDriverManager $drupal
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
   * @param string $message
   *    Debug response message.
   *
   * @Then I should get a :code for :language language coverage on the :path path
   */
  public function assertLanguageCoverage($code, $language, $path, $message = '') {
    global $base_url;

    $client = new \GuzzleHttp\Client([
      'headers' => [
        Service::HTTP_HEADER_SERVICE_NAME => Service::HTTP_HEADER_SERVICE_VALUE,
        Service::HTTP_HEADER_LANGUAGE_NAME => $language,
      ],
      'http_errors' => FALSE,
    ]);
    $response = $client->request(Service::HTTP_METHOD, $base_url . '/' . $path);
    if ($response->getStatusCode() != $code) {
      throw new \InvalidArgumentException("Language coverage for '$language' on '$path' returned '{$response->getStatusCode()}' instead of '$code'.");
    }
    $response_message = $response->getHeader('ec-nexteuropa-laco');
    if ($message && $message != $response_message[0]) {
      throw new \InvalidArgumentException("Expected message does not match with the actual message: {$response_message[0]}.");
    }
  }

  /**
   * Assert language coverage on a specific path given a list of parameters.
   *
   * @param \Behat\Gherkin\Node\TableNode $table
   *    Table containing response code, language code and relative path.
   *
   * @Then I should get the following language coverage responses:
   */
  public function iShouldGetTheFollowingLanguageCoverageResponses(TableNode $table) {
    foreach ($table->getIterator() as $row) {
      $row['message'] = isset($row['message']) ? $row['message'] : '';
      $this->assertLanguageCoverage($row['response'], $row['language'], $row['path'], $row['message']);
    }
  }

  /**
   * Enable debug mode.
   *
   * @beforeScenario
   */
  public function setDebugMode() {
    $this->debug = variable_get('nexteuropa_laco_debug', FALSE);
    variable_set('nexteuropa_laco_debug', TRUE);
  }

  /**
   * Reset debug mode.
   *
   * @afterScenario
   */
  public function resetDebugMode() {
    variable_set('nexteuropa_laco_debug', $this->debug);
  }

}
