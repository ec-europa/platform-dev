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
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;

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
   * Remove "poetry data" before triggering a scenario tagged with @cleanPoetry.
   *
   * @BeforeScenario @cleanPoetry
   *
   * @AfterScenario @cleanPoetry
   */
  public function removeTranslationJobs() {
    // Cleaning TMGMT jobs and related items.
    $jobs = PoetryMock::getAllTmgmtJobs();
    foreach ($jobs as $job) {
      $job_items = $job->getItems();
      foreach ($job_items as $item) {
        $item->delete();
      }
      $job->delete();
    }

    // Cleaning the tmgmt_poetry custom database tables.
    db_truncate('poetry_map')->execute();
    db_truncate('poetry_status')->execute();

    // Deleting files which were created by tmgmt_poetry_mock.
    PoetryMock::removeAllRequestTranslationFiles();
    file_unmanaged_delete_recursive(TMGMT_POETRY_MOCK_REQUESTS_PATH);

    // Setting up clean directory.
    $directory = 'public://tmgmt_file/poetry_mock_requests';
    file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
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
   * Assert a translation request was captured.
   *
   * @throws Exception
   *   When no translation request was captured.
   */
  protected function assertTranslationRequest() {
    if (!$this->translationRequest) {
      throw new Exception(
        'translator first needs to confirm they received the translation request'
      );
    }
  }

  /**
   * Assert the value of a 'demande_id' translation request property.
   *
   * @param string $property
   *   Which property of the reference to assert.
   * @param \bovigo\assert\predicate\Predicate|callable $predicate
   *   The assertion predicate.
   */
  protected function assertTranslationRequestDemandeIdProperty($property, $predicate) {
    $this->assertTranslationRequest();
    $value = $this->translationRequest['demande_id'][$property];

    assert($value, $predicate);
  }

  /**
   * Assert the value of a 'sequence' translation request property.
   *
   * @param string $value
   *   The string with the sequence.
   * @param \bovigo\assert\predicate\Predicate|callable $predicate
   *   The assertion predicate.
   */
  protected function assertTranslationRequestSequenceProperty($value, $predicate) {
    $this->assertTranslationRequest();
    assert($value, $predicate);
  }

  /**
   * Assert the value of 'codeDemandeur' of the translation request.
   *
   * @Then the translation request has the codeDemandeur :arg1
   */
  public function assertTranslationRequestHasCodeDemandeur($arg1) {
    $this->assertTranslationRequestDemandeIdProperty(
      'codeDemandeur',
      equals($arg1)
    );
  }

  /**
   * Assert the value of 'sequence' of the translation request.
   *
   * @Then the translation request has the sequence :arg1
   */
  public function assertTranslationHasRequestSequence($arg1) {
    $file_object = $this->translationRequest['file'];
    $message = file_get_contents($file_object->uri);
    $data = PoetryMock::getDataFromRequest($message);
    $sequence = $data['demande_id']['sequence'];

    $this->assertTranslationRequestSequenceProperty(
      $sequence,
      equals($arg1)
    );
  }

}
