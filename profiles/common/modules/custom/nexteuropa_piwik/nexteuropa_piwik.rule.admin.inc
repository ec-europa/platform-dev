<?php

/**
 * @file
 * Callbacks used by the administration area.
 */

use Drupal\nexteuropa_piwik\Entity\PiwikRule;

/**
 * Generates the Next Europa PIWIK rule editing form.
 */
function nexteuropa_piwik_rule_form($form, &$form_state, $piwik_rule, $op = 'edit', $entity_type = NULL) {
  // Adjusting the form page title.
  drupal_set_title(t("@operation the Next Europa PIWIK rule", array('@operation' => drupal_ucfirst($op))));

  $form['rule_section'] = array(
    '#title' => t('Site section'),
    '#type' => 'textfield',
    '#default_value' => isset($piwik_rule->rule_section) ? $piwik_rule->rule_section : '',
    '#required' => TRUE,
    '#description' => t('Enter the name of the site section.'),
  );

  // Preparing the PIWIK rule language options.
  $options = array('all' => t('All'));
  $options = array_merge($options, locale_language_list());

  $form['rule_language'] = array(
    '#title' => t('Language'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => isset($piwik_rule->rule_language) ? $piwik_rule->rule_language : 'all',
    '#required' => TRUE,
    '#description' => t(
      'Select the language for the section. You can use "All" if the given rule
      should be applied for all languages.'
    ),
  );

  // Setting up default rule path type.
  $rule_path_type_default_value = isset($piwik_rule->is_new) ? $piwik_rule::DIRECT_PATH : (string) $piwik_rule->rule_path_type;
  $form['rule_type'] = array(
    '#title' => t('Select rule type'),
    '#type' => 'radios',
    '#options' => array(
      $piwik_rule::DIRECT_PATH => t('Direct path'),
      $piwik_rule::REGEXP_PATH => t('Path based on regular expression'),
    ),
    '#limit_validation_errors' => array(),
    '#default_value' => $rule_path_type_default_value,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'nexteuropa_piwik_rule_path_type_selection',
      'wrapper' => 'specifics-for-piwik-rule-path-type',
    ),
  );

  // This fieldset just serves as a container for the part of the form
  // that gets rebuilt.
  $form['specifics'] = array(
    '#type' => 'item',
    '#prefix' => '<div id="specifics-for-piwik-rule-path-type">',
    '#suffix' => '</div>',
  );

  // Setting up the dynamic values based on the PIWIK rule type.
  $rule_path_type = '';
  $rule_path_desc = '';
  switch ($op) {
    case 'add':
      if (isset($form_state['values'])) {
        $rule_path_type = $form_state['values']['rule_type'];
        $rule_path_desc = _nexteuropa_piwik_rule_path_description($rule_path_type);
      }
      else {
        $rule_path_type = $piwik_rule::DIRECT_PATH;
        $rule_path_desc = _nexteuropa_piwik_rule_path_description($rule_path_type);
      }
      break;

    case 'edit':
      if (isset($form_state['values'])) {
        $rule_path_type = $form_state['values']['rule_type'];
        $rule_path_desc = _nexteuropa_piwik_rule_path_description($rule_path_type);
      }
      else {
        $rule_path_type = $piwik_rule->rule_path_type;
        $rule_path_desc = _nexteuropa_piwik_rule_path_description($rule_path_type);
      }

      break;
  }

  $form['specifics']['rule_path'] = array(
    '#title' => t('Site path'),
    '#type' => 'textfield',
    '#default_value' => isset($piwik_rule->rule_path) ? $piwik_rule->rule_path : '',
    '#required' => TRUE,
    '#description' => $rule_path_desc,
  );

  $form['rule_path_type'] = array(
    '#type' => 'value',
    '#value' => $rule_path_type,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Ajax callback triggered when the cache purge type is changed.
 */
function nexteuropa_piwik_rule_path_type_selection($form, $form_state) {
  return $form['specifics'];
}


/**
 * Form API submit callback for the cache purge rule editing form.
 */
function nexteuropa_piwik_rule_form_submit(&$form, &$form_state) {
  // Building and saving the PIWIK rule entity.
  $piwik_rule = entity_ui_form_submit_build_entity($form, $form_state);
  entity_save('nexteuropa_piwik_rule', $piwik_rule);

  // Redirecting a user to the PWIKI rules admin page.
  $form_state['redirect'] = 'admin/config/system/webtools/piwik/advanced_rules';
}

/**
 * Get the description for the PIWIK rule path field.
 *
 * @param string $rule_path_type
 *   PIWIK rule patt type.
 *
 * @return string $description
 *   Description for the field.
 */
function _nexteuropa_piwik_rule_path_description($rule_path_type) {
  $description = '';
  switch ($rule_path_type) {
    case PiwikRule::DIRECT_PATH:
      $description = t('Enter the direct path for the rule. The path should be relative to the base URL. <br/> Example: "content/test-page"');
      break;

    case PiwikRule::REGEXP_PATH:
      $wildcard_descriptions = array(
        t('"^admin/*" - All administrative pages'),
        t('"^content/*" - All pages following "content" part in the path'),
      );
      $description = '<p>' . t('Enter the regular expression path pattern for the rule.') . '</p>';
      $description .= '<p>' . t('You can check your expression at the
        <a href="@regex101">Regex101 page</a>.',
          array('@regex101' => 'https://regex101.com')
        ) . '</p>';
      $description .= '<p>' . t('Below you can find some examples:') . '</p>';
      $wildcard_description = array(
        '#theme' => 'item_list',
        '#type' => 'ul',
        '#items' => $wildcard_descriptions,
      );
      $description .= drupal_render(
        $wildcard_description
      );
      break;
  }

  return $description;
}
