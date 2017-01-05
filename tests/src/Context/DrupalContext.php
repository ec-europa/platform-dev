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

  /**
   * The last node id before a scenario starts.
   *
   * @var int
   */
  protected $maxNodeId;

  protected $createFieldList = array();

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
   * Removes any fields created after a scenario is executed.
   *
   * @AfterScenario @reset-fields
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
