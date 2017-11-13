<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FieldContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Exception;

/**
 * Context with field management.
 */
class FieldContext implements Context {

  /**
   * The list of field instances before a scenario starts.
   *
   * @var array
   */
  protected $defaultFields = array();

  /**
   * The list of field groups before a scenario starts.
   *
   * @var array
   */
  protected $defaultFieldGroups = array();

  /**
   * Remember the list of fields existing by default in the site.
   *
   * @BeforeScenario @resetFields
   */
  public function rememberCurrentFields() {
    $this->defaultFields = field_info_field_map();
  }

  /**
   * Removes any fields created by a scenario.
   *
   * @AfterScenario @resetFields
   */
  public function resetFields() {
    $current_fields = field_info_field_map();
    $purge_field_schema = FALSE;
    foreach ($current_fields as $field_name => $field_info) {
      if (!isset($this->defaultFields[$field_name])) {
        $field_info = field_info_field($field_name);
        if (!is_null($field_info)
          && !$field_info['locked']
          && !$field_info['deleted']) {
          field_delete_field($field_name);
          $purge_field_schema = TRUE;
        }
      }
      else {
        // We check if a test has not created an instance of an existing field.
        // If it is the case, we delete only this instance.
        $previous_field_info = $this->defaultFields[$field_name]['bundles'];
        foreach ($field_info['bundles'] as $entity_type => $bundles) {
          $default_bundles = $previous_field_info[$entity_type];
          $created_instances = array_diff($bundles, $default_bundles);
          if (!empty($created_instances)) {
            foreach ($created_instances as $created_instance) {
              $field_instance = field_info_instance($entity_type, $field_name, $created_instance);
              field_delete_instance($field_instance);
            }
          }
        }
      }
    }

    if ($purge_field_schema) {
      field_purge_batch(100);
    }
    $this->defaultFields = array();
  }

  /**
   * Remember the list of field groups existing by default in the site.
   *
   * @BeforeScenario @resetFieldGroups
   */
  public function rememberCurrentFieldGroups() {
    $this->defaultFieldGroups = field_group_read_groups();
  }

  /**
   * Removes any fields group created by a scenario.
   *
   * @AfterScenario @resetFieldGroups
   */
  public function resetFieldGroups() {
    $current_field_groups = field_group_read_groups();
    $this->scanFieldGroupsForResetting($current_field_groups, $this->defaultFieldGroups);
    $this->defaultFieldGroups = array();
  }

  /**
   * Scans the field group list in order to delete unwanted field groups.
   *
   * The process is recursive and it deletes field groups created by scenarios.
   *
   * @param array $field_groups_def_level
   *   The items of the "after tests" field groups array level to scan.
   * @param array $default_def_level
   *   The items of the "before tests" field groups array level to scan.
   * @param string $checked_def_level
   *   The information level implied in the method execution:
   *   - entity_type: first level of field_group_read_groups().
   *   - bundle: second level of field_group_read_groups().
   *   - group_type: third level of field_group_read_groups().
   *   - group: Fourth level of field_group_read_groups().
   *
   * @see field_group_read_groups()
   */
  private function scanFieldGroupsForResetting(array $field_groups_def_level, array $default_def_level, $checked_def_level = 'entity_type') {
    ctools_include('export');
    foreach ($field_groups_def_level as $key => $item) {
      $current_default_def_level = (isset($default_def_level[$key])) ? $default_def_level[$key] : FALSE;
      switch ($checked_def_level) {
        case 'entity_type':
          $this->scanFieldGroupsForResetting($item, $current_default_def_level, 'bundle');
          break;

        case 'bundle':
          $this->scanFieldGroupsForResetting($item, $current_default_def_level, 'group_type');
          break;

        case 'group_type':
          $this->scanFieldGroupsForResetting($item, $current_default_def_level, 'group');
          break;

        default:
          if (!$current_default_def_level) {
            field_group_group_export_delete($item, TRUE);
          }
          break;
      }
    }
  }

  /**
   * Configures the group access field for testing purposes.
   *
   * @Given the group access field is configured for test
   */
  public function groupAccessFieldIsConfiguredForTest() {
    $info = field_info_field('group_access');
    if (is_null($info)) {
      throw new Exception(
        sprintf('The group access field not found.')
      );
    }
    $values = &$info['settings']['allowed_values'];
    $values[0] = 'Public';
    $values[1] = 'Private';
    field_update_field($info);
  }

}
