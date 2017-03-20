<?php
/**
 * @file
 * Contains DrupalMailContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Hook\Scope\AfterScenarioScope;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\TableNode;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;
use function bovigo\assert\predicate\isNotEmpty;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Context for the internal mail handling.
 *
 * This context can be used for testing the mail features.
 */
class DrupalMailContext extends RawDrupalContext implements DrupalSubContextInterface {
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
   * The captured mail data.
   *
   * @var array
   */
  protected $capturedMail;

  /**
   * The variable context.
   *
   * @var VariableContext
   */
  protected $variableContext;

  /**
   * Constructs a DrupalMailContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Grabs other contexts we rely on from the environment.
   *
   * @BeforeScenario @internalMail
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    $this->variableContext = $environment->getContext(VariableContext::class);
  }

  /**
   * Clear the captured data.
   *
   * @AfterScenario @internalMail
   */
  public function clearCapturedData(AfterScenarioScope $scope) {
    // Deleting the 'drupal_test_email_collector' variable.
    variable_del('drupal_test_email_collector');
  }

  /**
   * Configure Drupal to use the DrupalMailContext for mail handling.
   *
   * @Given platform is configured to use the internal mail handling
   */
  public function platformIsConfiguredToUseInternalMailHandling() {
    $mail_system = array('default-system' => 'TestingMailSystem');
    // Using VariableContext to set the specific variable. It will be
    // restored to the previous value after finishing a scenario.
    $this->variableContext->setVariable('mail_system', $mail_system);
  }

  /**
   * Verifies that Drupal internal mail handler received the mail.
   *
   * @Then the e-mail has been sent
   */
  public function assertInternalMailHandlerReceivedTheMail() {
    $captured_mail = $this->getCapturedMail();
    assert($captured_mail, isNotEmpty());
    $this->capturedMail = $captured_mail;
  }

  /**
   * Assert the properties in the captured mail.
   *
   * @Then the sent e-mail has the following properties:
   */
  public function assertCapturedMailHasTheFollowingProperties(TableNode $table) {
    $this->assertCapturedMail();
    $expected_properties = $table->getRowsHash();
    foreach ($expected_properties as $key => $value) {
      assert($this->capturedMail[$key], equals($value), "Value of '{$key}' is not equal.");
    }
  }

  /**
   * Assert a mail was captured.
   *
   * @throws \Exception
   *   When no mail was captured.
   */
  protected function assertCapturedMail() {
    if (!$this->capturedMail) {
      throw new \Exception(
        'The internal mail handler first needs to confirm that it captured the mail'
      );
    }
  }

  /**
   * Returns a mail captured by the Drupal internal mail handler.
   *
   * @return array
   *   An empty or a mail data array
   */
  private function getCapturedMail() {
    // We can't use variable_get() here because $conf is loaded when the
    // Drupal driver is first bootstrapped. Any subsequent changes to variables
    // done through the UI
    // (ie with step definitions that use the built-in Mink/Behat functionality)
    // won't be reflected in $conf, so we need to fetch the variable directly
    // from the database.
    $mail_from_db = db_select('variable', 'var')
      ->fields('var', ['value'])
      ->condition('var.name', 'drupal_test_email_collector')
      ->execute()
      ->fetchField();
    $captured_mail = unserialize($mail_from_db);

    if (count($captured_mail)) {
      return array_pop($captured_mail);
    }

    return $captured_mail;
  }

}
