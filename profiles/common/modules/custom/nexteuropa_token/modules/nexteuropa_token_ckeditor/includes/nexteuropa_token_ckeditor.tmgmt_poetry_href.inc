<?php

/**
 * @file
 * Contains code for a bug fix when text contains href's with tokens in TMGMT Poetry.
 */
/**
 * Search for the href attr containing a token.
 */
define('NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_HREF_IGNORE_REGEX', '/(href=\"\[\w*\:\d*\:url\]\")/U');
/**
 * Search for the replaced href attr when translation comes back.
 */
define('NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_HREF_IGNORED_REGEX', '/tmgmt_poetry_ignore_(.*)/U');
/**
 * Format to replace found href attr with.
 */
define('NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_HREF_FORMAT', 'tmgmt_poetry_ignore_%s');

/**
 * Replace href attr containing tokens by TMGMT Poetry ignore tags.
 *
 * @param string $text
 *    Input text.
 *
 * @return string
 *    Text where tokens have been replaced by ignore tags.
 */
function nexteuropa_token_ckeditor_replace_href_with_tmgmt_poetry_ignore_href_token($text) {
  $regular_expressions = array(
    NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_HREF_IGNORE_REGEX,
  );

  foreach ($regular_expressions as $regular_expression) {
    $matches = array();
    preg_match_all($regular_expression, $text, $matches);
    if (!$matches && !isset($matches[1][0])) {
      continue;
    }
    $replace = sprintf(NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_HREF_FORMAT, $matches[1][0]);
    $text = str_replace($matches[1][0], $replace, $text);
  }
  return $text;
}

/**
 * Replace TMGMT Poetry ignore tags by href attr containing tokens.
 *
 * @param string $text
 *    Input text.
 *
 * @return string
 *    Text where ignore tags have been replaced by tokens.
 */
function nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_href_token_with_tokens($text) {
  preg_match_all(NEXTEUROPA_TOKEN_CKEDITOR_TMGMT_POETRY_HREF_IGNORED_REGEX, $text, $matches);
  if (!$matches || !is_array($matches) || empty($matches)) {
    return $text;
  }
  foreach ($matches[0] as $key => $value) {
    $text = str_replace($matches[0][$key], $matches[1][$key], $text);
  }
  return $text;
}
