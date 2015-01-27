<?php

/**
 * @file
 * Contains \Drupal\taxonomy\Config
 */

namespace Drupal\taxonomy;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Create a taxonomy term for a given vocabulary
   *
   * @param $vocabulary
   *    Vocabulary machine name
   * @param $name
   *    Term name
   * @param $parent
   *    Eventual parent name
   * @return bool|int
   */
  public function createVocabulary($machine_name, $name, $description = '', $hierarchy = 1) {
    $vocabulary = new \stdClass;
    $vocabulary->name = $name;
    $vocabulary->machine_name = $machine_name;
    $vocabulary->description = $description;
    $vocabulary->hierarchy = $hierarchy;
    return taxonomy_vocabulary_save($vocabulary);
  }

  /**
   * Create a taxonomy term for a given vocabulary
   *
   * @param $vocabulary
   *    Vocabulary machine name
   * @param $name
   *    Term name
   * @param $parent
   *    Eventual parent name
   * @return bool
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
