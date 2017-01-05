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
   * The list of field instances created during scenarios.
   *
   * @var array
   */
  protected $createdFieldList = array();

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
    foreach (node_type_get_types() as $result) {
      $this->nodeTypes[] = $result->type;
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

    foreach (node_type_get_types() as $result) {
      if (!in_array($result->type, $this->nodeTypes)) {
        node_type_delete($result->type);
      }
    }

    unset($this->nodeTypes);
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
   *  Given the following contents using "Full HTML + Change tracking"
   *  for WYSIWYG fields:
   *   | language | title         | body         | moderation state | type    |
   *   | und      | Content title | Content body | validated        | article |
   *   | en       | Content title | Content body | validated        | page    |
   *
   * @param string $text_format
   *    The filter format name or its machine name.
   * @param TableNode $table
   *    List of available content property.
   *
   * @return array
   *    Array containing the created node objects.
   *
   * @Given the following contents using :arg1 for WYSIWYG fields:
   */
  public function theFollowingContentsUsingForWysiwygFields($text_format, TableNode $table) {
    $nodes = array();

    $filters = filter_formats();
    foreach ($filters as $machine_name => $filter) {
      if ($filter->name == $text_format) {
        $text_format = $machine_name;
        break;
      }
    }

    foreach ($table->getHash() as $row) {
      $state = $row['moderation state'];
      unset($row['moderation state']);

      if (isset($row['Body'])) {
        $value = $row['Body'];
        unset($row['Body']);

        $field_instance = field_info_instance('node', 'field_ne_body', $row['type']);

        if ($field_instance) {
          $row['field_ne_body:value'] = $value;
          $row['field_ne_body:format'] = $text_format;
        }
        else {
          $row['body:value'] = $value;
          $row['body:format'] = $text_format;
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

  /**
   * Add a field to a specified content type.
   *
   * @param string $arg1
   *    The machine name of the content type to which attaching the field.
   * @param TableNode $settings
   *    Two columns table containing field settings.
   *
   * @Given a field with the following settings is added to :arg1 type:
   *
   * @throws \InvalidArgumentException
   *    If the field exist already in the Drupal system.
   */
  public function aFieldWithTheFollowingSettingsIsAddedToType($arg1, TableNode $settings) {
    $field_info = array();
    $field_instance_info = array();

    $field_instance_info['entity_type'] = 'node';
    $field_instance_info['bundle'] = $arg1;

    // Assign fields to user before creation.
    foreach ($settings->getRowsHash() as $setting_name => $value) {
      switch ($setting_name) {
        case 'Label':
          $field_instance_info['label'] = $value;
          break;

        case 'Name':
          $field_name = 'field_' . $value;
          $this->createFieldList[$field_name] = array(
            'field_name' => $field_name,
            'entity_type' => 'node',
            'bundle' => $arg1,
          );
          $is_field_exiting = field_info_field($field_name);
          if ($is_field_exiting) {
            throw new \InvalidArgumentException(sprintf('The field "%s" already exists and cannot be used for test purpose.', $setting_name));
          }
          $field_info['field_name'] = $field_name;
          $field_instance_info['field_name'] = $field_name;
          break;

        case 'Type':
          $field_info['type'] = $value;
          break;

        case 'Cardinality':
          $field_info['cardinality'] = ($value == "unlimited") ? -1 : $value;
          break;

        case 'Widget':
          $field_instance_info['widget']['type'] = $value;
          break;

        case 'Allowed values':
          $values = explode('::', $value);
          foreach ($values as $allowed_value) {
            $allowed_option = $allowed_value;
            $allowed_label = $allowed_value;
            $parsed_value = explode('>', $allowed_value);
            if (count($parsed_value) == 2) {
              $allowed_option = $parsed_value[0];
              $allowed_label = $parsed_value[1];
            }
            $allowed_values[$allowed_option] = $allowed_label;
          }
          $field_info['settings']['allowed_values'] = $allowed_values;
          break;

        case 'Translatable':
          $field_info['translatable'] = (bool) $value;
          break;

        case 'Default values':
          break;

        case 'description':
          $field_instance_info['label'] = $value;
          break;

        case 'Required':
          $field_instance_info['required'] = (bool) $value;
          break;
      }
    }
    field_create_field($field_info);
    field_create_instance($field_instance_info);
  }

  /**
   * Removes any fields created by a scenario.
   *
   * @AfterScenario
   */
  public function resetFields() {
    if (empty($this->createFieldList)) {
      return;
    }

    $fields_to_reset = $this->createFieldList;

    foreach ($fields_to_reset as $field_name => $field_instance) {
      field_delete_instance($field_instance, TRUE);
      unset($this->createFieldList[$field_name]);
    }
  }

}
