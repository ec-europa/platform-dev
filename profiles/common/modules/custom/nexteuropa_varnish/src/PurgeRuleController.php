<?php
/**
 * @file
 * Contains Drupal\nexteuropa_varnish\PurgeRuleController.
 */

namespace Drupal\nexteuropa_varnish;

use \EntityAPIController;

/**
 * Class PurgeRuleController.
 */
class PurgeRuleController extends EntityAPIController {

  /**
   * Overrides EntityAPIController::delete().
   *
   * Through it, we clear the content type rules cache. Entity API requests to
   * pass by the controller for deletion actions, while it allows passing by the
   * Entity class for the saving actions.
   *
   * @param array $ids
   *   The list of ids of the entity instances to delete.
   * @param DatabaseTransaction $transaction
   *   Optionally a DatabaseTransaction object to use. Allows overrides to pass
   *   in their transaction object.
   *
   * @throws \Exception
   *   Throws an exception if the delete process failed.
   */
  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    $entities = $ids ? $this->load($ids) : FALSE;
    if (!$entities) {
      // Do nothing, in case invalid or no ids have been passed.
      return;
    }

    // We clear the content type rules cache.
    $implied_entity_types = array();
    foreach ($entities as $entity) {
      $content_type = $entity->content_type;

      if (!in_array($content_type, $implied_entity_types)) {
        cache_clear_all('nexteuropa_varnish_get_node_purge_rules_' . $content_type, 'cache_nexteuropa_varnish');

        $implied_entity_types[] = $content_type;
      }
    }

    parent::delete($ids, $transaction);
  }

}
