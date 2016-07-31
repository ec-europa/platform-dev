<?php

namespace Drupal\entity_translation;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\entity_translation.
 */
class Config extends ConfigBase {

  /**
   * Enable Entity Translation support for a specific content type.
   *
   * @param string $content_type
   *    Content type machine name.
   */
  public function enableEntityTranslation($content_type) {
    variable_set('language_content_type_' . $content_type, ENTITY_TRANSLATION_ENABLED);
  }

}
