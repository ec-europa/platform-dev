<?php

/**
 * @file
 * Contains \\Drupal\\taxonomy\\Config.
 */

namespace Drupal\taxonomy;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\taxonomy.
 */
class Config extends ConfigBase {

  /**
   * Create a vocabulary.
   *
   * @param string $machine_name
   *    Vocabulary machine name.
   * @param string $name
   *    Vocabulary human readable name.
   * @param string $description
   *    Vocabulary description.
   * @param int $hierarchy
   *    If hierarchical or not.
   *
   * @return [a-zA-Z]+
   *   [a-zA-Z]+ vocabulary object.
   */
  public function createVocabulary($machine_name, $name, $description = '', $hierarchy = 1) {
    $vocabulary = new \stdClass();
    $vocabulary->name = $name;
    $vocabulary->machine_name = $machine_name;
    $vocabulary->description = $description;
    $vocabulary->hierarchy = $hierarchy;
    return taxonomy_vocabulary_save($vocabulary);
  }

  /**
   * Delete a vocabulary.
   *
   * @param string $machine_name
   *    Vocabulary machine name.
   *
   * @return bool|int
   *   Constant indicating items were deleted.
   */
  public function deleteVocabulary($machine_name) {

    if ($vocabulary = taxonomy_vocabulary_machine_name_load($machine_name)) {
      $return = taxonomy_vocabulary_delete($vocabulary->vid);
      // The vocabulary is correctly deleted but it only clears the page and
      // block caches; the menu one is untouched.
      // The consequence is that the admin menu is still showing the
      // vocabulary's menu items.
      menu_cache_clear_all();
      return $return;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Create a taxonomy term for a given vocabulary.
   *
   * @param string $vocabulary
   *    Vocabulary machine name.
   * @param string $name
   *    Term name.
   * @param string $parent
   *    Parent field name, if any.
   * @param array $fields
   *    Fields to be attached to term entity.
   * @param int $weight
   *    Term weight.
   *
   * @return object|bool
   *    Return new term object or FALSE.
   */
  public function createTaxonomyTerm($vocabulary, $name, $parent = NULL, $fields = array(), $weight = 0) {

    if ($vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary)) {

      // Exit if term already exists for that vocabulary.
      $term = db_select('taxonomy_term_data', 't')
        ->fields('t', array('tid'))
        ->condition('t.name', $name)
        ->condition('t.vid', $vocabulary->vid)
        ->execute()
        ->fetchAll(\PDO::FETCH_COLUMN);
      if ($term) {
        return FALSE;
      }

      $values = array();
      $values['vocabulary_machine_name'] = $vocabulary->machine_name;
      $values['vid'] = $vocabulary->vid;
      $values['name'] = $name;

      if ($parent) {
        $parent_tid = db_select('taxonomy_term_data', 't')
          ->fields('t', array('tid'))
          ->condition('t.name', $parent)
          ->condition('t.vid', $vocabulary->vid)
          ->execute()
          ->fetchAll(\PDO::FETCH_COLUMN);
        $values['parent'] = $parent_tid;
      }

      if ($fields) {
        foreach ($fields as $field_name => $field) {
          $values[$field_name] = $field;
        }
      }

      if ($weight) {
        $values['weight'] = $weight;
      }

      $entity = entity_create('taxonomy_term', $values);
      entity_save('taxonomy_term', $entity);
      return $entity;
    }
    return FALSE;
  }

  /**
   * Delete a taxonomy term.
   *
   * @param int $tid
   *    Taxonomy term ID.
   *
   * @return int
   *   Constant indicating items were deleted.
   */
  public function deleteTaxonomyTerm($tid) {
    return taxonomy_term_delete($tid);
  }

  /**
   * Perform a taxonomy_get_tree() for a given vocabulary.
   *
   * @param string $vocabulary_name
   *    Vocabulary machine name.
   * @param int $parent
   *    The term ID under which to generate the tree.
   *    If 0, generate the tree for the entire vocabulary.
   * @param int $max_depth
   *    Levels of the tree to return. Leave NULL to return all levels.
   * @param bool $load_entities
   *    If TRUE, a full entity load will occur on the term objects.
   *
   * @return [a-zA-Z]+
   *   [a-zA-Z]+ array of all term objects in the tree.
   *
   * @see: taxonomy_get_tree().
   */
  public function getVocabularyTerms($vocabulary_name, $parent = 0, $max_depth = NULL, $load_entities = FALSE) {

    if ($vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name)) {
      return taxonomy_get_tree($vocabulary->vid, $parent, $max_depth, $load_entities);
    }
    else {
      return array();
    }
  }

}
