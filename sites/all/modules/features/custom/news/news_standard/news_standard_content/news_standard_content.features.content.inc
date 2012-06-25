<?php
/**
 * @file
 * news_standard_content.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function news_standard_content_content_defaults() {
  $content = array();

  $content['news_nano'] = (object) array(
    'exported_path' => 'content/innovation-partnerships-raw-materials-and-agriculture-launched',
    'title' => 'Innovation partnerships on raw materials and agriculture launched',
    'status' => '1',
    'promote' => '0',
    'sticky' => '1',
    'type' => 'news',
    'language' => 'en',
    'created' => '1330675866',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'news_nano',
    'body' => array(),
  );

  $content['news_portugal'] = (object) array(
    'exported_path' => 'content/portugal’s-economic-reform-programme-track-says-review-mission',
    'title' => 'Portugal’s economic reform programme on track says review mission',
    'status' => '1',
    'promote' => '0',
    'sticky' => '1',
    'type' => 'news',
    'language' => 'en',
    'created' => '1330676024',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'news_portugal',
    'body' => array(),
  );

return $content;
}
