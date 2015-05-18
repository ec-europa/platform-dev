<?php

include_once('ecas_group_sync.admin.inc');

/*
 * create the mapping rules form
 */
function ecas_group_sync_mapping_group_form($form, &$form_state) {
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'ecas_group_sync') . '/css/ecas_group_sync.css',
  );
  $form['#prefix'] = '<div class="ecas_group_sync_mapping">';
  $form['#suffix'] = '</div>';
  
  $form['group_mapping'] = array(
    '#type' => 'fieldset',
    '#title' => t('Group mapping'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('to delete a mapping rule, put the mapping value to none'),
  );

  $none_option = array("0" => "none");
  $id_mapping = 0;
  
  $query = db_select('ecas_sync_mapping', 'esm');
  $query->condition('synctype', 'group','=');
  $query->fields('esm');
  $results = $query->execute();
              
  while($row = $results->fetchAssoc()) { // add the form elements for the existing mapping rules
    $row_to_add = get_row_group($id_mapping, 'dg', 'group', $row['LDAPfield_value'], $row['synctype_value'], $row['synctype_value_extra']);
    array_push($form['group_mapping'], $row_to_add);
    $id_mapping++;
  }

  $form['group_mapping']['group_mapping_add_wrapper'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="add_group_mapping_wrapper" class="row_mapping">',
    '#suffix' => '</div>',
  );

  // extra rows for new mapping
  if (empty($form_state['extra_row'])) {
    $form_state['extra_row'] = 0;
  }
  for ($i = 0; $i < $form_state['extra_row']; $i++) { // add the form elements for the new mapping rules added via ajax
    if(isset($form_state['values']['LDAPfield_value_extra_'.$i]))
      $row_to_add = get_row_group("extra_".$i, 'dg', 'group', $form_state['values']['LDAPfield_value_extra_'.$i], $form_state['values']['synctype_value_extra_'.$i], $form_state['values']['LDAPfield_extra_'.$i], $form_state['values']['synctype_extra_'.$i], $form_state['values']['synctype_extra_value_wrapper_extra_'.$i]);
    else
      $row_to_add = get_row_group("extra_".$i, 'dg', 'group');
    array_push($form['group_mapping']['group_mapping_add_wrapper'], $row_to_add);
  }

  $form['group_mapping']['group_mapping_add_wrapper']['group_mapping_add'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'add_mapping_group_callback',
      'wrapper' => 'add_group_mapping_wrapper',
    ),
    '#value' => t('Add group mapping'),
    '#submit' => array('add_group_mapping_submit'),
    '#prefix' => '<div class = "row_mapping">',
    '#suffix' => '</div>',
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save mapping'),
    '#prefix' => '<div id="mapping_submit">',
    '#suffix' => '</div>',
    '#weight' => 3,
  );

  $form['count_mapping'] = array(
    '#type'  => 'hidden',
    '#value'  => $id_mapping,
  );
  $form['count_extra_mapping'] = array(
    '#type'  => 'hidden',
    '#value'  => $form_state['extra_row'],
  );

  return $form;
}

function add_mapping_group_callback($form, $form_state) {
  return $form['group_mapping']['group_mapping_add_wrapper'];
}

function add_group_mapping_submit($form, &$form_state) {
  $form_state['extra_row']++;
  $form_state['rebuild'] = TRUE;
}

/*
 * save the mapping rules in the database
 */
