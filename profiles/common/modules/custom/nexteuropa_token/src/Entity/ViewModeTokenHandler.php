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
      foreach ($tokens as $original) {
        if ($this->isValidToken($original)) {
          $entity_view_mode_type = $this->getViewModeTypeHandlers();

          // By default let this be the token, not converted.
          $render = array(
            '#markup' => $original,
          );

          if (isset($entity_view_mode_type[$type])) {
            // Initialize the object.
            $entity_view_mode_type = $this->getEntityViewModeType($type, array(
              'entity id' => $this->getEntityIdFromToken($original),
              'view mode' => $this->getViewModeFromToken($original),
            )
            );

            // Before trying to render, check if the view mode is available.
            if ($entity_view_mode_type->isValidViewMode()) {
              if ($render_tmp = $entity_view_mode_type->entityView()) {
                // If the render is successful, overwrite the default
                // variable content.
                $render = $render_tmp;
              }
            }
          }

          // Remove contextual links for inline rendered entities.
          if (module_exists('contextual')) {
            unset($render['#contextual_links']);
          }

          $replacements[$original] = drupal_render($render);
        }
      }
    }
    return $replacements;
  }

  /**
   * Extract view mode machine name from a token string.
   *
   * @param string $original
   *   Token, in its original format, eg. [node:1:view-mode:full].
   *
   * @return string
   *   Extracted view mode machine name.
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
   *   Entity token type name.
   *
   * @return array
   *   List of view mode machine names for a given entity token type.
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
   *   View mode machine name.
   *
   * @return string
   *   Formatted token name.
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
   *   List of entity info array.
   */
  public function getEntityTokenTypes() {
    $supported_types = $this->getSupportedTokenTypes();
    return array_filter(parent::getEntityTokenTypes(), function ($entity) use ($supported_types) {
      return in_array($entity['token type'], $supported_types);
    });
  }

  /**
   * TODO: todo.
   *
   * @return array
   *   An array of plugin definitions.
   */
  private function getViewModeTypeHandlers() {
    $handlers = &drupal_static(__FUNCTION__);
    if (!isset($handlers)) {
      if ($cache = cache_get('nexteuropa_token:EntityViewModeType')) {
        $handlers = $cache->data;
      }
      else {
        $handlers = module_invoke_all('nexteuropa_token_entity_view_mode_type');
        drupal_alter('nexteuropa_token_entity_view_mode_type', $handlers);
        cache_set('nexteuropa_token:EntityViewModeType', $handlers, 'cache');
      }
    }
    return $handlers;
  }

  /**
   * Get instance of entity view mode type handler object.
   *
   * @param string $type
   *   The entity type.
   * @param array $configuration
   *   The configuration array.
   *
   * @return \Drupal\nexteuropa_token\Entity\ViewModeType\ViewModeTypeInterface
   *   Entity view mode type object.
   *
   * @throws \Exception
   *   Throws exception if no handler class has been found.
   */
  public function getEntityViewModeType($type, array $configuration = array()) {
    $handlers = $this->getViewModeTypeHandlers();
    if (!isset($handlers[$type])) {
      throw new \Exception(t('Entity view mode type handler with name !name not found.', array('!name' => $type)));
    }
    elseif (!class_exists($handlers[$type])) {
      throw new \Exception(t('Entity view mode type class !class not found.', array('!class' => $handlers[$type])));
    }
    else {
      $reflection = new \ReflectionClass($handlers[$type]);
      if (!$reflection->implementsInterface('\Drupal\nexteuropa_token\Entity\ViewModeType\ViewModeTypeInterface')) {
        throw new \Exception(t('Entity view mode type class !class must implement \Drupal\nexteuropa_token\Entity\ViewModeType\ViewModeTypeInterface interface.', array('!class' => $handlers[$type])));
      }
    }

    return $reflection->newInstance()->setConfiguration($configuration);
  }

}
