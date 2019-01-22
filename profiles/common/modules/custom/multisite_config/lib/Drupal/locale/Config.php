<?php

namespace Drupal\locale;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\locale.
 */
class Config extends ConfigBase {

  /**
   * Add language.
   *
   * @param string $language
   *   Language code.
   */
  public function addLanguage($language) {
    include_once DRUPAL_ROOT . '/includes/locale.inc';
    // Enable a language only if it has not been enabled already.
    $enabled_languages = locale_language_list();
    if (!isset($enabled_languages[$language])) {
      locale_add_language($language);
    }
  }

  /**
   * Set language negotiation.
   *
   * @param string $language_negotiation
   *   Language negotiation name.
   * @param string $type
   *   Language type.
   *
   * @see language_types_configurable()
   */
  public function setLanguageNegotiation($language_negotiation, $type = LANGUAGE_TYPE_INTERFACE) {
    include_once DRUPAL_ROOT . '/includes/language.inc';
    $negotiation = array(
      $language_negotiation => -10,
      'language-default' => 10,
    );
    // Reset available language provider.
    drupal_static_reset("language_negotiation_info");
    language_negotiation_set($type, $negotiation);
  }

  /**
   * Add a language negotiation to the active ones.
   *
   * @param string $language_negotiation
   *   Language negotiation name.
   * @param int $weight
   *   The language negotiation weight.
   * @param string $type
   *   Language type.
   *
   * @see language_types_configurable()
   */
  public function addLanguageNegotiation($language_negotiation, $weight = -10, $type = LANGUAGE_TYPE_INTERFACE) {
    include_once DRUPAL_ROOT . '/includes/language.inc';
    $language_negotiations = variable_get('language_negotiation_' . $type, array());
    $negotiation = array(
      $language_negotiation => $weight,
    );

    if (is_array($language_negotiations)) {
      foreach ($language_negotiations as $id => $provider) {
        if ($id == 'language-default') {
          $negotiation['language-default'] = ($weight + 2);
          continue;
        }
        if ($id != $language_negotiation) {
          $negotiation[$id] = $provider['weight'];
        }
      }
    }

    // Reset available language provider.
    drupal_static_reset("language_negotiation_info");
    language_negotiation_set($type, $negotiation);
  }

  /**
   * Disable a language negotiation from the active ones.
   *
   * @param string $language_negotiation
   *   Language negotiation name.
   * @param string $type
   *   Language type.
   *
   * @see language_types_configurable()
   */
  public function disableLanguageNegotiation($language_negotiation, $type = LANGUAGE_TYPE_INTERFACE) {
    include_once DRUPAL_ROOT . '/includes/language.inc';
    $language_negotiations = variable_get('language_negotiation_' . $type, array());
    $negotiation = array();

    if (is_array($language_negotiations)) {
      foreach ($language_negotiations as $id => $provider) {
        if ($id != $language_negotiation) {
          $negotiation[$id] = $provider['weight'];
          continue;
        }
      }
    }

    // Reset available language provider.
    drupal_static_reset("language_negotiation_info");
    language_negotiation_set($type, $negotiation);
  }

  /**
   * Set language prefix, given a certain language code.
   *
   * @param string $language
   *   Language code.
   * @param string $prefix
   *   Language prefix.
   */
  public function setLanguagePrefix($language, $prefix) {
    db_update('languages')
      ->fields(array(
        'prefix' => $prefix,
      ))
      ->condition('language', $language, '=')
      ->execute();
  }

}
