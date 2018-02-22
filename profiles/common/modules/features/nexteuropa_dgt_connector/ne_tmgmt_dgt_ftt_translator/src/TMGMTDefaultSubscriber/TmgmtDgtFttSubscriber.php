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
    /** @var \EC\Poetry\Messages\Notifications\TranslationReceived $message */
    $message = $event->getMessage();
    $identifier = $message->getIdentifier();
    DgtRulesTools::logResponseData($identifier, 'Translation Received', $message->getRaw());

    $jobs = DgtRulesTools::loadTmgmtJobsByReference($identifier->getFormattedIdentifier());

    /** @var \EC\Poetry\Messages\Components\Target $attribution */
    foreach ($message->getTargets() as $attribution) {
      /** @var \TMGMTJob $job */
      foreach ($jobs as $job) {
        $translator = $job->getTranslator();
        if ('dgt_ftt' != $translator->plugin) {
          continue;
        }

        $job_language = drupal_strtoupper($translator->mapToRemoteLanguage($job->target_language));
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
    DgtRulesTools::logResponseData($identifier, 'Status Update', $message->getRaw());

    $jobs = DgtRulesTools::loadTmgmtJobsByReference($identifier->getFormattedIdentifier());

    // Checking the Request Status.
    $request_status = $message->getRequestStatus();
    if ($request_status->getCode() != '0') {
      watchdog(
        'ne_dtmgmt_dgt_ftt_translator',
        'Job @reference receives a Status Update with issues. Message: @message',
        array(
          '@reference' => $identifier->getFormattedIdentifier(),
          '@message' => $request_status->getMessage(),
        ),
        WATCHDOG_ERROR
      );

      return;
    }

    // Checking the Demand Status.
    $demand_status = $message->getDemandStatus();
    foreach ($jobs as $job) {
      DgtRulesTools::updateStatusTmgmtJob($job, $demand_status);
    }

    // Checking the Attribution Status.
    /** @var \EC\Poetry\Messages\Components\Status $attribution_status */
    foreach ($message->getAttributionStatuses() as $attribution_status) {
      /** @var \TMGMTJob $job */
      foreach ($jobs as $job) {
        $translator = $job->getTranslator();
        if ('dgt_ftt' != $translator->plugin) {
          continue;
        }

        $job_language = drupal_strtoupper($translator->mapToRemoteLanguage($job->target_language));
        if ($job_language == $attribution_status->getLanguage()) {
          DgtRulesTools::updateStatusTmgmtJob($job, $attribution_status);
          continue;
        }
      }
    }
  }

}
