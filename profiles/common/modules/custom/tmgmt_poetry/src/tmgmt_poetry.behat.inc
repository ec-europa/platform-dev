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

}
