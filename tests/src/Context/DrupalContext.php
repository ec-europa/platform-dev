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
   * The list of node type before a scenario starts.
   *
   * @var array
   */
  protected $nodeTypes;

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
   * Remember the list of node type.
   *
   * @BeforeScenario @reset-node-types
   */
  public function rememberCurrentNodeTypes() {
    $results = db_select('node_type')
      ->fields('node_type', array('type'))
      ->execute();
    if ($results) {
      foreach ($results as $result) {
        $this->nodeTypes[] = $result->type;
      }
    }
  }

  /**
   * Removes any node types created after the last list node type remembered.
   *
   * @AfterScenario @reset-node-types
   */
  public function resetNodeTypes() {
    if (!isset($this->nodeTypes)) {
      return;
    }

    $results = db_select('node_type')
      ->fields('node_type', array('type'))
      ->execute();
    if ($results) {
      foreach ($results as $result) {
        if (!in_array($result->type, $this->nodeTypes)) {
          node_type_delete($result->type);
        }
      }
    }

    unset($this->nodeTypes);
  }

}
