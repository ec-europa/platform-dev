<?php

/**
 * @file
 * Contains \TmgmtPoetrySubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Hook\Scope\AfterScenarioScope;

/**
 * Behat step definitions for the TMGMT Poetry module.
 */
class TmgmtPoetrySubContext extends RawDrupalContext implements DrupalSubContextInterface {

  public $nodeId;
  public $jobId;

  /**
   * The Drupal driver manager.
   *
   * @var \Drupal\DrupalDriverManager;
   */
  protected $drupal;

  /**
   * Contains original variable values set during test execution.
   *
   * @var array
   */
  protected $variables = array();

  /**
   * Constructs a TmgmtPoetrySubContext object.
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
   * Click the first row of a view based on XPATH.
   *
   * @Then /^I click first row in the view table$/
   */
  public function iClickFirstRowInTheTableView() {
    $session = $this->getSession();
    $xpath = '//table/tbody/tr[1]';
    $element = $session->getPage()->find(
      'xpath',
      $session->getSelectorsHandler()->selectorToXpath('xpath', $xpath)
    );

    if (NULL === $element) {
      throw new \InvalidArgumentException(sprintf('Could not evaluate XPath: "%s"', $xpath));
    }

    $element->click();
  }

  /**
   * Storing node id from URL.
   *
   * @Then /^I store node ID of translation request page$/
   */
  public function iStoreNodeIdOfTranslationRequestPage() {
    $url = $this->getSession()->getCurrentUrl();
    preg_match_all('/node\/(\d*)/', $url, $matches);
    $node_id = isset($matches[1][0]) ? $matches[1][0] : FALSE;

    if (!$node_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a node translation page.");
    }
    else {
      $this->nodeId = $node_id;
    }
  }

  /**
   * Storing job id from URL.
   *
   * @Then /^I store job ID of translation request page$/
   */
  public function iStoreJobIdOfTranslationRequestPage() {
    $url = $this->getSession()->getCurrentUrl();
    preg_match_all('/admin\/tmgmt\/jobs\/(\d*)/', $url, $matches);
    $job_id = isset($matches[1][0]) ? $matches[1][0] : FALSE;

    if (!$job_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a translation job page.");
    }
    else {
      $this->jobId = $job_id;
    }
  }

  /**
   * Going back to stored node Id translation request page.
   *
   * @Then /^I go to stored node Id translation request page$/
   */
  public function iGoToTranslationRequestPageForStoredNodeId() {
    $path = url('node/' . $this->nodeId . '/translate', array(
      'base_url' => '',
      'absolute' => TRUE,
    ));
    $this->visitPath($path);
  }

  /**
   * Going back to stored job Id translation request page.
   *
   * @Then /^I go to stored job Id translation request page$/
   */
  public function iGoToTranslationRequestPageForStoredJobId() {
    $path = url('admin/tmgmt/jobs/' . $this->jobId, array(
      'base_url' => '',
      'absolute' => TRUE,
    ));
    $this->visitPath($path);
  }

  /**
   * Waiting for 1 second.
   *
   * @Then /^I wait$/
   */
  public function iWaitFor() {
    $this->getSession()->wait(1000);
  }

}
