<?php

namespace Drupal\ne_dgt_rules;

use EntityFieldQuery;
use TMGMTException;
use TMGMTJob;
use TMGMTJobItem;
use EC\Poetry\Messages\Components\Status;
use EC\Poetry\Messages\Components\Identifier;

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
  public static function checkParameters(array $parameters) {
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
   * @return string|bool
   *   Returns the name of the default FTT translator or FALSE if it's not set.
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
   * Return related translations by the translated entity id.
   *
   * @param string $reference
   *   Reference.
   *
   * @return array
   *   An Array of TMGMTJob.
   */
  public static function loadTmgmtJobsByReference($reference) {
    $job_ids = db_select('tmgmt_job', 'job')
      ->fields('job', array('tjid'))
      ->condition('job.reference', $reference, 'LIKE')
      ->execute()
      ->fetchAllAssoc('tjid');

    return tmgmt_job_load_multiple(array_keys($job_ids));
  }

  /**
   * Return related translations by the translated entity id.
   *
   * @param TMGMTJob $job
   *   The TMGMT job.
   * @param \EC\Poetry\Messages\Components\Status $status
   *   The status.
   */
  public static function updateStatusTmgmtJob(TMGMTJob $job, Status $status) {
    $status_map = array(
      'SUS' => TMGMT_JOB_STATE_ACTIVE,
      'ONG' => TMGMT_JOB_STATE_ACTIVE,
      'LCK' => TMGMT_JOB_STATE_ACTIVE,
      'EXE' => TMGMT_JOB_STATE_ACTIVE,
      'REF' => TMGMT_JOB_STATE_ABORTED,
      'CNL' => TMGMT_JOB_STATE_ABORTED,
    );

    // Check if the job is finished, so do nothing.
    if (TMGMT_JOB_STATE_FINISHED == $job->getState()) {
      DgtRulesTools::addMessageTmgmtJob(
        $job,
        'Receiving a status update (@new_status) on the finished job. Message: @message',
        array(
          '@new_status' => $status_map[$status->getCode()],
          '@message' => $status->getMessage(),
        )
      );

      return;
    }

    // Change the state of the Job.
    if ($status_map[$status->getCode()] != $job->getState()) {
      DgtRulesTools::addMessageTmgmtJob(
        $job,
        'Update the status from @old_status to @new_status by DGT. Message: @message',
        array(
          '@old_status' => $job->getState(),
          '@new_status' => $status_map[$status->getCode()],
          '@message' => $status->getMessage(),
        )
      );

      $job->setState($status_map[$status->getCode()]);
    }
  }

  /**
   * Return related translations by the translated entity id.
   *
   * @param TMGMTJob $job
   *   The TMGMT job.
   * @param string $content
   *   The content of the translation.
   *
   * @return bool
   *   The
   */
  public static function updateTranslationTmgmtJob(TMGMTJob $job, $content) {
    $job_items = $job->getItems();

    foreach ($job_items as $job_item) {
      $controller = tmgmt_file_format_controller($job->getSetting('export_format'));

      if (!$controller) {
        DgtRulesTools::addMessageTmgmtJob(
          $job,
          t('Failed to find the good controller, import aborted.'),
          array(),
          'error'
        );

        return FALSE;
      }

      $content = DgtRulesTools::parseTranslationTmgmtJob($job, $job_item, $content);

      // Validate the file.
      $validated_job = $controller->validateImport($content);

      if (!$validated_job) {
        DgtRulesTools::addMessageTmgmtJob(
          $job,
          t('@language Failed to validate file, import aborted.'),
          array('@language' => $job->target_language),
          'error'
        );

        return FALSE;
      }

      if ($validated_job->tjid != $job->tjid) {
        $uri = $validated_job->uri();
        $label = $validated_job->label();
        DgtRulesTools::addMessageTmgmtJob(
          $job,
          t('Import file is from job <a href="@url">@label</a>, import aborted.'),
          array(
            '@language' => $job->target_language,
            '@url' => url($uri['path']),
            '@label' => $label,
          ),
          'error'
        );

        return FALSE;
      }

      if ($job->isAborted()) {
        DgtRulesTools::addMessageTmgmtJob(
          $job,
          t('The Job is aborted, import aborted'),
          array(),
          'error'
        );

        return FALSE;
      }

      try {
        // Validation successful, start import.
        $job->addTranslatedData($controller->import($content));

        DgtRulesTools::addMessageTmgmtJob(
          $job,
          t('Successfully received the translation file.'),
          array()
        );
      }
      catch (Exception $e) {
        DgtRulesTools::addMessageTmgmtJob(
          $job,
          t('File import failed with the following message: @message'),
          array('@message' => $e->getMessage()),
          'error'
        );
      }
    }

    return TRUE;
  }

  /**
   * Return related translations by the translated entity id.
   *
   * @param TMGMTJob $job
   *   The TMGMT Job object.
   * @param TMGMTJobItem $job_item
   *   The TMGMT Job Item object.
   * @param string $content
   *   The translation content.
   *
   * @return string
   *   Parsed XML.
   */
  public static function parseTranslationTmgmtJob(TMGMTJob $job, TMGMTJobItem $job_item, $content) {
    $translator = $job->getTranslator();

    $dom = new \DOMDocument();
    if (!multisite_drupal_toolbox_load_html($dom, base64_decode($content))) {
      return FALSE;
    }

    // Workaround for saveXML() generating two xmlns attributes.
    // See https://bugs.php.net/bug.php?id=47666.
    if ($dom->documentElement->hasAttributeNS(NULL, 'xmlns')) {
      $dom->documentElement->removeAttributeNS(NULL, 'xmlns');
    }

    $xml = simplexml_import_dom($dom);

    if (count($xml->head->meta) > 0) {
      foreach ($xml->head->meta as $meta_tag) {
        if (isset($meta_tag['name'])) {
          switch ($meta_tag['name']) {
            case 'JobID':
              $meta_tag['content'] = $job->tjid;
              break;

            case 'languageSource':
              $meta_tag['content'] = $translator->mapToRemoteLanguage($job->source_language);
              break;

            case 'languageTarget':
              $meta_tag['content'] = $translator->mapToRemoteLanguage($job->target_language);
              break;
          }
        }
      }
    }
    if (isset($xml->head->title)) {
      $xml->head->title = "Job ID " . $job->tjid;
    }
    foreach ($xml->body->div as $parent_div) {
      if ($parent_div['class'] == 'meta' && $parent_div['id'] == 'languageTarget') {
        $parent_div[0] = $job->target_language;
      }
      if ($parent_div['class'] == 'asset') {
        $parent_div['id'] = $job_item->tjiid;

        /** @var SimpleXMLElement $div */
        foreach ($parent_div->div as $div) {
          if ($div['class'] == 'atom') {
            $data = drupal_substr($div['id'], 1);
            $data = base64_decode(str_pad(strtr($data, '-_', '+/'), drupal_strlen($data) % 4, '=', STR_PAD_RIGHT));
            $data = explode(']', $data);
            $data[0] = $job_item->tjiid;
            $data = implode(']', $data);
            $div['id'] = 'b' . rtrim(strtr(base64_encode($data), '+/', '-_'), '=');
          }
        }
      }
    }

    return $xml->saveXML();
  }

  /**
   * Return related translations by the translated entity id.
   *
   * @param TMGMTJob $job
   *   The TMGMT job.
   * @param string $message
   *   The message.
   * @param array $args
   *   An associative array of replacements for the message.
   * @param string $type
   *   Type of the message.
   */
  public static function addMessageTmgmtJob(TMGMTJob $job, $message, array $args, $type = 'info') {
    $job->addMessage($message, $args, $type);

    $message = 'Job @reference-@language: ' . $message;
    $watchdog_args = array_merge(
      $args,
      array(
        '@reference' => $job->reference,
        '@language' => $job->target_language,
      )
    );
    watchdog('ne_dgt_rules', $message, $watchdog_args, WATCHDOG_INFO);
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
  public static function sendReviewRequest(TMGMTJob $job, array $parameters) {
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
   * @return array
   *   Array of TMGMT Job object.
   */
  public static function sendTranslationRequest($default_translator, array $jobs, array $parameters) {
    $translator = tmgmt_translator_load($default_translator);
    $controller = $translator->getController();

    return $controller->requestTranslations($jobs, $parameters);
  }

  /**
   * Returns all mapping entities based on a request identifier.
   *
   * @param \EC\Poetry\Messages\Components\Identifier $identifier
   *   The translation request identifier.
   *
   * @return array
   *   Array of FTT Map objects.
   */
  public static function findMappingsByIdentifier(Identifier $identifier) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'ne_tmgmt_dgt_ftt_map')
      ->propertyCondition('year', $identifier->getYear())
      ->propertyCondition('number', $identifier->getNumber())
      ->propertyCondition('part', $identifier->getPart())
      ->propertyCondition('version', $identifier->getVersion());
    $results = $query->execute();
    if (isset($results['ne_tmgmt_dgt_ftt_map'])) {
      return entity_load('ne_tmgmt_dgt_ftt_map', array_keys($results['ne_tmgmt_dgt_ftt_map']));
    }
    return array();
  }

  /**
   * Returns all mapping entities based on a request identifier.
   *
   * @param object $node
   *   The Node Object.
   *
   * @return object | NULL $maps
   *   FTT Map object.
   */
  public static function findMappingsByNode($node) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'ne_tmgmt_dgt_ftt_map')
      ->propertyCondition('entity_id', $node->nid);
    $results = $query->execute();
    if (isset($results['ne_tmgmt_dgt_ftt_map'])) {
      $entities = entity_load('ne_tmgmt_dgt_ftt_map', array_keys($results['ne_tmgmt_dgt_ftt_map']));
      return array_shift($entities);
    }
    return NULL;
  }

}
