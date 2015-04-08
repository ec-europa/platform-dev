<?php

/**
 * Implements hook_nexteuropa_token_token_handlers().
 *
 * @see: nexteuropa_token_nexteuropa_token_token_handlers
 */
function hook_nexteuropa_token_token_handlers() {
  return array(
    'handler_name' => '\Drupal\module_name\HandlerNameTokenHandler',
  );
}