function ecas_group_sync_mapping_group_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  db_delete('ecas_sync_mapping')
    ->condition('synctype', 'group','=')
    ->execute();
  
  for($i = 0; $i < $values['count_mapping']; $i++) {
    if($values["LDAPfield_value_".$i] != '0' && $values["synctype_value_".$i] != '0' && $values['synctype_extra_value_'.$i] != '0') {
      $id = db_insert('ecas_sync_mapping')
      ->fields(array(
        'LDAPfield' => $values['LDAPfield_'.$i],
        'LDAPfield_value' => $values['LDAPfield_value_'.$i],
        'synctype' => $values['synctype_'.$i],
        'synctype_value' => $values['synctype_value_'.$i],
        'synctype_value_extra' => $values['synctype_extra_value_'.$i],
        )
      )
      ->execute();
    }
  }
  
  for($i = 0; $i < $values['count_extra_mapping']; $i++) {
    if($values["synctype_value_extra_".$i] != '0' && $values["LDAPfield_value_extra_".$i] != '0' && $values["synctype_extra_value_extra_".$i] != '0') {
      $id = db_insert('ecas_sync_mapping')
      ->fields(array(
        'LDAPfield' => $values['LDAPfield_extra_'.$i],
        'LDAPfield_value' => $values['LDAPfield_value_extra_'.$i],
        'synctype' => $values['synctype_extra_'.$i],
        'synctype_value' => $values['synctype_value_extra_'.$i],
        'synctype_value_extra' => $values['synctype_extra_value_extra_'.$i],
      ))
      ->execute();
    }
  }  
  
  drupal_set_message(t('The mapping rules have been saved.'));
}



/*
 * create a row for the form
 */
function get_row_group($id, $LDAPfield, $synctype, $LDAPfield_value = 0, $synctype_value = 0, $synctype_value_extra = 0) {
  $none_option = array("0" => "none");
  $form['LDAPfield_value_'.$id] = array(
    '#type' => 'select',
    '#options' => $none_option + get_dg(),
    '#default_value' => $LDAPfield_value,
    '#prefix' => '<div class = "row_mapping">',
    '#title' => $LDAPfield,
  );
  $form['LDAPfield_'.$id] = array(
    '#type'  => 'hidden',
    '#value'  => $LDAPfield,
  );
  $form['synctype_value_'.$id] = array(
    '#type' => 'select',
    '#options' => $none_option + get_groups(),
    '#default_value' => $synctype_value,
    '#title' => $synctype,
    '#ajax' => array(
      'callback' => 'update_og_roles',
      'wrapper' => 'synctype_extra_value_'.$id,
    ),
  );
  $form['synctype_'.$id] = array(
    '#type'  => 'hidden',
    '#value'  => $synctype,
  );
  
  $form['synctype_extra_value_wrapper_'.$id] = array(
    '#prefix' => '<div id="synctype_extra_value_'.$id.'">',
    '#suffix' => '</div></div>',
  );
  $form['synctype_extra_value_wrapper_'.$id]['synctype_extra_value_'.$id] = array(
    '#type' => 'select',
    '#options' => $none_option + get_og_roles($synctype_value),
    '#title' => 'group role',
    '#default_value' => $synctype_value_extra,
    '#states' => array(
      'disabled' => array(
        ':input[name="synctype_value_'.$id.'"]' => array('value' => '0'), // disable the form element when no group is selected
      ),
    ),
  );
  
  return $form;
}

/*
 * callback to update og roles select list regarding the group selected
 */
function update_og_roles($form, &$form_state) {
  $none_option = array("0" => 'none');

  if(count($form_state['triggering_element']['#array_parents']) > 3) { // check if the callback comes from the extra fields or from the existing fields
    $id = $form_state['triggering_element']['#array_parents'][2];
    // update the og roles select list
    $form['group_mapping']['group_mapping_add_wrapper'][$id]['synctype_extra_value_wrapper_extra_'.$id]['synctype_extra_value_extra_'.$id]['#options'] = $none_option + get_og_roles($form_state['triggering_element']['#value']);
    return $form['group_mapping']['group_mapping_add_wrapper'][$id]['synctype_extra_value_wrapper_extra_'.$id];
  }
  else {
    $id = $form_state['triggering_element']['#array_parents'][1];
    // update the og roles select list
    $form['group_mapping'][$id]['synctype_extra_value_wrapper_'.$id]['synctype_extra_value_'.$id]['#options'] = $none_option + get_og_roles($form_state['triggering_element']['#value']);
    return $form['group_mapping'][$id]['synctype_extra_value_wrapper_'.$id];
  }
}


/*
 * get all the og groups
 */
function get_groups() {
  $list_groups = og_get_all_group();
  foreach($list_groups as $gid) {
    $node = node_load($gid);
    $groups[$gid] = $node->title;
  }
  return $groups;
}

/*
 * get og roles
 */
function get_og_roles($gid = 0) {
  return og_roles('node', 'community', $gid);
}
