<?php
/**
 * @file
 * communities.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function communities_content_defaults() {
$content = array();
$content['first community'] = (object)array(
  'title' => 'my first community',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'community',
  'language' => 'en',
  'created' => '1327420321',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'first community',
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>This is a example community.</p>
',
        'summary' => '',
        'format' => 'filtered_html',
        'safe_value' => '<p>This is a example community.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
);
$content['second community'] = (object)array(
  'title' => 'second community',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'community',
  'language' => 'en',
  'created' => '1327479443',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'second community',
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>This is another community test.</p>
',
        'summary' => '',
        'format' => 'filtered_html',
        'safe_value' => '<p>This is another community test.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
);
return $content;
}
