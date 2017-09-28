<?php

/**
 * @file
 * Contains \TmgmtPoetrySubContext.
 */

use Behat\Mink\Exception\ExpectationException;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalContext;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Drupal\nexteuropa\Context\VariableContext;

/**
 * Behat step definitions for the TMGMT Poetry module.
 */
class TmgmtPoetrySubContext extends RawDrupalContext implements DrupalSubContextInterface {

  public $nodeId;
  public $jobId;
  public $jobReference;

  /**
   * The Drupal driver manager.
   *
   * @var \Drupal\DrupalDriverManager;
   */
  protected $drupal;

  /**
   * Constructs a TmgmtPoetrySubContext object.
   *
   * @param Drupal\DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
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
    $node_id = $this->getCurrentNodeId();
    if (!$node_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a node translation page.");
    }
    else {
      $this->nodeId = $node_id;
    }
  }

  /**
   * Get the Current Node Id in the URL.
   */
  private function getCurrentNodeId() {
    $url = $this->getSession()->getCurrentUrl();
    preg_match_all('/node\/(\d*)/', $url, $matches);
    return (isset($matches[1][0]) ? $matches[1][0] : FALSE);
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
   * Stores the job reference of the translation request page.
   *
   * @Then /^I store the job reference of the translation request page$/
   */
  public function iStoreJobReferenceOfTranslationRequestPage() {
    $node_id = $this->getCurrentNodeId();
    if (!$node_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a node translation page.");
    }
    else {
      $jobs = _tmgmt_poetry_get_active_translation_jobs_by_entity_id($node_id);
      foreach ($jobs as $job) {
        if (strpos($job->reference, "MAIN_") !== FALSE) {
          $this->jobReference = $job->reference;
          return;
        }
      }
      throw new \InvalidArgumentException("Job Reference mismatch: the current node don't have MAIN Job associated.");
    }
  }

  /**
   * Test if the job reference from the page have the next version.
   *
   * @Then /^I test job reference have the next version$/
   */
  public function iTestJobReferenceHaveTheNextVersion() {
    // Test if a Job reference is stored.
    if (empty($this->jobReference)) {
      throw new \InvalidArgumentException("Job Reference mismatch: the current test have not Job Reference stored.");
    }

    $node_id = $this->getCurrentNodeId();
    if (!$node_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a node translation page.");
    }

    $jobs = _tmgmt_poetry_get_active_translation_jobs_by_entity_id($node_id);
    foreach ($jobs as $job) {
      if (strpos($job->reference, "MAIN_") !== FALSE) {
        $old_job_reference_array = explode("/", $this->jobReference);
        $new_job_reference_array = explode("/", $job->reference);
        // Test 'Annee' is the same.
        if ($old_job_reference_array[1] != $new_job_reference_array[1]) {
          throw new \InvalidArgumentException("Reference mismatch: the 'Annee' is not the same.");
        }
        // Test 'Entity' is the same.
        if ($old_job_reference_array[2] != $new_job_reference_array[2]) {
          throw new \InvalidArgumentException("Reference mismatch: the 'Entity' is not the same.");
        }
        // Test 'Version' is the next.
        if ((intval($old_job_reference_array[3]) + 1) != intval($new_job_reference_array[3])) {
          throw new \InvalidArgumentException("Reference mismatch: the 'Version' is not the next.");
        }
        // Test 'Entity' is the same.
        if ($old_job_reference_array[4] != $new_job_reference_array[4]) {
          throw new \InvalidArgumentException("Reference mismatch: the 'Entity' is not the same.");
        }
        // Test 'Format' is the same.
        if ($old_job_reference_array[5] != $new_job_reference_array[5]) {
          throw new \InvalidArgumentException("Reference mismatch: the 'Format' is not the same.");
        }
        $this->jobReference = $job->reference;
        return;
      }
    }

    throw new \InvalidArgumentException("Job Reference mismatch: the current node don't have active MAIN job associated.");
  }

  /**
   * Waiting for 1 second.
   *
   * @Then /^I wait$/
   */
  public function iWaitFor() {
    $this->getSession()->wait(1000);
  }

  /**
   * Find specific date in a table row containing given text.
   *
   * @Then I see the date of the last change in the ":rowText" row
   */
  public function assertLastChangeDateInTableRow($row_text) {
    /** @var Drupal\DrupalExtension\Context\DrupalContext $drupal_context */
    $drupal_context = $this->getContext(DrupalContext::class);
    $row = $drupal_context->getTableRow($this->getSession()
      ->getPage(), $row_text);
    $date_regexp = "/\d{2}\/\d{2}\/\d{4} - \d{2}:\d{2}/";

    if (preg_match($date_regexp, $row->getText()) == FALSE) {
      throw new \Exception(
        sprintf(
          'Found a row containing "%s", but it did not contain a date of the last change.',
          $row_text
        )
      );
    }
  }

  /**
   * Generate a relative date for job deadline.
   *
   * @When I fill in :arg1 with a relative date of :arg2 days
   */
  public function iFillInWithArelativeDateOfDays($field, $number) {
    // Checking if the given field is available.
    if (!$this->getSession()->getPage()->findField($field)) {
      throw new ExpectationException("Field '$field' not found.", $this->getSession());
    }

    $relative_date = date('d/m/Y', strtotime("{$number} day"));
    $this->getSession()->getPage()->fillField($field, $relative_date);
  }

  /**
   * Returns the Behat context that corresponds with the given class name.
   *
   * This is different from InitializedContextEnvironment::getContext() in that
   * it also returns subclasses of the given class name. This allows us to
   * retrieve for example DrupalContext even if it is overridden in a project.
   *
   * @param string $class
   *   A fully namespaced class name.
   *
   * @return \Behat\Behat\Context\Context|false
   *   The requested context, or FALSE if the context is not registered.
   */
  protected function getContext($class) {
    /** @var \Behat\Behat\Context\Environment\InitializedContextEnvironment $environment */
    $environment = $this->drupal->getEnvironment();
    foreach ($environment->getContexts() as $context) {
      if ($context instanceof $class) {
        return $context;
      }
    }

    return FALSE;
  }

  /**
   * Prepares to clean up the website identifier setting.
   *
   * We don't need to do anything ourselves after the scenario finishes,
   * VariableContext will reset to the original value for us.
   *
   * @BeforeScenario cleanup-tmgmt-poetry-website-identifier
   */
  public function prepareCleanupWebsiteIdentifier() {
    /** @var Drupal\nexteuropa\Context\VariableContext $variable_context */
    $variable_context = $this->getContext(VariableContext::class);
    $variable_context->setVariable('website_identifier', '');
  }

  /**
   * Check values in the reference poetry job.
   *
   * @When I check the job reference of the translation request page
   */
  public function iCheckTheJobReferenceOfTheTranslationRequestPage() {
    $node_id = $this->getCurrentNodeId();
    if (!$node_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page is not a node translation page.");
    }
    else {
      $jobs = _tmgmt_poetry_get_active_translation_jobs_by_entity_id($node_id);
      foreach ($jobs as $job) {
        if (strpos($job->reference, "MAIN_") !== FALSE) {
          $test_reference = explode("/", $job->reference);

          // Check the syntax "MAIN_99_POETRY_XXXX/2016/9999/0/0/TRA".
          if (count($test_reference) == 0) {
            throw new \InvalidArgumentException("Job Reference mismatch: the current reference doesn't have good syntax.");
          }

          // Check the 'version' field (0-99).
          if (isset($test_reference[3]) && ($test_reference[3] < 0 || $test_reference[3] > 99)) {
            throw new \InvalidArgumentException("Job Reference mismatch: the 'version' doesn't respect specification.");
          }

          // Check the 'partie' field (0-99).
          if (isset($test_reference[4]) && ($test_reference[4] < 0 || $test_reference[4] > 99)) {
            throw new \InvalidArgumentException("Job Reference mismatch: the 'partie' doesn't respect specification.");
          }

          return;
        }
      }
      throw new \InvalidArgumentException("Job Reference mismatch: the current node don't have MAIN Job associated.");
    }
  }

}
