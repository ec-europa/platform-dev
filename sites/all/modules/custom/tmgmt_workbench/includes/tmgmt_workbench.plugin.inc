<?php

/**
 * @file
 * Provides the Workbench Moderation source controller.
 */

/**
 * Class TMGMTWorkbenchSourcePluginController.
 */
class TMGMTWorkbenchSourcePluginController extends TMGMTEntitySourcePluginController {

  /**
   * {@inheritdoc}
   */
  public function getLabel(TMGMTJobItem $job_item) {
    $node = node_load($job_item->item_id);
    $current_revision = $this->getModerationRevision($node);
    return $current_revision->title;
  }

  /**
   * {@inheritdoc}
   */
  public function getData(TMGMTJobItem $job_item) {

    $node = node_load($job_item->item_id);
    if (!$node) {
      throw new TMGMTException(t('Unable to load entity %type with id %id', array('%type' => $job_item->item_type, $job_item->item_id)));
    }
    $current_revision = $this->getModerationRevision($node);
    return tmgmt_field_get_source_data('node', $current_revision, $job_item->getJob()->source_language, TRUE);
  }


  /**
   * {@inheritdoc}
   */
  public function saveTranslation(TMGMTJobItem $job_item) {
    // If we need to save translations on a particular revision then node_save()
    // allows that.
    parent::saveTranslation($job_item);
  }

  /**
   * Get moderation state.
   *
   * @param object $node
   *    Node object.
   * @param string $type
   *    Moderation type.
   *
   * @return string|null
   *    Moderation state or null.
   */
  private function getModerationState($node, $type = 'current') {
    if (is_object($node) && property_exists($node, 'workbench_moderation') && isset($node->workbench_moderation[$type])) {
      $state = $node->workbench_moderation[$type];
      return $state->state;
    }
    return NULL;
  }

  /**
   * Get moderation revision.
   *
   * @param object $node
   *    Node object.
   * @param string $type
   *    Moderation type.
   *
   * @return object|null
   *    Node revision or null.
   */
  private function getModerationRevision($node, $type = 'current') {
    if (is_object($node) && property_exists($node, 'workbench_moderation') && isset($node->workbench_moderation[$type])) {
      $vid = $node->workbench_moderation[$type]->vid;
      return node_load($node->nid, $vid);
    }
    return NULL;
  }

}
