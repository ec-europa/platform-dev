<?php

/**
 * @file
 * Definition of views_europa_banner_plugin_rows.
 */

/**
 * Class to define a row plugin handler.
 *
 * @codingStandardsIgnoreFile
 */
class nexteuropa_formatters_views_timelines_rows extends views_plugin_row {
  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['title'] = array('default' => '');
    $options['text'] = array('default' => '');
    $options['footer'] = array('default' => '');
    return $options;
  }

  /**
   * Form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Pre-build all of our option lists for the dials and switches that follow.
    $fields = array('' => t('<None>'));
    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      if ($label = $handler->label()) {
        $fields[$field] = $label;
      }
      else {
        $fields[$field] = $handler->ui_name();
      }
    }

    $form['title'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Title'),
      '#description' => t('Timeline item title, needs to be a text field.'),
      '#options' => $fields,
      '#default_value' => $this->options['title'],
    );

    $form['text'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Text'),
      '#description' => t('Timeline item text, needs to be a text field.'),
      '#options' => $fields,
      '#default_value' => $this->options['text'],
    );

    $form['footer'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Footer'),
      '#description' => t('Timeline footer, needs to be a text field.'),
      '#options' => $fields,
      '#default_value' => $this->options['footer'],
    );
  }

  /**
   * Render a row object. This usually passes through to a theme template
   * of some form, but not always.
   *
   * @param stdClass $row
   *   A single row of the query result, so an element of $view->result.
   *
   * @return string
   *   The rendered output of a single row, used by the style plugin.
   */
  function render($row) {
    static $row_index;
    if (!isset($row_index)) {
      $row_index = 0;
    }

    // In order to have automatic theme hooks suggestions.
    $theme = sprintf('%s__%s__%s', 'timelines', $this->view->name, $this->view->current_display);

    $output = theme(array($theme),
      array(
        'title' => $this->get_field($row_index, $this->options['title']),
        'text' => $this->get_field($row_index, $this->options['text']),
        'footer' => $this->get_field($row_index, $this->options['footer']),
      ));
    $row_index++;
    return $output;
  }

  /**
   * Retrieves a views field value from the style plugin.
   *
   * @param $index
   *   The index count of the row as expected by views_plugin_style::get_field().
   * @param $field_id
   *   The ID assigned to the required field in the display.
   */
  function get_field($index, $field_id) {
    if (empty($this->view->style_plugin) || !is_object($this->view->style_plugin) || empty($field_id)) {
      return '';
    }
    return $this->view->style_plugin->get_field($index, $field_id);
  }
}