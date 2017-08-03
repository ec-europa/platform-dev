<?php

/**
 * @file
 * Field handler providing a widget to select view modes tokens.
 */

/**
 * Class nexteuropa_token_ckeditor_handler_field_selection.
 *
 * @see: nexteuropa_token_ckeditor_form_nexteuropa_token_settings_form_alter()
 *
 * @ingroup views_field_handlers
 */
class nexteuropa_token_ckeditor_handler_field_selection extends views_handler_field {

  /**
   * Views options definition.
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['label_field'] = array('default' => '');
    $options['view_modes'] = array('default' => array());
    return $options;
  }

  /**
   * Exposes field handler option form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['label_field'] = array(
      '#type' => 'select',
      '#title' => t('Entity label field'),
      '#default_value' => $this->options['label_field'],
      '#options' => $this->view->display_handler->get_field_labels(),
    );
    $form['view_modes'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Available view modes'),
      '#default_value' => $this->options['view_modes'],
      '#options' => $this->get_view_modes_options(),
      '#required' => TRUE,
    );
  }

  /**
   * Return the rendered field.
   *
   * @param object $values
   *   Render values.
   *
   * @return string
   *   Rendered output.
   */
  public function render($values) {
    $entity_id = $values->{$this->field_alias};
    $entity_label = '';
    if (isset($this->view->field[$this->options['label_field']])) {
      $field_alias = $this->view->field[$this->options['label_field']]->field_alias;
      $entity_label = $values->$field_alias;
    }

    $attributes = array('class' => 'token-ckeditor-selection');
    $attributes['token-ckeditor-label'] = $entity_label;
    $output = array();

    $attributes['token-ckeditor-token'] = "[node:$entity_id:link]";
    $attributes['token-ckeditor-type'] = 'link';
    $output[] = l(t('Link'), '', array('attributes' => $attributes));

    foreach ($this->options['view_modes'] as $view_mode => $enabled) {
      if ($enabled) {
        $attributes['token-ckeditor-token'] = "[node:$entity_id:view-mode:$view_mode]";
        $attributes['token-ckeditor-type'] = 'view-mode';
        $output[] = l($this->get_view_mode_label($view_mode), '', array('attributes' => $attributes));
      }
    }
    $output[] = t('Token:') . '<input type="text" onfocus="this.select()" class="token-ckeditor-input" value="[node:' . $entity_id . ':url]" />';
    return implode($output, ' - ');
  }

  /**
   * Get view modes machine names per entity type.
   *
   * @return array
   *   List of view modes machine names.
   */
  private function get_view_modes_options() {

    $view_modes = array();
    $info = entity_get_info($this->table);
    foreach ($info['view modes'] as $mode => $mode_info) {
      $view_modes[$mode] = $mode_info['label'];
    }
    return $view_modes;
  }

  /**
   * Get view mode label.
   *
   * @param string $view_mode
   *   View mode machine name.
   *
   * @return mixed
   *   View mode options array.
   */
  private function get_view_mode_label($view_mode) {

    $view_modes = $this->get_view_modes_options();
    return $view_modes[$view_mode];
  }

}
