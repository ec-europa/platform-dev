<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\DrupalContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\DrupalContext as DrupalExtensionDrupalContext;

/**
 * Provides step definitions for interacting with Drupal.
 */
class DrupalContext extends DrupalExtensionDrupalContext {

  /**
   * The last node id before a scenario starts.
   *
   * @var int
   */
  protected $maxNodeId;

  /**
   * {@inheritdoc}
   */
  public function loggedIn() {
    $session = $this->getSession();
    $session->visit($this->locatePath('/'));

    // Check if the 'logged-in' class is present on the page.
    $element = $session->getPage();
    return $element->find('css', 'body.logged-in');
  }

  /**
   * Visit a node page given its type and title.
   *
   * @param string $type
   *    The node type.
   * @param string $title
   *    The node title.
   *
   * @Then I visit the :type content with title :title
   */
  public function visitContentPage($type, $title) {
    $nodes = node_load_multiple([], ['title' => $title, 'type' => $type], TRUE);
    if (!$nodes) {
      throw new \InvalidArgumentException("Node of type '{$type}' and title '{$title}' not found.");
    }
    // Get node path without any base path by setting 'base_url' and 'absolute'.
    $node = array_shift($nodes);
    $path = 'node/' . $node->nid;
    cache_clear_all($path, 'cache_path');
    $path = url($path, ['base_url' => '', 'absolute' => TRUE]);
    // Visit newly created node page.
    $this->visitPath($path);
  }

  /**
   * Remember the last node id.
   *
   * @BeforeScenario @reset-nodes
   */
  public function rememberCurrentLastNode() {
    $query = db_select('node');
    $query->addExpression('MAX(nid)');
    $max_node_id = $query->execute()->fetchField();

    if (NULL === $max_node_id) {
      $this->maxNodeId = 0;
    }
    else {
      $this->maxNodeId = intval($max_node_id);
    }
  }

  /**
   * Removes any nodes created after the last node id remembered.
   *
   * @AfterScenario @reset-nodes
   */
  public function resetNodes() {
    if (!isset($this->maxNodeId)) {
      return;
    }

    $all_nodes_after_query = (new \EntityFieldQuery())
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('nid', $this->maxNodeId, '>');

    $all_nodes_after = $all_nodes_after_query->execute();
    $all_nodes_after = reset($all_nodes_after);
    if (is_array($all_nodes_after)) {
      entity_delete_multiple('node', array_keys($all_nodes_after));
    }
    unset($this->maxNodeId);
  }

  /**
   * Logout custom.
   *
   * @Given I am an anonymous user custom
   * @Given I am not logged in custom
   */
  public function assertAnonymousUser() {
    // Verify the user is logged out.
    if ($this->loggedIn()) {
      $this->logout();
    }
    if ($this->loggedIn()) {
      throw new \Exception("Logout failed.");
    }
  }

}
