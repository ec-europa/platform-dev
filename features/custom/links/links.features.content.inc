<?php
/**
 * @file
 * links.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function links_content_defaults() {
$content = array();
$content['link1'] = (object)array(
  'exported_path' => 'content/my-link-1',
  'title' => 'my link 1',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'links',
  'language' => 'en',
  'created' => '1326898557',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'link1',
  'field_link' => array(
    'und' => array(
      0 => array(
        'url' => 'http://www.my.url.com',
        'title' => NULL,
        'attributes' => array(),
      ),
    ),
  ),
);
$content['link2'] = (object)array(
  'exported_path' => 'content/my-link-2',
  'title' => 'my link 2',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'links',
  'language' => 'en',
  'created' => '1326883799',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'link2',
  'field_link' => array(
    'und' => array(
      0 => array(
        'url' => 'http://www.my.url.com',
        'title' => NULL,
        'attributes' => array(),
      ),
    ),
  ),
);
return $content;
}
