<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Context for configuring the SchedulerContext.
 */
class SchedulerContext implements Context {

  /**
   * The variable context.
   *
   * @var VariableContext
   */
  protected $variableContext;

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
   * Update unpublishing date of a node.
   *
   * @When I change the unpublishing date of the :type node with title :title to :date
   */
  public function iChangeUnpublishingDateOfTypeNodeWithTitleToDate($type, $title, $date) {
    $target_node = db_select('node', 'n')
      ->fields('n')
      ->condition('title', $title, '=')
      ->condition('type', $type, '=')
      ->execute()
      ->fetchAssoc();
    if (!empty($target_node)) {
      db_update("scheduler")
        ->fields(array("unpublish_on" => strtotime($date)))
        ->condition('nid', $target_node['nid'], '=')
        ->execute();
    }
    else {
      throw new \InvalidArgumentException("Node '{$title}' of type '{$type}' not found.");
    }
  }

  /**
   * Adds the current day with format Y-m-d.
   *
   * @Then I fill in :arg1 with current day
   */
  public function iFillInWithCurrentDay($arg1) {
    $page = $this->mink->getSession()->getPage();
    $element = $page->findField($arg1);
    if (NULL === $element) {
      throw new \InvalidArgumentException(sprintf('Could not find: "%s"', $arg1));
    }
    $element->setValue(date('Y-m-d'));
  }

  /**
   * Adds future time from now to the field with format H:m+1:10.
   *
   * @Then I fill in :arg1 with future time
   */
  public function iFillInWithFutureTime($arg1) {
    $page = $this->mink->getSession()->getPage();
    $element = $page->findField($arg1);
    if (NULL === $element) {
      throw new \InvalidArgumentException(sprintf('Could not find: "%s"', $arg1));
    }
    date_default_timezone_set(drupal_get_user_timezone());
    $scheduler = date('H:i:10', strtotime('+1 minutes'));
    $element->setValue($scheduler);
  }

}
