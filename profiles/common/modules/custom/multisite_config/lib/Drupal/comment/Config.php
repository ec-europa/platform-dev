<?php

/**
 * @file
 * Contains \\Drupal\\comment\\Config.
 */

namespace Drupal\comment;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\block
 */
class Config extends ConfigBase {

  /**
   * Set default comment setting for a specific content type.
   *
   * @param string $content_type
   *    Content type machine name.
   * @param string $value
   *    Value to be set (human readable).
   */
  public function setDefaultCommentForContentType($content_type, $value) {
    switch ($value) {
      case 'open':
      default:
        $value_id = 2;
        break;

      case 'closed':
        $value_id = 1;
        break;

      case 'hidden':
        $value_id = 0;
        break;
    }
    variable_set('comment_' . $content_type, $value_id);
  }

  /**
   * Set threading comment setting for a specific content type.
   *
   * @param string $content_type
   *    Content type machine name.
   * @param string $value
   *    Value to be set (boolean).
   */
  public function setThreadingCommentForContentType($content_type, $value) {
    variable_set('comment_form_location_' . $content_type, $value);
  }
}
