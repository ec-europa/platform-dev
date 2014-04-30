<?php
/**
 * @file
 * Admin page callbacks for the social bar block.
 */

/**
 * Implements configuration form().
 */
function _social_bookmark_bar_admin_settings() {
  // Get global variable with the form data.
  $saved_form = variable_get('data_table');
  $form = array();
  $rows = array();
  $row_elements = array();

  // Put it into a fieldset.
  $form['data_table'] = array(
    '#type' => 'fieldset',
    '#title' => t('Individual networks buttons'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Collect data.
  $data = array(
    'facebook' => array(
      'pos_init' => 0,
      'enable' => $saved_form['facebook']['enabled'],
      'weight' => $saved_form['facebook']['weight'],
      'name' => 'Facebook',
      'description' => '<div id="ec-widget-share-networks" style="pointer-events:none;"><!--{"to":"facebook"}//--></div>',
    ),
    'googleplus' => array(
      'pos_init' => 1,
      'enable' => $saved_form['googleplus']['enabled'],
      'weight' => $saved_form['googleplus']['weight'],
      'name' => 'Google+',
      'description' => '<div id="ec-widget-share-googleplus" style="pointer-events:none;"><!--{"to":"googleplus"}//--></div>',
    ),
    'twitter' => array(
      'pos_init' => 2,
      'enable' => $saved_form['twitter']['enabled'],
      'weight' => $saved_form['twitter']['weight'],
      'name' => 'Twitter',
      'description' => '<div id="ec-widget-share-twitter" style="pointer-events:none;"><!--{"to":"twitter"}//--></div>',
    ),
    'linkedin' => array(
      'pos_init' => 3,
      'enable' => $saved_form['linkedin']['enabled'],
      'weight' => $saved_form['linkedin']['weight'],
      'name' => 'Linkedin',
      'description' => '<div id="ec-widget-share-linkedin" style="pointer-events:none;"><!--{"to":"linkedin"}//--></div>',
    ),
    'pocket' => array(
      'pos_init' => 4,
      'enable' => $saved_form['pocket']['enabled'],
      'weight' => $saved_form['pocket']['weight'],
      'name' => 'Pocket',
      'description' => '<div id="ec-widget-share-pocket" style="pointer-events:none;"><!--{"to":"pocket"}//--></div>',
    ),
    'yammer' => array(
      'pos_init' => 5,
      'enable' => $saved_form['yammer']['enabled'],
      'weight' => $saved_form['yammer']['weight'],
      'name' => 'Yammer',
      'description' => '<div id="ec-widget-share-yammer" style="pointer-events:none;"><!--{"to":"yammer"}//--></div>',
    ),
    'pinterest' => array(
      'pos_init' => 6,
      'enable' => $saved_form['pinterest']['enabled'],
      'weight' => $saved_form['pinterest']['weight'],
      'name' => 'Pinterest',
      'description' => '<div id="ec-widget-share-pinterest" style="pointer-events:none;"><!--{"to":"pinterest"}//--></div>',
    ),
    'email_link' => array(
      'pos_init' => 7,
      'enable' => $saved_form['email_link']['enabled'],
      'weight' => $saved_form['email_link']['weight'],
      'name' => 'Email link',
      'description' => '<div id="ec-widget-share-email_link" style="pointer-events:none;"><!--{"to":"email_link"}//--></div>',
    ),
    'favorites' => array(
      'pos_init' => 8,
      'enable' => $saved_form['favorites']['enabled'],
      'weight' => $saved_form['favorites']['weight'],
      'name' => 'Favorites',
      'description' => '<div id="ec-widget-share-favorites" style="pointer-events:none;"><!--{"to":"favorites"}//--></div>',
    ),
    'wordpress' => array(
      'pos_init' => 9,
      'enable' => $saved_form['wordpress']['enabled'],
      'weight' => $saved_form['wordpress']['weight'],
      'name' => 'Wordpress',
      'description' => '<div id="ec-widget-share-wordpress" style="pointer-events:none;"><!--{"to":"wordpress"}//--></div>',
    ),
    'more' => array(
      'pos_init' => 10,
      'enable' => $saved_form['more']['enabled'],
      'weight' => $saved_form['more']['weight'],
      'name' => 'More',
      'description' => '<div id="ec-widget-share-more" style="word-wrap: normal; pointer-events:none;"><!--{"to":"more"}//--></div>',
    ),
  );

  if (variable_get('data_table')) {
    // Sort the rows.
    uasort($data, '_social_bookmark_bar_form_weight_arraysort');
  }

  // Build the rows.
  foreach ($data as $id => $entry) {
    // Build the table rows.
    $rows[$id] = array(
      'data' => array(
        // Cell for the cross drag&drop element and Name.
        array(
          'data' => $entry['name'],
          'class' => array('entry-cross'),
        ),
        // Weight item for the tabledrag.
        array(
          'data' => array(
            '#type' => 'weight',
            '#title' => t('Weight'),
            '#title_display' => 'invisible',
            '#default_value' => _social_bookmark_get_values($id, $entry),
            '#parents' => array(
              'data_table',
              $id,
              'weight',
            ),
            '#attributes' => array(
              'class' => array('entry-order-weight'),
            ),
          ),
        ),
        // Entry description.
        $entry['description'],
        // Enabled checkbox.
        array(
          'data' => array(
            '#type' => 'checkbox',
            '#title' => t('Enable'),
            '#title_display' => 'invisible',
            '#default_value' => $entry['enable'],
            '#parents' => array(
              'data_table',
              $id,
              'enabled',
            ),
          ),
        ),
      ),
      'class' => array('draggable'),
    );
    // Build rows of the form elements in the table.
    $row_elements[$id] = array(
      'weight' => &$rows[$id]['data'][1]['data'],
      'enabled' => &$rows[$id]['data'][3]['data'],
    );
  }

  // Add the table to the form.
  $form['data_table']['drag_table'] = array(
    '#theme' => 'table',
    // The row form elements need to be processed and build,
    // therefore pass them as element children.
    'elements' => $row_elements,
    '#header' => array(
      // We need two columns for the weigth field and the cross.
      array(
        'data' => t('Name'),
        'class' => 'entry-name-column',
      ),
      array(
        'data' => t('Weight'),
        'class' => 'entry-weight-column',
      ),
      array(
        'data' => t('Icon'),
        'class' => 'entry_icon_column',
      ),
      array(
        'data' => t('Enabled'),
        'class' => 'entry_enabled_column',
      ),
    ),
    '#rows' => $rows,
    '#empty' => t('There are no entries available.'),
    '#attributes' => array('id' => 'entry-order'),
  );
  drupal_add_tabledrag('entry-order', 'order', 'sibling', 'entry-order-weight');

  $form['style_socialbar'] = array(
    '#type' => 'fieldset',
    '#title' => t('Customize button look'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['style_socialbar']['type_socialbar'] = array(
    '#type' => 'radios',
    '#title' => t('Button display'),
    '#default_value' => variable_get('type_socialbar', 'Horizontal'),
    '#options' => drupal_map_assoc(array(
      0 => t('Horizontal'),
      1 => t('Vertical'),
    )),
    '#description' => t('Display the list of buttons in a horizontal or vertical bar.'),
  );

  $form['style_socialbar']['icon_size_socialbar'] = array(
    '#type' => 'select',
    '#title' => t('Icons size (px)'),
    '#options' => drupal_map_assoc(array(
      0 => t('16'),
      1 => t('24'),
      2 => t('32'),
    )),
    '#default_value' => variable_get('icon_size_socialbar', '24'),
    '#description' => t('Size of the icons in pixels.'),
  );

  $form['style_socialbar']['text_socialbar'] = array(
    '#type' => 'radios',
    '#title' => t('Label display'),
    '#default_value' => variable_get('text_socialbar', 'None'),
    '#options' => drupal_map_assoc(array(
      0 => t('None'),
      1 => t('Share'),
      2 => t('[Network name]'),
      3 => t('Share on [Network name]'),
    )),
    '#description' => t('Text to display on the button / icon.'),
  );

  $form['statistics'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enable/disable statistics'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['statistics']['statistics_socialbar'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable/disable statistics'),
    '#default_value' => variable_get('statistics_socialbar', TRUE),
    '#description' => t('By default statistics are enabled. In order to disable it, uncheck this parameter.'),
  );

  $form['language_detection'] = array(
    '#type' => 'fieldset',
    '#title' => t("Modify language's detection"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['language_detection']['language_socialbar'] = array(
    '#type' => 'radios',
    '#title' => t('Language source'),
    '#default_value' => variable_get('language_socialbar', 'From META DATA'),
    '#options' => drupal_map_assoc(array(
      0 => t('From URL'),
      1 => t('From META DATA'),
      2 => t('Language specified'),
    )),
    '#description' => t('In order to change the language detection you should use this options. </br>If this parameter is not defined, the application tries to detect the language automatically from META DATA.'),
  );
  global $language;
  $languages = language_list('enabled');
  $langs = array();
  foreach ($languages[1] as $lan) {
    $langs[$lan->language] = $lan->name;
  }
  $form['language_detection']['language_selector_socialbar'] = array(
    '#type' => 'select',
    '#title' => t('Set a specific language'),
    '#options' => $langs,
    '#default_value' => variable_get('language_selector_socialbar', $language->language),
    '#description' => t('Select a language (only available for the "Language specified" option)."'),
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'social_bookmark') . '/scripts/social_bookmark.form.js',
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'social_bookmark') . '/css/social_bookmark.form.css',
  );

  return system_settings_form($form);
}

/**
 * Helper function for sorting entry weights.
 */
function _social_bookmark_bar_form_weight_arraysort($a, $b) {
  if (isset($a['weight']) && isset($b['weight'])) {
    return $a['weight'] < $b['weight'] ? -1 : 1;
  }
  return 0;
}

/**
 * Function that returns default weight value.
 */
function _social_bookmark_get_values($id, $data) {
  // If exist saved data.
  if ($saved_form = variable_get('data_table')) {
    return $saved_form[$id]['weight'];
  }
  else {
    // If not, return 'pos_init' value.
    return $data['pos_init'];
  }
}
