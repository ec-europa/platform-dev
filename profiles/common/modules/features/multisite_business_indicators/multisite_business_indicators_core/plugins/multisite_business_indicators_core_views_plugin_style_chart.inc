<?php

/**
 * @file
 * multisite_business_indicators_core_views_plugin_style_chart.inc
 */

/**
 * Style plugin to render each item as a row in a table.
 *
 * @ingroup views_style_plugins
 */
class multisite_business_indicators_core_views_plugin_style_chart extends views_plugin_style {

  /**
   * Returns chart types.
   */
  public function get_chart_types() {
    return array(
      'column2d'    => t('Column chart 2D'),
      'pie2d'       => t('Pie chart 2D'),
      'column3d'    => t('Column chart 3D'),
      'pie3d'       => t('Pie chart 3D'),
    );
  }

  /**
   * Returns options.
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['caption'] = array('default' => '');
    $options['type'] = array('default' => 'column2d');
    $options['data_labels'] = array('default' => '');
    $options['data_values'] = array('default' => '');
    $options['number_prefix'] = array('default' => '');
    $options['width'] = array('default' => '');
    $options['height'] = array('default' => 350);

    return $options;
  }

  /**
   * Form constructor for the chart form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $handlers = $this->display->handler->get_handlers('field');
    if (!empty($handlers) && count($handlers) < 2) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least two fields before you can configure your chart settings') . '</div>',
      );
      return;
    }

    foreach ($handlers as $field_name => $field_handler) {
      $fields[$field_name] = $field_handler->ui_name();
    }

    $form['caption'] = array(
      '#type' => 'textfield',
      '#title' => t('Chart caption'),
      '#default_value' => $this->options['caption'],
    );
    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Type of chart'),
      '#options' => $this->get_chart_types(),
      '#default_value' => $this->options['type'],
      '#required' => TRUE,
    );
    $form['data_labels'] = array(
      '#type' => 'select',
      '#title' => t('Labels'),
      '#options' => $fields,
      '#default_value' => $this->options['data_labels'],
      '#required' => TRUE,
      '#description' => t('Field containined chart labels. ATTENTION: rendered values must not contain HTML (like links, etc...).'),
    );
    $form['data_values'] = array(
      '#type' => 'select',
      '#title' => t('Values'),
      '#options' => $fields,
      '#default_value' => $this->options['data_values'],
      '#required' => TRUE,
      '#description' => t('Field containined chart values. ATTENTION: rendered values must be valid numeric values.'),
    );
    $form['number_prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Number prefix'),
      '#default_value' => $this->options['number_prefix'],
      '#description' => t('Prefix to be added when printing our data values, for exemple "EUR"'),
      '#size' => 10,
    );
    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $this->options['width'],
      '#description' => t('Leave empty to span the chart at 100% witdh'),
      '#size' => 10,
    );
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => $this->options['height'],
      '#size' => 10,
      '#required' => TRUE,
    );

  }

}
