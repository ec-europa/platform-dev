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
define('NEXTEUROPA_TOKEN_CKEDITOR_REGEX_TMGMT_POETRY_IGNORE', '/<token value=\"(.*)\"\/>/U');

/**
 * TMGMT Poetry ignore tag template.
 *
 * @see nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags()
 * @see nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens()
 *
 * @link https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6851
 */
define('NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_IGNORE_TAG', '<token value="%s"/>');

/**
 * Implements hook_tmgmt_field_source_data_alter().
 */
function nexteuropa_token_ckeditor_tmgmt_field_source_data_alter(&$data, $entity_type, $entity, $langcode) {
  $entity_info = entity_get_info($entity_type);
  $bundle_key = $entity_info['bundle keys']['bundle'];
  $instances = field_info_instances($entity_type, $entity->{$bundle_key});
  foreach ($instances as $field_name => $instance) {
    $widget_type = $instance['widget']['type'];
    $widget_types = array('text_textarea_with_summary', 'text_textarea');
    if (in_array($widget_type, $widget_types) && isset($data[$field_name])) {
      foreach (element_children($data[$field_name]) as $key) {
        $data[$field_name][$key]['value']['#text'] = nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags($data[$field_name][$key]['value']['#text']);
      }
    }
  }
}

/**
 * Implements hook_tmgmt_field_pre_populate_entity_alter().
 */
function nexteuropa_token_ckeditor_tmgmt_field_pre_populate_entity_alter(&$data, $entity, $entity_type, $langcode) {
  $entity_info = entity_get_info($entity_type);
  $bundle_key = $entity_info['bundle keys']['bundle'];
  $instances = field_info_instances($entity_type, $entity->{$bundle_key});
  foreach ($instances as $field_name => $instance) {
    $widget_type = $instance['widget']['type'];
    $widget_types = array('text_textarea_with_summary', 'text_textarea');
    if (in_array($widget_type, $widget_types) && isset($data[$field_name])) {
      foreach (element_children($data[$field_name]) as $key) {
        $data[$field_name][$key]['value']['#text'] = nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens($data[$field_name][$key]['value']['#text']);
      }
    }
  }
}

/**
 * Replace NextEuropa Tokens by TMGMT Poetry ignore tags.
 *
 * @param string $text
 *    Input text.
 *
 * @return string
 *    Text where tokens have been replaced by ignore tags.
 */
function nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags($text) {
  $regular_expressions = array(
    NEXTEUROPA_TOKEN_CKEDITOR_REGEX_VIEW_MODE_TOKENS,
    NEXTEUROPA_TOKEN_CKEDITOR_REGEX_LINK_TOKENS,
  );

  foreach ($regular_expressions as $regular_expression) {
    $matches = array();
    preg_match_all($regular_expression, $text, $matches);
    if ($matches && isset($matches[1][0])) {
      $replace = sprintf(NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_IGNORE_TAG, $matches[1][0]);
      $text = str_replace($matches[1][0], $replace, $text);
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
 * @return string
 *    Text where ignore tags have been replaced by tokens.
 */
function nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens($text) {
  preg_match_all(NEXTEUROPA_TOKEN_CKEDITOR_REGEX_TMGMT_POETRY_IGNORE, $text, $matches);
  if ($matches && isset($matches[1][0])) {
    $text = str_replace($matches[1][0], $matches[2][0], $text);
  }
  return $text;
}
