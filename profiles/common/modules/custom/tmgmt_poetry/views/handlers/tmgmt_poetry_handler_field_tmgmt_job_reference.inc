<?php

/**
 * @file
 * Contains tmgmt_poetry_handler_field_tmgmt_job_reference class.
 */

/**
 * Class tmgmt_poetry_handler_field_tmgmt_job_reference.
 */
class tmgmt_poetry_handler_field_tmgmt_job_reference extends views_handler_field {

  /**
   * Reference delimiter.
   */
  const DELIMITER = '_POETRY_';

  /**
   * {@inheritdoc}
   */
  public function sanitize_value($value, $type = NULL) {
    if (strstr($value, self::DELIMITER) !== FALSE) {
      list(, $value) = explode(self::DELIMITER, $value);
    }
    $value = check_plain($value);
    return $value;
  }

}
