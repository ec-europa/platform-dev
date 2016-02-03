<?php
/**
 * @file
 * Contains nexteuropa_remote.pages.inc.
 */

use \Drupal\nexteuropa_remote\Entity\RemoteEntity;

/**
 * Generates the entity editing form.
 */
function nexteuropa_remote_entity_form($form, &$form_state, RemoteEntity $entity, $op = 'edit') {

  $form['label'] = [
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => isset($entity->label) ? $entity->label : '',
    '#description' => t('The label associated with the remote entity.'),
    '#required' => TRUE,
    '#weight' => -15,
  ];

  $form['created'] = [
    '#type' => 'textfield',
    '#title' => t('Creation date'),
    '#default_value' => isset($entity->created) ? format_date($entity->created, 'short') : '',
    '#description' => t('The date when the remote entity was created.'),
    '#required' => TRUE,
    '#weight' => -14,
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

  $form['actions']['delete'] = [
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#weight' => 45,
    '#limit_validation_errors' => [],
    '#submit' => ['nexteuropa_remote_entity_form_submit_delete'],
    '#access' => ($op != 'add' && $op != 'clone') && nexteuropa_remote_access('delete', $entity)
  ];

  field_attach_form('nexteuropa_remote_entity', $entity, $form, $form_state);

  return $form;
}

/**
 * entity editing form validation callback.
 */
function nexteuropa_remote_entity_form_validate(&$form, &$form_state) {
  entity_form_field_validate('entity', $form, $form_state);
}

/**
 * Form API submit callback for the entity form.
 */
function nexteuropa_remote_entity_form_submit(&$form, &$form_state) {
  $form_state['values']['created'] = REQUEST_TIME;
  /** @var RemoteEntity $entity */
  $entity = entity_ui_form_submit_build_entity($form, $form_state);
  $entity->save();
  $form_state['redirect'] = 'admin/structure/remote-entities';
}

/**
 * Form API submit callback for the delete button.
 */
function nexteuropa_remote_entity_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'remote-entity/' . $form_state['entity']->id . '/delete';
}
