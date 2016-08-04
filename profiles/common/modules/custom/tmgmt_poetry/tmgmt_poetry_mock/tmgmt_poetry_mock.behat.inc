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
   * @var string|null
   */
  protected $translationJobReference = null;

  /**
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
    \Drupal\tmgmt_poetry_mock\Mock\PoetryMock::removeAllRequestTranslationFiles();
  }

  /**
   * @Then I remember the translation job reference mentioned in the confirmation message
   */
  public function iRememberTheTranslationJobReferenceMentionedInTheConfirmationMessage()
  {
    $translationJobReference = NULL;
    // Job has been successfully submitted for translation. Project ID is: MAIN_94_POETRY_ABCD/2016/1234/0/26/TRA
    $selector = $this->getDrupalSelector('success_message_selector');
    $selectorObjects = $this->getSession()->getPage()->findAll("css", $selector);
    if (empty($selectorObjects)) {
      throw new \Exception(
        sprintf(
          'No translation job confirmation message found at %s.',
          $this->getSession()->getCurrentUrl()
        )
      );
    }

    foreach ($selectorObjects as $selectorObject) {
      $text = trim($selectorObject->getText());
      if (1 === preg_match(
          '/Project ID is: (?<reference>.*)$/',
          $text,
          $matches
        )
      ) {
        $translationJobReference = $matches['reference'];
        break;
      }
    }

    if (!$translationJobReference) {
      throw new \Exception(
        sprintf(
          'No translation job confirmation message found at %s.',
          $this->getSession()->getCurrentUrl()
        )
      );
    }

    $this->translationJobReference = $translationJobReference;
  }

  /**
   * @param string $name
   * @return string
   * @throws Exception
   */
  private function getDrupalSelector($name) {
    $text = $this->getDrupalParameter('selectors');
    if (!isset($text[$name])) {
      throw new \Exception(sprintf('No such selector configured: %s', $name));
    }
    return $text[$name];
  }

  /**
   * @Then the poetry translation service received the translation request
   */
  public function aPoetryTranslatorCanConfirmThatTheyReceivedTheTranslationRequest() {
    $translationRequest = PoetryMock::getTranslationRequestByJobReference(
      $this->translationJobReference
    );

    if (!$translationRequest) {
      throw new \Exception(
        sprintf(
          'the poetry translation service did not receive a translation request with reference %s',
          $this->translationJobReference
        )
      );
    }

    $this->translationRequest = $translationRequest;
  }

  /**
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
   * @Given I fill in the rich text editor :arg1 with :arg2
   */
  public function iFillInTheRichTextEditorWith($arg1, $arg2)
  {
    /** @var \Behat\Mink\Element\NodeElement $field */
    $field = $this->getSession()->getPage()->findField($arg1);

    if (null === $field) {
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
   * @Then the translation request document is valid XHTML :arg1
   */
  public function theTranslationRequestDocumentIsValidXhtml($arg1) {
    if (!$this->translationRequest) {
      throw new Exception(
        'translator first needs to confirm they received the translation request'
      );
    }

    $request = file_get_contents($this->translationRequest['file']->uri);

    $request_data = PoetryMock::getDataFromRequest($request);

    $document = base64_decode($request_data['content']);

    $response = drupal_http_request(
      'https://validator.w3.org/nu/?out=json&level=error',
      [
        'headers' => [
          'Content-Type' => 'Content-type: application/xhtml+xml; charset=utf-8',
        ],
        'method' => 'POST',
        'data'   => $document,
      ]
    );

    // Info on output from the validator: https://github.com/validator/validator/wiki/Output:-JSON.
    $validation = json_decode($response->data);


    if (!empty($validation->messages)) {
      throw new Exception(
        'The translation document did not pass the W3C XHTML validation.'
      );
    }
  }
}
