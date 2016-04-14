<?php
/**
 * @file
 * Contains nexteuropa_remote.pages.inc.
 */

use \Drupal\nexteuropa_remote\Entity\RemoteEntity;

/**
 * Bean view page.
 */
function nexteuropa_remote_view_page(RemoteEntity $entity) {
  $title = $entity->label();
  drupal_set_title($title);
  return nexteuropa_remote_view($entity);
}

/**
 * Menu callback; presents the node editing form.
 */
function nexteuropa_remote_edit_page(RemoteEntity $entity) {
  drupal_set_title(t('Edit @label', ['@label' => $entity->label()]));
  return drupal_get_form('nexteuropa_remote_form', $entity);
}

/**
 * Generates the entity editing form.
 */
function nexteuropa_remote_form($form, &$form_state, RemoteEntity $entity, $op = 'edit') {

  foreach (['id', 'revision_id', 'uid', 'type', 'language'] as $key) {
    $form[$key] = [
      '#type' => 'value',
      '#value' => isset($entity->$key) ? $entity->$key : NULL,
    ];
  }

  $form['label'] = [
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => isset($entity->label) ? $entity->label : '',
    '#description' => t('The label associated with the remote entity.'),
    '#required' => TRUE,
    '#weight' => -15,
  ];

  $form['status'] = [
    '#type' => 'checkbox',
    '#title' => t('Activate this remote entity'),
    '#default_value' => !empty($entity->status),
    '#weight' => -10,
  ];

  $form['actions'] = ['#type' => 'actions'];
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  ];

  $delete_access = ($op != 'add' && $op != 'clone') && nexteuropa_remote_access('delete', $entity);
  $form['actions']['delete'] = [
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#weight' => 45,
    '#limit_validation_errors' => [],
    '#submit' => ['nexteuropa_remote_form_submit_delete'],
    '#access' => $delete_access,
  ];

  field_attach_form('nexteuropa_remote', $entity, $form, $form_state);
  return $form;
}

/**
 * Entity editing form validation callback.
 */
function nexteuropa_remote_form_validate(&$form, &$form_state) {
  entity_form_field_validate('nexteuropa_remote', $form, $form_state);
}

/**
 * Form API submit callback for the entity form.
 */
function nexteuropa_remote_form_submit(&$form, &$form_state) {
  $entity = (object) $form_state['values'];
  entity_form_submit_build_entity('nexteuropa_remote', $entity, $form, $form_state);
  entity_save('nexteuropa_remote', $entity);
  $form_state['redirect'] = 'admin/structure/remote-entities';
}

/**
 * Form API submit callback for the delete button.
 */
function nexteuropa_remote_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'remote-entity/' . $form_state['entity']->id . '/delete';
}
