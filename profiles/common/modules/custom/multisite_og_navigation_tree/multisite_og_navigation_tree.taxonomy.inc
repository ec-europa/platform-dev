<?php

/**
 * @file
 * Taxonomy form handling : ADD/EDIT TERMS.
 */

/**
 * Add taxonomy form.
 */
function _mont_group_taxonomy_add_term($node) {
  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $group_taxonomy = _mont_group_taxonomy_load($node->nid);
  $vid = $group_taxonomy->vid;
  $tid = $group_taxonomy->tid;
  $vocabulary = taxonomy_vocabulary_load($vid);
  $children = _mont_group_taxonomy_get_allchildren($tid);
  $form = drupal_get_form('taxonomy_form_term', array(), $vocabulary);
  $parent_options = $form['relations']['parent']['#options'];
  foreach ($parent_options as $parent_tid => $option) {
    if (!($parent_tid == $tid || array_key_exists($parent_tid, $children))) {
      unset($form['relations']['parent']['#options'][$parent_tid]);
    }
  }
  $form['relations']['parent']['#default_value'] = array($tid => $tid);
  $form['relations']['parent']['#value'] = array($tid => $tid);
  $form['relations']['parent']['#required'] = TRUE;

  $output = drupal_render($form);
  return $output;
}

/**
 * Add taxonomy form.
 */
function _mont_group_taxonomy_edit_term($node, $term_id = 0) {
  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $group_taxonomy = _mont_group_taxonomy_load($node->nid);
  $vid = $group_taxonomy->vid;
  $tid = $group_taxonomy->tid;
  $vocabulary = taxonomy_vocabulary_load($vid);
  $children = _mont_group_taxonomy_get_allchildren($tid);

  $term = taxonomy_term_load($term_id);
  $form = drupal_get_form('taxonomy_form_term', $term, $vocabulary);
  // In case of a delete form, the relations is undefined.
  if (isset($form['relations']['parent'])) {
    $parent_options = $form['relations']['parent']['#options'];
    if ($tid != $term_id) {
      foreach ($parent_options as $parent_tid => $option) {
        if (!($parent_tid == $tid || array_key_exists($parent_tid, $children))) {
          unset($form['relations']['parent']['#options'][$parent_tid]);
        }
      }

      $form['relations']['parent']['#default_value'] = array($tid => $tid);
      $form['relations']['parent']['#value'] = array($tid => $tid);
      $form['relations']['parent']['#required'] = TRUE;
    }
    else {
      $form['relations']['parent']['#options'] = array(t('<root>'));
      $form['relations']['parent']['#default_value'] = array(0);
      $form['relations']['parent']['#value'] = array(0);
    }
  }

  $output = drupal_render($form);
  return $output;
}

/**
 * Returns the group taxonomy view for a given node and taxonomy term.
 */
function _mont_group_taxonomy_view_term($node, $term_id = 0) {
  $term = taxonomy_term_load($term_id);
  drupal_set_title($term->name);
  $output = views_embed_view('mont_grouptaxonomy', 'default', $term_id);
  if ($output) {
    return $output;
  }
  return t('No results');
}

/**
 * Modification of the core taxonomy overview terms form.
 *
 * Altered : taxonomy_get_tree($vocabulary->vid, $group_tid) instead of
 * taxonomy_get_tree($vocabulary->vid, $group_tid)
 */
