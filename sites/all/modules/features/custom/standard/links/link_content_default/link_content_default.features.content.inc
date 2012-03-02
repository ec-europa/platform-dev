<?php
/**
 * @file
 * link_content_default.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function link_content_default_content_defaults() {
  $content = array();

  $content['link_eurostat'] = (object) array(
    'exported_path' => 'links/eurostat',
    'title' => 'Eurostat',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'links',
    'language' => 'en',
    'created' => '1330674572',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'link_eurostat',
    'field_link' => array(
      'und' => array(
        0 => array(
          'url' => 'http://eur-lex.europa.eu/en/index.htm',
          'title' => NULL,
          'attributes' => array(),
        ),
      ),
    ),
    'field_tags' => array(
      'und' => array(
        0 => array(
          'tid' => '4',
        ),
      ),
    ),
  );

  $content['link_official_journal'] = (object) array(
    'exported_path' => 'links/official-journal',
    'title' => 'Official journal',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'links',
    'language' => 'en',
    'created' => '1330674508',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'link_official_journal',
    'field_link' => array(
      'und' => array(
        0 => array(
          'url' => 'http://publications.europa.eu/official/index_en.htm',
          'title' => NULL,
          'attributes' => array(),
        ),
      ),
    ),
    'field_tags' => array(
      'und' => array(
        0 => array(
          'tid' => '4',
        ),
      ),
    ),
  );

return $content;
}
