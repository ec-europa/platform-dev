<?php
/**
 * @file
 * news.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function news_content_defaults() {
  $content = array();

  $content['news1'] = (object) array(
    'exported_path' => 'content/my-news-1',
    'title' => 'my news 1',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'news',
    'language' => 'en',
    'created' => '1328886129',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'news1',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>test</p>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p>test</p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
  );

return $content;
}
