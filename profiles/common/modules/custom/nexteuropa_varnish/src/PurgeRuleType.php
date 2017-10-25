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
   * The actual type name as a string.
   *
   * @var string
   */
  private $type;

  /**
   * Prevents the class from instantiated, it just acts as an enum.
   */
  public function __construct($type) {
    $possible_types = self::getConstList();

    if (!in_array($type, $possible_types)) {
      throw new \InvalidArgumentException(
        sprintf('Invalid value "%s" for $type', $type)
      );
    }

    $this->type = $type;
  }

  /**
   * Get the possible purge rule types.
   *
   * @return array
   *   Purge rule types, as strings.
   */
  public static function getConstList() {
    return array(
      self::NODE,
      self::PATHS,
    );
  }

  /**
   * Get the type as a string.
   */
  public function __toString() {
    return $this->type;
  }

}
