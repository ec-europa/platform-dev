<?php

/**
 * @file
 * Contains \\Drupal\\filter\\Config.
 */

namespace Drupal\filter;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\filter.
 */
class Config extends ConfigBase {

  /**
   * Get a text format object given its machine name.
   *
   * @param string $format_name
   *    Text format machine name.
   * @param bool $reset
   *    TRUE to reset filter formats cache.
   *
   * @return object|bool
   *    Text format object or FALSE.
   */
  public function getFormat($format_name, $reset = FALSE) {
    if ($reset) {
      filter_formats_reset();
    }
    $formats = filter_formats();
    return isset($formats[$format_name]) ? (object) $formats[$format_name] : FALSE;
  }

  /**
   * Get a text format object given its machine name.
   *
   * It contains filters set for this format
   *
   * @param string $format_name
   *    Text format machine name.
   * @param bool $reset
   *    TRUE to reset filter formats cache.
   *
   * @return object|bool
   *    Text format object (filters config. included and filter format saving compatible) or FALSE.
   */
  public function getFullFormat($format_name, $reset = FALSE)
  {
    $format = $this->getFormat($format_name, $reset);
    if ($format) {
      $format->filters = array();
      $format_filters = $this->getFormatFilters($format_name, $reset);

      if ($format_filters) {
        foreach ($format_filters as $name => $filter) {
          $format->filters[$name] = (array)$filter;
        }
      }
      return $format;
    }
    return FALSE;
  }

  /**
   * Retrieves a list of filters for a given text format.
   *
   * @param string $format_name
   *    Text format machine name.
   * @param bool $reset
   *    TRUE to reset filter formats cache.
   *
   * @return array
   *    An array of filter objects associated to the given text format.
   */
  public function getFormatFilters($format_name, $reset = FALSE) {
    if ($reset) {
      filter_formats_reset();
    }
    return filter_list_format($format_name);
  }

  /**
   * Returns a list of all filters provided by modules.
   *
   * @return array
   *   An array of filter formats.
   */
  public function getFilters() {
    drupal_static_reset('filter_get_filters');
    return filter_get_filters();
  }

  /**
   * Enable a filter on a text format.
   *
   * @param string $format_name
   *    Text format machine name.
   * @param string $filter_name
   *    Machine name of text filter, as defined in hook_filter_info().
   *
   * @return bool|int
   *    SAVED_UPDATED if saved, FALSE otherwise.
   */
  public function enableTextFilter($format_name, $filter_name) {

    $format = $this->getFormat($format_name);
    if ($format) {

      // Populate text filter object as expected by filter_format_save().
      $format->filters = $this->getFormatFilters($format_name);

      // Enable filter and save text format.
      if (isset($format->filters[$filter_name])) {
        $format->filters[$filter_name]->status = 1;
        return $this->saveTextFormat($format);
      }

      $filters = $this->getFilters();
      if (isset($filters[$filter_name])) {
        // Enable filter and save text format.
        $format->filters[$filter_name] = $filters[$filter_name];
        $format->filters[$filter_name]['status'] = TRUE;
        return $this->saveTextFormat($format);
      }
    }
    return FALSE;
  }

  /**
   * Disable a filter on a text format.
   *
   * @param string $format_name
   *    Text format machine name.
   * @param string $filter_name
   *    Machine name of text filter, as defined in hook_filter_info().
   *
   * @return bool|int
   *    SAVED_UPDATED if saved, FALSE otherwise.
   */
  public function disableTextFilter($format_name, $filter_name) {

    $format = $this->getFormat($format_name);
    if ($format) {

      // Populate text filter object as expected by filter_format_save().
      $format->filters = $this->getFormatFilters($format_name);

      // Disable filter and save text format.
      if (isset($format->filters[$filter_name])) {
        $format->filters[$filter_name]->status = 0;
        return $this->saveTextFormat($format);
      }

      $filters = $this->getFilters();
      if (isset($filters[$filter_name])) {
        // Enable filter and save text format.
        $format->filters[$filter_name] = $filters[$filter_name];
        $format->filters[$filter_name]['status'] = FALSE;
        return $this->saveTextFormat($format);
      }
    }
    return FALSE;
  }

  /**
   * Enable the specified filter on a text format.
   *
   * @param string $format_name
   *    Text format machine name.
   * @param string $filter_name
   *    Machine name of text filter, as defined in hook_filter_info().
   * @param int $weight
   *    Weight that specified text filter will have in the text format.
   *
   * @return bool|int
   *    SAVED_UPDATED if saved, FALSE otherwise.
   */
  public function setTextFilterWeight($format_name, $filter_name, $weight) {

    $format = $this->getFormat($format_name);
    if ($format) {

      // Populate text filter object as expected by filter_format_save().
      $format->filters = $this->getFormatFilters($format_name);

      // Set filter weight and save text format.
      if (isset($format->filters[$filter_name])) {
        $format->filters[$filter_name]->weight = $weight;
        return $this->saveTextFormat($format);
      }

      $filters = $this->getFilters();
      if (isset($filters[$filter_name])) {
        // Enable filter and save text format.
        $format->filters[$filter_name] = $filters[$filter_name];
        $format->filters[$filter_name]['weight'] = $weight;
        return $this->saveTextFormat($format);
      }
    }
    return FALSE;
  }

  /**
   * Normalize and save format objects.
   *
   * @param object $format
   *    Text format object to be sanitized and saved.
   *
   * @return bool|int
   *    SAVED_UPDATED if saved, FALSE otherwise.
   */
  private function saveTextFormat($format) {
    foreach ($format->filters as $key => $value) {
      $format->filters[$key] = (array) $value;
    }

    return filter_format_save($format);
  }

  /**
   * Retrieves a list of roles for a given text format.
   *
   * @param string $format_name
   *    Text format machine name.
   *
   * @return array
   *    An array of role names, keyed by role ID.
   */
  public function getFormatRoles($format_name) {
    $format = $this->getFormat($format_name);
    return filter_get_roles_by_format($format);
  }

  /**
   * Set roles for the specified text format.
   *
   * @param string $format_name
   *    Text format machine name.
   * @param array $roles
   *    Roles array keyed by the role ID.
   *
   * @return bool
   *    TRUE / FALSE when filter name is invalid.
   */
  public function setFormatRoles($format_name, $roles) {
    $format = $this->getFormat($format_name);
    // Save user permissions.
    if ($permission = filter_permission_name($format)) {
      foreach ($roles as $rid => $enabled) {
        user_role_change_permissions($rid, array($permission => $enabled));
      }

      return TRUE;
    }

    return FALSE;
  }

}
