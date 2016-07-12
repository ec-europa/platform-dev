<?php

/**
 * @file
 * Contains \TmgmtPoetrySubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Hook\Scope\AfterScenarioScope;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

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
   * Setup test Poetry service before running a scenario tagged with @poetry.
   *
   * @BeforeScenario @poetry
   */
  public function setupPoetry(BeforeScenarioScope $scope) {
    global $base_url;
    $this->variables['poetry_service'] = variable_get('poetry_service');
    variable_set('poetry_service', array(
      'address' => $base_url . '/profiles/multisite_drupal_standard/modules/custom/tmgmt_poetry/tests/tmgmt_poetry_test.wsdl',
      'method' => 'requestService',
      'callback_user' => 'Poetry',
      'callback_password' => 'PoetryPWD',
      'poetry_user' => 'Poetry',
      'poetry_password' => 'PoetryPWD',
    ));
  }

  /**
   * Restore initial Poetry service setup in a scenario tagged with @poetry.
   *
   * @AfterScenario @poetry
   */
  public function restorePoetry(AfterScenarioScope $scope) {
    variable_set('poetry_service', $this->variables['poetry_service']);
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
