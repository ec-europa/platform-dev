<?php

/**
 * @file
 * Contains \Drupal\multisite_config\Tests\NextEuropaDataExportTest.
 */

namespace Drupal\multisite_config\Tests\Drupal\taxonomy;

use Drupal\multisite_config\Tests\ConfigAbstractTest;
use Drupal\taxonomy\Config;

/**
 * Class ConfigTest.
 *
 * @package Drupal\multisite_config\Tests\Drupal\taxonomy
 */
class ConfigTest extends ConfigAbstractTest {

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    $this->service = new Config();
  }

  /**
   * Test vocabulary and terms creation.
   */
  public function testVocabularyAndTermsCreation() {

    $vocabulary_name = 'vocabulary_' . rand();
    $vocabulary_label = 'Vocabulary ' . rand();

    $this->service->createVocabulary($vocabulary_name, $vocabulary_label);
    $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);

    $this->assertEquals($vocabulary_name, $vocabulary->machine_name);
    $this->assertEquals($vocabulary_label, $vocabulary->name);

    $term = $this->service->createTaxonomyTerm($vocabulary_name, 'Term');
    $this->assertNotFalse($term);

    $tree = taxonomy_get_tree($vocabulary->vid);
    $this->assertNotEmpty($tree);
    $this->assertEquals('Term', $tree[0]->name);

    $this->assertEquals(SAVED_DELETED, $this->service->deleteTaxonomyTerm($term->tid));
    $this->assertEmpty(taxonomy_get_tree($vocabulary->vid));

    $this->assertEquals(SAVED_DELETED, $this->service->deleteVocabulary($vocabulary_name));
    $this->assertEmpty(taxonomy_vocabulary_machine_name_load($vocabulary_name));
  }

}
