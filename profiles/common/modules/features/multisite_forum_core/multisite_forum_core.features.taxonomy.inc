<?php
/**
 * @file
 * multisite_forum_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function multisite_forum_core_taxonomy_default_vocabularies() {
  return array(
    'forums' => array(
      'name' => 'Forums',
      'machine_name' => 'forums',
      'description' => 'Forum navigation vocabulary',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -10,
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
