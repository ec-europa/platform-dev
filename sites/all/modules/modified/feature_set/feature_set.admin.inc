<?php
/**
 * @file
 * Administration forms for feature_sets.
 */

/**
 * Define the administration form.
 */
function feature_set_admin_form($form, &$form_state, $install_state = NULL) {
  $featuresets = feature_set_get_featuresets($install_state);

  $form = array();

  if (!empty($install_state)) {
    // Indicate we are in an install.
    $form['install'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }

  // Really too bad tableselect has no easy way to disable a single checkbox...
  if (!empty($featuresets)) {
    foreach ($featuresets as $featureset => $details) {
      if (!$details['meta']) {
        $elementname = 'featureset-' . $featureset;
        $form[$elementname] = array(
          '#type' => 'checkbox',
          // Disable the widget if its in an inconsistent.
          '#disabled' => (empty($details['status']) || _feature_set_is_requiredby($featureset) || _feature_set_requires($featureset)) ? TRUE : FALSE,
          '#default_value' => (FEATURE_SET_ENABLED & $details['status']) ? 1 : 0,
          '#featuresetinfo' => array(
            'featureset' => $details['title'],
            'description' => $details['description'] . _feature_set_get_require($featureset),
            'icon' => empty($details['icon']) ? '' : $details['icon'],
            'font' => empty($details['font']) ? '' : $details['font'],
            'category' => empty($details['category']) ? '' : $details['category'],
          ),
        );

        if (empty($details['status'])) {
          $info = t('This feature set is in an inconsistent state. Please use the following links to correct the feature set.');
          $variables = array(
            'links' => array(
              'feature-set-enable-link' => array(
                'title' => t('Enable'),
                'href' => 'admin/structure/feature-set/enable/' . $featureset,
              ),
              'feature-set-disable-link' => array(
                'title' => t('Disable'),
                'href' => 'admin/structure/feature-set/disable/' . $featureset,
              ),
            ),
          );
          $form[$elementname]['#featuresetinfo']['status'] = $info . theme('links', $variables);
          $form[$elementname]['#featuresetinfo']['class'] = 'warning';
        }
        else {
          if ($form[$elementname]['#default_value']) {
            $form[$elementname]['#featuresetinfo']['status'] = t('OK');
            $form[$elementname]['#featuresetinfo']['class'] = 'status';
          }
          else {
            $form[$elementname]['#featuresetinfo']['status'] = t('Disabled');
            $form[$elementname]['#featuresetinfo']['class'] = 'disabled';
          }
        }
      }
    }
  }

  $form['#theme'] = 'feature_set_admin_form';

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Validate'),
    '#attributes' => array(
      'class' => array(
        'btn',
        'btn-lg',
        'btn-success',
      ),
    ),
  );

  $form['#submit'][] = '_feature_set_admin_form_submit';
  $form['#submit'][] = '_feature_set_adjust_meta_feature_sets';

  return $form;
}

/**
 * Submit handler for our form.
 *
 * This only processes feature sets that are in a known state.
 */
function _feature_set_admin_form_submit($form, &$form_state) {
  $featuresets = feature_set_get_featuresets();
  $operations = array();
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'featureset-') === 0) {
      $featureset = str_replace('featureset-', '', $key);
      // Only operate if its in an 'OK' status.
      if (isset($featuresets[$featureset]) && $featuresets[$featureset]['status'] != 0) {
        if ($form_state['values'][$key]) {
          // Do not enable a module already enabled.
          if (!module_exists($featureset)) {
            $operations[] = array('feature_set_enable_feature_set', array($featuresets[$featureset]));
          }
        }
        else {
          // Do not disable a module already disabled.
          if (module_exists($featureset)) {
            $operations[] = array('feature_set_disable_feature_set', array($featuresets[$featureset]));
          }
        }
      }
    }
  }

  if (!empty($operations)) {
    // We might be in an install profile an thus have another batch active.
    // Use batch system to enable features.
    $_SESSION['http_request_count'] = 0;
    $batch = _feature_set_batch($operations);
    $batch['title'] = t('Adjusting feature sets.');
    $batch['finished'] = 'drupal_flush_all_caches';
    if (empty($form_state['values']['install'])) {
      batch_set($batch);
    }
    else {
      // Store feature sets to enable in session so we can get them back later.
      $_SESSION['feature_set_batch'] = $batch;
    }
  }
}

/**
 * Function _feature_set_adjust_meta_feature_sets().
 */
function _feature_set_adjust_meta_feature_sets($form, &$form_state) {
  $featuresets = feature_set_get_featuresets();
  $metasets = feature_set_get_meta_feature_sets($form_state);

  if (!empty($metasets['enable'])) {
    foreach ($metasets['enable'] as $enable) {
      $operations[] = array('feature_set_enable_feature_set', array($featuresets[$enable]));
    }
  }
  if (!empty($metasets['disable'])) {
    foreach ($metasets['disable'] as $disable) {
      $operations[] = array('feature_set_disable_feature_set', array($featuresets[$disable]));
    }
  }

  if (!empty($operations)) {
    // We might be in an install profile an thus have another batch active.
    $batch['operations'] = $operations;
    $batch['title'] = t('Adjusting meta feature sets.');
    $batch['finished'] = 'drupal_flush_all_caches';
    watchdog('debug', '<pre>' . var_export($batch, 1) . '</pre>');
    if (empty($form_state['values']['install'])) {
      batch_set($batch);
    }
    else {
      // Store feature sets to enable in session so we can get them back later.
      $_SESSION['feature_set_meta_batch'] = $batch;
    }
  }
}

/**
 * Function _feature_set_install_enable().
 */
function _feature_set_install_enable() {
  if (!empty($_SESSION['feature_set_batch'])) {
    return $_SESSION['feature_set_batch'];
  }
}

/**
 * Function _feature_set_meta_install_enable().
 */
function _feature_set_meta_install_enable() {
  if (!empty($_SESSION['feature_set_meta_batch'])) {
    return $_SESSION['feature_set_meta_batch'];
  }
}

/**
 * Return install time tasks.
 */
function feature_set_install_tasks() {
  $tasks = array(
    'feature_set_admin_form' => array(
      'display_name' => st('Feature Set Options'),
      'type' => 'form',
    ),
    'freature_set_install_modules' => array(
      'display' => FALSE,
      'type' => 'batch',
      'function' => '_feature_set_install_enable',
    ),
    'feature_set_install_meta_feature_sets' => array(
      'display' => FALSE,
      'type' => 'batch',
      'function' => '_feature_set_meta_install_enable',
    ),
  );
  return $tasks;
}

/**
 * Disable a feature set, intended to disable an inconsinstent feature set.
 */
function _feature_set_disable_url() {
  $featureset = arg(4);
  $featuresets = $featuresets = feature_set_get_featuresets();
  if (isset($featuresets[$featureset])) {
    feature_set_disable_feature_set($featuresets[$featureset]);
    drupal_goto('admin/structure/feature-set');
  }
  else {
    return t('The feature set "%featureset" could not be found. Please check the link and try again', array('%featureset' => $featureset));
  }
}

/**
 * Enable a feature set intended to enable an inconsinstent feature set.
 */
function _feature_set_enable_url() {
  $featureset = arg(4);
  $featuresets = $featuresets = feature_set_get_featuresets();
  if (isset($featuresets[$featureset])) {
    feature_set_enable_feature_set($featuresets[$featureset]);
    drupal_goto('admin/structure/feature-set');
  }
  else {
    return t('The feature set "%featureset" could not be found. Please check the link and try again', array('%featureset' => $featureset));
  }
}
