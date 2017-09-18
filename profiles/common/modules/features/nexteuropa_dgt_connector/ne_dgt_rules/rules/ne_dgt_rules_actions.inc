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
    'group' => t('NE DGT Rules'),
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

  return $items;
}

/**
 * Action: Send the content review request to the DGT Translation Service.
 *
 * @return array
 *   An array with the DGT Translation Service response.
 */
function ne_dgt_rules_send_the_review_request($node, $tmgmt_job) {
  $translator = $tmgmt_job->getTranslator();
  $controller = $translator->getController();

  $dgt_service_response = $controller->requestReview($tmgmt_job, $node->nid);

  return array(
    'dgt_service_response' => $dgt_service_response,
  );
}
