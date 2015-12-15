<?php
/**
 * @file
 * Contains the user's session group context argument default plugin.
 */

/**
 * The user's session group context argument default handler.
 */
class e_library_og_plugin_argument_default_og_context_session extends views_plugin_argument_default {

  /**
   * Return the user's session group context argument.
   */
  public function get_argument() {
    return isset($_SESSION['og_context']['gid']) ? $_SESSION['og_context']['gid'] : NULL;
  }

}
