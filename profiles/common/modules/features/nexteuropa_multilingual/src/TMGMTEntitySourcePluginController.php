<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_multilingual\TMGMTEntitySourcePluginController.
 */

namespace Drupal\nexteuropa_multilingual;

/**
 * Class TMGMTEntitySourcePluginController.
 *
 * @package Drupal\nexteuropa_multilingual
 */
class TMGMTEntitySourcePluginController extends \TMGMTEntitySourcePluginController {

  /**
   * {@inheritdoc}
   */
  public function saveTranslation(\TMGMTJobItem $job_item) {
    $entity = entity_load_single($job_item->item_type, $job_item->item_id);
    $job = tmgmt_job_load($job_item->tjid);

    // Make sure a path alias is created when importing a translation.
    // @link https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6826
    if ($job_item->item_type == 'node') {
      unset($entity->path);
    }

    tmgmt_field_populate_entity($job_item->item_type, $entity, $job->target_language, $job_item->getData());

    // Change the active language of the entity to the target language.
    $handler = entity_translation_get_handler($job_item->item_type, $entity);
    $handler->setFormLanguage($job_item->getJob()->target_language);

    entity_save($job_item->item_type, $entity);

    $translation = array(
      // @todo Improve hardcoded values.
      'translate' => 0,
      'status' => TRUE,
      'language' => $job_item->getJob()->target_language,
      'source' => $job_item->getJob()->source_language,
    );
    $handler->setTranslation($translation);
    $handler->saveTranslations();
    $job_item->accepted();
  }

}
