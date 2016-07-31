<?php

namespace Drupal\pathauto;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\pathauto.
 */
class Config extends ConfigBase {

  /**
   * Set URL Alias Pattern.
   *
   * @param string $pattern
   *    Pattern to be set, ex. content/[node:title].
   * @param string $entity
   *    Entity machine name, ex. 'node'.
   * @param string $bundle
   *    Bundle machine name, ex. 'page' (optional).
   * @param string $language
   *    Language code, ex. 'en' (optional).
   */
  public function createUrlAliasPattern($pattern, $entity, $bundle = NULL, $language = NULL) {
    $parts = array($entity);
    if ($bundle) {
      $parts[] = $bundle;
    }
    if ($language) {
      $parts[] = $language;
    }
    $variable_name = 'pathauto_' . implode('_', $parts) . '_pattern';
    variable_set($variable_name, $pattern);
  }

}
