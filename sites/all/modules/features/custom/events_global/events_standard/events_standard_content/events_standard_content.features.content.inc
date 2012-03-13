<?php
/**
 * @file
 * event_content_default.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function events_standard_content_content_defaults() {
  $content = array();

  $content['event01'] = (object) array(
    'exported_path' => 'content/happy-new-year-2013',
    'title' => 'Happy New Year 2013',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'event',
    'language' => 'en',
    'created' => '1331119453',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'event01',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Event example.</p>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p>Event example.</p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_event_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-12-30 23:00:00',
          'value2' => '2012-12-30 23:00:00',
          'timezone' => 'Europe/Luxembourg',
          'timezone_db' => 'UTC',
          'date_type' => 'datetime',
        ),
      ),
    ),
  );

return $content;
}
