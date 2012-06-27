<?php

/**
 * @file
 * Contains the basic 'node' field handler.
 */
class eaq_field_questions_operations extends views_handler_field {

  function render($values) {
    global $user;
    
    $value = $values->{$this->field_alias};

    $node = node_load($value);
    if (isset($node->field_assigned_user_uid[LANGUAGE_NONE][0]['value']) &&
     $node->field_assigned_user_uid[LANGUAGE_NONE][0]['value'] == $user->uid &&
       $node->field_handled[LANGUAGE_NONE][0]['value'] == 0) {
      $operations['handle'] = l(t('Handle Question'), 'admin/config/ask-a-question/handle/' . $value);
    }
    else {
      $operations['view'] = l(t('View Question'), 'admin/config/ask-a-question/view/' . $value);
    }
    
    if (user_access('administer ask a question reassign')) {
      $operations['reassign'] = l(t('Reassign Question'), 'admin/config/ask-a-question/reassign/' . $value);
    }
    
    $output = theme('item_list', array('items' => $operations, 'type' => 'ul', 'attributes' => array('class' => 'links inline')));

    return $output;
  }
}