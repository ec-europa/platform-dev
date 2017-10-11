<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator listener.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultTranslatorListener;

use EC\Poetry\Events\Notifications\TranslationReceivedEvent;

/**
 * TMGMT DGT FTT translator listener.
 */
class TmgmtDgtFttTranslatorListener {
  /**
   * Implements the event onTranslationReceived.
   */
  public static function onTranslationReceived(TranslationReceivedEvent $event) {
    $event->getMessage();
  }

}
