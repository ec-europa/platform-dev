<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator listener.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultTranslatorListener;

use EC\Poetry\Messages\Notifications\TranslationReceived;

/**
 * TMGMT DGT FTT translator listener.
 */
class TmgmtDgtFttTranslatorListener {
  /**
   * Implements the event onTranslationReceived.
   */
  public function onTranslationReceived(TranslationReceived $message) {
    // Log the event.
    // @todo: Remove this log.
    watchdog(
      'ne_tmgmt_dgt_ftt_translator',
      'The translator DGT FTT receives a request/response.',
      array(),
      WATCHDOG_INFO
    );

    $filename = 'dump_' . date('m-d-Y_hia');
    $path = "public://dgt_req_res/dumps/" . $filename . '.xml';
    $dirname = dirname($path);
    if (file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      file_save_data($message, $path);
    }
    else {
      watchdog(
        'ne_tmgmt_dgt_ftt_translator',
        'Unable to save the DGT request/response dump.',
        array(),
        WATCHDOG_ERROR
      );
    }
  }

}