function _mont_overview_terms($form, &$form_state, $node) {
  global $pager_page_array, $pager_total, $pager_total_items;

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $group_taxonomy = _mont_group_taxonomy_load($node->nid);

  if (!is_object($group_taxonomy)) {
    $vid = variable_get('multisite_og_navigation_tree_vid', FALSE);
    if ($vid) {
      _mont_group_taxonomy_insert($node, $vid);
      $group_taxonomy = _mont_group_taxonomy_load($node->nid);
    }
    else {
      $form['error_text'] = array('#markup' => t('No group taxonomy associated with this group.'));
      return $form;
    }
  }

  $group_vid = $group_taxonomy->vid;
  $group_tid = $group_taxonomy->tid;
  $vocabulary = taxonomy_vocabulary_load($group_vid);

  $form['#vocabulary'] = $vocabulary;
  $form['#tree'] = TRUE;
  $form['#parent_fields'] = FALSE;
  $form['#theme'] = 'mont_taxonomy_overview_terms';

  $page = isset($_GET['page']) ? $_GET['page'] : 0;
  $page_increment = variable_get('taxonomy_terms_per_page_admin', 100);
  // Number of terms per page.
  $page_entries = 0;
  // Elements shown on this page.
  $before_entries = 0;
  // Elements at the root level before this page.
  $after_entries = 0;
  // Elements at the root level after this page.
  $root_entries = 0;
  // Elements at the root level on this page.
  // Terms from previous and next pages are shown if the term tree would have
  // been cut in the middle. Keep track of how many extra terms we show on each
  // page of terms.
  $back_step = NULL;
  $forward_step = 0;

  // An array of the terms to be displayed on this page.
  $current_page = array();

  $delta = 0;
  $term_deltas = array();
  $tree = taxonomy_get_tree($vocabulary->vid, $group_tid);
  $term = current($tree);
  $complete_tree = FALSE;
  do {
    // In case this tree is completely empty.
    if (empty($term)) {
      break;
    }
    $delta++;
    // Count entries before the current page.
    if ($page && ($page * $page_increment) > $before_entries && !isset($back_step)) {
      $before_entries++;
      continue;
    }
    // Count entries after the current page.
    elseif ($page_entries > $page_increment && $complete_tree) {
      $after_entries++;
      continue;
    }

    // Do not let a term start the page that is not at the root.
    if (isset($term->depth) && ($term->depth > 0) && !isset($back_step)) {
      $back_step = 0;
      while ($pterm = prev($tree)) {
        $before_entries--;
        $back_step++;
        if ($pterm->depth == 0) {
          prev($tree);
          continue 2;
          // Jump back to the start of the root level parent.
        }
      }
    }
    $back_step = isset($back_step) ? $back_step : 0;

    // Continue rendering the tree until we reach the a new root item.
    if ($page_entries >= $page_increment + $back_step + 1 && $term->depth == 0 && $root_entries > 1) {
      $complete_tree = TRUE;
      // This new item at the root level is the first item on the next page.
      $after_entries++;
      continue;
    }
    if ($page_entries >= $page_increment + $back_step) {
      $forward_step++;
    }

    // Finally, if we've gotten down this far, we're rendering a term on this
    // page.
    $page_entries++;
    $term_deltas[$term->tid] = isset($term_deltas[$term->tid]) ? $term_deltas[$term->tid] + 1 : 0;
    $key = 'tid:' . $term->tid . ':' . $term_deltas[$term->tid];

    // Keep track of the first term displayed on this page.
    if ($page_entries == 1) {
      $form['#first_tid'] = $term->tid;
    }
    // Keep a variable to make sure at least 2 root elements are displayed.
    if ($term->parents[0] == 0) {
      $root_entries++;
    }
    $current_page[$key] = $term;
  } while ($term = next($tree));

  // Because we didn't use a pager query, set the necessary pager variables.
  $total_entries = $before_entries + $page_entries + $after_entries;
  $pager_total_items[0] = $total_entries;
  $pager_page_array[0] = $page;
  $pager_total[0] = ceil($total_entries / $page_increment);

  // If this form was already submitted once, it's probably hit a validation
  // error. Ensure the form is rebuilt in the same order as the user submitted.
  if (!empty($form_state['input'])) {
    $order = array_flip(array_keys($form_state['input']));
    // Get the $_POST order.
    $current_page = array_merge($order, $current_page);
    // Update our form with the new order.
    foreach ($current_page as $key => $term) {
      // Verify this is a term for the current page and set at the current
      // depth.
      if (is_array($form_state['input'][$key]) && is_numeric($form_state['input'][$key]['tid'])) {
        $current_page[$key]->depth = $form_state['input'][$key]['depth'];
      }
      else {
        unset($current_page[$key]);
      }
    }
  }

  $path = arg(0) . '/' . arg(1) . '/vocabulary/edit_term';
  // Build the actual form.
  foreach ($current_page as $key => $term) {
    // Save the term for the current page so we don't have to load it a
    // second time.
    $form[$key]['#term'] = (array) $term;
    if (isset($term->parents)) {
      $form[$key]['#term']['parent'] = $term->parent = $term->parents[0];
      unset($form[$key]['#term']['parents'], $term->parents);
    }

    $form[$key]['view'] = array(
      '#type' => 'link',
      '#title' => $term->name,
      '#href' => "taxonomy/term/$term->tid",
    );
    if ($vocabulary->hierarchy < 2 && count($tree) > 1) {
      $form['#parent_fields'] = TRUE;
      $form[$key]['tid'] = array(
        '#type' => 'hidden',
        '#value' => $term->tid,
      );
      $form[$key]['parent'] = array(
        '#type' => 'hidden',
        // Yes, default_value on a hidden. It needs to be changeable by the
        // javascript.
        '#default_value' => $term->parent,
      );
      $form[$key]['depth'] = array(
        '#type' => 'hidden',
        // Same as above, the depth is modified by javascript, so it's a
        // default_value.
        '#default_value' => $term->depth,
      );
      $form[$key]['weight'] = array(
        '#type' => 'weight',
        '#delta' => $delta,
        '#title_display' => 'invisible',
        '#title' => t('Weight for added term'),
        '#default_value' => $term->weight,
      );
    }
    $form[$key]['edit'] = array(
      '#type' => 'link',
      '#title' => t('edit'),
      '#href' => $path . '/' . $term->tid ,
      '#options' => array('query' => drupal_get_destination()),
    );
  }

  $form['#total_entries'] = $total_entries;
  $form['#page_increment'] = $page_increment;
  $form['#page_entries'] = $page_entries;
  $form['#back_step'] = $back_step;
  $form['#forward_step'] = $forward_step;
  $term_link = $_GET['q'];
  $form['#empty_text'] = t('No terms available. <a href="@link">Add term</a>.', array('@link' => url($term_link . '/add_term')));

  if ($vocabulary->hierarchy < 2 && count($tree) > 1) {
    $form['actions'] = array(
      '#type' => 'actions',
      '#tree' => FALSE,
    );
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    $form_state['redirect'] = array(
      $_GET['q'],
      (isset($_GET['page']) ? array('query' => array('page' => $_GET['page'])) : array()),
    );
  }

  return $form;
}

