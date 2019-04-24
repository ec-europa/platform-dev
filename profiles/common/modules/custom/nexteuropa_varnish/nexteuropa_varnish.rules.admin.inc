<?php

/**
 * @file
 * Callbacks used by the administration area.
 */

use Drupal\nexteuropa_varnish\PurgeRuleType;

/**
 * Generates the cache purge rule editing form.
 */
function nexteuropa_varnish_cache_purge_rule_form($form, &$form_state, $purge_rule, $op = 'edit', $entity_type = NULL) {
  $all = array('all' => 'All');
  $form['content_type'] = array(
    '#title' => t('Content Type'),
    '#type' => 'select',
    '#empty_option' => '',
    '#options' => $all + node_type_get_names(),
    '#default_value' => isset($purge_rule->content_type) ? $purge_rule->content_type : '',
    '#required' => TRUE,
  );

  $type_default_value = isset($purge_rule->is_new) ? PurgeRuleType::PATHS : (string) $purge_rule->type();

  $form['rule_type'] = array(
    '#title' => t('What should be purged'),
    '#type' => 'radios',
    '#options' => _nexteuropa_varnish_get_rule_types(),
    '#limit_validation_errors' => array(),
    '#default_value' => $type_default_value,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'nexteuropa_varnish_cache_purge_rule_type_selection',
      'wrapper' => 'specifics-for-cache-purge-type',
    ),
  );

  // This fieldset just serves as a container for the part of the form.
  // that gets rebuilt.
  $form['specifics'] = array(
    '#type' => 'item',
    '#prefix' => '<div id="specifics-for-cache-purge-type">',
    '#suffix' => '</div>',
  );
  // Code here to populate the scope container.
  // @TODO views paths?
  if (isset($form_state['scope'])) {
    $warning = '<h2>Here is the 100 first results matching your regex</h2>';
    $warning .= '<h3>Your rule was not saved, to save it click "Save" button</h3>';
    $form['scope']['#prefix'] = '<div class="messages status">';
    $form['scope']['#suffix'] = '</div>';
    $form['scope']['#markup'] = $warning . $form_state['scope'];
  }

  $current_rule_type = isset($form_state['values']['rule_type']) ? $form_state['values']['rule_type'] : $type_default_value;

  $form['actions'] = array('#type' => 'actions');

  if ($current_rule_type === PurgeRuleType::PATHS) {
    $form['specifics']['paths'] = array(
      '#title' => t('Paths'),
      '#type' => 'textarea',
      '#default_value' => isset($purge_rule->paths) ? $purge_rule->paths : '',
      '#attributes' => array(
        'placeholder' => t('Enter one regular expression per line'),
      ),
      '#required' => TRUE,
      '#description' => _nexteuropa_varnish_paths_description(),
    );
    $form['specifics']['actions']['check_scope'] = array(
      '#type' => 'submit',
      '#value' => t('Check scope'),
      '#submit' => array('_nexteuropa_varnish_check_scope'),
      '#weight' => 41,
    );
    $form['#validate'][] = '_nexteuropa_varnish_regex_validate';
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  );

  $form['actions']['cancel'] = array(
    '#type' => 'item',
    '#markup' => l(t('Cancel'), 'admin/config/system/nexteuropa-varnish/purge_rules'),
    '#weight' => 42,
  );
  return $form;
}

/**
 * Custom validate function, checks if regex is valid.
 */
function _nexteuropa_varnish_regex_validate($form, &$form_state) {
  $regex = _nexteuropa_varnish_gather_expressions($form_state['values']['paths']);
  if (@preg_match('/' . $regex . '/', NULL) === FALSE) {
    form_set_error('specifics', t('Regex is invalid. <br> Please check your expression at the
        <a href="@regex101">Regex101 page</a>.',
          array('@regex101' => 'https://regex101.com')
        ));
  }
}

/**
 * Custom function checks which site URLs match the regex pattern.
 */
function _nexteuropa_varnish_check_scope(&$form, &$form_state) {
  $output = '';
  $regex = _nexteuropa_varnish_gather_expressions($form_state['values']['paths']);
  $query = db_select('url_alias', 'u')
    ->fields('u');
  $or = db_or();
  $or->condition('alias', $regex, 'REGEXP');
  $query->condition($or);
  $query = $query->extend('PagerDefault')->limit(100);
  $results = $query->execute();

  $headers = array('URL alias');
  $rows = array();
  foreach ($results as $u) {
    $rows[] = array($u->alias);
  }
  if (!empty($rows)) {
    $output = theme('table', array('header' => $headers, 'rows' => $rows)) . theme('pager');
  }

  $form_state['rebuild'] = TRUE;
  $form_state['scope'] = $output;
}

/**
 * Custom function that gather the regex entered into one single expression.
 */
function _nexteuropa_varnish_gather_expressions($paths) {
  $regex = preg_split("/[\r\n]+/", $paths);
  $regex = implode('|', $regex);
  return $regex;
}

/**
 * Ajax callback triggered when the cache purge type is changed.
 */
function nexteuropa_varnish_cache_purge_rule_type_selection($form, $form_state) {
  return $form['specifics'];
}

/**
 * Get the description for the purge paths field.
 *
 * @return string
 *   Description for the field.
 */
function _nexteuropa_varnish_paths_description() {
  $regex_descriptions = array(
    t('Add ^ at the begining of each path, unless you want to match using part of the path. <br>Example : ^content\/article\/(how-to-.*|faqs\/.*) will match <b>content/article/how-to-use-regex</b> and <b>content/article/faqs/using-regex</b> but not <b>my-content/article/how-to-use-regex</b>'),
    t('You can test your site URLs matching the regex by clicking the <b>Check scope</b> button.'),
    t('Regex validation is done at save. For example, if you try saving <b>*</b> alone, you will get an error.'),
  );

  $description = '<p>' . t('You can check your expression at the
        <a href="@regex101">Regex101 page</a>.',
          array('@regex101' => 'https://regex101.com')
        ) . '</p>';
  $wildcard_description = array(
    '#theme' => 'item_list',
    '#type' => 'ul',
    '#items' => $regex_descriptions,
  );

  $description .= drupal_render(
    $wildcard_description
  );

  return $description;
}

/**
 * Form API submit callback for the cache purge rule editing form.
 */
function nexteuropa_varnish_cache_purge_rule_form_submit(&$form, &$form_state) {
  if ($form_state['values']['rule_type'] !== PurgeRuleType::PATHS) {
    $form_state['values']['paths'] = '';
  }
  $purge_rule = entity_ui_form_submit_build_entity($form, $form_state);
  entity_save('nexteuropa_varnish_cache_purge_rule', $purge_rule);

  $form_state['redirect'] = 'admin/config/system/nexteuropa-varnish/purge_rules';
}

/**
 * Returns the options array with the purge rule types.
 */
function _nexteuropa_varnish_get_rule_types() {
  // Remove option if the default purge rule is enabled to prevent an
  // overlapping rules. There is no need of the 'NODE' type because default
  // rule works for all of the content types.
  if (variable_get('nexteuropa_varnish_default_purge_rule', FALSE)) {
    return array(
      PurgeRuleType::PATHS => t('A specific list of regex'),
    );
  }

  return array(
    PurgeRuleType::NODE => t('Paths of the node the action is performed on'),
    PurgeRuleType::PATHS => t('A specific list of regex'),
  );
}
