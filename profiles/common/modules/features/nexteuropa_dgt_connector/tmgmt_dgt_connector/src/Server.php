<?php

namespace Drupal\tmgmt_dgt_connector;

use EC\Poetry\Poetry;
use Drupal\nexteuropa_core\Psr3Watchdog;

/**
 * Class to handle messages from Poetry.
 *
 * @package Drupal\tmgmt_dgt_connector
 */
class Server {

  /**
   * Callback to be called from Poetry Server.
   *
   * Available from page "tmgmt_dgt_connector/server".
   */
  public static function endpoint() {
    $translator = tmgmt_translator_load(TMGMT_DGT_CONNECTOR_TRANSLATOR_NAME);
    $settings = $translator->getSetting('settings');

    $poetry = new Poetry(array(
      'notification.username' => $settings['callback_user'],
      'notification.password' => $settings['callback_password'],
      'logger' => new Psr3Watchdog(),
      'log_level' => variable_get('poetry_client_log_level', FALSE),
    ));

    $poetry->getEventDispatcher()->addSubscriber(new Subscriber());
    $poetry->getServer()->handle();

    exit;
  }

  /**
   * Callback for exposing WSDL configuration.
   *
   * Available from page "tmgmt_dgt_connector/wsdl".
   */
  public static function wsdl() {
    drupal_add_http_header('Content-Type', 'application/xml; utf-8');

    $url = url('tmgmt_dgt_connector/server', array(
      'absolute' => TRUE,
      'language' => (object) array('language' => FALSE),
    ));
    $poetry = new Poetry(array('notification.endpoint' => $url));
    print $poetry->getWsdl()->getXml();

    exit();
  }

}
