<?php
/**
 * @file
 * This file provides the ecas_extra_handler_field_user_is_denied class.
 */

/**
 * Provides a Views 3 field that displays the "denied" state of a user.
 *
 * It can also display the date of the denying and the denier.
 */
class ecas_extra_handler_field_user_is_denied extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function query() {
    // Boolean field, we always include it.
    $this->query->add_field(NULL, 'IF ((select count(uid) from {denied_users} denied_users WHERE denied_users.uid = users.uid) > 0, 1, 0)', 'user_denied');
    $this->field_alias = 'user_denied';

    // Date and denier fields are optional.
    if (isset($this->options['display_denier'])) {
      $this->query->add_field(NULL, 'IF ((select count(uid) from {denied_users} denied_users WHERE denied_users.uid = users.uid) > 0, (select `denied_by`     from {denied_users} denied_users WHERE denied_users.uid = users.uid), 0)', 'user_denied_by');
    }

    if (isset($this->options['display_date'])) {
      $this->query->add_field(NULL, 'IF ((select count(uid) from {denied_users} denied_users WHERE denied_users.uid = users.uid) > 0, (select `denied` from {denied_users} denied_users WHERE denied_users.uid = users.uid), 0)', 'user_denied_when');
    }
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    $value = $this->get_value($values);

    if ($value == 1) {
      // The user is denied.
      $boolean_displayed_text = t('Yes');
      $date_displayed_text = t('Yes, on %s');
      $denier_displayed_text = t('Yes, by %s');
      $date_dernier_displayed_text = t('Yes, by %s on %s');

      if ($this->options['display_denier']) {
        $denier_string = theme('username', user_load($values->user_denied_by));
      }
      if ($this->options['display_date']) {
        $date_string = format_date($values->user_denied_when);
      }

      if ($this->options['display_date'] && $this->options['display_denier']) {
        $displayed_text = sprintf($date_dernier_displayed_text, $denier_string, $date_string);
      }
      elseif ($this->options['display_denier']) {
        $displayed_text = sprintf($denier_displayed_text, $denier_string);
      }
      elseif ($this->options['display_date']) {
        $displayed_text = sprintf($date_displayed_text, $date_string);
      }
      else {
        $displayed_text = $boolean_displayed_text;
      }

      return $displayed_text;
    }
    else {
      // The user is not denied.
      return t('No');
    }
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['display_date'] = array('default' => '0');
    $options['display_denier'] = array('default' => '0');
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    $form['display_date'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display date'),
      '#default_value' => $this->options['display_date'],
    );
    $form['display_denier'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the denier'),
      '#default_value' => $this->options['display_denier'],
    );
    parent::options_form($form, $form_state);

    // @todo This method should not return a value.
    return $form;
  }

}
