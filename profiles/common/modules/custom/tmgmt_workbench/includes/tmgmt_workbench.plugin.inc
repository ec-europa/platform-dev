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
    // Deleting a node does not delete its translation jobs.
    // Here we make sure the job has always a label.
    $node = node_load($job_item->item_id);
    if ($node) {
      $current_revision = $this->getModerationRevision($node);
      return $current_revision->title;
    }
    return t("Node !nid (deleted)", array('!nid' => $job_item->item_id));
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
    $job = tmgmt_job_load($job_item->tjid);
    $node = node_load($job_item->item_id);

    // Get current node revision.
    $current_revision = $this->getModerationRevision($node);
    tmgmt_field_populate_entity($job_item->item_type, $current_revision, $job->target_language, $job_item->getData());

    // Change the active language of the entity to the target language.
    $handler = entity_translation_get_handler($job_item->item_type, $current_revision);
    $handler->setActiveLanguage($job_item->getJob()->target_language);

    // Save current node revision.
    node_save($current_revision);

    // Save translation information for current revision.
    $translation = array(
      // @todo Improve hardcoded values.
      'translate' => 0,
      'status' => TRUE,
      'language' => $job_item->getJob()->target_language,
      'source' => $job_item->getJob()->source_language,
    );
    $handler->setTranslation($translation);
    $handler->saveTranslations();

    // Accept the translation job.
    $job_item->accepted();
  }

  /**
   * Get moderation revision.
   *
   * @param object $node
   *    Node object.
   * @param string $type
   *    Moderation type.
   *
   * @return object|FALSE
   *    Current node object or FALSE.
   */
  private function getModerationRevision($node, $type = 'current') {
    if (is_object($node) && property_exists($node, 'workbench_moderation') && isset($node->workbench_moderation[$type])) {
      $vid = $node->workbench_moderation[$type]->vid;
      return node_load($node->nid, $vid);
    }
    return FALSE;
  }

}
