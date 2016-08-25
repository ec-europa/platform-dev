<?php
/**
 * @file
 * Contains TMGMTPoetryMockSubContexts.
 */

use Behat\Behat\Hook\Scope\AfterScenarioScope;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;

/**
 * Behat step definitions for the TMGMT Poetry Mock module.
 */
class TMGMTPoetryMockSubContext extends RawDrupalContext implements DrupalSubContextInterface {
  /**
   * The Drupal driver manager.
   *
   * @var DrupalDriverManager
   */
  protected $drupal;

  /**
   * Contains original variable values set during test execution.
   *
   * @var array
   */
  protected $variables = array();

  /**
   * The translation request data.
   *
   * @var array
   */
  protected $translationRequest;

  /**
   * Constructs a TMGMTPoetryMockSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * The poetry context.
   *
   * @var TmgmtPoetrySubContext
   */
  private $poetryContext;

  /**
   * Grabs other contexts we rely on from the environment.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->poetryContext = $environment->getContext(TmgmtPoetrySubContext::class);
  }

  /**
   * Configure tmgmt_poetry to use tmgmt_poetry_mock.
   *
   * @Given tmgmt_poetry is configured to use tmgmt_poetry_mock
   */
  public function tmgmtPoetryIsConfiguredToUseTmgmtPoetryMock() {
    $this->variables['poetry_service'] = variable_get('poetry_service');

    $poetry_service = tmgmt_poetry_mock_service_configuration();

    variable_set('poetry_service', $poetry_service);
  }

  /**
   * Restore initial variables.
   *
   * @AfterScenario
   */
  public function restoreVariables(AfterScenarioScope $scope) {
    foreach ($this->variables as $variable => $initial_value) {
      if (NULL === $initial_value) {
        variable_del($variable);
      }
      else {
        variable_set($variable, $initial_value);
      }
    }
  }

  /**
   * Remove pending translations in a scenario tagged with @poetry.
   *
   * @AfterScenario @poetry
   */
  public function removePendingTranslations() {
    PoetryMock::removeAllRequestTranslationFiles();
  }

  /**
   * Verifies that poetry received the last translation request.
   *
   * @Then the poetry translation service received the translation request
   */
  public function assertPoetryTranslationServiceReceivedTheTranslationRequest() {
    $translation_request = PoetryMock::getTranslationRequestByJobReference(
      $this->poetryContext->jobReference
    );

    if (!$translation_request) {
      throw new \Exception(
        sprintf(
          'the poetry translation service did not receive a translation request with reference %s',
          $this->poetryContext->jobReference
        )
      );
    }

    $this->translationRequest = $translation_request;
  }

  /**
   * Verifies the version of the last translation request.
   *
   * @Then the translation request has version :arg1
   */
  public function assertTranslationRequestHasVersion($arg1) {
    if (!$this->translationRequest) {
      throw new Exception(
        'translator first needs to confirm they received the translation request'
      );
    }

    if ($this->translationRequest['demande_id']['version'] != $arg1) {
      throw new Exception(
        sprintf(
          'Translation request version is %s, expected %s instead',
          $this->translationRequest['demande_id']['version'],
          $arg1
        )
      );
    }
  }

  /**
   * Verifies that the last translation request document is valid XHTML.
   *
   * @Then the translation request document is valid XHTML
   */
  public function assertTranslationRequestDocumentIsValidXhtml() {
    if (!$this->translationRequest) {
      throw new Exception(
        'translator first needs to confirm they received the translation request'
      );
    }

    $request = file_get_contents($this->translationRequest['file']->uri);

    $request_data = PoetryMock::getDataFromRequest($request);

    $document = base64_decode($request_data['content']);

    $response = drupal_http_request(
      'https://validator.w3.org/check',
      [
        'method' => 'POST',
        'data' => http_build_query(
          [
            'fragment' => $document,
            'output' => 'json',
          ]
        ),
      ]
    );

    // Info on output from the validator:
    // https://github.com/validator/validator/wiki/Output:-JSON.
    $validation = json_decode($response->data);
    $errors = $validation->messages;

    if (!empty($errors)) {
      $first_error = reset($errors);
      throw new Exception(
        sprintf(
          'The translation document did not pass the W3C XHTML validation (error count: %d). First error: %s.',
          count($errors),
          $first_error->message
        )
      );
    }
  }

  /**
   * Verifies that poetry received initial request with NEXT_EUROPA_COUNTER.
   *
   * @Then the poetry translation service received initial request with automatic counter
   */
  public function assertPoetryTranslationServiceReceivedTheInitialRequest() {
    $message = '';
    if (is_object($this->translationRequest['file'])) {
      $file_object = $this->translationRequest['file'];
      $message = file_get_contents($file_object->uri);
    }

    if (strpos($message, PoetryMock::COUNTER_STRING) === FALSE) {
      throw new \Exception(
        sprintf(
          'the poetry translation service did not receive the initial translation with automatic counter %s',
          PoetryMock::COUNTER_STRING
        )
      );
    }
  }

}
