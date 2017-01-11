<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\ContextUtil.
 */

namespace Drupal\nexteuropa\Context;

/**
 * Util trait proposing.
 *
 * @package Drupal\nexteuropa\Context
 */
trait ContextUtil {

  /**
   * Returns whether or not Pathauto is enabled for the given entity.
   *
   * @param string $entity_type
   *   The entity type.
   * @param mixed $entity
   *   The entity.
   * @param string $langcode
   *   The language code for the entity.
   *
   * @return bool
   *   TRUE if Pathauto is enabled, FALSE if not.
   *
   * @see pathauto_field_attach_form()
   * @see \NextEuropaMultilingualSubContext::createMultilingualContent()
   * @see \Drupal\nexteuropa\Context\DrupalContext::theFollowingContents()
   */
  public function isPathautoEnabled($entity_type, $entity, $langcode) {
    list($id, , $bundle) = entity_extract_ids($entity_type, $entity);
    if (!isset($entity->path['pathauto'])) {
      if (!empty($id)) {
        module_load_include('inc', 'pathauto');
        $uri = entity_uri($entity_type, $entity);
        $path = drupal_get_path_alias($uri['path'], $langcode);
        $pathauto_alias = pathauto_create_alias($entity_type, 'return', $uri['path'], array($entity_type => $entity), $bundle, $langcode);
        return $path != $uri['path'] && $path == $pathauto_alias;
      }
      else {
        return TRUE;
      }
    }
    return $entity->path['pathauto'];
  }

}
