<?php

/**
 * @file
 * Administrative functions for Selfish Varnish.
 */

define('SELFISH_VARNISH_MAX_PATH', 5);

/**
 * Implements hook_form().
 *
 * Menu callback describing a form which enables users to invalidate specific
 * entries from Varnish.
 */
function selfish_varnish_invalidate_form() {

  $form = array();

  if (!_selfish_varnish_check_purge_function(TRUE)) {
    return $form;
  }

  // Fieldset for paths.
  $form['selfish_varnish_path_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choose paths to be invalidated'),
    '#collapsible' => TRUE,
  );
  for ($i = 1; $i <= constant('SELFISH_VARNISH_MAX_PATH'); ++$i) {
    $form['selfish_varnish_path_fieldset']['path' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Path :num:', array(':num' => $i)),
      '#label' => t(
          'for example :base_path/foo',
          array(':base_path' => _selfish_varnish_base_path())
      ),
    );
    $form['selfish_varnish_path_fieldset']['wildcard' . $i] = array(
      '#type' => 'checkbox',
      '#title' => t('Path :path_id is wildcard', array(':path_id' => $i)),
      '#default_value' => 0,
    );
  }
  $form['selfish_varnish_path_fieldset']['info'] = array(
    '#markup' => t(
        '
      <ul>
        <li>Paths which do not start with :base_path will be ignored</li>
        <li>
            Multiple slashes are handled automatically; for example stating
            foo/bar is enough to invalidate foo/bar, foo//bar and foo/bar/ )
        </li>
        <li>
            If "Wildcard" is checked, all URLs starting with the provided path
            will be invalidated.
        </li>
      </ul>',
        array(':base_path' => _selfish_varnish_base_path())
    ),
  );

  $form['selfish_varnish_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Invalidate paths above'),
  );
  if (!variable_get('selfish_varnish_disable_big_red_button', FALSE)) {
    $form['big_red_button'] = array(
      '#type' => 'submit',
      '#value' => t('Invalidate everything'),
      '#submit' => array('_selfish_varnish_invalidate_everything'),
    );
  }
  return $form;
}

/**
 * Handle validation of the form defined by selfish_varnish_invalidate_form.
 */
function selfish_varnish_invalidate_form_validate($form, &$form_state) {

  // Check paths only when the "Invalidate paths above" button was clicked.
  if ($form_state['input']['op'] === t('Invalidate paths above')) {
    _selfish_varnish_check_paths($form_state);
  }
}

/**
 * Handle submission of the form defined by selfish_varnish_invalidate_form.
 */
function selfish_varnish_invalidate_form_submit($form, &$form_state) {

  if (!_selfish_varnish_check_purge_function(TRUE)) {
    return;
  }

  $cache = new FlexiblePurgeCache('cache_page');

  // First trigger a clear operation on the actual backend cache, if any.
  $backend = $cache->keepCachingObject();
  if (!is_null($backend)) {
    $backend->clear(NULL, FALSE);
  }

  $provided_paths = _selfish_varnish_get_submitted_paths($form_state);
  $cache->emitRequests($provided_paths['path'], $provided_paths['wildcard']);
  drupal_set_message(t('Triggered fine-grained frontend cache invalidation.'));
}

/**
 * Check paths posted by users.
 *
 * @param array $form_state
 *   Form state from selfish_varnish_invalidate_form().
 *
 * @return mixed
 *   Either FALSE if an error occurred or a verified array of paths that
 *   can be used directly to compose the final Varnish command.
 */
function _selfish_varnish_check_paths($form_state) {

  $provided_paths = _selfish_varnish_get_submitted_paths($form_state);

  // Ensure at least one path was submitted.
  if (empty($provided_paths['path'])) {
    form_set_error('path1', 'You must provide at least one path.');
    return FALSE;
  }

  // Reject paths which do not start with the site's base path.
  foreach ($provided_paths['path'] as $path_key => $path) {
    if (strpos($path, _selfish_varnish_base_path()) !== 0) {
      form_set_error(
            'path' . $path_key,
            t(
                'All paths should start with the :base_path base path',
                array(':base_path' => _selfish_varnish_base_path())
            )
        );
      return FALSE;
    }
  }

  // Reject paths which contain double quotes.
  foreach ($provided_paths['path'] as $path_key => $path) {
    if (strpos($path, '"') !== FALSE) {
      form_set_error(
            'path' . $path_id,
            t(
                'Paths should not contain double quotes.',
                array(':base_path', _selfish_varnish_base_path())
            )
        );
      return FALSE;
    }
  }

  return $provided_paths;
}

/**
 * Return the paths submitted by users through the form.
 *
 * @param array $form_state
 *   Form state from selfish_varnish_invalidate_form_validate().
 *
 * @return array
 *   An array of non-empty submitted paths.
 */
function _selfish_varnish_get_submitted_paths($form_state) {

  $provided_paths = array(
    'path' => array(),
    'wildcard' => array(),
  );
  for ($i = 1; $i <= constant('SELFISH_VARNISH_MAX_PATH'); ++$i) {
    if (isset($form_state['values']['path' . $i], $form_state['values']['wildcard' . $i])) {
      if (drupal_strlen(trim($form_state['values']['path' . $i]))) {
        $provided_paths['path'][$i] = $form_state['values']['path' . $i];
        $provided_paths['wildcard'][$i] = $form_state['values']['wildcard' . $i];
      }
    }
  }
  return $provided_paths;
}

/**
 * Handler called when the "big red button" was clicked.
 */
function _selfish_varnish_invalidate_everything($form, $form_state) {

  _selfish_varnish_force_invalidation(TRUE);
}
