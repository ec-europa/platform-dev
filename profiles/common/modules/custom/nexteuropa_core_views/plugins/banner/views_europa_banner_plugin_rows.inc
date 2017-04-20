<?php
/**
 * @file
 * Definition of views_bootstrap_plugin_rows.
 */

/**
 * Class to define a row plugin handler.
 *
 * @codingStandardsIgnoreFile
 */
class ViewsEuropaBannerPluginRows extends views_plugin_row {
  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['quote'] = array('default' => '');
    $options['author'] = array('default' => '');
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

    $form['quote'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Quote'),
      '#options' => $fields,
      '#default_value' => $this->options['quote'],
    );

    $form['author'] = array(
      '#type' => 'select',
      '#title' => t('Author'),
      '#options' => $fields,
      '#default_value' => $this->options['author'],
    );

  }

}
