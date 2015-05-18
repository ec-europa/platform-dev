<?php

/**
 * @file
 * Definition of views_handler_field_user_roles.
 */

/**
 * Field handler to provide a list of roles.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_business_indicators_ext_uuid extends views_handler_field {
  function render($values) {
    global $language;

    if (array_key_exists($values->business_indicators_ext_index_type, node_type_get_types())) {
      $result = db_select('node', 'n')
        ->fields('n')
        ->condition('uuid', $values->business_indicators_ext_index_uuid, '=')
        ->execute()
        ->fetchAssoc();

      $title = node_load_string_translate($result, $language->language);
    }
    else {
      $result = db_select('taxonomy_term_data', 't')
        ->fields('t')
        ->condition('uuid', $values->business_indicators_ext_index_uuid, '=')
        ->execute()
        ->fetchAssoc();

      $title = taxonomy_load_string_translate($result['tid'], $result['name'], 'term', $language->language);
    }
    return $this->sanitize_value($title);
  }
}
