<?php

/**
 * @file
 * Contains Drupal\nexteuropa_trackedchanges\NETCInfoController.
 */

namespace Drupal\nexteuropa_trackedchanges;

/**
 * Class NETCInfoController.
 */
class NETCInfoController extends \EntityAPIController {

  /**
   * Override the save method.
   *
   * It sets the Scan date and the label (if not set) before saving.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (empty($entity->rel_entity_type)) {
      throw new Exception('NextEuropaTrackedChangesInfo entity_type missing');
    }

    if (empty($entity->rel_entity_id)) {
      throw new EntityMalformedException('NextEuropaTrackedChangesInfo entity_id missing');
    }

    // Forced data setting.
    $entity->scanned = REQUEST_TIME;

    switch ($entity->rel_entity_type) {
      case 'field_collection_item':
      case 'paragraphs_item':
        // We need the entity label and id that host these kinds of field.
        // Retrieve the right NETCInfo in order to update it.
        $tested_entity_id = $entity->rel_entity_id;
        $tested_entity_type = $entity->rel_entity_type;
        $in_array = array(
          'field_collection_item',
          'paragraphs_item',
        );
        // Recursive loop because a field collection/paragraph can be hosted in
        // another field collection/paragraph.
        while (in_array($tested_entity_type, $in_array)) {
          $items = entity_load($tested_entity_type, array($tested_entity_id));
          $related_entity = reset($items);
          $wrapper = entity_metadata_wrapper($tested_entity_type, $related_entity);

          $parent_entity_type = $wrapper->hostEntityType();
          $parent_wrapper = entity_metadata_wrapper($parent_entity_type, $wrapper->host_entity());

          $entity->rel_entity_label = $parent_wrapper->label();
          $entity->rel_entity_id = $parent_wrapper->id();
          $entity->rel_entity_type = $parent_entity_type;

          $tested_entity_id = $parent_wrapper->id();
          $tested_entity_type = $parent_entity_type;
        }

        break;

      default:
        if (empty($entity->rel_entity_label)) {
          $related_entities = entity_load($entity->rel_entity_type, array($entity->rel_entity_id));
          $related_entity = reset($related_entities);
          $wrapper = entity_metadata_wrapper($entity->rel_entity_type, $related_entity);
          $entity->rel_entity_label = $wrapper->label();
        }
        break;

    }

    return parent::save($entity, $transaction);
  }

}
