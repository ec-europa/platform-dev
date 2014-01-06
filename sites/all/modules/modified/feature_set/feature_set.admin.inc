<?php
/**
 * @file
 * Administration forms for feature_sets.
 */

/**
 * Define the administration form
 */
function feature_set_admin_form($form, &$form_state, $install_state = NULL) {
  $featuresets = feature_set_get_featuresets($install_state);

  $form = array();

  if (!empty($install_state)) {
    // indicate we are in an install
    $form['install'] = array(
      '#type' => 'value',
      '#value' => TRUE
    );
  }

  // Really too bad tableselect has no easy way to disable a single checkbox...
  if (!empty($featuresets)) {
    foreach ($featuresets as $featureset => $details) {
      if ( !$details['meta']) {
        $elementname = 'featureset-' . $featureset;
        $form[$elementname] = array(
          '#type' => 'checkbox',
          '#disabled' => (empty($details['status']) || is_requiredby($featureset) || requires($featureset) ) ? TRUE : FALSE, // disabled the widget if its in an inconsistent
          '#default_value' => (FEATURE_SET_ENABLED & $details['status']) ? 1 : 0,
          '#featuresetinfo' => array(
            'featureset' => $details['title'],
            'description' => $details['description'] . get_require($featureset),
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

  $form['#submit'][] = 'feature_set_admin_form_submit';
  $form['#submit'][] = 'feature_set_adjust_meta_feature_sets';

  return $form;
}

/**
 * Theme the administration form
 *
 * Tableselect does not have a method to easily disable a single checkbox.
 */
function theme_feature_set_admin_form($form) {
  $form = array_pop($form);
  $header = array('', 'Feature Set', 'status');

  $rows = array();
  foreach (element_children($form) as $key) {
    if (strpos($key, 'featureset-') === 0) {
      // set the icon if available.
      if (!empty($form[$key]['#featuresetinfo']['icon'])) {
        $variables = array(
          'path' => $form[$key]['#featuresetinfo']['icon'],
          'alt' => t('@feature-set icon', array('@feature-set' => $form[$key]['#featuresetinfo']['featureset'])),
          'attributes' => array(),
        );
        $icon = '<div class="feature-set-image">' . theme_image($variables) . '</div>';
      }
      else {
        $icon = '';
      }
      if (!empty($form[$key]['#featuresetinfo']['font'])) {
        $icon = '<div class="feature-set-image ' . $form[$key]['#featuresetinfo']['font'] . '"></div>';
      }
      $featureset = '<blockquote>';
      $featureset .= '<p>' . $form[$key]['#featuresetinfo']['featureset'] . '</p>';
      if (!empty($form[$key]['#featuresetinfo']['description'])) {
        $featureset .= '<small>' . $form[$key]['#featuresetinfo']['description'] . '</small>';
      }
      $featureset .= '</blockquote>';

      $row = array(
        'data' => array(
          array('data' => $icon . $featureset, 'class' => array('feature')),
          array('data' => drupal_render($form[$key]), 'class' => array('switcher')),
        ),
      );

      // set category if available
      if (!empty($form[$key]['#featuresetinfo']['category'])) {
        $rows[$form[$key]['#featuresetinfo']['category']][] = $row;
      }
      else {
        $rows['Uncategorized'][] = $row;
      }
    }
  }
  ksort($rows);

  $output = '<div class="row">';

  $output_left = '<div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">';
  $output_left .= '<ul class="list-group nav nav-tabs nav-stacked">';

  $output_right = $output_left;

  $first_column = 1;
  foreach ($rows as $key => $value) {
    if ($first_column) {
      $output_left .= '<li><a class="list-group-item feature-set-category">' . t($key) . '</a><div class="feature-set-content">' . theme('table', array('header' => $header, 'rows' => $value, 'attributes' => array('class' => array('table', 'table-striped', 'table-hover')))) . '</div></li>';
    } else {
      $output_right .= '<li><a class="list-group-item feature-set-category">' . t($key) . '</a><div class="feature-set-content">' . theme('table', array('header' => $header, 'rows' => $value, 'attributes' => array('class' => array('table', 'table-striped', 'table-hover')))) . '</div></li>';
    }
    
    $first_column = 1 - $first_column;
  }

  $output_left .= '</ul></div>';
  $output_right .= '</ul></div>';
  $output .= $output_left . $output_right . '</div>';

  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Submit handler for our form
 *
 * This only processes feature sets that are in a known state.
 */
function feature_set_admin_form_submit($form, &$form_state) {
  $featuresets = feature_set_get_featuresets();
  $operations = array();
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'featureset-') === 0) {
      $featureset = str_replace('featureset-', '', $key);
      // only operate if its in an 'OK' status
      if ( isset($featuresets[$featureset]) && $featuresets[$featureset]['status'] != 0) {
        if ($form_state['values'][$key]) {
          if (!module_exists($featureset)) // do not enable a module already enabled
            $operations[] = array('feature_set_enable_feature_set', array($featuresets[$featureset]));
        }
        else {
          if (module_exists($featureset)) // do not disable a module already disabled
            $operations[] = array('feature_set_disable_feature_set', array($featuresets[$featureset]));
        }
      }
    }

  }

  if (!empty($operations)) {
    // we might be in an install profile an thus have another batch active
    // use batch system to enable features
    $_SESSION['http_request_count'] = 0;
    $batch = _feature_set_batch($operations);
    $batch['title'] = t('Adjusting feature sets.');
    $batch['finished'] = 'drupal_flush_all_caches';
    if (empty($form_state['values']['install'])) {
      batch_set($batch);
    }
    else {
      // store the feature sets to enable in session so we can get them back later
      $_SESSION['feature_set_batch'] = $batch;
    }
  }
}

/**
 * Function feature_set_adjust_meta_feature_sets().
 */
function feature_set_adjust_meta_feature_sets($form, &$form_state) {
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
    // we might be in an install profile an thus have another batch active
    $batch['operations'] = $operations;
    $batch['title'] = t('Adjusting meta feature sets.');
    $batch['finished'] = 'drupal_flush_all_caches';
    watchdog('debug', '<pre>' . var_export($batch, 1) . '</pre>');
    if (empty($form_state['values']['install'])) {
      batch_set($batch);
    }
    else {
      // store the feature sets to enable in session so we can get them back later
      $_SESSION['feature_set_meta_batch'] = $batch;
    }
  }

}

/**
 * Function feature_set_install_enable().
 */
function feature_set_install_enable() {
  if (!empty($_SESSION['feature_set_batch'])) {
    return $_SESSION['feature_set_batch'];
  }
}

/**
 * Function feature_set_meta_install_enable().
 */
function feature_set_meta_install_enable() {
  if (!empty($_SESSION['feature_set_meta_batch'])) {
    return $_SESSION['feature_set_meta_batch'];
  }
}

/**
 * Return install time tasks
 */
function feature_set_install_tasks() {
  $tasks = array(
    'feature_set_admin_form' => array(
      'display_name' => st('Feature Set Options'),
      'type' => 'form'
    ),
    'freature_set_install_modules' => array(
      'display' => FALSE,
      'type' => 'batch',
      'function' => 'feature_set_install_enable',
    ),
    'feature_set_install_meta_feature_sets' => array(
      'display' => FALSE,
      'type' => 'batch',
      'function' => 'feature_set_meta_install_enable',
    ),
  );
  return $tasks;
}

/**
 * Disable a feature set, intended to disable an inconsinstent feature set.
 */
function feature_set_disable_url() {
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
function feature_set_enable_url() {
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
