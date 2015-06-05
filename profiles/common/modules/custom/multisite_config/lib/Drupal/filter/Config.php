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
   *
   * @return object|bool
   *    Text format object or FALSE.
   */
  public function getFormat($format_name) {
    $formats = filter_formats();
    return isset($formats[$format_name]) ? $formats[$format_name] : FALSE;
  }

  /**
   * Retrieves a list of filters for a given text format.
   *
   * @param string $format_name
   *    Text format machine name.
   *
   * @return array
   *    An array of filter objects associated to the given text format.
   */
  public function getFormatFilters($format_name) {
    return filter_list_format($format_name);
  }

}
