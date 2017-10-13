<?php
/**
 * @file
 * Provides Next Europa TMGMT DGT FTT translator listener.
 */

namespace Drupal\ne_tmgmt_dgt_ftt_translator\TMGMTDefaultSubscriber;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use EC\Poetry\Events\Notifications\TranslationReceivedEvent;
use EC\Poetry\Events\Notifications\StatusUpdatedEvent;
use Drupal\ne_dgt_rules\DgtRulesTools;
use TMGMTJob;

/**
 * TMGMT DGT FTT translator listener.
 */
class TMGMTDgtFttSubscriber implements EventSubscriberInterface {

  /**
   * Implements the event getSubscribedEvents.
   */
  public static function getSubscribedEvents() {
    return array(
      TranslationReceivedEvent::NAME => 'onTranslationReceivedEvent',
      StatusUpdatedEvent::NAME  => 'onStatusUpdatedEvent',
    );
  }

  /**
   * Implements the event onTranslationReceivedEvent.
   *
   * @param TranslationReceivedEvent $event
   *   The event for the translation Received.
   */
  public function onTranslationReceivedEvent(TranslationReceivedEvent $event) {
    /** @var \EC\Poetry\Messages\Notifications\StatusUpdated $message */
    $message = $event->getMessage();
    $identifier = $message->getIdentifier();
    $requestStatus = $message->getRequestStatus();

    if ($requestStatus->getCode() != '0') {
      watchdog(
        'ne_dtmgmt_dgt_ftt_translator',
        'Job @reference receives a Status Update with issues. Message: @message',
        array(
          '@reference' => $identifier->getFormattedIdentifier(),
          '@message' => $requestStatus->getMessage(),
        ),
        WATCHDOG_ERROR
      );

      return;
    }

    watchdog(
      'ne_dtmgmt_dgt_ftt_translator',
      'Job @reference receives a Status Update. Message: @message',
      array(
        '@reference' => $identifier->getFormattedIdentifier(),
        '@message' => $message->getRaw(),
      ),
      WATCHDOG_INFO
    );

    $jobs = DgtRulesTools::loadTmgmtJobsByReference($identifier->getFormattedIdentifier());
    $attributions = $message->getTargets();

    /** @var \EC\Poetry\Messages\Components\Target $attribution */
    foreach ($attributions as $attribution) {
      /** @var TMGMTJob $job */
      foreach ($jobs as $job) {
        $translator = $job->getTranslator();
        $job_language = strtoupper($translator->mapToRemoteLanguage($job->target_language));

        if ($job_language == $attribution->getLanguage()) {
          if (DgtRulesTools::updateTranslationTmgmtJob($job, $attribution->getTranslatedFile())) {
            if (module_exists('rules')) {
              rules_invoke_event('ftt_translation_received', $identifier);
            }
            else {
              $job->acceptTranslation();

              DgtRulesTools::addMessageTmgmtJob(
                $job,
                t('The translation has been accepted automatically by DGT.'),
                array()
              );
            }
          }

          continue;
        }
      }
    }
  }

  /**
   * Implements the event onStatusUpdatedEvent.
   *
   * @param StatusUpdatedEvent $event
   *   The event for the Status Update.
   */
  public function onStatusUpdatedEvent(StatusUpdatedEvent $event) {
    /** @var \EC\Poetry\Messages\Notifications\StatusUpdated $message */
    $message = $event->getMessage();
    $identifier = $message->getIdentifier();

    $jobs = DgtRulesTools::loadTmgmtJobsByReference($identifier->getFormattedIdentifier());
    $requestStatus = $message->getRequestStatus();
    $demandStatus = $message->getDemandStatus();
    $attributionsStatuses = $message->getAttributionStatuses();

    if ($requestStatus->getCode() != '0') {
      watchdog(
        'ne_dtmgmt_dgt_ftt_translator',
        'Job @reference receives a Status Update with issues. Message: @message',
        array(
          '@reference' => $identifier->getFormattedIdentifier(),
          '@message' => $requestStatus->getMessage(),
        ),
        WATCHDOG_ERROR
      );

      return;
    }

    watchdog(
      'ne_dtmgmt_dgt_ftt_translator',
      'Job @reference receives a Status Update. Message: @message',
      array(
        '@reference' => $identifier->getFormattedIdentifier(),
        '@message' => $message->getRaw(),
      ),
      WATCHDOG_INFO
    );

    // Checking the Demand Status.
    foreach ($jobs as $job) {
      DgtRulesTools::updateStatusTmgmtJob($job, $demandStatus);
    }

    /** @var \EC\Poetry\Messages\Components\Status $attributionStatus */
    foreach ($attributionsStatuses as $attributionStatus) {
      /** @var TMGMTJob $job */
      foreach ($jobs as $job) {
        $translator = $job->getTranslator();
        $job_language = strtoupper($translator->mapToRemoteLanguage($job->target_language));

        if ($job_language == $attributionStatus->getLanguage()) {
          DgtRulesTools::updateStatusTmgmtJob($job, $attributionStatus);
          continue;
        }
      }
    }
  }

}
