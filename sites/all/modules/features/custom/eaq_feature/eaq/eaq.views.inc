<?php

/**
 * @file
 * 
 */

/**
 * Implements hook_views_data().
 * 
 * Add field with operations for questions
 */
function eaq_views_data() {
  $data = array();
  
  $data['node']['operations'] = array(
    'title' => t('Operations'), 
    'help' => t('Operations for Ask a Question.'),
    'real field' => 'nid',
    'field' => array(
      'handler' => 'eaq_field_questions_operations',
    ),
  );
  
  return $data;
}