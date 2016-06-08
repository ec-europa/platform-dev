<?php

/**
 * @file
 * Automated QA of Multisite projects, built on the Security Review module.
 */

/**
 * Security Review callback. Performs QA for Multisite projects.
 *
 * @see hook_security_checks()
 * @see multisite_review_security_checks()
 */
function multisite_review_qa() {
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  $results = array();
  // Check if the setting form contain selected modules.
  // If so proceed on these only.
  $target_modules = array();
  foreach (module_list() as $module_name) {
    $module = new MultisiteReviewModule($module_name);
    $selected_modules = $module->getSpecific();
    if (!empty($selected_modules)) {
      $target_modules = $selected_modules;
    }
    else {
      $target_modules = module_list();
    }
  }
  // Loop over the modules and perform the reviews.
  foreach ($target_modules as $module_name) {
    $module = new MultisiteReviewModule($module_name);

    // Only check custom modules.
    if (!$module->isCustom()) {
      continue;
    }

    // Call all reviews declared in the hook and found in reviews folder.
    foreach (module_invoke_all('multisite_review_reviews') as $review => $info) {
      // Include the .inc file from reviews folder if it has been specified.
      if (!empty($info['file'])) {
        if (is_file($file = DRUPAL_ROOT . '/' . $info['file'])) {
          require_once $file;
        }
      }

      // Perform the review by calling all callbacks found.
      $result = $info['callback']($module);
      if (!empty($result)) {
        $results[$module_name][$review] = $result;
      }
    }
  }

  return array('result' => empty($results), 'value' => $results);
}

/**
 * Help callback for Security Review. Provides help for the QA check.
 */
function multisite_review_qa_help($check = NULL, $skipped_message = NULL) {
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  // Retrieve the metadata of the reviews.
  $reviews_info = module_invoke_all('multisite_review_reviews');

  $element = array();
  $element['title'] = t('Basic Multisite QA checks');
  $element['descriptions'][] = t('The modules and features on the Multisite platform should adhere to the standards outlined in the !link.', array('!link' => l(t('Guidelines for feature creation'), 'https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Build+custom+features')));

  if (!empty($skipped_message)) {
    $element['results']['descriptions'][] = $skipped_message;
  }
  elseif ($check && $check['result'] == FALSE) {
    $results_message = t('The following problems were identified:');
    $element['results']['descriptions'][] = $results_message;
    $element['findings']['descriptions'][] = $results_message;

    // Extract and format the review results.
    // @todo Format this as a nice table.
    $output = array();
    $values = $check['value'];
    foreach ($values as $module_name => $reviews) {
      $module = new MultisiteReviewModule($module_name);
      foreach ($reviews as $review => $results) {
        // Create a container and title for the module if we don't have one yet.
        if (empty($output[$module->getType()][$module_name])) {
          $output[$module->getType()][$module_name] = array(
            '#type' => 'container',
            '#prefix' => '<h3>' . check_plain($module->getHumanName()) . '</h3>',
            '#attributes' => array(),
          );
        }

        // Assemble the results as table rows.
        $rows = array();
        foreach ($results as $result) {
          $rows[] = array($result);
        }

        $output[$module->getType()][$module_name][] = array(
          '#theme' => 'table',
          '#header' => array(check_plain($reviews_info[$review]['name'])),
          '#rows' => $rows,
        );
      }
    }

    // Provide a container and title for the module type: 'Feature' or 'Module'.
    foreach ($output as $type => &$items) {
      $items['#type'] = 'container';
      $items['#prefix'] = '<h2>' . ucfirst(check_plain($type)) . '</h2>';
      $items['#attributes'] = array();
    }
  }

  $element['findings']['items'][] = array(
    'html' => drupal_render($output),
  );

  return $element;
}
