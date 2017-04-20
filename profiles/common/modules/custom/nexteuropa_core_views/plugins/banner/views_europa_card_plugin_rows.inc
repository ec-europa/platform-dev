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
class ViewsEuropaCardPluginRows extends views_plugin_row {
  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['image'] = array('default' => '');
    $options['label'] = array('default' => '');
    $options['url'] = array('default' => '');
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

    $form['image'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Image'),
      '#options' => $fields,
      '#default_value' => $this->options['image'],
    );

    $form['label'] = array(
      '#type' => 'select',
      '#title' => t('Label'),
      '#options' => $fields,
      '#default_value' => $this->options['label'],
    );

    $form['url'] = array(
      '#type' => 'select',
      '#title' => t('URL'),
      '#options' => $fields,
      '#default_value' => $this->options['url'],
    );
  }

}
