<?php

/**
 * @file
 * e_library_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function e_library_core_taxonomy_default_vocabularies() {
  return array(
    'media_tags' => array(
      'name' => 'Media tags',
      'machine_name' => 'media_tags',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'media_library_core',
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
