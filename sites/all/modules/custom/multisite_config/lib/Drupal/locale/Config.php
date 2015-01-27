<?php

/**
 * @file
 * Contains \Drupal\locale\Config
 */

namespace Drupal\locale;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Add language.
   *
   * @param string $language
   *    Language code.
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
   * @param $language_negotiation
   *    Language negotiation name.
   * @param string $type
   *    Language type.
   *
   * @see language_types_configurable()
   */
  public function setLanguageNegotiation($language_negotiation, $type = LANGUAGE_TYPE_INTERFACE) {
    $negotiation = array(
      $language_negotiation => -10,
      'language-default' => 10,
    );
    language_negotiation_set($type, $negotiation);
  }

  /**
   * Set language prefix, gived a certain language code.
   *
   * @param type $language
   *    Language code.
   * @param type $prefix
   *    Language prefix.
   */
  public function setLanguagePrefix($language, $prefix) {
    $arguments = array(':language' => $language, ':prefix' => $prefix);
    db_query("UPDATE {languages} SET prefix = ':prefix' WHERE language = ':language'", $arguments)->execute();
  }

} 
