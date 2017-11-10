<?php

/**
 * @file
 * Contains \NexteuropaSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Behat step definitions for Nexteuropa modules.
 */
class MultisiteNotificationsCoreSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  public $nid;

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
   * Constructs a NexteuropaSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Storing node id from URL.
   *
   * @Then /^I remember the node ID of this page$/
   */
  public function iRememberIdOfPage() {
    $url = $this->getSession()->getCurrentUrl();
    preg_match_all('/node\/(\d*)/', $url, $matches);
    $node_id = isset($matches[1][0]) ? $matches[1][0] : FALSE;

    if (!$node_id) {
      throw new \InvalidArgumentException("URL mismatch: the current page does not exist.");
    }
    else {
      $this->nid = $node_id;
    }
  }

  /**
   * Storing node id from URL.
   *
   * @Then /^I insert in Blocked nodes the node ID$/
   */
  public function iInsertNodeIdInBlockedNodes() {
    $this->getSession()->getPage()->fillField("Blocked nodes", $this->nid);
  }

  /**
   * Browsing to node page saved as blocked.
   *
   * @Then /^I go to the page of the node I remembered$/
   */
  public function iGoToThePageRememberedOf() {
    $path = url('node/' . $this->nid, array(
      'base_url' => '',
      'absolute' => TRUE,
    ));
    $this->visitPath($path);
  }

}
