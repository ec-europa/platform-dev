<?php

/**
 * @file
 * Helper class with helper static methods for the NE DGT Rules module.
 */

namespace Drupal\ne_dgt_rules;

use EntityFieldQuery;
use TMGMTException;
use TMGMTJob;


/**
 * Class DgtRulesTools.
 *
 * Helper class with helper static methods.
 */
class DgtRulesTools {
  /**
   * Checks if all of the organisation parameters are set.
   *
   * @param array $parameters
   *   An array with additional parameters.
   *
   * @return bool
   *   FALSE whenever one of the parameters is not set otherwise TRUE.
   */
  public static function checkParameters($parameters) {
    foreach ($parameters as $parameters_group) {
      foreach ($parameters_group as $parameter) {
        if (empty($parameter)) {

          return FALSE;
        }
      }

    }

    return TRUE;
  }

  /**
   * Provides default translator for the FTT workflow.
   *
   * @return string/bool
   *  Returns the name of the default FTT translator or FALSE if it's not set.
   */
  public static function getDefaultFttTranslator() {
    $default_translator = variable_get('ne_dgt_rules_translator', FALSE);
    // Checking if the default translator is set.
    if (!$default_translator) {
      watchdog(
        'ne_dgt_rules',
        'Default translator for the Fast Track Translations workflow is not set.',
        array(),
        WATCHDOG_ERROR
      );
      drupal_set_message(
        t('Please set up the default translator for the FTT workflow in order to send
        the review request to DGT Services.'),
        'error'
      );
    }

    return $default_translator;
  }

  /**
   * Provides IDs of TMGMT Job Items which are under translation processes.
   *
   * @param string $entity_id
   *   Entity ID (for some edge cases the string type can appear).
   *
   * @return array|bool
   *   An array with IDs or FALSE if no items where found.
   */
  public static function getActiveTmgmtJobItemsIds($entity_id) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'tmgmt_job_item')
      ->propertyCondition('item_id', $entity_id)
      ->propertyCondition('state', array(TMGMT_JOB_ITEM_STATE_ACTIVE, TMGMT_JOB_ITEM_STATE_REVIEW));

    $results = $query->execute();

    if (isset($results['tmgmt_job_item'])) {
      // Informing user that the review request can not be send.
      $job_items = implode(" ,", array_keys($results['tmgmt_job_item']));

      $error_message = t("Content type with ID: '@entity_id' is currently
      included in one of the translation processes
      (TMGMT Job Item IDs: '@job_items'). You can not request the review for
      the content which is currently under translation process.
      Please finish ongoing processes and try again.",
        array('@entity_id' => $entity_id, '@job_items' => $job_items)
      );

      drupal_set_message($error_message, 'error');

      // Logging an error to the watchdog.
      watchdog('ne_tmgmt_dgt_ftt_translator',
        "Content type with ID: $entity_id is currently
      included in one of the translation processes
      (TMGMT Job Item IDs: $job_items). You can not request the review for
      the content which is currently under translation process.
      Please finish ongoing processes and try again.",
        array(),
        WATCHDOG_ERROR
      );
      return array_keys($results['tmgmt_job_item']);
    }

    return FALSE;
  }

  /**
   * Creates TMGMT Job and TMGMT Job Item for further processing.
   *
   * @param string $default_translator
   *   The default translator fot the FTT workflow.
   * @param object $node
   *   The node that needs to be reviewed by the DGT Reviewer.
   * @param string $target_language
   *   The target language.
   *
   * @return TMGMTJob
   *   Returns created TMGMT Job.
   */
  public static function createTmgmtJobAndItemForNode($default_translator, $node, $target_language = '') {
    // Getting the default translator object.
    $translator = tmgmt_translator_load($default_translator);

    // Checking if the default translator is configured and available and if so
    // creating related job item as placeholder for further workflow steps.
    if ($translator && $translator->isAvailable()) {
      // Creating TMGMT Main job.
      if ('' === $target_language) {
        $target_language = $node->language;
      }

      // Creating TMGMT Main job.
      $tmgmt_job = tmgmt_job_create($node->language, $target_language);

      // Assiging the default translator to the job.
      $tmgmt_job->translator = $default_translator;

      // Adding the TMGMT Job Item to the created TMGMT Job.
      try {
        $tmgmt_job->addItem('workbench_moderation', $node->entity_type, $node->nid);
      }
      catch (TMGMTException $e) {
        watchdog_exception('ne_dgt_rules', $e);
        drupal_set_message(t('Unable to add job item of type %type with id %id. Make sure the source content is not empty.',
          array('%type' => $node->entity_type, '%id' => $node->nid)), 'error');
      }

      return $tmgmt_job;
    }

    // Printing an error message.
    $error_message = t("The default TMGMT translator: '[@translator]' is not
    available or is not configured correctly.",
      array('@translator' => $default_translator)
    );
    drupal_set_message($error_message, 'error');

    // Logging an error to the watchdog.
    watchdog('ne_tmgmt_dgt_ftt_translator',
      "The default TMGMT translator: '$default_translator' is not
    available or is not configured correctly.",
      array(),
      WATCHDOG_ERROR
    );

    return FALSE;
  }

  /**
   * Sends the review request to DGT Services for a given node.
   *
   * @param TMGMTJob $job
   *   TMGMT Job object.
   * @param array $parameters
   *   An array with additional parameters.
   *
   * @return array
   *   An array with data which are going to be exposed for the 'Rules'.
   */
  public static function sendReviewRequest(TMGMTJob $job, $parameters) {
    $translator = $job->getTranslator();
    $controller = $translator->getController();

    return $controller->requestReview(array($job), $parameters);
  }

  /**
   * Sends the translation request to DGT Services for a given node.
   *
   * @param string $default_translator
   *   The default translator fot the FTT workflow.
   * @param array $jobs
   *   Array of TMGMT Job object.
   * @param array $parameters
   *   An array with additional parameters.
   *
   * @return array $jobs
   *   Array of TMGMT Job object.
   */
  public static function sendTranslationRequest($default_translator, $jobs, $parameters) {
    $translator = tmgmt_translator_load($default_translator);
    $controller = $translator->getController();

    return $controller->requestTranslations($jobs, $parameters);
  }

}
