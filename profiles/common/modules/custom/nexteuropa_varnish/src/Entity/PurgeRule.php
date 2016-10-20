<?php
/**
 * @file
 * Definition of Drupal\nexteuropa_varnish\Entity\PurgeRule.
 */

namespace Drupal\nexteuropa_varnish\Entity;
use Drupal\nexteuropa_varnish\PurgeRuleType;
use \Entity;

/**
 * Purge rule entity.
 */
class PurgeRule extends Entity {

  /**
   * Paths of the purge rule.
   *
   * Empty when the purge rule needs to target the specific paths of the node
   * that triggered the rule.
   *
   * @var string
   */
  public $paths;

  /**
   * Get the type of the purge rule.
   *
   * @return string
   *   The type of the purge rule.
   */
  public function type() {
    if (is_string($this->paths) && $this->paths !== '') {
      return PurgeRuleType::PATHS;
    }
    else {
      return PurgeRuleType::NODE;
    }
  }

  /**
   * Get the paths associated with the purge rule.
   *
   * @return array
   *   The paths, as an array.
   */
  public function paths() {
    return preg_split("/[\r\n]+/", $this->paths);
  }

}
