<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Entity\ViewModeTokenHandler.
 */

namespace Drupal\nexteuropa_token\Entity;

/**
 * Class ViewModeTokenHandler.
 *
 * @package Drupal\nexteuropa_token\Entity
 */
class ViewModeTokenHandler extends TokenAbstractHandler {

  /**
   * {@inheritdoc}
   */
  public function getTokenSuffix() {
    return 'view-mode';
  }

  /**
   * {@inheritdoc}
   */
  public function hookTokenInfoAlter(&$data) {
    foreach ($this->getEntityTokenTypes() as $token_type => $entity_info) {
      foreach ($this->getEntityViewModes($token_type) as $view_mode) {
        $data['tokens'][$token_type][$this->getTokenName($view_mode)] = array(
          'name' => t("!entity view mode token", array('!entity' => $entity_info['label'])),
          'description' => t("Render entity using the specified view mode."),
        );
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function hookTokens($type, $tokens, array $data = array(), array $options = array()) {
    $replacements = array();

    if ($this->isValidTokenType($type)) {
      foreach ($tokens as $name => $original) {
        if ($this->isValidToken($original)) {
          $render = array();
          $entity_id = $this->getEntityIdFromToken($original);
          $view_mode = $this->getViewModeFromToken($original);

          switch ($type) {
            case 'node':
              $node = node_load($entity_id);
              $render = node_view($node, $view_mode);
              break;

            case 'term':
              $term = taxonomy_term_load($entity_id);
              $render = taxonomy_term_view($term, $view_mode);
              break;

            case 'user':
              $account = user_load($entity_id);
              $render = user_view($account, $view_mode);
              break;
          }

          // Remove contextual links for inline rendered entities.
          if (module_exists('contextual')) {
            unset($render['#contextual_links']);
          }
          $replacements[$original] = $render ? drupal_render($render) : '';
        }
      }
    }
    return $replacements;
  }

  /**
   * Extract view mode machine name from a token string.
   *
   * @param string $original
   *    Token, in its original format, eg. [node:1:view-mode:full].
   *
   * @return string
   *    Extracted view mode machine name.
   */
  public function getViewModeFromToken($original) {
    return $this->parseToken($original, 'view_mode');
  }

  /**
   * {@inheritdoc}
   */
  public function isValidToken($original) {
    return $this->getEntityIdFromToken($original) && $this->getViewModeFromToken($original);
  }

  /**
   * {@inheritdoc}
   */
  protected function parseToken($original, $item = 'entity_id') {
    $matches = array();
    $supported_types = implode('|', $this->getSupportedTokenTypes());
    switch ($item) {
      case 'entity_id':
        $regex = sprintf('/\[(%s)\:(\d*)\:%s\:\w*\]/', $supported_types, $this->getTokenSuffix());
        preg_match_all($regex, $original, $matches);
        return isset($matches[2][0]) && !empty($matches[2][0]) ? $matches[2][0] : '';

      case 'view_mode':
        $regex = sprintf('/\[(%s)\:\d*\:%s\:(\w*)\]/', $supported_types, $this->getTokenSuffix());
        preg_match_all($regex, $original, $matches);
        return isset($matches[2][0]) && !empty($matches[2][0]) ? $matches[2][0] : '';
    }
  }

  /**
   * Get view modes machine names per entity.
   *
   * @param string $token_type
   *    Entity token type name.
   *
   * @return array
   *    List of view mode machine names for a given entity token type.
   */
  public function getEntityViewModes($token_type) {

    $view_modes = array();
    $entity_type = $token_type == 'term' ? 'taxonomy_term' : $token_type;
    $info = entity_get_info($entity_type);
    foreach ($info['view modes'] as $mode => $mode_info) {
      $view_modes[] = $mode;
    }
    return $view_modes;
  }

  /**
   * Get token name using predefined token prefix.
   *
   * @param string $view_mode
   *    View mode machine name.
   *
   * @return string
   *    Formatted token name.
   *
   * @see ViewModeTokenHandler::hookTokenInfoAlter()
   */
  public function getTokenName($view_mode, $entity_id = 'ID') {
    return $entity_id . ':' . $this->getTokenSuffix() . ':' . $view_mode;
  }

  /**
   * Returns entity token types list.
   *
   * @return array
   *    List of entity token types.
   */
  public function getEntityTokenTypes() {
    return array_filter(parent::getEntityTokenTypes(), function ($entity) {
      return in_array($entity['token type'], $this->getSupportedTokenTypes());
    });
  }

}
