<?php

/**
 * @file
 * Taxonomy browser admin.inc file.
 */

/**
 * Function form_taxonomy_browser_settings().
 */
function _taxonomy_browser_form_taxonomy_browser_settings($form, &$form_state) {
  global $base_path;

  $vocabularies = taxonomy_get_vocabularies();

  foreach ($vocabularies as $vid => $vocabulary) {
    $items_vocabulary[$vid] = $vocabulary->name;
  }

  $form['taxonomy_browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('TAXONOMY VOCABULARIES'),
    '#description' => t('Select vocabularies to create blocks with their taxonomy terms. Each of these blocks will display the taxonomy vocabulary terms as a tree to browse through the related content.</p>'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $header = array(
    'name' => t('Vocabulary name'),
    'description' => t('Description'),
    'edit' => t('Edit'),
  );

  $options = array();
  foreach ($vocabularies as $vid => $vocabulary) {
    $options[$vocabulary->vid] = array(
      'name' => $vocabulary->name,
      'description' => $vocabulary->description,
      'edit' => array(
        'data' => _taxonomy_browser_configure_block_link($vocabulary->vid),
      ),
    );
  }

  $form['taxonomy_browser']['taxonomy_browser_vocabulary'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#default_value' => variable_get('taxonomy_browser_vocabulary'),
  );

  return system_settings_form($form);
}

/**
 * Function _taxonomy_browser_configure_block_link().
 */
function _taxonomy_browser_configure_block_link($vid) {
  if ($vids_var = variable_get('taxonomy_browser_vocabulary')) {
    if (isset($vids_var[$vid]) &&  ($vids_var[$vid] != 0)) {
      $link = array(
        '#title' => 'configure block',
        '#type' => 'link',
        '#href' => 'admin/structure/block/manage/taxonomy_browser/taxonomy_browser_vocabulary_' . $vid . '/configure',
      );
    }
    else {
      $link = array(
        '#title' => NULL,
        '#type' => 'link',
        '#href' => 'admin/structure/block/manage/taxonomy_browser/taxonomy_browser_vocabulary_' . $vid . '/configure',
      );
    }

    return $link;
  }
}
