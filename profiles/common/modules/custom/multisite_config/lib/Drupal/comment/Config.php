<?php

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
   *   Content type machine name.
   * @param string $value
   *   Value to be set (human readable).
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
   * Set reply form on the same page as comments for a specific content type.
   *
   * @param string $content_type
   *   Content type machine name.
   * @param string $value
   *   Value to be set (boolean).
   */
  public function setReplyFormCommentForContentType($content_type, $value) {
    variable_set('comment_form_location_' . $content_type, $value);
  }

  /**
   * Set threading comment setting for a specific content type.
   *
   * @param string $content_type
   *   Content type machine name.
   * @param string $value
   *   Value to be set (boolean).
   */
  public function setThreadingCommentForContentType($content_type, $value) {
    variable_set('comment_default_mode_' . $content_type, $value);
  }

  /**
   * Set title comment setting for a specific content type.
   *
   * @param string $content_type
   *   Content type machine name.
   * @param string $value
   *   Value to be set (boolean).
   */
  public function setTitleCommentForContentType($content_type, $value) {
    variable_set('comment_subject_field_' . $content_type, $value);
  }

  /**
   * Set preview comment setting for a specific content type.
   *
   * @param string $content_type
   *   Content type machine name.
   * @param string $value
   *   Value to be set (human readable).
   */
  public function setPreviewCommentForContentType($content_type, $value) {
    switch ($value) {
      case 'required':
        $value_id = 2;
        break;

      case 'optional':
      default:
        $value_id = 1;
        break;

      case 'disabled':
        $value_id = 0;
        break;
    }
    variable_set('comment_preview_' . $content_type, $value_id);
  }

  /**
   * Set comments per page setting for a specific content type.
   *
   * @param string $content_type
   *   Content type machine name.
   * @param string $value
   *   Value to be set (human readable).
   */
  public function setNumberCommentForContentType($content_type, $value) {
    switch ($value) {
      case '10':
        $value_id = 10;
        break;

      case '30':
        $value_id = 30;
        break;

      case '50':
      default:
        $value_id = 50;
        break;

      case '70':
        $value_id = 70;
        break;

      case '90':
        $value_id = 90;
        break;

      case '150':
        $value_id = 150;
        break;

      case '200':
        $value_id = 200;
        break;

      case '250':
        $value_id = 250;
        break;

      case '300':
        $value_id = 300;
        break;
    }
    variable_set('comment_default_per_page_' . $content_type, $value_id);
  }

  /**
   * Set anonymous comment setting for a specific content type.
   *
   * @param string $content_type
   *   Content type machine name.
   * @param string $value
   *   Value to be set (boolean).
   */
  public function setAnonymousCommentForContentType($content_type, $value) {
    variable_set('comment_anonymous_' . $content_type, $value);
  }

  /**
   * Create the field base definition of the 'comment_body'.
   *
   * If the field base already exist, it returns directly the field base info.
   *
   * @return array
   *   The $field array with field base info.
   */
  public function createCommentBodyField() {
    if ($field = field_info_field('comment_body')) {
      return $field;
    }

    // Exported field_base: 'comment_body'.
    $comment_body_field_base = array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(
        0 => 'comment',
      ),
      'field_name' => 'comment_body',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 1,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_long',
    );

    return field_create_field($comment_body_field_base);
  }

}
