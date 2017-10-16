<?php

/**
 * @file
 * The mapping rules form.
 */

include_once 'ecas_group_sync.admin.inc';

/**
 * Form constructor for the mapping rules form.
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

  $id_mapping = 0;

  $query = db_select('ecas_sync_mapping', 'esm');
  $query->condition('synctype', 'group', '=');
  $query->fields('esm');
  $results = $query->execute();

  while ($row = $results->fetchAssoc()) {
    // Add the form elements for the existing mapping rules.
    $row_to_add = eacs_group_sync_get_row_group($id_mapping, 'dg', 'group', $row['LDAPfield_value'], $row['synctype_value'], $row['synctype_value_extra']);
    array_push($form['group_mapping'], $row_to_add);
    $id_mapping++;
  }

  $form['group_mapping']['group_mapping_add_wrapper'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="add_group_mapping_wrapper" class="row_mapping">',
    '#suffix' => '</div>',
  );

  // Extra rows for new mapping.
  if (empty($form_state['extra_row'])) {
    $form_state['extra_row'] = 0;
  }
  for ($i = 0; $i < $form_state['extra_row']; $i++) {
    // Add the form elements for the new mapping rules added via ajax.
    if (isset($form_state['values']['LDAPfield_value_extra_' . $i])) {
      $row_to_add = eacs_group_sync_get_row_group("extra_" . $i, 'dg', 'group', $form_state['values']['LDAPfield_value_extra_' . $i], $form_state['values']['synctype_value_extra_' . $i], $form_state['values']['synctype_extra_' . $i]);
    }
    else {
      $row_to_add = eacs_group_sync_get_row_group("extra_" . $i, 'dg', 'group');
    }
    array_push($form['group_mapping']['group_mapping_add_wrapper'], $row_to_add);
  }

  $form['group_mapping']['group_mapping_add_wrapper']['group_mapping_add'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'ecas_group_sync_mapping_group_form_add_mapping_group_callback',
      // @todo This wrapper callback doesn't exist.
      'wrapper' => 'add_group_mapping_wrapper',
    ),
    '#value' => t('Add group mapping'),
    '#submit' => array('ecas_group_sync_mapping_group_form_add_group_mapping_submit'),
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
 * AJAX callback for ecas_group_sync_mapping_group_form().
 *
 * @see ecas_group_sync_mapping_group_form()
 */
function ecas_group_sync_mapping_group_form_add_mapping_group_callback($form, $form_state) {
  return $form['group_mapping']['group_mapping_add_wrapper'];
}

/**
 * Form submit handler for ecas_group_sync_mapping_group_form().
 *
 * @see ecas_group_sync_mapping_group_form()
 */
