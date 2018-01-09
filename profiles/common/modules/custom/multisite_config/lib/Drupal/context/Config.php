<?php

/**
 * @file
 * Contains \\Drupal\\context\\Config.
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
   *   Context machine name.
   *
   * @return object|bool
   *   Context object if loaded, FALSE otherwise.
   */
  public function loadContext($name) {
    return context_load($name, TRUE);
  }

  /**
   * Add a block to a context.
   *
   * @param string $name
   *   Context machine name.
   * @param string $module
   *   Machine name of the module the block belongs to.
   * @param string $delta
   *   Block delta.
   * @param string $region
   *   Theme region machine name.
   * @param int $weight
   *   Block weight in the specified region.
   *
   * @return bool
   *   TRUE if context is saved correctly, FALSE otherwise.
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
   *   Context machine name.
   * @param string $module
   *   Machine name of the module the block belongs to.
   * @param string $delta
   *   Block delta.
   *
   * @return bool
   *   TRUE if context is saved correctly, FALSE otherwise.
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
   *   A valid context object, as returned from context_load().
   *
   * @return bool
   *   TRUE if context is saved correctly, FALSE otherwise.
   */
  public function saveContext($context) {
    return context_save($context);
  }


  /**
   * Add a content type as condition to trigger a context.
   *
   * @param string $context_name
   *   Machine name of the context to modify.
   * @param string $content_type
   *   Machine name of the content type to use as condition for the the context.
   */
  public function addContentTypeContext($context_name, $content_type) {
    $list_content_types = array_keys(node_type_get_types());
    // Load context.
    $context = module_invoke('context', 'load', $context_name);
    // Add modification to the context.
    if ($context && in_array($content_type, $list_content_types)) {
      $context->conditions['node']['values'][$content_type] = $content_type;
      // Update the context.
      module_invoke('context', 'save', $context);
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Remove a content type used to trigger a context.
   *
   * @param string $context_name
   *   Machine name of the context to modify.
   * @param string $content_type
   *   Machine name of the content type to use as condition for the the context.
   */
  public function removeContentTypeContext($context_name, $content_type) {
    $list_content_types = array_keys(node_type_get_types());
    // Load context.
    $context = module_invoke('context', 'load', $context_name);
    if ($context && in_array($content_type, $list_content_types)) {
      // Remove element from the context.
      unset($context->conditions['node']['values'][$content_type]);
      // Update the context.
      module_invoke('context', 'save', $context);
      return TRUE;
    }
    return FALSE;
  }

}
