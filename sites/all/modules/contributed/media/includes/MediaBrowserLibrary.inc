<?php

/**
 * @file
 * Definition of MediaBrowserLibrary.
 */

/**
 * Media browser plugin for displaying the media browser library.
 *
 * @deprecated
 */
class MediaBrowserLibrary extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    // @todo Replace with file_access().
    return media_access('view', $account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    $path = drupal_get_path('module', 'media');
    $build['#attached']['js'][] = $path . '/js/plugins/media.library.js';

    $build['#settings']['viewMode'] = 'thumbnails';
    $build['#settings']['getMediaUrl'] = url('media/browser/list');
    $build['#settings'] += $this->params;

    $build['#markup'] = '<div id="container"><div id="scrollbox"><ul id="media-browser-library-list" class="media-list-thumbnails"></ul><div id="status"></div></div></div>';
    return $build;
  }
}
