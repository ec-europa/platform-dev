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
              if ($node = node_load($entity_id)) {
                if ($this->canViewNode($node)) {
                  $render = node_view($node, $view_mode);
                }
              }
              else {
                $this->watchdogTokenNotFound($data, $original);
              }
              break;

            case 'term':
              if ($term = taxonomy_term_load($entity_id)) {
                $render = taxonomy_term_view($term, $view_mode);
              }
              else {
                $this->watchdogTokenNotFound($data, $original);
              }
              break;

            case 'user':
              if ($account = user_load($entity_id)) {
                if (user_access('access user profiles')) {
                  $render = user_view($account, $view_mode);
                }
              }
              else {
                $this->watchdogTokenNotFound($data, $original);
              }
              break;

            case 'bean':
              if ($bean = bean_load($entity_id)) {
                if (bean_access('view', $bean)) {
                  $render = bean_view($bean, $view_mode);
                }
              }
              else {
                $this->watchdogTokenNotFound($data, $original);
              }
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
    $token_types = token_get_entity_mapping();
    if (isset($token_types[$token_type])) {
      $entity_type = $token_types[$token_type];
    }
    else {
      $entity_type = $token_type;
    }
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
   *    List of entity info array.
   */
  public function getEntityTokenTypes() {
    $supported_types = $this->getSupportedTokenTypes();
    return array_filter(parent::getEntityTokenTypes(), function ($entity) use ($supported_types) {
      return in_array($entity['token type'], $supported_types);
    });
  }

  /**
   * Check if current node can be viewed.
   *
   * @param object $node
   *    Node object.
   *
   * @return bool
   *    TRUE if provided node can be viewed, FALSE otherwise.
   */
  private function canViewNode($node) {
    global $user;

    // Make sure we don't render a node inside itself, preventing infinite loop.
    $object = menu_get_object('node');
    if (is_object($object) && isset($object->nid) && $object->nid == $node->nid) {
      drupal_set_message(t('Cannot render a node inside itself, remove any view mode token related to the current node.'));
      return FALSE;
    }

    // Make sure current user can actually access the rendered node.
    if (user_access('bypass node access') || user_access('administer nodes')) {
      return TRUE;
    }
    if (!node_access('view', $node)) {
      return FALSE;
    }
    if ($node->status == 0) {
      return ($node->uid == $user->uid) && user_access('view own unpublished content');
    }
    else {
      return TRUE;
    }
  }

}
