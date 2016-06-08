<?php

namespace Drupal\field\BaseField;

/**
 * Class TaxonomyTermReferenceFieldHandler.
 *
 * @package Drupal\field\BaseField.
 */
class TaxonomyTermReferenceFieldHandler extends DefaultFieldHandler {

  /**
   * Set which vocabulary can be referenced by the field.
   *
   * @param string $vocabulary_name
   *    Vocabulary machine name.
   *
   * @return $this
   *    Reference to this object instance, so to allow method chaining.
   */
  public function setVocabulary($vocabulary_name) {
    $this->field['settings']['allowed_values'] = array(
      array(
        'vocabulary' => $vocabulary_name,
        'parent' => 0,
      ),
    );
    return $this;
  }

}
