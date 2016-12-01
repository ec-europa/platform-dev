<?php
/**
 * @file
 * Contains NextEuropaTrackedChangesInfoController.
 */

/**
 * Class NETCInfoController.
 */
class NETCInfoController extends EntityAPIController {

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
        // TODO: implement recursive code.
        $items = entity_load($entity->rel_entity_type, array($entity->rel_entity_id));
        $related_entity = reset($items);
        $wrapper = entity_metadata_wrapper($entity->rel_entity_type, $related_entity);
        $entity->rel_entity_label = $wrapper->host_entity()->label();
        $entity->rel_entity_id = $wrapper->host_entity()->id();
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
