<?php

/**
 * @file
 * Contains \MultisiteMaxlengthSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Behat step definitions for the Multisite Maxlength module.
 */
class MultisiteMaxlengthSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * {@inheritdoc}
   */
  protected $drupal;

  /**
   * List of Fields created during test execution.
   *
   * @var \Fields[]
   */
  protected $fields = [];

  /**
   * Constructs a MultisiteMaxlengthSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Create a new field and a new instance.
   *
   * @param string $field_name
   *    Machine name of the field.
   * @param string $field_type
   *    Type of the field.
   * @param string $field_bundle
   *    Bundle of type.
   *
   * @Then I create a new :field_type field named :field_name on :field_bundle
   */
  public function iCreateNewFieldNamedOn($field_name, $field_type, $field_bundle) {
    // Make sure the field doesn't already exist.
    if (!field_info_field($field_name)) {
      // Create the field.
      $field = array(
        'field_name' => $field_name,
        'type' => $field_type,
        'settings' => array('max_length' => 64),
      );
      field_create_field($field);

      // Create the instance.
      $instance = array(
        'field_name' => $field_name,
        'entity_type' => 'node',
        'bundle' => $field_bundle,
        'label' => $field_name,
        'description' => '',
        'required' => FALSE,
      );
      field_create_instance($instance);

      // Backup fields created.
      $this->fields[] = $field;
    }
    else {
      throw new \InvalidArgumentException("The field '{$field_name}' already exists.");
    }
  }

  /**
   * Revert to previous settings after scenario execution.
   *
   * @AfterScenario
   */
  public function removeFields() {
    // Remove the fields.
    foreach ($this->fields as $field) {
      field_delete_field($field['field_name']);
    }
    $this->fields = [];
    field_purge_batch(100);
  }

}
