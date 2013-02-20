<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function wiki_og_views_default_views_alter(&$views) {
  if (array_key_exists('wiki_list', $views)) {
    $view=$views['wiki_list'];

    /* Display: Defaults */
    //$handler = $view->display['default']->handler;

    /* Display: Block */
    //$handler = $view->display['block_1']->handler;

  }
}

