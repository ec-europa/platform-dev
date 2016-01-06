<?php

/**
 * @file
 * Definition of views_handler_field_taxonomy.
 */

/**
 * Field handler to provide renderer that allows linking to a taxonomy term.
 *
 * @ingroup views_field_handlers
 */
class nexteuropa_newsroom_views_handler_field_taxonomy extends views_handler_field_taxonomy {
  /**
   * Constructor to provide additional field to add.
   *
   * This constructer assumes the taxonomy_term_data table. If using another
   * table, we'll need to be more specific.
   */
  public function construct() {
    parent::construct();
  }

  /**
   * Defines additional options.
   *
   * @return array
   *   Options.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['convert_path_auto'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

  /**
   * Provides link to taxonomy option.
   */
  public function options_form(&$form, &$form_state) {
    $form['convert_path_auto'] = array(
      '#title' => t('Convert URL with pathauto'),
      '#description' => t('Use pathauto clean function to get proper URL'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['convert_path_auto']),
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Render whatever the data is as a link to the taxonomy.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  public function render_link($data, $values) {
    $tid = $this->get_value($values, 'tid');
    if (!empty($this->options['link_to_taxonomy']) && !empty($tid) && $data !== NULL && $data !== '') {
      $term = new stdClass();
      $term->tid = $tid;
      $term->vid = $this->get_value($values, 'vid');
      $term->vocabulary_machine_name = $values->{$this->aliases['vocabulary_machine_name']};
      $this->options['alter']['make_link'] = TRUE;
      $uri = entity_uri('taxonomy_term', $term);
      $this->options['alter']['path'] = $uri['path'];
    }

    if (!empty($this->options['convert_spaces'])) {
      $data = str_replace(' ', '-', $data);
    }

    if (!empty($this->options['convert_path_auto'])) {
      module_load_include('inc', 'pathauto', 'pathauto');
      $data = pathauto_cleanstring($data);
    }

    return $data;
  }

  /**
   * Renders the current field.
   *
   * @param string $values
   *   Value of the field.
   *
   * @return string
   *   Output of the field.
   */
  public function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }

}
