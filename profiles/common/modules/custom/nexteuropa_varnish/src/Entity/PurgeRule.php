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
   * @return PurgeRuleType
   *   The type of the purge rule.
   */
  public function type() {
    $type = PurgeRuleType::NODE;

    if (is_string($this->paths) && $this->paths !== '') {
      $type = PurgeRuleType::PATHS;
    }

    return new PurgeRuleType($type);
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

  /**
   * {@inheritdoc}
   */
  public function save() {
    $content_type = $this->content_type;
    cache_clear_all('nexteuropa_varnish_get_node_purge_rules_' . $content_type, 'cache_nexteuropa_varnish');
    return parent::save();
  }

}
