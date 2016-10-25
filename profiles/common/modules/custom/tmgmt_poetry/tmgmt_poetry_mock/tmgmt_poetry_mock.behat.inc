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
use Behat\Gherkin\Node\TableNode;
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

    $request_xml = file_get_contents($this->translationRequest['file']->uri);
    $this->translationRequest['data'] = PoetryMock::getDataFromRequest($request_xml);
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
   * Sets the version of the last translation request.
   *
   * @Then set the translation request version to :arg1
   */
  public function setTranslationRequestHasVersion($arg1) {
    if (!$this->translationRequest) {
      throw new Exception(
        'translator first needs to confirm they received the translation request'
      );
    }

    db_update('poetry_map')
      ->fields(array('version' => $arg1))
      ->condition('annee', $this->translationRequest['demande_id']['annee'], '=')
      ->condition('numero', $this->translationRequest['demande_id']['numero'], '=')
      ->condition('version', $this->translationRequest['demande_id']['version'], '=')
      ->condition('partie', $this->translationRequest['demande_id']['partie'], '=')
      ->execute();

    $this->translationRequest['demande_id']['version'] = $arg1;
  }

  /**
   * Verifies that the last translation request document is valid XHTML.
   *
   * @Then the translation request document is valid XHTML
   */
  public function assertTranslationRequestDocumentIsValidXhtml() {
    $this->assertTranslationRequest();

    $document = base64_decode($this->translationRequest['data']['content']);

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
   * Assert the contacts in the translation request.
   *
   * @Then the translation request has the following contacts:
   */
  public function assertTranslationRequestHasTheFollowingContacts(TableNode $table) {
    $this->assertTranslationRequest();

    $expected_contacts = $table->getHash();

    $by_type = function ($a, $b) {
      return strcmp($a['type'], $b['type']);
    };

    usort($expected_contacts, $by_type);
    usort($this->translationRequest['data']['contacts'], $by_type);

    assert($this->translationRequest['data']['contacts'], equals($expected_contacts));
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
   * Assert the value of organisationResponsable of the translation request.
   *
   * @Then the translation request has organisationResponsable :arg1
   */
  public function assertTranslationRequestHasOrganisationResponsable($arg1) {
    $this->assertTranslationRequestDemandeProperty(
      'organisationResponsable',
      equals($arg1)
    );
  }

  /**
   * Assert the value of organisationAuteur of the translation request.
   *
   * @Then the translation request has organisationAuteur :arg1
   */
  public function assertTranslationRequestHasOrganisationAuteur($arg1) {
    $this->assertTranslationRequestDemandeProperty(
      'organisationAuteur',
      equals($arg1)
    );
  }

  /**
   * Assert the value of serviceDemandeur of the translation request.
   *
   * @Then the translation request has serviceDemandeur :arg1
   */
  public function assertTranslationRequestHasServiceDemandeur($arg1) {
    $this->assertTranslationRequestDemandeProperty(
      'serviceDemandeur',
      equals($arg1)
    );
  }

  /**
   * Assert the value of remarque of the translation request.
   *
   * @Then the translation request has remarque :arg1
   */
  public function assertTranslationRequestHasRemarque($arg1) {
    $this->assertTranslationRequestDemandeProperty(
      'remarque',
      equals($arg1)
    );
  }

  /**
   * Assert the value of a 'demande' translation request property.
   *
   * @param string $property
   *   Which property to assert.
   * @param \bovigo\assert\predicate\Predicate|callable $predicate
   *   The assertion predicate.
   */
  protected function assertTranslationRequestDemandeProperty($property, $predicate) {
    $this->assertTranslationRequest();

    $value = $this->translationRequest['data']['demande'][$property];

    assert($value, $predicate);
  }

  /**
   * Assert the value of titre of the translation request.
   *
   * @Then the translation request has titre :arg1
   */
  public function assertTranslationRequestHasTitre($arg1) {
    $this->assertTranslationRequestDemandeProperty(
      'titre',
      equals($arg1)
    );
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
