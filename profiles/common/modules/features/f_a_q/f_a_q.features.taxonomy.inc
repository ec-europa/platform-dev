<?php
/**
 * @file
 * f_a_q.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function f_a_q_taxonomy_default_vocabularies() {
  return array(
    'faq_categories' => (object) array(
      'name' => 'FAQ categories',
      'machine_name' => 'faq_categories',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'faq',
      'weight' => 0,
      'language' => 'und',
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
