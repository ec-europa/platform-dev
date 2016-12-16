<?php
/**
 * @file
 * Form settings for Multisite Review.
 */

/**
 * Return a setting form to choose which modules to review.
 *
 * @return mixed
 *   Return form with additional buttons.
 */
function multisite_review_form($form, &$form_state) {
  $enabled_modules = _get_enabled_modules();

  $form['what_to_review'] = array(
    '#title' => 'Candidates for reviewing',
    '#description' => 'Select what custom modules should be reviewed',
    '#type' => 'checkboxes',
    '#options' => array_combine($enabled_modules, $enabled_modules),
    '#default_value' => variable_get('what_to_review', 'what_to_review'),
  );

  return system_settings_form($form);
}

/**
 * Helper to provide enabled modules.
 *
 * @return array
 *   Returns enabled modules.
 */
function _get_enabled_modules() {
  module_load_include('inc', 'multisite_review', 'multisite_review_module');
  $result = array();
  $module_list = module_list();
  foreach ($module_list as $module_name) {
    $module = new MultisiteReviewModule($module_name);

    // Only check custom modules.
    if (!$module->isCustom()) {
      continue;
    }
    $result[] = $module->getName();
  }

  return $result;
}
