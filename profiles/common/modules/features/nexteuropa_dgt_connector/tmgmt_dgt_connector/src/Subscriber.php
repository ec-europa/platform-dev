<?php

/**
 * @file
 * Provides events subscriber for TMGMT DGT Connector.
 */

namespace Drupal\tmgmt_dgt_connector;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use EC\Poetry\Events\Notifications\TranslationReceivedEvent;
use EC\Poetry\Events\Notifications\StatusUpdatedEvent;
use EC\Poetry\Messages\Notifications\TranslationReceived;
use EC\Poetry\Messages\Notifications\StatusUpdated;

/**
 * Subscriber with listeners for Server events.
 *
 * @package Drupal\tmgmt_dgt_connector
 */
class Subscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {

    watchdog(
      'tmgmt_poetry',
      'SIM Subs',
      array(),
      WATCHDOG_INFO
    );

    return array(
      TranslationReceivedEvent::NAME => 'onTranslationReceivedEvent',
      StatusUpdatedEvent::NAME  => 'onStatusUpdatedEvent',
    );
  }

  /**
   * Listener for the event onTranslationReceivedEvent.
   *
   * @param \EC\Poetry\Events\Notifications\TranslationReceivedEvent $event
   *   The event for the Translation Received.
   */
  public function onTranslationReceivedEvent(TranslationReceivedEvent $event) {
    /** @var \EC\Poetry\Messages\Notifications\TranslationReceived $message */
    $message = $event->getMessage();
    $identifier = $message->getIdentifier();
    watchdog(
      'tmgmt_poetry',
      'Job @reference got a Translation Received. Message: @message',
      array(
        '@reference' => $identifier->getFormattedIdentifier(),
        '@message' => $message->getRaw(),
      ),
      WATCHDOG_INFO
    );
  }

  /**
   * Listener for the event onStatusUpdatedEvent.
   *
   * @param StatusUpdatedEvent $event
   *   The event for the Status Update.
   */
  public function onStatusUpdatedEvent(StatusUpdatedEvent $event) {
    /** @var \EC\Poetry\Messages\Notifications\StatusUpdated $message */
    $message = $event->getMessage();
    $identifier = $message->getIdentifier()->getFormattedIdentifier();

    watchdog(
      'tmgmt_poetry',
      'Job @reference got a Status. Message: @message',
      [
        '@reference' => $identifier,
        '@message' => $message->getRaw(),
      ],
      WATCHDOG_INFO
    );
  }

}
