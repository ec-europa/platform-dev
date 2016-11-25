<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\TaxonomyContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Drupal\nexteuropa\Component\Utility\Transliterate;

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
   * The transliterate utility object.
   *
   * @var \Drupal\nexteuropa\Component\Utility\Transliterate
   */
  protected $transliterate;

  /**
   * TaxonomyContext constructor.
   */
  public function __construct() {
    $this->transliterate = new Transliterate();
  }

  /**
   * Create vocabulary.
   *
   * @param string $name
   *    Name of the taxonomy.
   *
   * @Given the vocabulary :name exists
   *
   * @When I create a new vocabulary :name
   */
  public function iCreateNewVocabulary($name) {
    $vocabulary = array(
      'name' => $name,
      'machine_name' => $this->transliterate->getMachineName($name),
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
      taxonomy_vocabulary_delete($this->getTaxonomyIdByName($vocabulary_name));
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
   * @Given the term :term_name in the vocabulary :vocabulary_name exists
   *
   * @Then I create a new term :term_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewTermInTheVocabulary($term_name, $vocabulary_name) {
    $term = new \stdClass();
    $term->name = $term_name;
    $term->vid = $this->getTaxonomyIdByName($vocabulary_name);
    $term->parent = 0;
    taxonomy_term_save($term);
  }

  /**
   * Create term with a parent in a vocabulary.
   *
   * @param string $term_name
   *    Name of the term.
   * @param string $vocabulary_name
   *    Name of the vocabulary.
   *
   * @Given the term :term_name with the parent term :parent_term in the vocabulary :vocabulary_name exists
   *
   * @Then I create a new term :term_name with a parent term :parent_term in the vocabulary :vocabulary_name
   */
  public function iCreateNewTermWithParentInTheVocabulary($term_name, $parent_name, $vocabulary_name) {
    $parent_term = array_shift(taxonomy_get_term_by_name($parent_term, $vocabulary_name));
    if (!empty($parent_term)) {
      $term = new \stdClass();
      $term->name = $term_name;
      $term->vid = $this->getTaxonomyIdByName($vocabulary_name);
      $term->parent = $parent_term->tid;
      taxonomy_term_save($term);
    }
    else {
      throw new \InvalidArgumentException("The parent term '{$parent_name}' doesn't exist.");
    }
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
   * @Given the group :group_type named :group_name in the vocabulary :vocabulary_name exists
   *
   * @Then I create a new group :group_type named :group_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewGroupNamedInTheVocabulary($group_name, $group_type, $vocabulary_name) {

    $group_machine_type = $this->getGroupTypeFormatByName($group_type);
    $group_machine_name = $this->transliterate->getMachineName('group_' . $group_name);
    $vocabulary_machine_name = $this->transliterate->getMachineName($vocabulary_name);

    $group = (object) array(
      'identifier' => $group_machine_name . '|taxonomy_term|' . $vocabulary_machine_name . '|form',
      'group_name' => $group_machine_name,
      'entity_type' => 'taxonomy_term',
      'bundle' => $vocabulary_machine_name,
      'mode' => 'form',
      'label' => $group_name,
      'children' => array(),
      'weight' => '7',
      'format_type' => $group_machine_type,
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
   * @Given the field :field_type named :field_name grouped in :group_name in the vocabulary :vocabulary_name exists
   *
   * @Then I create a new field :field_type named :field_name grouped in :group_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewFieldNamedGroupedInInTheVocabulary($field_name, $field_type, $group_name, $vocabulary_name) {
    $field_machine_name = $this->transliterate->getMachineName('field_' . $field_name);
    $field_machine_type = $this->getFieldTypeFormatByName($field_type);
    $group_machine_name = $this->transliterate->getMachineName('group_' . $group_name);
    $vocabulary_machine_name = $this->transliterate->getMachineName($vocabulary_name);

    // Make sure the field doesn't already exist.
    if (!field_info_field($field_machine_name)) {
      // Create a field.
      $field = array(
        'field_name' => $field_machine_name,
        'type' => $field_machine_type,
        'label' => $field_name,
      );
      field_create_field($field);
      // Attach the field to our taxonomy entity.
      $instance = array(
        'field_name' => $field_machine_name,
        'entity_type' => 'taxonomy_term',
        'bundle' => $vocabulary_machine_name,
        'label' => $field_name,
        'description' => '',
      );
      field_create_instance($instance);

      // Backup fields created.
      $this->fields[] = $field;

      $groups = field_group_read_groups(array(
        'name' => 'taxonomy_term',
        'bundle' => $vocabulary_machine_name,
        'view_mode' => 'full',
      ));
      $your_group = $groups['taxonomy_term'][$vocabulary_machine_name]['form'][$group_machine_name];
      $your_group->children[] = $field_machine_name;
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

  /**
   * Get the type format of a Group by the name.
   *
   * @param string $name
   *    Name of the group.
   *
   * @return string
   *    Machine name of the group.
   */
  private function getGroupTypeFormatByName($name) {
    $formats = field_group_formatter_info();
    foreach ($formats['form'] as $key => $value) {
      if (strtolower($value['label']) == strtolower($name)) {
        $group_type_id = $key;
      }
    }

    if (!isset($group_type_id)) {
      throw new \InvalidArgumentException("The Group Type Format '{$name}' doesn't exist.");
    }

    return $group_type_id;
  }

  /**
   * Get the type format of a Field by the name.
   *
   * @param string $name
   *    Name of the field.
   *
   * @return string
   *    Machine name of the field.
   */
  private function getFieldTypeFormatByName($name) {
    $formats = array_merge(text_field_info(), number_field_info(), list_field_info(), image_field_info(), file_field_info());
    foreach ($formats as $key => $value) {
      if (strtolower($value['label']) == strtolower($name)) {
        $field_type_id = $key;
      }
    }

    if (!isset($field_type_id)) {
      throw new \InvalidArgumentException("The Field Type Format '{$name}' doesn't exist.");
    }

    return $field_type_id;
  }

  /**
   * Get the Taxonomy Id by the name.
   *
   * @param string $name
   *    Name of the taxonomy.
   *
   * @return string
   *    Id of the taxonomy.
   */
  private function getTaxonomyIdByName($name) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($this->transliterate->getMachineName($name));
    if (empty($vocabulary)) {
      throw new \InvalidArgumentException("The vocabulary '{$name}' doesn't exist.");
    }
    return $vocabulary->vid;
  }

}
