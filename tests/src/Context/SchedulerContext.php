<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

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

}
