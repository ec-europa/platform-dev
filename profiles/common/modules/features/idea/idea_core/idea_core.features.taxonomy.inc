<?php
/**
 * @file
 * idea_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function idea_core_taxonomy_default_vocabularies() {
  return array(
    'idea_categories' => array(
      'name' => 'Idea categories',
      'machine_name' => 'idea_categories',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'idea_core',
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
    'idea_status' => array(
      'name' => 'Idea status',
      'machine_name' => 'idea_status',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'idea_core',
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
