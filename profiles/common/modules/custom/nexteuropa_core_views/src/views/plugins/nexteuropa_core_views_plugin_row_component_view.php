<?php
/**
 * @file
 * Definition of a Views row style plugin.
 */

/**
 * Class to define a row plugin handler.
 *
 * @codingStandardsIgnoreFile
 */
class nexteuropa_core_views_plugin_row_component_view extends views_plugin_row {

  /**
   * @inheritDoc
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['theme'] = '';
    $options['variables'] = array();
    return $options;
  }

  /**
   * @inheritDoc
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $hook_definitions = variable_get('nexteuropa_core_views_hooks', array());

    $form['theme'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Theme hook'),
      '#description' => t('Select the theme hook to use to render your fields.'),
      '#empty_option' => t('<none>'),
      '#options' => array_combine(array_keys($hook_definitions), array_keys($hook_definitions)),
      '#default_value' => $this->options['theme'],
      '#ajax' => array(
        'path' => views_ui_build_form_url($form_state),
      ),
    );

    // Pre-build all of our option lists for the dials and switches that follow.
    $fields = array();
    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      if ($label = $handler->label()) {
        $fields[$field] = $label;
      }
      else {
        $fields[$field] = $handler->ui_name();
      }
    }

    $hook = isset($form_state['values']['row_options']['theme']) ? $form_state['values']['row_options']['theme'] : $this->options['theme'];

    if (isset($hook_definitions[$hook]['variables'])) {
      $form['variables'] = array(
        '#type' => 'fieldset',
        '#title' => 'Theme hook variables mapping'
      );

      foreach ($hook_definitions[$hook]['variables'] as $var => $val) {
        $form['variables'][$var] = array(
          '#type' => 'select',
          '#empty_option' => t('<none>'),
          '#title' => t('Theme variable: @variable', array('@variable' => $var)),
          '#options' => $fields,
          '#default_value' => $this->options['variables'][$var],
        );
      };
    }

  }

  /**
   * @inheritDoc
   */
  public function options_submit(&$form, &$form_state) {
    // In order to make AJAX working fine, we need this line.
    $form_state['values']['row_options']['variables'] = $form_state['input']['row_options']['variables'];
  }

  /**
   * @inheritDoc
   */
  function render($row) {
    // This part shouldn't be moved to the pre_render method.
    // The pre_render method is called only once and there is no way to get
    // the values of fields in each rows, individually.
    // This is the reason why we are using the render method with the custom
    // method get_field.
    // See the similar plugin views_plugin_row_rss_fields() which is also using
    // the render() method to render.
    static $row_index;
    if (!isset($row_index)) {
      $row_index = 0;
    }

    // In order to have automatic theme hooks suggestions.
    $theme = sprintf('%s__%s__%s', $this->options['theme'], $this->view->name, $this->view->current_display);

    // We build the variables array based on fields mapping.
    $variables = array();
    foreach ($this->options['variables'] as $key => $variable) {
      $variables[$key] = $this->get_field($row_index, $variable);
    }

    // Increment the row_index to get the get_field() method working.
    // Inspired from views_plugin_row_rss_fields.
    $row_index++;

    return theme($theme, $variables);
  }

  /**
   * Retrieves a views field value from the style plugin.
   * This comes from views_plugin_row_rss_fields.
   *
   * @param $index
   *   The index count of the row as expected by views_plugin_style::get_field().
   * @param $field_id
   *   The ID assigned to the required field in the display.
   *
   * @return string
   *   The rendered field.
   */
  function get_field($index, $field_id) {
    if (empty($this->view->style_plugin) || !is_object($this->view->style_plugin) || empty($field_id)) {
      return '';
    }
    return $this->view->style_plugin->get_field($index, $field_id);
  }

}
