<?php
/**
 * @file
 * f_a_q.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function f_a_q_content_defaults() {
$content = array();
$content['question01'] = (object)array(
  'title' => 'Question 01',
  'status' => '1',
  'promote' => '1',
  'sticky' => '0',
  'type' => 'f_a_q',
  'language' => 'en',
  'created' => '1326704355',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'question01',
  'body' => array(),
);
$content['question02'] = (object)array(
  'title' => 'Question 02',
  'status' => '1',
  'promote' => '1',
  'sticky' => '0',
  'type' => 'f_a_q',
  'language' => 'en',
  'created' => '1326704390',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'question02',
  'body' => array(),
);
return $content;
}