function ecas_group_sync_mapping_group_form_add_group_mapping_submit($form, &$form_state) {
  $form_state['extra_row']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Form submit handler for ecas_group_sync_mapping_group_form().
 *
 * Saves the mapping rules in the database.
 *
 * @see ecas_group_sync_mapping_group_form()
 */
function ecas_group_sync_mapping_group_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  db_delete('ecas_sync_mapping')
    ->condition('synctype', 'group', '=')
    ->execute();

  for ($i = 0; $i < $values['count_mapping']; $i++) {
    if ($values["LDAPfield_value_" . $i] != '0' && $values["synctype_value_" . $i] != '0' && $values['synctype_extra_value_' . $i] != '0') {
      db_insert('ecas_sync_mapping')
        ->fields(array(
          'LDAPfield' => $values['LDAPfield_' . $i],
          'LDAPfield_value' => $values['LDAPfield_value_' . $i],
          'synctype' => $values['synctype_' . $i],
          'synctype_value' => $values['synctype_value_' . $i],
          'synctype_value_extra' => $values['synctype_extra_value_' . $i],
        ))
        ->execute();
    }
  }

  for ($i = 0; $i < $values['count_extra_mapping']; $i++) {
    if ($values["synctype_value_extra_" . $i] != '0' && $values["LDAPfield_value_extra_" . $i] != '0' && $values["synctype_extra_value_extra_" . $i] != '0') {
      db_insert('ecas_sync_mapping')
        ->fields(array(
          'LDAPfield' => $values['LDAPfield_extra_' . $i],
          'LDAPfield_value' => $values['LDAPfield_value_extra_' . $i],
          'synctype' => $values['synctype_extra_' . $i],
          'synctype_value' => $values['synctype_value_extra_' . $i],
          'synctype_value_extra' => $values['synctype_extra_value_extra_' . $i],
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
function eacs_group_sync_get_row_group($id, $ldap_field, $synctype, $ldap_field_value = 0, $synctype_value = 0, $synctype_value_extra = 0) {
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
    '#options' => $none_option + ecas_group_sync_get_groups(),
    '#default_value' => $synctype_value,
    '#title' => $synctype,
    '#ajax' => array(
      'callback' => 'ecas_group_sync_update_og_roles',
      'wrapper' => 'synctype_extra_value_' . $id,
    ),
  );
  $form['synctype_' . $id] = array(
    '#type'  => 'hidden',
    '#value'  => $synctype,
  );

  $form['synctype_extra_value_wrapper_' . $id] = array(
    '#prefix' => '<div id="synctype_extra_value_' . $id . '">',
    '#suffix' => '</div></div>',
  );

  $select_options = $none_option;
  $synctype_node = node_load($synctype_value);
  if ($synctype_node) {
    $select_options += ecas_group_sync_get_og_roles($synctype_node->nid, $synctype_node->type);
  }
  $form['synctype_extra_value_wrapper_' . $id]['synctype_extra_value_' . $id] = array(
    '#type' => 'select',
    '#options' => $select_options,
    '#title' => 'group role',
    '#default_value' => $synctype_value_extra,
    // Disable the form element when no group is selected.
    '#states' => array(
      'disabled' => array(
        ':input[name="synctype_value_' . $id . '"]' => array('value' => '0'),
      ),
    ),
  );

  return $form;
}

/**
 * AJAX callback to update OG roles select list regarding the group selected.
 *
 * @see eacs_group_sync_get_row_group()
 */
function ecas_group_sync_update_og_roles($form, &$form_state) {
  $none_option = array("0" => 'none');

  // Get og roles corresponding to the DG.
  $group_id = $form_state['triggering_element']['#value'];
  $corresponding_og_roles = array();
  $group_node = node_load($group_id);
  if ($group_node) {
    $corresponding_og_roles = ecas_group_sync_get_og_roles($group_node->nid, $group_node->type);
  }
  $select_options = $none_option + $corresponding_og_roles;

  if (count($form_state['triggering_element']['#array_parents']) > 3) {
    // Check if the callback comes from the extra fields or from the existing
    // fields.
    $id = $form_state['triggering_element']['#array_parents'][2];
    // Update the OG roles select list.
    $form['group_mapping']['group_mapping_add_wrapper'][$id]['synctype_extra_value_wrapper_extra_' . $id]['synctype_extra_value_extra_' . $id]['#options'] = $select_options;
    return $form['group_mapping']['group_mapping_add_wrapper'][$id]['synctype_extra_value_wrapper_extra_' . $id];
  }
  else {
    $id = $form_state['triggering_element']['#array_parents'][1];
    // Update the OG roles select list.
    $form['group_mapping'][$id]['synctype_extra_value_wrapper_' . $id]['synctype_extra_value_' . $id]['#options'] = $select_options;
    return $form['group_mapping'][$id]['synctype_extra_value_wrapper_' . $id];
  }
}

/**
 * Get all the OG groups.
 *
 * @return array
 *   An associative array of OG groups, keyed on group ID.
 */
function ecas_group_sync_get_groups() {
  $list_groups = og_get_all_group();
  foreach ($list_groups as $gid) {
    $node = node_load($gid);
    $groups[$gid] = $node->title;
  }
  return $groups;
}

/**
 * Get OG roles.
 *
 * @return array
 *   An associative array with the role id as the key and the role name as
 *   value. The anonymous and authenticated default roles are on the top of the
 *   array.
 */
function ecas_group_sync_get_og_roles($gid = 0, $bundle = 'community') {
  return og_roles('node', $bundle, $gid);
}
