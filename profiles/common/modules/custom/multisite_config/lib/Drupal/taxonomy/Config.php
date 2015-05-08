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
   * @return object
   *    Return vocabulary object.
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
   * Create a taxonomy term for a given vocabulary.
   *
   * @param string $vocabulary
   *    Vocabulary machine name.
   * @param string $name
   *    Term name.
   * @param string $parent
   *    Eventual parent name.
   *
   * @return object|bool
   *    Return new term object or FALSE.
   */
  public function createTaxonomyTerm($vocabulary, $name, $parent = NULL) {

    if ($vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary)) {

      // Exit if term already exists for that vocabulary.
      $term = db_select('taxonomy_term_data', 't')
        ->fields('t', array('tid'))
        ->condition('t.name', $name)
        ->condition('t.vid', $vocabulary->vid)
        ->execute()
        ->fetchAll(PDO::FETCH_COLUMN);
      if ($term) {
        return FALSE;
      }

      $values = array();
      $values['vocabulary_machine_name'] = $vocabulary->machine_name;
      $values['vid'] = $vocabulary->vid;
      $values['name'] = $name;

      if ($parent) {
        $parent_tid = (int) db_select('taxonomy_term_data', 't')
          ->fields('t', array('tid'))
          ->condition('t.name', $parent)
          ->condition('t.vid', $vocabulary->vid)
          ->execute()
          ->fetchAll(PDO::FETCH_COLUMN);
        $values['parent'] = $parent_tid;
      }

      $entity = entity_create('taxonomy_term', $values);
      return entity_save('taxonomy_term', $entity);
    }
    return FALSE;
  }

}
