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

  $items['ne_dgt_rules_send_the_review_request'] = array(
    'label' => t('Send the review request'),
    'group' => t('Next Europa DGT Rules'),
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Content'),
        'description' => t('The content that requires review done by the DGT reviewer.'),
      ),
      'tmgmt_job' => array(
        'type' => 'tmgmt_job',
        'label' => t('Translation Job'),
        'description' => t('The translation job for which the review request should be sent.'),
      ),
    ),
    'provides' => array(
      'dgt_service_response' => array(
        'type' => 'dgt_service_response',
        'label' => t('DGT Service response'),
        'description' => t('Response from the DGT Translation Service.'),
      ),
    ),
  );

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

  return $items;
}

/**
 * Obsolete !!!
 * Action: Send the content review request to the DGT Translation Service.
 *
 * @param object $node
 *   Node object.
 * @param object $tmgmt_job
 *   TMGMT Job object.
 *
 * @return array An array with the DGT Translation Service response.
 * An array with the DGT Translation Service response.
 */
function ne_dgt_rules_send_the_review_request($node, TMGMTJob $tmgmt_job) {
  $translator = $tmgmt_job->getTranslator();
  $controller = $translator->getController();

  $dgt_service_response = $controller->requestReview($tmgmt_job, $node->nid);

  return array(
    'dgt_service_response' => $dgt_service_response,
  );
}

/**
 * Action: Send the review request for a given node.
 *
 * @param object $node
 *   The node that needs to be reviewed by the DGT Reviewer.
 *
 * @return array
 */
function ne_dgt_rules_ftt_node_send_review_request($node) {
  $dgt_service_response = array();

  if ($default_translator = getDefaultFttWorkflowTranslator()) {
    // The review request can be only sent for the english version of the node.
    if (isset($node->language) && $node->language === 'en') {
      $job = createTmgmtJobAndItemForNode($default_translator, $node);
    }
    // Sending the review request to DGT Services.
    if($job) {
      $dgt_service_response = sendReviewRequest($job, $node);
    }

  }
  // @Todo - when there is no translator

  return array(
    'tmgmt_job' => $job,
    'dgt_service_response' => $dgt_service_response,
  );
}

/**
 * Sends the review request to DGT Services for a given node.
 *
 * @param \TMGMTJob $job
 * @param $node
 */
function sendReviewRequest(TMGMTJob $job, $node) {
  $translator = $job->getTranslator();
  $controller = $translator->getController();

  $service_response = $controller->requestReview($job, $node->nid);

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
function createTmgmtJobAndItemForNode($default_translator, $node) {
  // Creating TMGMT Main job.
  $tmgmt_job = tmgmt_job_create($node->language, '');
  $tmgmt_job->translator = $default_translator;

  // Adding the TMGMT Job Item to the created TMGMT Job
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

/**
 * Provides default translator for the FTT workflow.
 *
 * @return string/bool
 *  Returns the name of the default FTT workflow translator or FALSE if not set.
 */
function getDefaultFttWorkflowTranslator() {
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
