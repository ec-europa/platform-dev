<?php
/**
 * @file
 * survey_contents.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function survey_standard_contents_content_defaults() {
  $content = array();

  $content['survey1'] = (object) array(
    'exported_path' => 'community/survey/movie-quizz',
    'webform' => array(
      'confirmation' => '',
      'confirmation_format' => NULL,
      'redirect_url' => '<confirmation>',
      'status' => '1',
      'block' => '0',
      'teaser' => '0',
      'allow_draft' => '0',
      'auto_save' => '0',
      'submit_notice' => '1',
      'submit_text' => '',
      'submit_limit' => '-1',
      'submit_interval' => '-1',
      'total_submit_limit' => '-1',
      'total_submit_interval' => '-1',
      'record_exists' => TRUE,
      'roles' => array(
        0 => '1',
        1 => '2',
      ),
      'emails' => array(),
      'components' => array(
        0 => array(
          'pid' => '0',
          'form_key' => 'your_favorite_genre',
          'name' => 'your favorite genre',
          'type' => 'select',
          'value' => '',
          'extra' => array(
            'items' => '0|action
  1|comedy
  2|history
  3|documentary
  4|thriller
  5|Sci-fi
  6|drama
  7|other',
            'multiple' => 1,
            'title_display' => 'before',
            'private' => 0,
            'aslist' => 0,
            'optrand' => 0,
            'conditional_operator' => '=',
            'other_option' => NULL,
            'other_text' => 'Other...',
            'description' => '',
            'custom_keys' => FALSE,
            'options_source' => '',
            'conditional_component' => '',
            'conditional_values' => '',
          ),
          'mandatory' => '1',
          'weight' => '0',
          'page_num' => 1,
        ),
        1 => array(
          'pid' => '0',
          'form_key' => 'your_favorite_movie',
          'name' => 'your favorite movie',
          'type' => 'textfield',
          'value' => '',
          'extra' => array(
            'title_display' => 'before',
            'private' => 0,
            'disabled' => 0,
            'unique' => 0,
            'conditional_operator' => '=',
            'width' => '',
            'maxlength' => '',
            'field_prefix' => '',
            'field_suffix' => '',
            'description' => '',
            'attributes' => array(),
            'conditional_component' => '',
            'conditional_values' => '',
          ),
          'mandatory' => '1',
          'weight' => '1',
          'page_num' => 1,
        ),
        2 => array(
          'pid' => '0',
          'form_key' => 'rate_these_movies',
          'name' => 'rate these movies',
          'type' => 'grid',
          'value' => '',
          'extra' => array(
            'options' => '0|0
  1|1
  2|2
  3|3',
            'questions' => '0|Titanic
  1|Gone with the wind
  2|Apocalypse now
  3|It\'s a Wonderful Life',
            'title_display' => 0,
            'private' => 0,
            'optrand' => 0,
            'qrand' => 0,
            'conditional_operator' => '=',
            'custom_option_keys' => 0,
            'custom_question_keys' => 0,
            'description' => '',
            'conditional_component' => '',
            'conditional_values' => '',
          ),
          'mandatory' => '1',
          'weight' => '2',
          'page_num' => 1,
        ),
        3 => array(
          'pid' => '0',
          'form_key' => 'your_last_movie_experience',
          'name' => 'your last movie experience',
          'type' => 'textarea',
          'value' => '',
          'extra' => array(
            'title_display' => 0,
            'private' => 0,
            'resizable' => 1,
            'disabled' => 0,
            'conditional_operator' => '=',
            'cols' => '',
            'rows' => '',
            'description' => '',
            'attributes' => array(),
            'conditional_component' => '',
            'conditional_values' => '',
          ),
          'mandatory' => '1',
          'weight' => '3',
          'page_num' => 1,
        ),
        4 => array(
          'pid' => '0',
          'form_key' => 'page_break',
          'name' => 'page break',
          'type' => 'pagebreak',
          'value' => '',
          'extra' => array(
            'conditional_operator' => '=',
            'private' => 0,
            'conditional_component' => '',
            'conditional_values' => '',
          ),
          'mandatory' => '0',
          'weight' => '4',
          'page_num' => 2,
        ),
        5 => array(
          'pid' => '0',
          'form_key' => 'your_email',
          'name' => 'your email',
          'type' => 'email',
          'value' => '',
          'extra' => array(
            'title_display' => 'before',
            'private' => 0,
            'disabled' => 0,
            'unique' => 0,
            'conditional_component' => '1',
            'conditional_operator' => '=',
            'width' => '',
            'description' => '',
            'attributes' => array(),
            'conditional_values' => '',
          ),
          'mandatory' => '0',
          'weight' => '5',
          'page_num' => 2,
        ),
      ),
    ),
    'title' => 'movie quizz',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'webform',
    'language' => 'en',
    'created' => '1330701483',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'survey1',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Quizz about movies</p>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p>Quizz about movies</p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
  );

return $content;
}
