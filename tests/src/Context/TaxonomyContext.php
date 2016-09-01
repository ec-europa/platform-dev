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
   * @Given The vocabulary :name exists
   * @When I create a new vocabulary :name
   */
  public function iCreateNewVocabulary($name) {
    $vocabulary = array(
      'name' => $name,
      'machine_name' => $this->getMachineName($name),
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
   * @Given The term :term_name in the vocabulary :vocabulary_name exists
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
   * Create a group in a vocabulary.
   *
   * @param string $group_name
   *    Name of the group.
   * @param string $group_type
   *    Type of the group.
   * @param string $vocabulary_name
   *    Name of the vocabulary.
   *
   * @Given The group :group_type named :group_name in the vocabulary :vocabulary_name exists
   * @Then I create a new group :group_type named :group_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewGroupNamedInTheVocabulary($group_name, $group_type, $vocabulary_name) {

    $group_machine_type = $this->getGroupTypeFormatByName($group_type);
    $group_machine_name = 'group_' . $this->getMachineName($group_name);
    $vocabulary_machine_name = $this->getMachineName($vocabulary_name);

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
   * @Then The field :field_type named :field_name grouped in :group_name in the vocabulary :vocabulary_name exists
   * @Then I create a new field :field_type named :field_name grouped in :group_name in the vocabulary :vocabulary_name
   */
  public function iCreateNewFieldNamedGroupedInInTheVocabulary($field_name, $field_type, $group_name, $vocabulary_name) {
    $field_machine_name = "field_" . $this->getMachineName($field_name);
    $field_machine_type = $this->getFieldTypeFormatByName($field_type);
    $group_machine_name = "group_" . $this->getMachineName($group_name);
    $vocabulary_machine_name = $this->getMachineName($vocabulary_name);

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
   * Create a machine name.
   *
   * @param string $name
   *    Name.
   *
   * @return string
   *    Machine name.
   */
  private function getMachineName($name) {
    $a = explode(",", " ,&,à,á,â,ã,ä,å,æ,ç,è,é,ê,ë,ì,í,î,ï,ñ,ò,ó,ô,õ,ö,ø,ù,ú,û,ü,ý,ÿ,ā,ă,ą,ć,ĉ,ċ,č,ď,đ,ē,ĕ,ė,ę,ě,ĝ,ğ,ġ,ģ,ĥ,ħ,ĩ,ī,ĭ,į,ı,ĳ,ĵ,ķ,ĺ,ļ,ľ,ŀ,ł,ń,ņ,ň,ŉ,ō,ŏ,ő,œ,ŕ,ŗ,ř,ś,ŝ,ş,š,ţ,ť,ŧ,ũ,ū,ŭ,ů,ű,ų,ŵ,ŷ,ź,ż,ž,ƒ,ơ,ư,ǎ,ǐ,ǒ,ǔ,ǖ,ǘ,ǚ,ǜ,ǻ,ǽ,ǿ,ά,έ,ό,Ώ,ώ,ί,ϊ,ΐ,ύ,ϋ,ΰ,ή");
    $b = explode(",", "_,_,a,a,a,a,a,a,ae,c,e,e,e,e,i,i,i,i,n,o,o,o,o,o,o,u,u,u,u,y,y,a,a,a,c,c,c,c,d,d,e,e,e,e,e,g,g,g,g,h,h,i,i,i,i,i,ij,j,k,l,l,l,l,l,l,n,n,n,n,o,o,o,oe,r,r,r,s,s,s,s,t,t,t,u,u,u,u,u,u,w,y,z,z,z,s,f,o,u,a,i,o,u,u,u,u,u,a,ae,o,α,ε,ο,Ω,ω,ι,ι,ι,υ,υ,υ,η");
    $machine_name = str_replace($a, $b, strtolower($name));
    return $machine_name;
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
    $vocabulary = taxonomy_vocabulary_machine_name_load($this->getMachineName($name));
    if (empty($vocabulary)) {
      throw new \InvalidArgumentException("The vocabulary '{$vocabulary_name}' doesn't exist.");
    }
    
    return $vocabulary->vid;
  }

}
