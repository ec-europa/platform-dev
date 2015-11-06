<?php
/**
 * @file
 * Create an Avportal Stream Wrapper class for the Media/Resource module.
 */

/**
 * Create an instance like this.
 *
 * @code
 *   $avportal = new MediaAvportalStreamWrapper('avportal://v/[video-code]');
 * @endcode
 */
class MediaAvportalStreamWrapper extends MediaReadOnlyStreamWrapper {

  // Overrides $base_url defined in MediaReadOnlyStreamWrapper.
  protected $baseUrl = 'http://ec.europa.eu/avservices/video/player.cfm';

  /**
   * Returns a URL in the format.
   *
   * @see http://ec.europa.eu/avservices/video/player.cfm?ref=qsPQN4MiTeE
   *
   * Overrides interpolateUrl() defined in MediaReadOnlyStreamWrapper.  This is
   * an exact copy of the function in MediaReadOnlyStreamWrapper, here in case
   * that example is redefined or removed.
   */
  public function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->baseUrl . '?' . http_build_query($parameters);
    }
  }

  /**
   * Implements getMimeType().
   */
  static public function getMimeType($uri, $mapping = NULL) {
    return 'video/avportal';
  }

  /**
   * Implements getTarget().
   */
  public function getTarget($f) {
    return FALSE;
  }

  /**
   * Implements getVideoInformation().
   */
  private function getVideoInformation() {

    $parts = $this->get_parameters();
    $video_id = check_plain($parts['v']);

    // Using cache to avoid a call to the webservice each time.
    $video_info = &drupal_static(__FUNCTION__ . $video_id);
    if (!isset($video_info)) {
      $cache = cache_get('av_video_' . $video_id);
      if (!empty($cache->data)) {
        $video_info = $cache->data;
      }
      else {
        $url = 'http://ec.europa.eu/avservices/cfc/video.cfc?method=getVideoDetails&ref=' . $video_id . '&format=json';
        $response = drupal_http_request($url);
        if ($response->data == 200) {
          $video_info = drupal_json_decode($response->data);
          cache_set('av_video_' . $video_id, $video_info, 'cache');
        }
        else {
          $video_info = array(
            'TITLE' => t('!!! ERROR !!! retrieving the video title'),
            'THUMB' => t('none'),
          );
        }
      }
    }
    return $video_info;
  }

  /**
   * Implements getVideoTitle().
   */
  public function getVideoTitle() {
    $info = $this->getVideoInformation();
    return $info['TITLE'];
  }

  /**
   * Implements getVideoThumb().
   */
  public function getVideoThumb() {
    $info = $this->getVideoInformation();
    return $info['THUMB'];
  }

  /**
   * Implements getLocalThumbnailPath().
   */
  public function getLocalThumbnailPath($remote_path) {
    $parts = $this->get_parameters();
    $local_path = file_default_scheme() . '://media-avportal/' . check_plain($parts['v']) . '.jpg';
    // If image does not exist, create a new from remote.
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      $response = drupal_http_request($remote_path);
      if (empty($response->error) || strlen(trim($response->error)) == 0) {
        file_unmanaged_save_data($response->data, $local_path, TRUE);
      }
      else {
        $local_path = drupal_get_path('module', 'media_avportal') . '/img/avportal.png';
      }
    }
    return $local_path;
  }

}
