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
  'title' => 'my link 1',
  'status' => '1',
  'promote' => '1',
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
        'url' => 'http://uesp.com',
        'title' => NULL,
        'attributes' => array(),
      ),
    ),
  ),
  'field_tags' => array(
    'und' => array(
      0 => array(
        'tid' => '3',
      ),
    ),
  ),
);
$content['link2'] = (object)array(
  'title' => 'my link 2',
  'status' => '1',
  'promote' => '1',
  'sticky' => '0',
  'type' => 'links',
  'language' => 'en',
  'created' => '1326883799',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'link2',
);
return $content;
}
