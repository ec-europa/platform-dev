<?php

/**
 * @file
 * 
 */

function eaq_feature_rules_list() {
  $output = '';
  $result = db_select('question_assignment_rules', 'qar')
    ->fields('qar')
    ->execute()
    ->fetchAll();

  $header = array(
    array('data' => t('Language'), 'field' => 'language_id'),
    array('data' => t('Related Country'), 'field' => 'related_country_id'),
    array('data' => t('User'), 'field' => 'user_id'),
    array('data' => t('Operations')),
  );
  if (isset($result) && !empty($result)) {
    $rows = array();
    foreach ($result as $rule) {
      $user = user_load($rule->user_id);
      $operations['edit'] = l(t('edit'), 'admin/config/ask-a-question/rules/' . $rule->qarid . '/edit');
      $operations['delete'] = l(t('delete'), 'admin/config/ask-a-question/rules/' . $rule->qarid . '/delete');
      $rows[] = array(
        $rule->language_id,
        $rule->related_country_id,
        l($user->name, 'user/' . $rule->user_id),
        theme('item_list', array('items' => $operations, 'type' => 'ul', 'attributes' => array('class' => 'links inline'))),
      );
    }
    $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('width' => '100%')));
  }
  else {
    $output = t('There are currently no rules defined.');
  }

  return $output;
}

