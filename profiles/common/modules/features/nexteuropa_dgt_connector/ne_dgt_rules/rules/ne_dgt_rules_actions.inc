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

  return $items;
}

/**
 * Action: Send the review request for a given node.
 *
 * @param object $node
 *   The node that needs to be reviewed by the DGT Reviewer.
 *
 * @return array
 *   An array of arrays with data which are exposed to the 'Rules'.
 */
function ne_dgt_rules_ftt_node_send_review_request($node, $org_responsible = '', $org_dg_author = '', $org_requester = '') {
  $return = array(
    'tmgmt_job' => NULL,
    'dgt_service_response' => array(),
    'dgt_service_response_status' => array(),
    'dgt_service_demand_status' => array(),
  );

  // Initializing the parameters array..
  $parameters = array(
    'details' => array(
      'responsible' => $org_responsible,
      'author' => $org_dg_author,
      'requester' => $org_requester,
    ),
  );

  // Checking if all the organisation parameters are set.
  if (!DgtRulesTools::checkParameters($parameters)) {
    $parameters = array();
  }

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
