<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Gherkin\Node\TableNode;

/**
 * Context with content type management.
 */
class ContentTypeContext implements Context {

  /**
   * The list of node type before a scenario starts.
   *
   * @var array
   */
  protected $defaultNodeTypes = array();

  /**
   * Remember the list of node type.
   *
   * @BeforeScenario @resetNodeTypes
   */
  public function rememberCurrentNodeTypes() {
    foreach (node_type_get_types() as $result) {
      $this->defaultNodeTypes[$result->type] = $result->type;
    }
  }

  /**
   * Removes any node types created after the last list node type remembered.
   *
   * @AfterScenario @resetNodeTypes
   */
  public function resetNodeTypes() {
    foreach (node_type_get_types() as $result) {
      if (!in_array($result->type, $this->defaultNodeTypes)) {
        node_type_delete($result->type);
      }
    }
    $this->defaultNodeTypes = array();
  }

  /**
   * Add a field to a specified content type.
   *
   * @param string $arg1
   *    The machine name of the content type to which attaching the field.
   * @param TableNode $settings
   *    Two columns table containing field settings.
   *
   * @Given a field with the following settings is added to the :arg1 type:
   *
   * @throws \InvalidArgumentException
   *    If the field exist already in the Drupal system.
   */
  public function aFieldWithTheFollowingSettingsIsAddedToTheType($arg1, TableNode $settings) {
    $field_info = array();
    $field_instance_info = array();

    $field_instance_info['entity_type'] = 'node';

    if (!node_type_get_type($arg1)) {
      throw new \InvalidArgumentException(
        sprintf(
          'The "%s" content type does not exist; then cannot be used for test purposes.',
          $arg1
        )
      );
    }
    $field_instance_info['bundle'] = $arg1;

    // Assign fields to user before creation.
    foreach ($settings->getRowsHash() as $setting_name => $value) {
      switch ($setting_name) {
        case 'Label':
          $field_instance_info['label'] = $value;
          break;

        case 'Name':
          $field_name = 'field_' . $value;
          $is_field_exiting = field_info_field($field_name);
          if ($is_field_exiting) {
            throw new \InvalidArgumentException(
              sprintf(
                'The field "%s" already exists and cannot be used for test purposes.',
                $setting_name
              )
            );
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
   * Add a field group in the content type view and assign fields as children.
   *
   * @param string $arg1
   *    The machine name of the content type to which attaching the field.
   * @param TableNode $settings
   *    Two columns table containing field settings.
   *
   * @Given a field group with the following settings is added to the :arg1 type view:
   */
  public function aFieldGroupWithTheFollowingSettingsIsAddedToTheTypeView($arg1, TableNode $settings) {

    if (!node_type_get_type($arg1)) {
      throw new \InvalidArgumentException(
        sprintf(
          'The "%s" content type does not exist; then cannot be used for test purposes.',
          $arg1
        )
      );
    }

    $group_machine_type = 'fieldset';
    $mode = 'default';
    $group_children = array();
    // TODO : implement the fully support of the group type, missing
    // formatter settings and group mode.
    foreach ($settings->getRowsHash() as $setting_name => $value) {
      switch ($setting_name) {
        case 'Label':
          $group_label = $value;
          break;

        case 'Group name':
          $group_machine_name = $value;
          break;

        case 'Extra CSS classes':
          $css_classes = $value;
          break;

        case 'Weight':
          $weight = $value;
          break;

        case 'Children':
          $raw_children = explode(',', $value);
          foreach ($raw_children as $raw_child) {
            $field_name = 'field_' . $raw_child;
            if (empty(field_info_instance('node', $field_name, $arg1))) {
              throw new \InvalidArgumentException(
                sprintf(
                  'The "%s" field does not exist for "%s" content type does not exist; then it cannot be added to the field group.',
                  $field_name,
                  $arg1
                )
              );
            }
            $group_children[] = $field_name;
          }
          break;
      }
    }

    $identifier = $group_machine_name . '|node|' . $arg1 . '|' . $mode;

    if (field_group_exists($group_machine_name, 'node', $arg1, $mode)) {
      throw new \InvalidArgumentException(
        sprintf(
          'The field group with the id "%s" already exists and cannot be used for test purpose.',
          $identifier
        )
      );
    }

    $group = (object) array(
      'identifier' => $identifier,
      'group_name' => $group_machine_name,
      'entity_type' => 'node',
      'bundle' => $arg1,
      'mode' => $mode,
      'label' => $group_label,
      'children' => $group_children,
      'weight' => $weight,
      'disabled' => FALSE,
      'format_type' => $group_machine_type,
      'format_settings' => array(
        'formatter' => 'collapsible',
        'instance_settings' => array(
          'tab' => 'closed',
          'required_fields' => 0,
          'classes' => $css_classes,
        ),
      ),
    );
    field_group_group_save($group);
  }

}
