<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FieldContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

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
   * @BeforeScenario
   */
  public function rememberCurrentFields() {
    $this->defaultFields = field_info_field_map();
  }

  /**
   * Removes any fields created by a scenario.
   *
   * @AfterScenario
   */
  public function resetFields() {
    if (empty($this->defaultFields)) {
      return;
    }

    $current_fields = field_info_field_map();

    foreach ($current_fields as $field_name => $field_info) {
      if (!isset($this->defaultFields[$field_name])) {
        field_delete_field($field_name);
        continue;
      }

      // We check if a test has not created an instance of an existing field.
      // If it is the case, we delete only this instance.
      $previous_field_info = $this->defaultFields[$field_name]['bundles'];
      foreach ($field_info['bundles'] as $entity_type => $bundles) {
        $default_bundles = $previous_field_info[$entity_type];
        $created_instances = array_diff($bundles, $default_bundles);
        if (!empty($created_instances)) {
          foreach ($created_instances as $created_instance) {
            $field_instance = array(
              'field_name' => $field_name,
              'entity_type' => $entity_type,
              'bundle' => $created_instance,
            );
            field_delete_instance($field_instance);
          }
        }
      }
    }
    $this->defaultFields = array();
    field_purge_batch(100);
  }

  /**
   * Remember the list of field groups existing by default in the site.
   *
   * @BeforeScenario
   */
  public function rememberCurrentFieldGroups() {
    $this->defaultFieldGroups = field_group_read_groups();
  }

  /**
   * Removes any fields group created by a scenario.
   *
   * @AfterScenario
   */
  public function resetFieldGroups() {
    if (empty($this->defaultFieldGroups)) {
      return;
    }
    $current_field_groups = field_group_read_groups();
    $this->scanFieldGroupsForResetting($current_field_groups, $this->defaultFieldGroups);
    $this->defaultFieldGroups = array();
    drupal_flush_all_caches();
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
  private function scanFieldGroupsForResetting($field_groups_def_level, $default_def_level, $checked_def_level = 'entity_type') {
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
            ctools_export_crud_delete('field_group', $item);
          }
          break;
      }
    }
  }

}
