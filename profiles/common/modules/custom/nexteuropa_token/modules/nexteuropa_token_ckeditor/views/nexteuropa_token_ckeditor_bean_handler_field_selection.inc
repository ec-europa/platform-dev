<?php

/**
 * @file
 * Field handler providing a widget to select view modes tokens.
 */

/**
 * Class nexteuropa_token_ckeditor_bean_handler_field_selection.
 *
 * @see: nexteuropa_ckeditor_form_nexteuropa_webtools_settings_form_alter()
 *
 * @ingroup views_field_handlers
 */
class nexteuropa_token_ckeditor_bean_handler_field_selection extends views_handler_field {

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

    $attributes = array('class' => array('token-ckeditor-selection'));
    $attributes['token-ckeditor-label'] = $entity_label;
    $output = array();

    $attributes['token-ckeditor-token'] = "[bean:" . $entity_id . ":view-mode:" . $values->bean_view_mode . "]";
    $attributes['token-ckeditor-type'] = 'default';

    $output[] = l(drupal_ucfirst($values->bean_view_mode), '', array('attributes' => $attributes));
    $output[] = '<input type="text" onfocus="this.select()" class="token-ckeditor-input" value="' . $attributes['token-ckeditor-token'] . '" />';

    return implode(' - ', $output);
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

}
