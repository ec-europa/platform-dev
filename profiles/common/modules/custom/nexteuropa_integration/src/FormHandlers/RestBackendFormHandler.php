<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_integration\FormHandlers\Backend\RestBackendFormHandler.
 */

namespace Drupal\nexteuropa_integration\FormHandlers\Backend;

use Drupal\integration_ui\FormHandlers\Backend\AbstractBackendFormHandler;
use Drupal\integration_ui\FormHelper;
use Drupal\integration\Backend\Configuration\BackendConfiguration;

/**
 * Class RestBackendFormHandler.
 *
 * @method BackendConfiguration getConfiguration(array &$form_state)
 *
 * @package Drupal\integration_ui\FormHandlers\Backend
 */
class RestBackendFormHandler extends AbstractBackendFormHandler {

  /**
   * {@inheritdoc}
   */
  public function resourceSchemaForm($machine_name, array &$form, array &$form_state, $op) {
    $configuration = $this->getConfiguration($form_state);
    $form['endpoint'] = FormHelper::textField(t('Resource endpoint'), $configuration->getResourceEndpoint($machine_name));
    $form['changes'] = FormHelper::textField(t('Change feed endpoint'), $configuration->getResourceChangeFeed($machine_name));
  }

  /**
   * {@inheritdoc}
   */
  public function form(array &$form, array &$form_state, $op) {
    $configuration = $this->getConfiguration($form_state);
    $form['base_url'] = FormHelper::textField(t('Base URL'), $configuration->getPluginSetting('backend.base_url'));
    $form['backend_id'] = FormHelper::textField(t('Backend ID endpoint'), $configuration->getPluginSetting('backend.backend_id'));
  }

  /**
   * {@inheritdoc}
   */
  public function formSubmit(array $form, array &$form_state) {

  }

  /**
   * {@inheritdoc}
   */
  public function formValidate(array $form, array &$form_state) {

  }

}
