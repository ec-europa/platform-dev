<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\BeanContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Drupal\nexteuropa\Component\Utility\Transliterate;

/**
 * Context for configuring the Bean.
 */
class BeanContext implements Context {

  /**
   * The transliterate utility object.
   *
   * @var \Drupal\nexteuropa\Component\Utility\Transliterate
   */
  protected $transliterate;

  /**
   * The random utility object.
   *
   * @var \Rych\Random\Random
   */
  protected $random;

  /**
   * The list of block types created before or during a scenario starts.
   *
   * @var array
   */
  protected $blockType = array();

  /**
   * BeanContext constructor.
   */
  public function __construct() {
    $this->transliterate = new Transliterate();
    $this->random = new \Rych\Random\Random();
  }

  /**
   * Create a block type.
   *
   * @param string $type
   *   Type of the block.
   *
   * @When /^I create the new block type "([^"]*)"$/
   */
  public function iCreateTheNewBlockType($type) {
    $plugin_info = _bean_admin_default_plugin();
    $plugin_info['name'] = '';

    $bean_type = new \BeanCustom($plugin_info);
    $bean_type->type = substr(str_pad(substr($this->transliterate->getMachineName($type), 0, 32), 32, '_'), 0, 23) . '_' . $this->transliterate->getMachineName($this->random->getRandomString(8));
    $bean_type->setLabel($type);
    $bean_type->setDescription('Behat');
    $bean_type->save(TRUE);
    $this->blockType[] = $bean_type;
  }

  /**
   * Revert to previous settings after scenario execution.
   *
   * @AfterScenario
   */
  public function removeBlockTypes() {
    // Remove the beans.
    foreach ($this->blockType as $block_type) {
      $block_type->revert();
    }
  }

}
