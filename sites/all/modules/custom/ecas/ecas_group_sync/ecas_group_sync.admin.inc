<?php


/*
 * create the mapping rules form
 */
function ecas_group_sync_mapping_form($form, &$form_state) {
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'ecas_group_sync') . '/css/ecas_group_sync.css',
  );
  $form['#prefix'] = '<div class="ecas_group_sync_mapping">';
  $form['#suffix'] = '</div>';
  
  $form['role_mapping'] = array(
    '#type' => 'fieldset',
    '#title' => t('Roles mapping'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('to delete a mapping rule, put the mapping value to none'),
  );

  $none_option = array("0" => "none");
  $id_mapping = 0;
  $id_role = 0;
  $id_group = 0;
  
  $query = db_select('ecas_sync_mapping', 'esm');
  $query->condition('synctype', 'role','=');
  $query->fields('esm');
  $query->join('role', 'r', 'esm.synctype_value = r.rid');
  $query->fields('r',array('name'));
  $results = $query->execute();
              
  while($row = $results->fetchAssoc()) {
    $row_to_add = get_row($id_mapping, 'dg', 'role', $row['LDAPfield_value'], $row['synctype_value']);
    array_push($form['role_mapping'], $row_to_add);
    $id_mapping++;
  }

  $form['role_mapping']['role_mapping_add_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('New mapping'),
    '#prefix' => '<div id="add_role_mapping_wrapper" class="row_mapping">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['extra_row'])) {
    $form_state['extra_row'] = 1;
  }
  for ($i = 0; $i < $form_state['extra_row']; $i++) {
    $id = $id_role+$i;
    $row_to_add = get_row("extra_".$id, 'dg', 'role');
    array_push($form['role_mapping']['role_mapping_add_wrapper'], $row_to_add);
  }

  $form['role_mapping']['role_mapping_add_wrapper']['role_mapping_add'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'add_mapping_callback',
      'wrapper' => 'add_role_mapping_wrapper',
    ),
    '#value' => t('Add role mapping'),
    '#submit' => array('add_role_mapping_submit'),
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

function add_mapping_callback($form, $form_state) {
  return $form['role_mapping']['role_mapping_add_wrapper'];
}

function add_role_mapping_submit($form, &$form_state) {
  $form_state['extra_row']++;
  $form_state['rebuild'] = TRUE;
}

/*
 * save the mapping rules in the database
 */
function ecas_group_sync_mapping_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  db_delete('ecas_sync_mapping')->execute();
  
  for($i = 0; $i < $values['count_mapping']; $i++) {
    if($values["LDAPfield_value_".$i] != '' && $values["synctype_value_".$i] != '' && $values["LDAPfield_value_".$i] != 'none' && $values["synctype_value_".$i] != 'none') {
      $id = db_insert('ecas_sync_mapping')
      ->fields(array(
        'LDAPfield' => $values['LDAPfield_'.$i],
        'LDAPfield_value' => $values['LDAPfield_value_'.$i],
        'synctype' => $values['synctype_'.$i],
        'synctype_value' => $values['synctype_value_'.$i],
        )
      )
      ->execute();
    }
  }
  
  for($i = 0; $i < $values['count_extra_mapping']; $i++) {
    if($values["LDAPfield_value_extra_".$i] != '' && $values["synctype_value_extra_".$i] != '' && $values["LDAPfield_value_extra_".$i] != 'none' && $values["synctype_value_extra_".$i] != 'none') {
      $id = db_insert('ecas_sync_mapping')
      ->fields(array(
        'LDAPfield' => $values['LDAPfield_extra_'.$i],
        'LDAPfield_value' => $values['LDAPfield_value_extra_'.$i],
        'synctype' => $values['synctype_extra_'.$i],
        'synctype_value' => $values['synctype_value_extra_'.$i],
      ))
      ->execute();
    }
  }  
  
  drupal_set_message(t('The mapping rules have been saved.'));
}



/*
 * create a row for the form
 */
function get_row($id, $LDAPfield, $synctype, $LDAPfield_value = 0, $synctype_value = 0) {
  $none_option = array("0" => "none");
  $form['LDAPfield_value_'.$id] = array(
    '#type' => 'select',
    '#options' => array_merge($none_option, get_dg()),
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
    '#options' => array_merge($none_option, user_roles()),
    '#default_value' => $synctype_value,
    '#title' => $synctype,
  );
  $form['synctype_'.$id] = array(
    '#type'  => 'hidden',
    '#value'  => $synctype,
    '#suffix' => '</div>'
  );
  return $form;
}

/*
 * get the list of DG from the LDAP
 */
function get_dg() {
  if (($cache = cache_get('list_dg', 'cache')) && !empty($cache->data)) {
    $list_dg = $cache->data;
  }
  else {
    $result = getLdapEntries(_ecas_import_users_groups_dn(), 'cn=DG_*', array('cn'));
    $list_dg = array();
    for ($i = 0; $i < $result['count']; ++ $i) {
      if ($result[$i]['cn'][0] != '') {
        $array_dg = explode('_', $result[$i]['cn'][0]);
        $list_dg[$array_dg[1]] = $array_dg[1];
      }
    }
    ksort($list_dg);
    
    cache_clear_all('list_dg', 'cache', TRUE);
    cache_set('list_dg', $list_dg, 'cache');
  }
  
  return $list_dg;
}
