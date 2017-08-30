<?php
/**
 * @file
 * Contains integration code for TMGMT Poetry custom module.
 */

/**
 * Regular expression matching TMGMT Poetry ignore tags.
 *
 * @see nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags()
 * @see nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens()
 *
 * @link https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6851
 */
define('NEXTEUROPA_TOKEN_CKEDITOR_REGEX_TMGMT_POETRY_IGNORE', '/<tmgmt_poetry_ignore value=\"(.*)\"\/>/U');

/**
 * TMGMT Poetry ignore tag template.
 *
 * @see nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags()
 * @see nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens()
 *
 * @link https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6851
 */
define('NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_IGNORE_TAG', '<tmgmt_poetry_ignore value="%s"/>');

/**
 * Implements hook_tmgmt_field_source_data_alter().
 */
function nexteuropa_token_ckeditor_tmgmt_field_source_data_alter(&$data, $entity_type, $entity, $langcode) {
  if (module_exists('tmgmt_poetry')) {
    $fields = nexteuropa_token_ckeditor_tmgmt_poetry_get_fields($entity, $entity_type);
    foreach ($fields as $field_name) {
      if (isset($data[$field_name])) {
        foreach (element_children($data[$field_name]) as $key) {
          $data[$field_name][$key]['value']['#text'] = nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags($data[$field_name][$key]['value']['#text']);
        }
      }
    }
  }
}

/**
 * Implements hook_tmgmt_field_pre_populate_entity_alter().
 */
function nexteuropa_token_ckeditor_tmgmt_field_pre_populate_entity_alter(&$data, $entity, $entity_type, $langcode) {
  if (module_exists('tmgmt_poetry')) {
    $fields = nexteuropa_token_ckeditor_tmgmt_poetry_get_fields($entity, $entity_type);
    foreach ($fields as $field_name) {
      if (isset($data[$field_name])) {
        foreach (element_children($data[$field_name]) as $key) {
          $data[$field_name][$key]['value']['#translation']['#text'] = nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens($data[$field_name][$key]['value']['#translation']['#text']);
        }
      }
    }
  }
}

/**
 * Get fields that need to be processed by TMGMT alter hooks.
 *
 * @param object $entity
 *   An entity object.
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 *   List of field base names.
 *
 * @see nexteuropa_token_ckeditor_tmgmt_field_pre_populate_entity_alter()
 * @see nexteuropa_token_ckeditor_tmgmt_field_source_data_alter()
 */
function nexteuropa_token_ckeditor_tmgmt_poetry_get_fields($entity, $entity_type) {
  $fields = array();
  $entity_info = entity_get_info($entity_type);
  $bundle_key = $entity_info['bundle keys']['bundle'];
  $instances = field_info_instances($entity_type, $entity->{$bundle_key});
  foreach ($instances as $field_name => $instance) {
    $widget_type = $instance['widget']['type'];
    $widget_types = array('text_textarea_with_summary', 'text_textarea');
    if (in_array($widget_type, $widget_types)) {
      $fields[] = $field_name;
    }
  }
  return $fields;
}

/**
 * Replace NextEuropa Tokens by TMGMT Poetry ignore tags.
 *
 * @param string $text
 *    Input text.
 *
 * @return [a-zA-Z]+
 *   [a-zA-Z]+ where tokens have been replaced by ignore tags.
 */
function nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags($text) {
  $regular_expressions = array(
    NEXTEUROPA_TOKEN_CKEDITOR_REGEX_VIEW_MODE_TOKENS,
    NEXTEUROPA_TOKEN_CKEDITOR_REGEX_LINK_TOKENS,
  );

  foreach ($regular_expressions as $regular_expression) {
    $matches = array();
    preg_match_all($regular_expression, $text, $matches);
    if ($matches && !empty($matches[1])) {
      foreach (array_unique($matches[1]) as $match) {
        $replace = sprintf(NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_IGNORE_TAG, $match);
        $text = str_replace($match, $replace, $text);
      }
    }
  }
  return $text;
}

/**
 * Replace TMGMT Poetry ignore tags by NextEuropa Tokens.
 *
 * @param string $text
 *    Input text.
 *
 * @return [a-zA-Z]+
 *   [a-zA-Z]+ where ignore tags have been replaced by tokens.
 */
function nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens($text) {
  preg_match_all(NEXTEUROPA_TOKEN_CKEDITOR_REGEX_TMGMT_POETRY_IGNORE, $text, $matches);
  if ($matches && is_array($matches) && !empty($matches)) {
    if ($matches) {
      foreach ($matches[0] as $key => $value) {
        $text = str_replace($matches[0][$key], $matches[1][$key], $text);
      }
    }
  }
  return $text;
}
