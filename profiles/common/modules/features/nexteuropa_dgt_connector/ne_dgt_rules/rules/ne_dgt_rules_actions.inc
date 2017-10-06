<?php
/**
 * @file
 * Next Europa DGT Rules integration - Custom actions.
 */

/**
 * Implements hook_rules_action_info().
 */
function ne_dgt_rules_rules_action_info() {
  $items = array();

  $items['ne_dgt_rules_ftt_node_send_review_request'] = array(
    'label' => t('FTT | Node | Send the review request'),
    'group' => t('Next Europa DGT Rules'),
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Content'),
        'description' => t('The content that requires review done by the DGT reviewer.'),
      ),
    ),
    'provides' => array(
      'tmgmt_job' => array(
        'type' => 'tmgmt_job',
        'label' => t('Translation Job'),
        'description' => t('The translation job for which the review request should be sent.'),
      ),
      'dgt_service_response' => array(
        'type' => 'dgt_service_response',
        'label' => t('DGT Service response'),
        'description' => t('Response from the DGT Translation Service.'),
      ),
    ),
  );

  $items['ne_dgt_rules_ftt_node_send_translation_request'] = array(
    'label' => t('FTT | Node | Send the translation request'),
    'group' => t('Next Europa DGT Rules'),
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Content'),
        'description' => t('The content that requires to be translated by the DGT reviewer.'),
      ),
    ),
    'provides' => array(
      'tmgmt_job' => array(
        'type' => 'tmgmt_job',
        'label' => t('Translation Job'),
        'description' => t('The translation job for which the translation request should be sent.'),
      ),
      'dgt_service_response' => array(
        'type' => 'dgt_service_response',
        'label' => t('DGT Service response'),
        'description' => t('Response from the DGT Translation Service.'),
      ),
    ),
  );

  return $items;
}

/**
 * Action: Send the review request for a given node.
 *
 * @param object $node
 *   The node that needs to be reviewed by the DGT Reviewer.
 *
 * @return array
 *   An Array with the job and the response, this element can be NULL.
 */
function ne_dgt_rules_ftt_node_send_review_request($node) {
  $return = array(
    'tmgmt_job' => NULL,
    'dgt_service_response' => array(),
  );

  if ($default_translator = get_default_ftt_workflow_translator()) {
    // The review request can be only sent for the english version of the node.
    if (isset($node->language) && $node->language === 'en') {
      // Checking if review request conditions are met.
      if (!get_active_tmgmt_job_items_ids($node->nid)
        && $job = create_tmgmt_job_and_item_for_node($default_translator, $node)) {
        // Sending the review request to DGT Services.
        $return = send_review_request($job);
      }
    }
  }

  return $return;
}

/**
 * Action: Send the review request for a given node.
 *
 * @param object $node
 *   The node that needs to be reviewed by the DGT Reviewer.
 *
 * @return array
 *   An Array with the job and the response, this element can be NULL.
 */
function ne_dgt_rules_ftt_node_send_translation_request($node) {
  if ($default_translator = get_default_ftt_workflow_translator()) {
    // The review request can be only sent for the english version of the node.
    if (isset($node->language) && $node->language === 'en') {
      // Checking if review request conditions are met.
      if (!get_active_tmgmt_job_items_ids($node->nid)
        && $job = create_tmgmt_job_and_item_for_node($default_translator, $node)) {
        // Sending the review request to DGT Services.
        $dgt_service_response = send_translation_request($job);

        return array(
          'tmgmt_job' => $job,
          'dgt_service_response' => $dgt_service_response,
        );
      }
    }
  }

  return array(
    'tmgmt_job' => NULL,
    'dgt_service_response' => array(),
  );
}

/**
 * Sends the review request to DGT Services for a given node.
 *
 * @param \TMGMTJob $job
 *   TMGMT Job object.
 */
function send_review_request(TMGMTJob $job) {
  $translator = $job->getTranslator();
  $controller = $translator->getController();

  return $controller->requestReview($job);
}

/**
 * Sends the review request to DGT Services for a given node.
 *
 * @param \TMGMTJob $job
 *   TMGMT Job object.
 */
function send_translation_request(TMGMTJob $job) {
  $translator = $job->getTranslator();
  $controller = $translator->getController();

  $service_response = $controller->requestTranslation($job);

  return $service_response;
}

/**
 * Creates TMGMT Job and TMGMT Job Item for further processing.
 *
 * @param string $default_translator
 *   The default translator fot the FTT workflow.
 * @param object $node
 *   The node that needs to be reviewed by the DGT Reviewer.
 *
 * @return \TMGMTJob
 *   Returns created TMGMT Job.
 */
function create_tmgmt_job_and_item_for_node($default_translator, $node) {
  // Creating TMGMT Main job.
  $tmgmt_job = tmgmt_job_create($node->language, '');
  // Assiging the default translator to the job.
  $tmgmt_job->translator = $default_translator;
  // Getting the default translator object.
  $translator = $tmgmt_job->getTranslator();

  // Checking if the default translator is configured and available and if so
  // creating related job item as placeholder for further workflow steps.
  if ($translator && $translator->isAvailable()) {
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
 * Provides default translator for the FTT workflow.
 *
 * @return string/bool
 *  Returns the name of the default FTT workflow translator or FALSE if not set.
 */
function get_default_ftt_workflow_translator() {
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
function get_active_tmgmt_job_items_ids($entity_id) {
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