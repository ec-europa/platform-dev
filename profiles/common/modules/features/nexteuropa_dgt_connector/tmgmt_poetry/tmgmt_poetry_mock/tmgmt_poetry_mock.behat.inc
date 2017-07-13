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
use Symfony\Component\Process\Exception\ProcessFailedException;
use Symfony\Component\Process\Process;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;
use function bovigo\assert\predicate\isTrue;

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
   * Reset the 'numero' column in the poetry_map table.
   *
   * @BeforeScenario @resetPoetryNumero
   */
  public function resetTheNumeroIntoPoetryHistory() {
    // Resetting all entries in the 'numero' column to enforce the 'sequence'
    // XML tag instead of the 'numero' in the outgoing translation request.
    if (db_table_exists('poetry_map')) {
      db_update('poetry_map')
        ->fields(array(
          'numero' => '-1',
        ))
        ->execute();
    }
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
   * Remove all translation files in a scenario tagged with @poetry_mock.
   *
   * @poetry
   */
  public function removeAllRequestTranslationFiles() {
    PoetryMock::removeAllRequestTranslationFiles();

    // Delete the tmgmt_file directory.
    $tmgmt_poetry_dir = drupal_realpath('public://') . '/tmgmt_file';
    $process = new Process('rm -rf ' . $tmgmt_poetry_dir);
    $process->run();

    if (!$process->isSuccessful()) {
      throw new ProcessFailedException($process);
    }
  }

  /**
   * Remove pending jobs in a scenario tagged with @poetry_mock.
   *
   * @AfterScenario @poetry_mock
   */
  public function removePendingJobs() {
    PoetryMock::removeAllRequestJobs();
  }

  /**
   * Removes the mock TMGMT translator.
   *
   * @AfterScenario @poetry_mock_cleanup_translator
   */
  public function cleanupMockTranslator() {
    PoetryMock::removeMockTranslator();
    PoetryMock::importMockTranslator();
  }

  /**
   * Verifies that poetry received the last translation request.
   *
   * @Then the poetry translation service received the translation request
   * @Then the poetry translation service received the additional language translation request
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
   * Verifies the version/partie of the last translation request.
   *
   * @Then the translation request has :arg1 to :arg2
   */
  public function assertTranslationRequestHasElement($arg1, $arg2) {
    if (!$this->translationRequest) {
      throw new Exception(
        'translator first needs to confirm they received the translation request'
      );
    }

    if (!isset($this->translationRequest['demande_id'][$arg1])) {
      throw new Exception(
        sprintf(
          '%s does not exist',
          $arg1
        )
      );
    }

    if ($this->translationRequest['demande_id'][$arg1] != $arg2) {
      throw new Exception(
        sprintf(
          'Translation request version is %s, expected %s instead',
          $this->translationRequest['demande_id'][$arg1],
          $arg2
        )
      );
    }
  }

  /**
   * Sets the version/partie of the last translation request.
   *
   * @Then set the translation request :arg1 to :arg2
   */
  public function setTranslationRequest($arg1, $arg2) {
    if (!$this->translationRequest) {
      throw new Exception(
        'translator first needs to confirm they received the translation request'
      );
    }

    if (!in_array($arg1, array('version', 'partie'))) {
      throw new Exception(
        sprintf(
          '%s does not exist or is not allowed to be changed',
          $arg1
        )
      );
    }

    db_update('poetry_map')
      ->fields(array($arg1 => $arg2))
      ->condition('annee', $this->translationRequest['demande_id']['annee'], '=')
      ->condition('numero', $this->translationRequest['demande_id']['numero'], '=')
      ->condition('version', $this->translationRequest['demande_id']['version'], '=')
      ->condition('partie', $this->translationRequest['demande_id']['partie'], '=')
      ->execute();

    $this->translationRequest['demande_id'][$arg1] = $arg2;
  }

  /**
   * Verifies that the last translation request document is valid XHTML.
   *
   * @Then the translation request document is valid XHTML
   */
  public function assertTranslationRequestDocumentIsValidXhtml() {

    $msg = 'You need Tidy extension to test if XHTML is valid.';
    assert(class_exists('tidy'), isTrue(), $msg);

    $this->assertTranslationRequest();

    $document = base64_decode($this->translationRequest['data']['content']);

    $tidy = new tidy();
    $tidy->parseString($document);
    assert($tidy->getStatus(), equals(0), sprintf(
      'The translation document did not pass the tidy XHTML validation: %s.',
      $tidy->errorBuffer
    ));
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

  /**
   * Verifies that the new target language request contains given languages.
   *
   * @Then the additional language translation request contains the following languages:
   */
  public function assertNewTargetLanguageRequestContainsLanguages(TableNode $table) {
    // Getting languages from the given table.
    $table_body_rows = $table->getHash();
    $expected_languages = array_map(
      function ($row) {
        return $row['Language'];
      },
      $table_body_rows
    );

    // Initializing helper arrays.
    $new_languages = [];

    // Checking if there are multiple requests stored in files by poetry mock
    // and getting the last of them.
    if (isset($this->translationRequest['files'])) {
      // Getting available languages.
      $languages = language_list();

      $request_file_info = end($this->translationRequest['files']);
      $request_file = file_load($request_file_info->fid);

      // Getting and processing a XML request.
      $request_xml = file_get_contents($request_file->uri);
      $xml = new SimpleXMLElement($request_xml);
      $results = $xml->xpath('/POETRY/request/attributions');

      // Preparing an array with languages which are part of the request.
      foreach ($results as $result) {
        foreach ($result->attributes() as $key => $attribute) {
          if ($key == 'lgCode') {
            $lg_code = drupal_strtolower((string) $attribute);
            $new_languages[] = $languages[$lg_code]->name;
          }
        }
      }

    }

    assert($new_languages, equals($expected_languages));
  }

}
