<?php

/**
 * @file
 * Contains \Drupal\context\Config.
 */

namespace Drupal\context;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\context
 */
class Config extends ConfigBase {

  /**
   * Load a context object given its machine name.
   *
   * @param string $name
   *    Context machine name.
   *
   * @return object|bool
   *    Context object if loaded, FALSE otherwise.
   */
  public function loadContext($name) {
    return context_load($name, TRUE);
  }

  /**
   * Add a block to a context.
   *
   * @param string $name
   *    Context machine name.
   * @param string $module
   *    Machine name of the module the block belongs to.
   * @param string $delta
   *    Block delta.
   * @param string $region
   *    Theme region machine name.
   * @param int $weight
   *    Block weight in the specified region.
   *
   * @return bool
   *    TRUE if context is saved correctly, FALSE otherwise.
   */
  public function addBlock($name, $module, $delta, $region, $weight = 0) {

    $context = $this->loadContext($name);
    $context->reactions['block']['blocks'][$module . '-' . $delta] = array(
      'module' => $module,
      'delta' => $delta,
      'region' => $region,
      'weight' => $weight,
    );
    return $this->saveContext($context);
  }

  /**
   * Remove a block from a context.
   *
   * @param string $name
   *    Context machine name.
   * @param string $module
   *    Machine name of the module the block belongs to.
   * @param string $delta
   *    Block delta.
   *
   * @return bool
   *    TRUE if context is saved correctly, FALSE otherwise.
   */
  public function removeBlock($name, $module, $delta) {

    $context = $this->loadContext($name);
    unset($context->reactions['block']['blocks'][$module . '-' . $delta]);
    return $this->saveContext($context);
  }

  /**
   * Save a context object.
   *
   * @param object $context
   *    A valid context object, as returned from context_load().
   *
   * @return bool
   *    TRUE if context is saved correctly, FALSE otherwise.
   */
  public function saveContext($context) {
    return context_save($context);
  }

}
