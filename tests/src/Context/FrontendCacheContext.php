<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FrontendCacheContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Behat\Tester\Exception\PendingException;
use Behat\Gherkin\Node\TableNode;

/**
 * Context for steps and assertions related to web frontend caching (Varnish).
 */
class FrontendCacheContext implements Context {

  /**
   * The Mink context.
   *
   * @var MinkContext
   */
  protected $mink;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->mink = $environment->getContext(MinkContext::class);
  }

  /**
   * @Given :arg1 is configured as the purge application tag
   */
  public function valueIsConfiguredAsThePurgeApplicationTag($arg1) {
    throw new PendingException();
  }

  /**
   * @Given the following cache purge rules:
   */
  public function theFollowingCachePurgeRules(TableNode $table) {
    throw new PendingException();
  }

  /**
   * @Then I see an overview with the following cache purge rules:
   */
  public function iSeeAnOverviewWithTheFollowingCachePurgeRules(TableNode $table) {
    throw new PendingException();
  }

  /**
   * @When I click :arg1 next to the :nth cache purge rule
   */
  public function iClickLinkNextToTheNdCachePurgeRule($nth) {
    throw new PendingException();
  }

  /**
   * @Then the web front end cache was instructed to purge the following paths for the application tag :arg1:
   */
  public function theWebFrontEndCacheWasInstructedToPurgeTheFollowingPathsForTheApplicationTag($arg1, TableNode $table) {
    throw new PendingException();
  }

  /**
   * @Then the web front end cache was not instructed to purge any paths
   */
  public function theWebFrontEndCacheWasNotInstructedToPurgeAnyPaths() {
    throw new PendingException();
  }

}
