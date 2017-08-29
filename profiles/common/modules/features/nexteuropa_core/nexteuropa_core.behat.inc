<?php
/**
 * @file
 * Contains NexteuropaCoreSubContext.
 */

use \Drupal\DrupalExtension\Context\DrupalSubContextBase;

/**
 * Behat context for the test setup related to Nexteuropa core tokens.
 */
class NexteuropaCoreSubContext extends DrupalSubContextBase {

  /**
   * Creates a single value term_reference field in the article content type.
   *
   * @Given there is a single tag field in the article content type
   */
  public function createSingleTermReferenceField() {
    $single_tag_set_field = array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_tag',
      'foreign keys' => array(
        'tid' => array(
          'columns' => array(
            'tid' => 'tid',
          ),
          'table' => 'taxonomy_term_data',
        ),
      ),
      'indexes' => array(
        'tid' => array(
          0 => 'tid',
        ),
      ),
      'locked' => 1,
      'module' => 'taxonomy',
      'settings' => array(
        'allowed_values' => array(
          0 => array(
            'vocabulary' => 'tags',
            'parent' => 0,
          ),
        ),
        'options_list_callback' => 'i18n_taxonomy_allowed_values',
      ),
      'translatable' => 0,
      'type' => 'taxonomy_term_reference',
    );
    field_create_field($single_tag_set_field);

    $article_single_tag_set_field = array(
      'bundle' => 'article',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => 'Test single value tag.',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'i18n_taxonomy',
          'settings' => array(),
          'type' => 'i18n_taxonomy_term_reference_link',
          'weight' => 10,
        ),
        'teaser' => array(
          'label' => 'above',
          'module' => 'taxonomy',
          'settings' => array(),
          'type' => 'taxonomy_term_reference_link',
          'weight' => 10,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_tag',
      'label' => 'Tag',
      'required' => FALSE,
      'settings' => array(
        'user_field_privacy' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'taxonomy',
        'settings' => array(
          'autocomplete_path' => 'taxonomy/autocomplete',
          'size' => 60,
        ),
        'type' => 'taxonomy_autocomplete',
        'weight' => 220,
      ),
    );

    field_create_instance($article_single_tag_set_field);
  }

}
