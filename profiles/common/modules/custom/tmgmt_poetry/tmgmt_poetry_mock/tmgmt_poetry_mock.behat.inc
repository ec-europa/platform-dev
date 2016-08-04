<?php
/**
 * @file
 * Contains TMGMTPoetryMockSubContexts.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Hook\Scope\AfterScenarioScope;
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
   * The last memorized tmgmt_poetry translation job reference.
   *
   * @var string|null
   */
  protected $translationJobReference = NULL;

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
    \Drupal\tmgmt_poetry_mock\Mock\PoetryMock::removeAllRequestTranslationFiles(
    );
  }

  /**
   * Memorizes the translation job reference found in the confirmation message.
   *
   * @Then I remember the translation job reference mentioned in the confirmation message
   */
  public function iRememberTheTranslationJobReferenceMentionedInTheConfirmationMessage() {
    $translation_job_reference = NULL;

    $selector = $this->getDrupalSelector('success_message_selector');
    $success_messages = $this->getSession()->getPage()->findAll(
      "css",
      $selector
    );
    if (empty($success_messages)) {
      throw new \Exception(
        sprintf(
          'No translation job confirmation message found at %s.',
          $this->getSession()->getCurrentUrl()
        )
      );
    }

    foreach ($success_messages as $success_message) {
      $text = trim($success_message->getText());
      if (1 === preg_match(
          '/Project ID is: (?<reference>.*)$/',
          $text,
          $matches
        )
      ) {
        $translation_job_reference = $matches['reference'];
        break;
      }
    }

    if (!$translation_job_reference) {
      throw new \Exception(
        sprintf(
          'No translation job confirmation message found at %s.',
          $this->getSession()->getCurrentUrl()
        )
      );
    }

    $this->translationJobReference = $translation_job_reference;
  }

  /**
   * Retrieves a specific named selector.
   *
   * @param string $name
   *   Name of the selector.
   *
   * @return string
   *   The selector.
   *
   * @throws Exception
   *   When the selector is not configured.
   */
  private function getDrupalSelector($name) {
    $text = $this->getDrupalParameter('selectors');
    if (!isset($text[$name])) {
      throw new \Exception(sprintf('No such selector configured: %s', $name));
    }
    return $text[$name];
  }

  /**
   * Verifies that poetry received the last translation request.
   *
   * @Then the poetry translation service received the translation request
   */
  public function aPoetryTranslatorCanConfirmThatTheyReceivedTheTranslationRequest() {
    $translation_request = PoetryMock::getTranslationRequestByJobReference(
      $this->translationJobReference
    );

    if (!$translation_request) {
      throw new \Exception(
        sprintf(
          'the poetry translation service did not receive a translation request with reference %s',
          $this->translationJobReference
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
  public function theTranslationRequestHasVersion($arg1) {
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
   * Fills in a specific value in a rich text editor (CKEditor).
   *
   * @Given I fill in the rich text editor :arg1 with :arg2
   */
  public function iFillInTheRichTextEditorWith($arg1, $arg2) {
    /** @var \Behat\Mink\Element\NodeElement $field */
    $field = $this->getSession()->getPage()->findField($arg1);

    if (NULL === $field) {
      throw new Exception(sprintf('Unable to find field "%s"', $arg1));
    }

    $id = $field->getAttribute('id');

    $args = [
      'ckeditor_instance_id' => $id,
      'value' => $arg2,
    ];

    $args_as_js_object = json_encode($args);

    $this->getSession()->executeScript(
      "args = {$args_as_js_object};" .
      "CKEDITOR.instances[args.ckeditor_instance_id].setData(args.value);"
    );
  }

  /**
   * Verifies that the last translation request document is valid XHTML.
   *
   * @Then the translation request document is valid XHTML
   */
  public function theTranslationRequestDocumentIsValidXhtml() {
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

}