function eaq_feature_rules_add($form, &$form_state) {
  $fields = field_info_fields();
  
  $form['language_id'] = array(
    '#title' => t('Language'),
    '#type' => 'select',
    '#options' => list_allowed_values($fields['field_language']),
    '#description' => t('Language which is used by the visitor.'),
    '#required' => TRUE,
  );

  $form['related_country_id'] = array(
    '#title' => t('Related Country'), 
    '#type' => 'select',
    '#options' => list_allowed_values($fields['field_related_country']),
    '#description' => t('The country to which the question is related.'),
    '#required' => TRUE,
  );

  $form['user_id'] = array(
    '#title' => t('User'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'ask-a-question/autocomplete/users',
    '#description' => t('Eurodesk Employee to which the question will be assigned.'),
    '#required' => TRUE,
  );
  
  $form['operation'] = array(
    '#type' => 'hidden',
    '#value' => 'add'
  );
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('eaq_feature_rules_save'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/config/ask-a-question/rules'),
  );
  
  return $form;
}

function eaq_feature_rules_edit($form, &$form_state, $qarid) {
  $fields = field_info_fields();
  
  $result = db_select('question_assignment_rules', 'qar')
  ->fields('qar')
  ->condition('qarid', $qarid, '=')
  ->execute()
  ->fetchAssoc();
  
  $form['language_id'] = array(
    '#title' => t('Language'),
    '#type' => 'select',
    '#options' => list_allowed_values($fields['field_language']),
    '#default_value' => $result['language_id'],
    '#description' => t('Language which is used by the visitor.'),
    '#required' => TRUE,
  );

  $form['related_country_id'] = array(
    '#title' => t('Related Country'), 
    '#type' => 'select',
    '#options' => list_allowed_values($fields['field_related_country']),
    '#default_value' => $result['related_country_id'],
    '#description' => t('The country to which the question is related.'),
    '#required' => TRUE,
  );
  
  $user = user_load($result['user_id']);
  $form['user_id'] = array(
    '#title' => t('User'),
    '#type' => 'textfield',
    '#autocomplete_path' => 'ask-a-question/autocomplete/users',
    '#default_value' => $user->name . ' [uid:' . $result['user_id'] . ']',
    '#description' => t('Eurodesk Employee to which the question will be assigned.'),
    '#required' => TRUE,
  );
  
  $form['operation'] = array(
    '#type' => 'hidden',
    '#value' => 'edit'
  );
  
  $form['qarid'] = array(
    '#type' => 'hidden',
    '#value' => $qarid
  );
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('eaq_feature_rules_save'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/config/ask-a-question/rules'),
  );
  
  return $form;
}

function eaq_feature_rules_delete($form, &$form_state, $qarid) {
  $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');
  $form['qarid'] = array('#type' => 'hidden', '#value' => $qarid);
  
  $form['#submit'][] = 'eaq_feature_rules_save';
  
  $confirm_question = 'Are you sure you want to delete this item?';
  
  return confirm_form($form, $confirm_question, 'admin/config/ask-a-question/rules', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

function eaq_feature_rules_save($form, &$form_state) {
  if (isset($form_state['values']['user_id'])) {
    preg_match('/\[uid:(\d+)\]/', $form_state['values']['user_id'], $matches);
  }
  
  if ($form_state['values']['operation'] == "add" && $form_state['values']['operation'] == "edit") {
    $new_role = user_role_load_by_name('eurodesk employee assignee');
    if (!isset($new_role->rid)) {
      $role = new stdClass();
      $role->name = 'eurodesk employee assignee';
      user_role_save($role);
    }
    
    $user = user_load($matches[1]);
    if (isset($user) && !in_array('eurodesk employee assignee', array_values($user->roles))) {
      $role = user_role_load_by_name('eurodesk employee assignee');
      $roles = $user->roles + array($role->rid => $role->name);
      user_save($user, array('roles' => $roles));
    }
  }
  
  //eurodesk employee assignee
  switch ($form_state['values']['operation']) {
    case 'add':
      $result = db_insert('question_assignment_rules')
        ->fields(array(
          'language_id' => $form_state['values']['language_id'],
          'related_country_id' => $form_state['values']['related_country_id'],
          'user_id' => $matches[1],
        ))
        ->execute();
      $message = t('New rule is saved.');
      break;
    case 'edit':
      $result = db_update('question_assignment_rules')
        ->fields(array(
          'language_id' => $form_state['values']['language_id'],
          'related_country_id' => $form_state['values']['related_country_id'],
          'user_id' => $matches[1],
        ))
        ->condition('qarid', $form_state['values']['qarid'], '=')
        ->execute();
      $message = t('Rule is updated.');
      break;
    case 'delete':
      $result = db_delete('question_assignment_rules')
        ->condition('qarid', $form_state['values']['qarid'], '=')
        ->execute();
      $message = t('Rule is deleted.');
      break;
  }

  if (isset($result)) {
    drupal_set_message($message);
  }
  else {
    drupal_set_message(t('Problem during saving rule.'), 'error');
  }
  
  $form_state['redirect'] = 'admin/config/ask-a-question/rules';
}


function eaq_feature_rules_get_user($node) {
  $language = (isset($node->field_language['und'][0]['value'])) ? $node->field_language['und'][0]['value']: 'any';
  $related_country = (isset($node->field_related_country['und'][0]['value'])) ? $node->field_related_country['und'][0]['value']: 'any';

  $result = db_select('question_assignment_rules', 'qar')
    ->fields('qar', array(
      'user_id'
    ))
    ->condition('language_id', $language, '=')
    ->condition('related_country_id', $related_country, '=')
    ->execute()
    ->fetchAssoc();

  return $result;
}

function eaq_feature_get_users_list($value = NULL, $inactive = FALSE) {
  $role = user_role_load_by_name('eurodesk employee assignee');
  
  $list = array();
  if (isset($value)) {
    $list = array(
      '' => t('- ' . $value . ' -'),
    );
  }
  
  $result = db_select('users', 'u');

  $result->join('users_roles', 'ur', 'u.uid = ur.uid');
 
  $result->fields('u', array('uid', 'name'))
    ->condition('u.uid', '0', '<>');

  if (variable_get('eaq_feature_role_assignee_user', '')) {
    $rid = variable_get('eaq_feature_role_assignee_user', '');
    if ($inactive == TRUE) {
      $result->condition('ur.rid', array($role->rid, $rid), 'IN');
    }
    else {
      $result->condition('ur.rid', $rid, '=');
    }
  }
  else {
    if (isset($inactive)) {
     $result->condition('ur.rid', $role->rid, '=');
    }
  }

  $result = $result->execute();
   
  foreach ($result as $user) {
    $list[$user->uid] = check_plain($user->name);
  }
 
  return $list;
}

function _eaq_feature_autocomplete_users($string = '') {
  $matches = array();
 
  if ($string) {
    $result = db_select('users', 'u');

    if (variable_get('eaq_feature_role_assignee_user', '')) {
      $result->join('users_roles', 'ur', 'u.uid = ur.uid');
    }
    
    $result->fields('u', array('uid', 'name'))
      ->condition('u.name', '%' . db_like($string) . '%', 'LIKE');

    if (variable_get('eaq_feature_role_assignee_user', '')) {
      $rid = variable_get('eaq_feature_role_assignee_user', '');
      $result->condition('ur.rid', $rid, '=');
    }
    
    $result = $result->range(0, 10)
      ->execute();
   
    foreach ($result as $user) {
      $matches[$user->name . ' [uid:' . $user->uid . ']'] = check_plain($user->name . ' [uid:' . $user->uid . ']');
    }
  }
 
  // return for JS
  drupal_json_output($matches);
}
