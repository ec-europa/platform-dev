<?php

namespace Drupal\nexteuropa_token;

/**
 * Class BaseUrlTokenHandler.
 *
 * @package Drupal\nexteuropa_token
 */
class BaseUrlTokenHandler extends TokenAbstractHandler {

  /**
   * Provide replacement values for placeholder tokens.
   *
   * @param string $type
   *   The machine-readable name of the type (group) of token being replaced.
   * @param mixed $tokens
   *   An array of tokens to be replaced.
   * @param array $data
   *   (optional) An associative array of data objects.
   * @param array $options
   *   (optional) An associative array of options for token replacement.
   *
   * @return array
   *   An associative array of replacement values.
   *
   * @see hook_token_info_alter()
   * @see hook_tokens()
   */
  public function hookTokens($type, $tokens, array $data = array(), array $options = array()) {
    global $base_url;
    if ($type != 'site' || empty($tokens['base-url'])) {
      return array();
    }
    // Original value => replacement.
    return array($tokens['base-url'] => $base_url);
  }

  /**
   * Alter the metadata about available placeholder tokens and token types.
   *
   * @param mixed $data
   *   The associative array of token definitions from hook_token_info().
   */
  public function hookTokenInfoAlter(&$data) {
    $data['tokens']['site']['base-url'] = array(
      'name' => t('Site base URL'),
      'description' => t('Base URL of the website'),
    );
  }

}
