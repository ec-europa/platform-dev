<?php

/**
 * @file
 * Contains MediaInternetAvportalHandler.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetAvportalHandler extends MediaInternetBaseHandler {

  /**
   * Check if a Avportal video id is valid.
   */
  static public function validId($id) {
    // url: http://ec.europa.eu/avservices/video/player.cfm?sitelang=en&ref=xxx
    $ourl = 'http://ec.europa.eu/avservices/video/player.cfm?ref=' . $id;
    $response = drupal_http_request($ourl, array('method' => 'HEAD'));

    if ($response->code == 401) {
      throw new MediaInternetValidationException('Embedding has been disabled for this avportal video.');
    }
    elseif ($response->code != 200) {
      throw new MediaInternetValidationException('The avportal video ID is invalid or the video was deleted.');
    }
    return TRUE;
  }

  /**
   * Implements parent:parse().
   */
  public function parse($embed_code) {
    // url: http://ec.europa.eu/avservices/video/player.cfm
    $patterns = array(
      '@ec\.europa\.eu/avservices/video/player\.cfm\?(.+)@i',
    );

    foreach ($patterns as $pattern) {
      preg_match($pattern, $embed_code, $matches);
      if (isset($matches[1]) && self::validId($matches[1])) {
        preg_match('/ref=(\w+)/', $matches[1], $mas);
        return file_stream_wrapper_uri_normalize('avportal://v/' . check_plain($mas[1]));
      }
    }
  }

  /**
   * Implements parent:claim().
   */
  public function claim($embed_code) {
    if ($this->parse($embed_code)) {
      return TRUE;
    }
  }

  /**
   * Implements parent:getFileObject().
   */
  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    if (empty($file->fid)) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
      $video_title = $wrapper->getVideoTitle();
      $file->filename = truncate_utf8(strip_tags($video_title), 255);
    }
    return $file;
  }

}
