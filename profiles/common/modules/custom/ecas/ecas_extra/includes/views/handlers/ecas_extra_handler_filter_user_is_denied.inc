<?php

/**
 * @file
 * This file provides the ecas_extra_handler_filter_user_is_denied class.
 */

/**
 * This class provides a Views 3 filter on the "denied" state of a user.
 */
class ecas_extra_handler_filter_user_is_denied extends views_handler_filter_boolean_operator {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->query->ensure_table('users');

    // Should we filter on the denied users or not? To answer this question,
    // we have to take into account that this parameter may be exposed to the
    // user.
    if ($this->options['exposed']) {
      $value_name = $this->options['expose']['identifier'];
      if (isset($this->view->exposed_input[$value_name])) {
        $value = $this->view->exposed_input[$value_name];
      }
      else {
        $value = $this->view->exposed_data[$value_name];
      }
    }
    else {
      $value = $this->options['value'];
    }

    $operator = ($value == 1) ? 'NOT IN' : 'IN';
    $this->query->add_where_expression(0, sprintf('users.uid %s (SELECT uid FROM {denied_users})', $operator));
  }

  /**
   * {@inheritdoc}
   */
  public function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'radios',
      '#title' => 'Display only users who are',
      '#options' => array(
        t('denied'),
        t('not denied'),
      ),
      '#default_value' => $this->options['value'],
    );
    return $form;
  }

}
