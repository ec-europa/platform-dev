<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\DrupalContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\DrupalContext as DrupalExtensionDrupalContext;
use Behat\Gherkin\Node\TableNode;

/**
 * Provides step definitions for interacting with Drupal.
 */
class DrupalContext extends DrupalExtensionDrupalContext {
  use \Drupal\nexteuropa\Context\ContextUtil;

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
   * Create a node along with workbench moderation state.
   *
   * Currently it supports only title and body fields since that is enough to
   * cover basic multilingual behaviors, such as URL aliasing or field
   * translation.
   *
   * Below an example of this step usage:
   *
   *  Given the following contents::
   *   | language | title         | body         | moderation state | type    |
   *   | und      | Content title | Content body | validated        | article |
   *   | en       | Content title | Content body | validated        | page    |
   *
   * @param TableNode $table
   *    List of available content prperty.
   *
   * @return array
   *    Array containing the created node objects.
   *
   * @Given the following contents:
   */
  public function theFollowingContents(TableNode $table) {
    $nodes = array();
    foreach ($table->getHash() as $row) {
      $state = $row['moderation state'];
      unset($row['moderation state']);

      if (isset($row['body'])) {
        $field_instance = field_info_instance('node', 'field_ne_body', $row['type']);

        if ($field_instance) {
          $row['field_ne_body'] = $row['body'];
          unset($row['body']);
        }
      }

      $node = (object) $row;
      // If the node is managed by Workbench Moderation, mark it as published.
      if (workbench_moderation_node_moderated($node)) {
        $node->workbench_moderation_state_new = $state;
      }
      $node = $this->nodeCreate($node);
      $node->path['pathauto'] = $this->isPathautoEnabled('node', $node, $node->language);

      // Preserve original language setting.
      $node->field_language = $node->language;

      node_save($node);
      $nodes[] = $node;
    }
    return $nodes;
  }

}
