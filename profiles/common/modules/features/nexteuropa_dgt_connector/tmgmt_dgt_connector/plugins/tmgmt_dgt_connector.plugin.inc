<?php

/**
 * @file
 * Provides TMGMT DGT Connector translation plugin controller.
 */

/**
 * DGT Connector translation plugin controller.
 *
 * It's now mostly based on TMGMTPoetryTranslatorPluginController
 * Later this should extend TMGMTDefaultTranslatorPluginController and
 * TMGMTPoetryTranslatorPluginController should be deprecated.
 */
class TmgmtDgtConnectorTranslatorPluginController extends TMGMTPoetryTranslatorPluginController {

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::canTranslation().
   *
   * We will check are source and target language supported
   * and the number of items.
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    // Check that the item does not have pending requests.
    $items = $job->getItems();
    $item = array_shift($items);
    if (!empty($item)) {
      $results = db_select('tmgmt_job_item', 'tji')
        ->fields('tji', array('tjid', 'tjiid'))
        ->condition('item_type', $item->item_type, '=')
        ->condition('item_id', $item->item_id, '=')
        ->execute()
        ->fetchAllAssoc('tjid');
      if ($results) {
        foreach ($results as $result) {
          if ($job = tmgmt_job_load($result->tjid)) {
            $translator = $job->getTranslator();
            if ($translator && $translator->plugin == 'tmgmt_dgt_connector' && $job->getState() == 1) {
              // Check the poetry status.
              $result_ps = db_select('poetry_status', 'ps')
                ->fields('ps', array('status'))
                ->condition('tjiid', $result->tjiid, '=')
                ->execute()
                ->fetchAssoc();
              if (empty($result_ps) || (!empty($result_ps) && $result_ps['status'] == POETRY_STATUS_MESSAGE_PEN)) {
                return FALSE;
              }
            }
          }
        }
      }
    }
    // All languages are supported at the moment.
    return TRUE;
  }

  /**
   * Implements getNotCanTranslateReason().
   *
   * Show the reason why we can not translate.
   */
  public function getNotCanTranslateReason(TMGMTJob $job) {
    return t('An active translation for this item already exists');
  }

}
