<?php

/**
 *  @file media_avportal/includes/MediaAvportalStreamWrapper.inc
 *
 *  Create a Avportal Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $avportal = new MediaAvportalStreamWrapper('avportal://v/[video-code]');
 */
class MediaAvportalStreamWrapper extends MediaReadOnlyStreamWrapper {

  // Overrides $base_url defined in MediaReadOnlyStreamWrapper.
  protected $base_url = 'http://ec.europa.eu/avservices/video/player.cfm';

  /**
   * Returns a url in the format "http://ec.europa.eu/avservices/video/player.cfm?ref=qsPQN4MiTeE".
   *
   * Overrides interpolateUrl() defined in MediaReadOnlyStreamWrapper.
   * This is an exact copy of the function in MediaReadOnlyStreamWrapper,
   * here in case that example is redefined or removed.
   */
  function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '?' . http_build_query($parameters);
    }
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/avportal';
  }

  function getTarget($f) {
    return FALSE;
  }
}
