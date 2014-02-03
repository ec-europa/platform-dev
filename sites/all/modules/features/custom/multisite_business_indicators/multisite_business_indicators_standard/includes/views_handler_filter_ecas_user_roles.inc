<?php

/**
 * @file
 * Definition of views_handler_filter_user_roles.
 */

/**
 * Filter handler for user roles.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_ecas_user_roles extends views_handler_filter_many_to_one {
  function get_value_options() {
    $this->value_options[1] = t('Anonymous User');
    $this->value_options[2] = t('Ecas User');
    $this->value_options[3] = t('Regular User');
  }

  /**
   * Override empty and not empty operator labels to be clearer for user roles.
   */
  function operators() {
    $operators = parent::operators();
    return $operators;
  }
}
