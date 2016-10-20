<?php
/**
 * @file
 * Definition of Drupal\nexteuropa_varnish\PurgeRuleType.
 */

namespace Drupal\nexteuropa_varnish;

/**
 * Enum of purge rule types.
 */
class PurgeRuleType {
  const NODE = 'node';
  const PATHS = 'paths';

  /**
   * Prevents the class from instantiated, it just acts as an enum.
   */
  private function __construct() {

  }

}
