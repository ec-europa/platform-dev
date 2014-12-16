<?php

/**
 * @file media_avportal/includes/MediaInterenetAvportalHandler.inc
 *
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
   *
   * Check against the oembed stream instead of the gdata api site to
   * avoid "yt:quota too_many_recent_calls" errors.
   *
   * @return
   *   Boolean.
   */
  static public function validId($id) {
    //url: http://ec.europa.eu/avservices/video/player.cfm?sitelang=en&ref=I003228
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

  public function parse($embedCode) {
    //url: http://ec.europa.eu/avservices/video/player.cfm
    $patterns = array(
      '@ec\.europa\.eu/avservices/video/player\.cfm\?(.+)@i'
    );

    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      // @TODO: Parse is called often. Refactor so that valid ID is checked
      // when a video is added, but not every time the embedCode is parsed.
      if (isset($matches[1]) && self::validId($matches[1])) {
        preg_match('/ref=(\w+)/', $matches[1], $mas);
        return file_stream_wrapper_uri_normalize('avportal://v/' . check_plain($mas[1]));
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    if (empty($file->fid)) {
      $response = drupal_http_request($this->embedCode);
      $dom = new DOMDocument();
      @$dom->loadHTML($response->data);
      $xpath = new DOMXPath($dom);
      $result = $xpath->query("//div[contains(@class, 'append-bottom')]/h3[1]");
      $title = $result->item(0)->nodeValue;
      $file->filename = truncate_utf8($title, 255);
    }
    return $file;
  }
}
