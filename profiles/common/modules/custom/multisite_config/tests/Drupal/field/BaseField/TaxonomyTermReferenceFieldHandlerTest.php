<?php

namespace Drupal\multisite_config\Tests\Drupal\field\BaseField;

use Drupal\multisite_config\Tests\ConfigAbstractTest;

/**
 * Class DefaultFieldHandlerTest.
 *
 * @package Drupal\multisite_config\Tests\Drupal\field\BaseField
 */
class TaxonomyTermReferenceFieldHandlerTest extends ConfigAbstractTest {

  /**
   * Test base field saving.
   *
   * @dataProvider fieldDataProvider
   */
  public function testFieldSaving($field_name, $vocabulary_name) {
    $service = multisite_config_service('field');
    $service->createBaseField($field_name, 'taxonomy_term_reference')
      ->setVocabulary($vocabulary_name)
      ->save();

    $field = field_info_field($field_name);

    $this->assertEquals('taxonomy_term_reference', $field['type']);
    $this->assertEquals($field_name, $field['field_name']);
    $this->assertEquals('taxonomy', $field['module']);
    $this->assertEquals(1, $field['cardinality']);
    $this->assertEquals($vocabulary_name, $field['settings']['allowed_values'][0]['vocabulary']);

    field_delete_field($field_name);
  }

  /**
   * Data provider: file name, referenced vocabulary.
   *
   * @see self::testHandlerConstructor()
   */
  public function fieldDataProvider() {
    return array(
      array('field_name_' . rand(), 'tags'),
    );
  }

}
