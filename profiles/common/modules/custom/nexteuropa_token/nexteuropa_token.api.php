<?php

/**
 * @file
 * List of hooks exposed by the module.
 */

/**
 * Implements hook_nexteuropa_token_token_handlers().
 *
 * @see nexteuropa_token_nexteuropa_token_token_handlers()
 */
function hook_nexteuropa_token_token_handlers() {
  return array(
    'handler_name' => '\Drupal\module_name\HandlerNameTokenHandler',
  );
}

/**
 * Implements hook_nexteuropa_token_token_handlers_alter().
 *
 * @see nexteuropa_token_nexteuropa_token_token_handlers()
 * @see nexteuropa_token_get_token_handlers()
 */
function hook_nexteuropa_token_token_handlers_alter(array &$handlers) {
  $handlers['handler_name'] = '\Drupal\module_name\HandlerNameTokenHandler';
}
