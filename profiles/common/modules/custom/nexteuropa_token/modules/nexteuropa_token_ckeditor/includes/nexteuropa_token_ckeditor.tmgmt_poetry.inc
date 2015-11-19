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
define('NEXTEUROPA_TOKEN_CKEDITOR_REGEX_TMGMT_POETRY_IGNORE', '/<poetry_ignore value=\"(.*)\"\/>/U');

/**
 * TMGMT Poetry ignore tag template.
 *
 * @see nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags()
 * @see nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens()
 *
 * @link https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6851
 */
define('NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_IGNORE_TAG', '<poetry_ignore value="%s"/>');

/**
 * Replace NextEuropa Tokens with TMGMT ignore tags in the given text.
 *
 * @param string $text
 *    Input text.
 *
 * @return string
 *    Text where NextEuropa Tokens have been replaced with TMGMT ignore tags.
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
 * Replace TMGMT ignore tags with NextEuropa Tokens in the given text.
 *
 * @param string $text
 *    Input text.
 *
 * @return string
 *    Text where TMGMT ignore tags have been replaced with NextEuropa Tokens.
 */
function nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens($text) {
  preg_match_all(NEXTEUROPA_TOKEN_CKEDITOR_REGEX_TMGMT_POETRY_IGNORE, $text, $matches);
  if ($matches && isset($matches[1][0])) {
    $text = str_replace($matches[1][0], $matches[2][0], $text);
  }
  return $text;
}
