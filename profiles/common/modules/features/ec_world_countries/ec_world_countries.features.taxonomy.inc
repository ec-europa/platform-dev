<?php
/**
 * @file
 * ec_world_countries.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ec_world_countries_taxonomy_default_vocabularies() {
  return array(
    'ec_world_countries' => array(
      'name' => 'EC World Countries',
      'machine_name' => 'ec_world_countries',
      'description' => 'A list of the world countries',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => LANGUAGE_NONE,
      'i18n_mode' => 1,
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
