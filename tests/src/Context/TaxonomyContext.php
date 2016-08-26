<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\TaxonomyContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

/**
 * Context with Taxonomy functionality.
 */
class TaxonomyContext implements Context {

  /**
   * List of Vocabularies created during test execution.
   *
   * @var \Vocabulary[]
   */
  protected $vocabularies = [];

  /**
   * List of Fields created during test execution.
   *
   * @var \Fields[]
   */
  protected $fields = [];

  /**
   * Create vocabulary.
   *
   * @param string $name
   *    Name of the taxonomy.
   *
   * @When I create a new vocabulary :name
   */
  public function iCreateNewVocabulary($name) {
    $vocabulary = array(
      'name' => $name,
      'machine_name' => $name,
      'description' => '',
      'module' => 'taxonomy',
    );
    taxonomy_vocabulary_save((object) $vocabulary);

    // Save the vocabulary for cleaning.
    $this->vocabularies[] = $name;
  }

  /**
   * Revert to previous settings after scenario execution.
   *
   * @AfterScenario
   */
  public function removeVocabularies() {
    // Remove the vocabularies.
    foreach ($this->vocabularies as $vocabulary_name) {
      $vid = db_query("SELECT vid FROM {taxonomy_vocabulary} WHERE machine_name = '$vocabulary_name'")->fetchField();
      taxonomy_vocabulary_delete($vid);
    }
  }

  /**
   * Create term in a vocabulary.
   *
   * @param string $term_name
   *    Name of the term.
   * @param string $vocabulary_name
   *    Name of the vocabulary.
   *
   * @Then I create a new term :term_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewTermInTheVocabulary($term_name, $vocabulary_name) {
    // Get the vocabulary ID.
    $vid = db_query("SELECT vid FROM {taxonomy_vocabulary} WHERE machine_name = '$vocabulary_name'")->fetchField();
    if (empty($vid)) {
      throw new \InvalidArgumentException("The vocabulary '{$vocabulary_name}' doesn't exist.");
    }

    $term = new \stdClass();
    $term->name = $term_name;
    $term->vid = $vid;
    $term->parent = 0;
    taxonomy_term_save($term);
  }

  /**
   * Create a group in a vocabulary.
   *
   * @param string $group_name
   *    Name of the group.
   * @param string $group_type
   *    Type of the group.
   * @param string $vocabulary_name
   *    Name of the vocabulary.
   *
   * @Then I create a new group :group_type named :group_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewGroupNamedInTheVocabulary($group_name, $group_type, $vocabulary_name) {

    $group = (object) array(
      'identifier' => $group_name . '|taxonomy_term|' . $vocabulary_name . '|form',
      'group_name' => $group_name,
      'entity_type' => 'taxonomy_term',
      'bundle' => $vocabulary_name,
      'mode' => 'form',
      'label' => $group_name,
      'children' => array(),
      'weight' => '7',
      'format_type' => $group_type,
      'format_settings' => array(
        'formatter' => 'collapsible',
        'instance_settings' => array(
          'tab' => 'closed',
          'required_fields' => 0,
        ),
      ),
    );
    field_group_group_save($group);
  }

  /**
   * Create a field in a group and in a vocabulary.
   *
   * @param string $field_name
   *    Name of the field.
   * @param string $field_type
   *    Type of the field.
   * @param string $group_name
   *    Name of the group.
   * @param string $vocabulary_name
   *    Name of the vocabulary.
   *
   * @Then I create a new field :field_type named :field_name grouped in :group_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewFieldNamedGroupedInInTheVocabulary($field_name, $field_type, $group_name, $vocabulary_name) {

    // field_delete_field("field_test");
    // field_purge_batch(100);.
    // Make sure the field doesn't already exist.
    if (!field_info_field($field_name)) {
      // Create a field.
      $field = array(
        'field_name' => $field_name,
        'type' => $field_type,
        'label' => $field_name,
      );
      field_create_field($field);
      // Attach the field to our taxonomy entity.
      $instance = array(
        'field_name' => $field_name,
        'entity_type' => 'taxonomy_term',
        'bundle' => $vocabulary_name,
        'label' => $field_name,
        'description' => '',
      );
      field_create_instance($instance);

      // Backup fields created.
      $this->fields[] = $field;

      $groups = field_group_read_groups(array(
        'name' => 'taxonomy_term',
        'bundle' => $vocabulary_name,
        'view_mode' => 'full',
      ));
      $your_group = $groups['taxonomy_term'][$vocabulary_name]['form'][$group_name];
      $your_group->children[] = $field_name;
      field_group_group_save($your_group);
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
    field_purge_batch(100);
  }

}
