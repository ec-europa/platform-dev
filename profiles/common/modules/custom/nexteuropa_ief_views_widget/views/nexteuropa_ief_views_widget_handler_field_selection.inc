<?php

/**
 * @file
 * Contains IEF selection field handler class.
 */

/**
 * Class nexteuropa_ief_views_widget_handler_field_selection.
 */
class nexteuropa_ief_views_widget_handler_field_selection extends views_handler_field {

  /**
   * Define default options.
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['entity_reference_field'] = array('default' => '');
    $options['label_field'] = array('default' => '');
    return $options;
  }

  /**
   * Exposes field handler options form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['entity_reference_field'] = array(
      '#type' => 'select',
      '#title' => t('Entity reference field'),
      '#default_value' => $this->options['entity_reference_field'],
      '#options' => $this->get_entity_reference_field_options(),
    );
    $form['label_field'] = array(
      '#type' => 'select',
      '#title' => t('Entity label field'),
      '#default_value' => $this->options['label_field'],
      '#options' => $this->view->display_handler->get_field_labels(),
    );
  }

  /**
   * Render views field.
   */
  public function render($values) {
    $entity_id = $values->{$this->field_alias};
    $entity_label = '';
    if (isset($this->view->field[$this->options['label_field']])) {
      $field_alias = $this->view->field[$this->options['label_field']]->field_alias;
      $entity_label = $values->$field_alias;
    }
    $field_name = drupal_clean_css_identifier($this->options['entity_reference_field']);

    $attributes = array(
      'entity-id' => sprintf('%s (%s)', filter_xss($entity_label), $entity_id),
      'autocomplete-id' => 'edit-' . $field_name . '-und-form-entity-id',
      'class' => 'ief-selection-link',
    );
    return l(t('Select'), '', array('attributes' => $attributes));
  }

  /**
   * Get list of fields that use Inline Entity Form widget.
   *
   * @return array
   *    Get list of fields that uses inline entity form widgets.
   */
  public function get_entity_reference_field_options() {
    $options = array();
    foreach (field_info_instances($this->table) as $fields) {
      foreach ($fields as $field_name => $field) {
        if (in_array($field['widget']['type'], array('inline_entity_form', 'inline_entity_form_single'))) {
          $options[$field_name] = $field['label'];
        }
      }
    }
    return $options;
  }

}