/**
 * Modification of the core taxonomy overview terms form submit.
 */
function _mont_overview_terms_submit($form, &$form_state) {
  // Sort term order based on weight.
  uasort($form_state['values'], 'drupal_sort_weight');

  $vocabulary = $form['#vocabulary'];
  $hierarchy = 0;
  // Update the current hierarchy type as we go.
  $changed_terms = array();
  $tree = taxonomy_get_tree($vocabulary->vid);

  if (empty($tree)) {
    return;
  }

  // Build a list of all terms that need to be updated on previous pages.
  $weight = 0;
  $term = (array) $tree[0];
  while ($term['tid'] != $form['#first_tid']) {
    if ($term['parents'][0] == 0 && $term['weight'] != $weight) {
      $term['parent'] = $term['parents'][0];
      $term['weight'] = $weight;
      $changed_terms[$term['tid']] = $term;
    }
    $weight++;
    $hierarchy = $term['parents'][0] != 0 ? 1 : $hierarchy;
    $term = (array) $tree[$weight];
  }

  // Renumber the current page weights and assign any new parents.
  $level_weights = array();
  foreach ($form_state['values'] as $tid => $values) {
    if (isset($form[$tid]['#term'])) {
      $term = $form[$tid]['#term'];
      // Give terms at the root level a weight in sequence with terms on
      // previous pages.
      if ($values['parent'] == 0 && $term['weight'] != $weight) {
        $term['weight'] = $weight;
        $changed_terms[$term['tid']] = $term;
      }
      // Terms not at the root level can safely start from 0 because they're all
      // on this page.
      elseif ($values['parent'] > 0) {
        $level_weights[$values['parent']] = isset($level_weights[$values['parent']]) ? $level_weights[$values['parent']] + 1 : 0;
        if ($level_weights[$values['parent']] != $term['weight']) {
          $term['weight'] = $level_weights[$values['parent']];
          $changed_terms[$term['tid']] = $term;
        }
      }
      // Update any changed parents.
      if ($values['parent'] != $term['parent']) {
        $term['parent'] = $values['parent'];
        $changed_terms[$term['tid']] = $term;
      }
      $hierarchy = $term['parent'] != 0 ? 1 : $hierarchy;
      $weight++;
    }
  }

  // Build a list of all terms that need to be updated on following pages.
  for ($weight; $weight < count($tree); $weight++) {
    $term = (array) $tree[$weight];
    if ($term['parents'][0] == 0 && $term['weight'] != $weight) {
      $term['parent'] = $term['parents'][0];
      $term['weight'] = $weight;
      $changed_terms[$term['tid']] = $term;
    }
    $hierarchy = $term['parents'][0] != 0 ? 1 : $hierarchy;
  }

  // Save all updated terms.
  foreach ($changed_terms as $changed) {
    $term = (object) $changed;
    // Update term_hierachy and term_data directly since we don't have a
    // fully populated term object to save.
    db_update('taxonomy_term_hierarchy')->fields(array('parent' => $term->parent))->condition('tid', $term->tid, '=')->execute();

    db_update('taxonomy_term_data')->fields(array('weight' => $term->weight))->condition('tid', $term->tid, '=')->execute();
  }

  // Update the vocabulary hierarchy to flat or single hierarchy.
  if ($vocabulary->hierarchy != $hierarchy) {
    $vocabulary->hierarchy = $hierarchy;
    taxonomy_vocabulary_save($vocabulary);
  }
  drupal_set_message(t('The configuration options have been saved.'));
}
