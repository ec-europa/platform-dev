<?php

/**
 * @file
 * nexteuropa_faq.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function nexteuropa_faq_taxonomy_default_vocabularies() {
  return array(
    'faq_categories' => (object) array(
      'name' => 'FAQ categories',
      'machine_name' => 'faq_categories',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'faq',
      'weight' => 0,
      'language' => LANGUAGE_NONE,
      'i18n_mode' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
