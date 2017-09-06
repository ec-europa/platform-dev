<?php

/**
 * @file
 * Admin section for ECAS Group Sync.
 */

/**
 * Form constructor for the mapping rules form.
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

  $id_mapping = 0;

  $query = db_select('ecas_sync_mapping', 'esm');
  $query->condition('synctype', 'role', '=');
  $query->fields('esm');
  $results = $query->execute();

  while ($row = $results->fetchAssoc()) {
    // Add the form elements for the existing mapping rules.
    $row_to_add = ecas_group_sync_get_row($id_mapping, 'dg', 'role', $row['LDAPfield_value'], $row['synctype_value']);
    array_push($form['role_mapping'], $row_to_add);
    $id_mapping++;
  }

  $form['role_mapping']['role_mapping_add_wrapper'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="add_role_mapping_wrapper" class="row_mapping">',
    '#suffix' => '</div>',
  );

  // Extra rows for new mapping.
  if (empty($form_state['extra_row'])) {
    $form_state['extra_row'] = 0;
  }
  for ($i = 0; $i < $form_state['extra_row']; $i++) {
    // Add the form elements for the new mapping rules added via AJAX.
    $row_to_add = ecas_group_sync_get_row("extra_" . $i, 'dg', 'role');
    array_push($form['role_mapping']['role_mapping_add_wrapper'], $row_to_add);
  }

  $form['role_mapping']['role_mapping_add_wrapper']['role_mapping_add'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'ecas_group_sync_role_mapping_form_callback',
      'wrapper' => 'add_role_mapping_wrapper',
    ),
    '#value' => t('Add role mapping'),
    '#submit' => array('ecas_group_sync_role_mapping_form_submit'),
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

/**
 * AJAX callback function for ecas_group_sync_mapping_form().
 *
 * @see ecas_group_sync_mapping_form()
 */
function ecas_group_sync_role_mapping_form_callback($form, $form_state) {
  return $form['role_mapping']['role_mapping_add_wrapper'];
}

/**
 * Form submit handler for ecas_group_sync_mapping_form().
 *
 * @see ecas_group_sync_mapping_form()
 */
function ecas_group_sync_role_mapping_form_submit($form, &$form_state) {
  $form_state['extra_row']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Form submit handler for ecas_group_sync_mapping_form().
 *
 * Saves the mapping rules in the database.
 *
 * @see ecas_group_sync_mapping_form()
 */
function ecas_group_sync_mapping_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  db_delete('ecas_sync_mapping')
    ->condition('synctype', 'role', '=')
    ->execute();

  for ($i = 0; $i < $values['count_mapping']; $i++) {
    if ($values["LDAPfield_value_" . $i] != '0' && $values["synctype_value_" . $i] != '0') {
      db_insert('ecas_sync_mapping')
        ->fields(array(
          'LDAPfield' => $values['LDAPfield_' . $i],
          'LDAPfield_value' => $values['LDAPfield_value_' . $i],
          'synctype' => $values['synctype_' . $i],
          'synctype_value' => $values['synctype_value_' . $i],
        ))
        ->execute();
    }
  }

  for ($i = 0; $i < $values['count_extra_mapping']; $i++) {
    if ($values["LDAPfield_value_extra_" . $i] != '0' && $values["synctype_value_extra_" . $i] != '0') {
      db_insert('ecas_sync_mapping')
        ->fields(array(
          'LDAPfield' => $values['LDAPfield_extra_' . $i],
          'LDAPfield_value' => $values['LDAPfield_value_extra_' . $i],
          'synctype' => $values['synctype_extra_' . $i],
          'synctype_value' => $values['synctype_value_extra_' . $i],
        ))
        ->execute();
    }
  }

  // Clearing the rules of synchronisation cached during
  // the "ecas_group_sync_get_ecas_sync_rules" function process.
  cache_clear_all('ecas_group_sync_rules', 'cache');

  drupal_set_message(t('The mapping rules have been saved.'));
}

/**
 * Create a row for the form.
 *
 * @param string $id
 *   The row number to use.
 * @param string $ldap_field
 *   The name of the LDAP field.
 * @param string $synctype
 *   The type of synchronisation to use, e.g. 'role'.
 * @param int $ldap_field_value
 *   The value of the LDAP field.
 * @param int $synctype_value
 *   The value of the sync type.
 *
 * @return array
 *   The row as a form API array.
 */
function ecas_group_sync_get_row($id, $ldap_field, $synctype, $ldap_field_value = 0, $synctype_value = 0) {
  $none_option = array("0" => "none");
  $form['LDAPfield_value_' . $id] = array(
    '#type' => 'select',
    '#options' => $none_option + ecas_group_sync_get_dg(),
    '#default_value' => $ldap_field_value,
    '#prefix' => '<div class = "row_mapping">',
    '#title' => $ldap_field,
  );
  $form['LDAPfield_' . $id] = array(
    '#type'  => 'hidden',
    '#value'  => $ldap_field,
  );
  $form['synctype_value_' . $id] = array(
    '#type' => 'select',
    '#options' => $none_option + user_roles(),
    '#default_value' => $synctype_value,
    '#title' => $synctype,
  );
  $form['synctype_' . $id] = array(
    '#type'  => 'hidden',
    '#value'  => $synctype,
    '#suffix' => '</div>',
  );
  return $form;
}
