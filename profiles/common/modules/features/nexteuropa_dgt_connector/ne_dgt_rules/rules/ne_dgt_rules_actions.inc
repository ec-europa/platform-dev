<?php
/**
 * @file
 * Next Europa DGT Rules integration - Custom actions.
 */

use Drupal\ne_dgt_rules\DgtRulesTools;

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
      'code' => array(
        'type' => 'text',
        'label' => t('Requester code'),
        'description' => t('Eg.: WEB'),
        'optional' => TRUE,
      ),
      'org_responsible' => array(
        'type' => 'text',
        'label' => t('Responsible'),
        'description' => t('Eg.: DIGIT'),
        'optional' => TRUE,
      ),
      'org_dg_author' => array(
        'type' => 'text',
        'label' => t('DG Author'),
        'description' => t('Eg.: IE/CE/DIGIT'),
        'optional' => TRUE,
      ),
      'org_requester' => array(
        'type' => 'text',
        'label' => t('Requester'),
        'description' => t('Eg.: IE/CE/DIGIT/A/3'),
        'optional' => TRUE,
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
        'description' => t('Response from the DGT Service.'),
      ),
      'dgt_service_response_status' => array(
        'type' => 'dgt_service_response_status',
        'label' => t('DGT Service Response - Response status'),
        'description' => t('Response from the DGT Service - response status.'),
      ),
      'dgt_service_demand_status' => array(
        'type' => 'dgt_service_demand_status',
        'label' => t('DGT Service Response - Demand status'),
        'description' => t('Response from the DGT Service - demand status.'),
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
        'description' => t('The content for the translation request.'),
      ),
      'code' => array(
        'type' => 'text',
        'label' => t('Requester code'),
        'description' => t('Eg.: WEB'),
        'optional' => TRUE,
      ),
      'org_responsible' => array(
        'type' => 'text',
        'label' => t('Responsible'),
        'description' => t('Eg.: DIGIT'),
        'optional' => TRUE,
      ),
      'org_dg_author' => array(
        'type' => 'text',
        'label' => t('DG Author'),
        'description' => t('Eg.: IE/CE/DIGIT'),
        'optional' => TRUE,
      ),
      'org_requester' => array(
        'type' => 'text',
        'label' => t('Requester'),
        'description' => t('Eg.: IE/CE/DIGIT/A/3'),
        'optional' => TRUE,
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
        'description' => t('Response from the DGT Service.'),
      ),
      'dgt_service_response_status' => array(
        'type' => 'dgt_service_response_status',
        'label' => t('DGT Service Response - Response status'),
        'description' => t('Response from the DGT Service - response status.'),
      ),
      'dgt_service_demand_status' => array(
        'type' => 'dgt_service_demand_status',
        'label' => t('DGT Service Response - Demand status'),
        'description' => t('Response from the DGT Service - demand status.'),
      ),
    ),
  );

  $items['accept_all_translations'] = array(
    'group' => t("Next Europa DGT Rules"),
    'label' => t("Accept all translations"),
    'base' => 'ne_dgt_rules_accept_all_translations',
    'parameter' => array(
      'identifier' => array(
        'type' => 'struct',
        'label' => t("Translation request identifier"),
        'restriction' => 'selector',
      ),
    ),
    'provides' => array(
      'entity_id' => array(
        'type' => 'integer',
        'label' => t("Translated content ID."),
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
 * @param string $org_responsible
 *   Organisation 'Responsible' value.
 * @param string $org_dg_author
 *   Organisation 'DG Author' value.
 * @param string $org_requester
 *   Organisation 'Requester' value.
 *
 * @return array
 *   An array of arrays with data which are exposed to the 'Rules'.
 */
function ne_dgt_rules_ftt_node_send_review_request($node, $code = '', $org_responsible = '', $org_dg_author = '', $org_requester = '') {
  $return = array(
    'tmgmt_job' => NULL,
    'dgt_service_response' => array(),
    'dgt_service_response_status' => array(),
    'dgt_service_demand_status' => array(),
  );

  // Initializing the parameters array..
  $parameters = array(
    'identifier' => array(
      'identifier.code' => $code,
    ),
    'data' => array(
      'details' => array(
        'responsible' => $org_responsible,
        'author' => $org_dg_author,
        'requester' => $org_requester,
      ),
    ),
  );

  if ($default_translator = DgtRulesTools::getDefaultFttTranslator()) {
    // The review request can be only sent for the english version of the node.
    if (isset($node->language) && $node->language === 'en') {
      // Checking if review request conditions are met.
      if (!DgtRulesTools::getActiveTmgmtJobItemsIds($node->nid)
        && $job = DgtRulesTools::createTmgmtJobAndItemForNode($default_translator, $node)) {
        // Sending the review request to DGT Services.
        $return = DgtRulesTools::sendReviewRequest($job, $parameters);
      }
    }
  }

  return $return;
}

/**
 * Action: Send the translation request for a given node.
 *
 * @param object $node
 *   The node that needs to be reviewed by the DGT Reviewer.
 * @param string $org_responsible
 *   Organisation 'Responsible' value.
 * @param string $org_dg_author
 *   Organisation 'DG Author' value.
 * @param string $org_requester
 *   Organisation 'Requester' value.
 *
 * @return array
 *   An Array with the job and the response, this element can be NULL.
 */
function ne_dgt_rules_ftt_node_send_translation_request($node, $code = '', $org_responsible = '', $org_dg_author = '', $org_requester = '') {
  $return = array(
    'tmgmt_job' => NULL,
    'dgt_service_response' => array(),
    'dgt_service_response_status' => array(),
    'dgt_service_demand_status' => array(),
  );

  // Initializing the parameters array..
  $parameters = array(
    'identifier' => array(
      'identifier.code' => $code,
    ),
    'data' => array(
      'details' => array(
        'responsible' => $org_responsible,
        'author' => $org_dg_author,
        'requester' => $org_requester,
      ),
    ),
  );

  $jobs = array();

  if ($default_translator = DgtRulesTools::getDefaultFttTranslator()) {
    // The review request can be only sent for the english version of the node.
    if (isset($node->language) && $node->language === 'en') {
      // Checking if review request conditions are met.
      if (!DgtRulesTools::getActiveTmgmtJobItemsIds($node->nid)) {
        foreach (language_list('enabled')[1] as $target_language) {
          if ($target_language->language != $node->language) {
            $job = DgtRulesTools::createTmgmtJobAndItemForNode($default_translator, $node, $target_language->language);
            if ($job) {
              $jobs[] = $job;
            }
          }
        }
        // Sending the translation request to DGT Services.
        $return = DgtRulesTools::sendTranslationRequest($default_translator, $jobs, $parameters);
      }
    }
  }

  return $return;
}

/**
 * Condition: All translations are received for a content.
 *
 * @param \EC\Poetry\Messages\Components\Identifier $identifier
 *   The translation request identifier.
 *
 * @return array
 *   The translation request identifier.
 */
function ne_dgt_rules_accept_all_translations(\EC\Poetry\Messages\Components\Identifier $identifier) {
  $ftt_mappings = DgtRulesTools::findMappingsByIdentifier($identifier);
  $entity_id = array();
  if (!empty($ftt_mappings)) {
    $entity_id['entity_id'] = reset($ftt_mappings)->entity_id;
  }
  $jobs = DgtRulesTools::loadTmgmtJobsByReference($identifier->getFormattedIdentifier());
  /** @var \TMGMTJob $job */
  foreach ($jobs as $job) {
    $job_items = $job->getItems();
    foreach ($job_items as $job_item) {
      $job_item->acceptTranslation();
    }
    $job->finished();
    DgtRulesTools::addMessageTmgmtJob($job, "Accepted by DGT FTT.", array());
  }

  return $entity_id;
}
