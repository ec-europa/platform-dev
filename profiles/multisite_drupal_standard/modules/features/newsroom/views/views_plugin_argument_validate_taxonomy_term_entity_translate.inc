<?php

/**
 * @file
 * Contains the 'taxonomy term' argument validator plugin.
 */

/**
 * Validate whether an argument is an acceptable node.
 */
class views_plugin_argument_validate_taxonomy_term_entity_translate extends views_plugin_argument_validate_taxonomy_term {

  function validate_argument($argument) {
    $vocabularies = array_filter($this->options['vocabularies']);
    $type = $this->options['type'];
    $transform = $this->options['transform'];

    switch ($type) {
      case 'tid':
        if (!is_numeric($argument)) {
          return FALSE;
        }

        $query = db_select('taxonomy_term_data', 'td');
        $query->leftJoin('taxonomy_vocabulary', 'tv', 'td.vid = tv.vid');
        $query->fields('td');
        $query->condition('td.tid', $argument);
        $query->addTag('term_access');
        $term = $query->execute()->fetchObject();
        if (!$term) {
          return FALSE;
        }
        $term = taxonomy_term_load($term->tid);
        $this->argument->validated_title = check_plain(entity_label('taxonomy_term', $term));
        return empty($vocabularies) || !empty($vocabularies[$term->vocabulary_machine_name]);

      case 'tids':
        // An empty argument is not a term so doesn't pass.
        if (empty($argument)) {
          return FALSE;
        }

        $tids = new stdClass();
        $tids->value = $argument;
        $tids = views_break_phrase($argument, $tids);
        if ($tids->value == array(-1)) {
          return FALSE;
        }

        $test = drupal_map_assoc($tids->value);
        $titles = array();

        // check, if some tids already verified
        static $validated_cache = array();
        foreach ($test as $tid) {
          if (isset($validated_cache[$tid])) {
            if ($validated_cache[$tid] === FALSE) {
              return FALSE;
            }
            else {
              $titles[] = $validated_cache[$tid];
              unset($test[$tid]);
            }
          }
        }

        // if unverified tids left - verify them and cache results
        if (count($test)) {
          $query = db_select('taxonomy_term_data', 'td');
          $query->leftJoin('taxonomy_vocabulary', 'tv', 'td.vid = tv.vid');
          $query->fields('td');
          $query->fields('tv', array('machine_name'));
          $query->condition('td.tid', $test);

          $result = $query->execute();

          foreach ($result as $term) {
            if ($vocabularies && empty($vocabularies[$term->machine_name])) {
              $validated_cache[$term->tid] = FALSE;
              return FALSE;
            }
            $term = taxonomy_term_load($term->tid);
            $titles[] = $validated_cache[$term->tid] = check_plain(entity_label('taxonomy_term', $term));
            unset($test[$term->tid]);
          }
        }

        // Remove duplicate titles
        $titles = array_unique($titles);

        $this->argument->validated_title = implode($tids->operator == 'or' ? ' + ' : ', ', $titles);
        // If this is not empty, we did not find a tid.
        return empty($test);

      case 'name':
      case 'convert':

        // faccio la query verso la tabella name_field per capire se c'è una traduzione
        $query = db_select('field_data_name_field', 'nf');
        $query->fields('nf', array('entity_id', 'language'));
        $query->condition('name_field_value', $argument, '=');

        $term = $query->execute()->fetchObject();

        // se esiste il termine di tassonomia e/o una sua traduzione:
        if ($term) {
          if ($type == 'convert') {
            $this->argument->argument = $term->entity_id;
          }
          $this->argument->validated_title = check_plain($argument);
          return TRUE;
        }
        return FALSE;
    }
  }
}