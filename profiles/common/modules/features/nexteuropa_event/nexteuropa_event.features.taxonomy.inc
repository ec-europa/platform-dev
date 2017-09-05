<?php
/**
 * @file
 * nexteuropa_event.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function nexteuropa_event_taxonomy_default_vocabularies() {
  return array(
    'nexteuropa_event_type' => (object) array(
      'name' => 'Nexteuropa Event type',
      'machine_name' => 'nexteuropa_event_type',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
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
