<?php

/**
 * @file
 * Adding BEM related custom field formatters.
 */

global $_nexteuropa_formatters_listing_view_modes;
$_nexteuropa_formatters_listing_view_modes = array(
  'title',
  'meta',
  'teaser',
  'image_label',
);

/**
 * Implements hook_field_formatter_info().
 */
function nexteuropa_formatters_field_formatter_info() {
  return array(
    'context_nav_item' => array(
      'label' => t('Context nav item'),
      'field types' => array(
        'text',
        'entityreference',
        'link_field',
        'datetime',
        'date',
        'datestamp',
      ),
      'settings' => array(
        'expander_has_expander' => FALSE,
        'expander_trim_at' => 0,
        'expander_trim_to' => 0,
        'contextual_date' => '',
      ),
    ),
    'nexteuropa_tags' => array(
      'label' => t('Tags (NextEuropa)'),
      'field types' => array(
        'taxonomy_term_reference',
        'entityreference',
        'link_field',
      ),
    ),
    'link_button_default' => array(
      'label' => t('Link button default'),
      'field types' => array(
        'link_field',
        'taxonomy_term_reference',
        'entityreference',
      ),
      'settings' => array(
        'link_title' => '',
        'force_language_default' => 0,
      ),
    ),
    'link_button_primary' => array(
      'label' => t('Link button primary'),
      'field types' => array(
        'link_field',
        'taxonomy_term_reference',
      ),
    ),
    'link_button_secondary' => array(
      'label' => t('Link button secondary'),
      'field types' => array(
        'link_field',
        'taxonomy_term_reference',
      ),
    ),
    'link_button_call_for_action' => array(
      'label' => t('Link button call for action'),
      'field types' => array(
        'link_field',
        'taxonomy_term_reference',
      ),
    ),
    'link_button_block' => array(
      'label' => t('Link button block'),
      'field types' => array(
        'link_field',
        'taxonomy_term_reference',
      ),
    ),
    'link_button_two_column' => array(
      'label' => t('Link button two column'),
      'field types' => array(
        'link_field',
      ),
    ),
    'link_listing_title' => array(
      'label' => t('Listing title'),
      'field types' => array(
        'link_field',
        'taxonomy_term_reference',
      ),
    ),
    'link_listing_title' => array(
      'label' => t('Listing title'),
      'field types' => array(
        'link_field',
        'taxonomy_term_reference',
      ),
    ),
    'entity_reference_section' => array(
      'label' => t('Entity reference section group'),
      'field types' => array(
        'entityreference',
      ),
      'settings' => array(
        'use_content_language' => TRUE,
        'view_mode' => 'default',
        'links' => TRUE,
      ),
    ),
    'telephone' => array(
      'label' => t('Telephone link'),
      'field types' => array('text'),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function nexteuropa_formatters_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'context_nav_item') {
    $element['expander_has_expander'] = array(
      '#title' => t('Has expander'),
      '#type' => 'checkbox',
      '#size' => 1,
      '#default_value' => $settings['expander_has_expander'],
    );
    $element['expander_trim_at'] = array(
      '#title' => t('Trim at'),
      '#type' => 'textfield',
      '#size' => 2,
      '#default_value' => $settings['expander_trim_at'],
      '#element_validate' => array('element_validate_integer'),
    );
    $element['expander_trim_to'] = array(
      '#title' => t('Trim to'),
      '#type' => 'textfield',
      '#size' => 2,
      '#default_value' => $settings['expander_trim_to'],
      '#element_validate' => array('element_validate_integer'),
    );

    if ($display['type'] == 'context_nav_item' && $field['type'] == 'datetime') {
      module_load_include('inc', 'date', 'date_admin');
      $element[] = date_default_formatter_settings_form($field, $instance, $view_mode, $form, $form_state);
    }
  }

  if ($display['type'] == 'entity_reference_section') {
    $element['use_content_language'] = array(
      '#title' => t('Use the content language for referenced items.'),
      '#type' => 'checkbox',
      '#default_value' => $settings['use_content_language'],
    );
  }

  if ($display['type'] == 'link_button_default' && $field['type'] == 'entityreference') {
    $element['link_title'] = array(
      '#title' => t('Title'),
      '#type' => 'textfield',
      '#default_value' => $settings['link_title'],
    );
    $element['force_language_default'] = array(
      '#title' => t('Force the link to point to the default language.'),
      '#type' => 'checkbox',
      '#default_value' => $settings['force_language_default'],
    );
  }

  return $element;
}

/**
 * Helper function to select the right class.
 *
 * @param string $formatter
 *   Formatter name.
 *
 * @return string
 *   Class connected to formatter.
 */
function _nexteuropa_formatters_field_formatter_view_classes($formatter) {
  switch ($formatter) {
    case 'link_button_default':
      return 'btn btn-default';

    case 'link_button_primary':
      return 'btn btn-primary';

    case 'link_button_secondary':
      return 'btn btn-secondary';

    case 'link_button_call_for_action':
      return 'btn btn-ctn';

    case 'link_button_block':
      return 'btn btn-default btn-block';

    case 'link_button_two_column':
      return 'btn btn-default';

    case 'link_listing_title':
      return 'listing__title';

    case 'entity_reference_section':
      return 'section__item';
  }
  return '';
}

/**
 * Implements hook_field_formatter_prepare_view().
 */
function nexteuropa_formatters_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
  if ($field['type'] == 'entityreference') {
    $target_ids = array();

    // Collect every possible entity attached to any of the entities.
    foreach ($entities as $id => $entity) {
      foreach ($items[$id] as $delta => $item) {
        if (isset($item['target_id'])) {
          $target_ids[] = $item['target_id'];
        }
      }
    }

    if ($target_ids) {
      $target_entities = entity_load($field['settings']['target_type'], $target_ids);
    }
    else {
      $target_entities = array();
    }

    // Iterate through the fieldable entities again to attach the loaded data.
    foreach ($entities as $id => $entity) {
      $rekey = FALSE;

      foreach ($items[$id] as $delta => $item) {
        // Check whether the referenced entity could be loaded.
        if (isset($target_entities[$item['target_id']])) {
          // Replace the instance value with the term data.
          $items[$id][$delta]['entity'] = $target_entities[$item['target_id']];
          // Check whether the user has access to the referenced entity.
          $has_view_access = (entity_access('view', $field['settings']['target_type'], $target_entities[$item['target_id']]) !== FALSE);
          $has_update_access = (entity_access('update', $field['settings']['target_type'], $target_entities[$item['target_id']]) !== FALSE);
          $items[$id][$delta]['access'] = ($has_view_access || $has_update_access);
        }
        // Otherwise, unset the instance value, since the entity does not exist.
        else {
          unset($items[$id][$delta]);
          $rekey = TRUE;
        }
      }

      if ($rekey) {
        // Rekey the items array.
        $items[$id] = array_values($items[$id]);
      }
    }
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function nexteuropa_formatters_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  if (!empty($items)) {
    $formatter = $display['type'];

    switch ($formatter) {
      case 'context_nav_item':
        $layout_field_settings = ds_get_field_settings($entity_type, $entity->type, 'full');
        $field_name = $field['field_name'];
        if (isset($layout_field_settings[$field_name]['formatter_settings']['ft']['lb'])) {
          $label_altered = $layout_field_settings[$field_name]['formatter_settings']['ft']['lb'];
        }
        $wrapper_label = (isset($label_altered) ? $label_altered : $instance['label']);

        // Apply custom label to the element.
        $element = array_merge(
          $element,
          _nexteuropa_formatters_get_context_nav_wrapper(
            $wrapper_label,
            isset($display['settings']['expander_has_expander']) ? $display['settings']['expander_has_expander'] : FALSE,
            isset($display['settings']['expander_trim_at']) ? $display['settings']['expander_trim_at'] : FALSE,
            isset($display['settings']['expander_trim_to']) ? $display['settings']['expander_trim_to'] : FALSE
          )
        );

        switch ($field['type']) {
          case 'entityreference':
            $handler = entityreference_get_selection_handler($field, $instance, $entity_type, $entity);
            foreach ($items as $delta => $item) {
              if ($label = $handler->getLabel($item['entity'])) {
                if ($uri = entity_uri($field['settings']['target_type'], $item['entity'])) {
                  $link_url = isset($item['entity']->legacy) ? $item['entity']->legacy : $uri['path'];
                  $link = l($label, $link_url, $uri['options']);
                  $element[$delta] = array(
                    '#prefix' => '<span class="context-nav__item">',
                    '#markup' => $link,
                    '#suffix' => '</span>',
                  );
                }
                else {
                  $element[$delta] = array('#markup' => check_plain($label));
                }
              }
            }
            break;

          case 'link_field':
            foreach ($items as $delta => $item) {
              $link = l($item['title'], $item['url'], array('attributes' => $item['attributes']));
              $element[$delta] = array(
                '#markup' => '<span class="context-nav__item">' . $link . '</span>',
              );
            }
            // End of context_nav_item.
            break;

          case 'text':
            foreach ($items as $delta => $item) {
              $element[$delta] = array(
                '#markup' => '<span class="context-nav__item">' . $item['safe_value'] . '</span>',
              );
            }
            break;

          case 'date':
          case 'datestamp':
          case 'datetime':
            // @TODO: Make date format flexible based on formatter options.
            foreach ($items as $delta => $item) {
              $node_wrapper = entity_metadata_wrapper('node', $entity);
              if ($date_updated = $node_wrapper->field_core_date_updated->value()) {
                $element[$delta] = array(
                  '#markup' => '<span class="context-nav__item">' .
                  format_date(strtotime($item['value']), 'ec_date_j_f_y') . ' ' .
                  t('(last update on: @date)',
                    array('@date' => format_date($date_updated, 'ec_date_j_f_y'))) .
                  '</span>',
                );
              }
              else {
                $element[$delta] = array(
                  '#markup' => '<span class="context-nav__item">' .
                  format_date(strtotime($item['value']), 'ec_date_j_f_y') .
                  '</span>',
                );
              }
            }
            break;
        }
        break;

      case 'nexteuropa_tags':
        switch ($field['type']) {

          case 'taxonomy_term_reference':
            foreach ($items as $delta => $item) {
              $term = taxonomy_term_load($item['tid']);
              $link_url = isset($term->legacy) ? $term->legacy : url('taxonomy/term/' . $item['tid']);
              $element[$delta] = _nexteuropa_formatters_tags_item_link($term->name, $link_url);
            }
            break;

          case 'entityreference':
            $handler = entityreference_get_selection_handler($field, $instance, $entity_type, $entity);
            foreach ($items as $delta => $item) {
              if ($label = $handler->getLabel($item['entity'])) {
                if ($uri = entity_uri($field['settings']['target_type'], $item['entity'])) {
                  $link_url = isset($item['entity']->legacy) ? $item['entity']->legacy : $uri['path'];
                  $element[$delta] = _nexteuropa_formatters_tags_item_link($label, $link_url);
                }
                else {
                  $element[$delta] = array('#markup' => check_plain($label));
                }
              }
            }
            break;

          case 'link_field':
            foreach ($items as $delta => $item) {
              $element[$delta] = _nexteuropa_formatters_tags_item_link($item['title'], $item['url']);
            }
            break;
        }
        break;

      case 'telephone':
        foreach ($items as $delta => $item) {
          // Make the phone value a link, if possible.
          $telf = dt_shared_function_phonetohtml($item['safe_value']);
          $element[$delta] = array(
            '#markup' => $telf,
          );
        }
        break;

      case 'link_button_default':
      case 'link_button_primary':
      case 'link_button_secondary':
      case 'link_button_call_for_action':
      case 'link_button_two_column':
      case 'link_button_block':
        switch ($field['type']) {
          case 'link_field':
            foreach ($items as $delta => $item) {
              // Set attribute from formatter settings.
              $item['attributes']['class'] = _nexteuropa_formatters_field_formatter_view_classes($formatter);

              // Call theme function of link module (theme_link_formatter_link_
              // default).
              $element[$delta] = array(
                '#theme' => 'link_formatter_link_default',
                '#element' => $item,
                '#field' => $instance,
                '#display' => $display,
              );
            }
            break;

          case 'taxonomy_term_reference':
            foreach ($items as $delta => $item) {
              $term = taxonomy_term_load($item['tid']);
              $link = isset($term->legacy) ? $term->legacy : url('taxonomy/term/' . $item['tid']);

              $element[$delta] = array(
                '#type' => 'link',
                '#title' => $term->name,
                '#href' => $link,
                '#options' => array(
                  'attributes' => array(
                    'class' => _nexteuropa_formatters_field_formatter_view_classes($formatter),
                  ),
                ),
              );
            }
            break;

          case 'entityreference':
            $lang = language_default();
            $settings = $display['settings'];
            foreach ($items as $delta => $item) {
              // Classes.
              $classes = _nexteuropa_formatters_field_formatter_view_classes($formatter);
              // @codingStandardsIgnoreLine.
              $label = $settings['link_title'] != '' ? t($settings['link_title']) : $item['entity']->title;
              // Whether to force or not the language of the link.
              $force = isset($settings['force_language_default']) && $settings['force_language_default'];

              if (!$force) {
                $element[$delta] = array(
                  '#type' => 'link',
                  '#title' => $label,
                  '#href' => 'node/' . $items[$delta]['target_id'],
                  '#options' => array(
                    'attributes' => array(
                      'class' => $classes,
                    ),
                  ),
                );
              }
              else {
                $element[$delta] = array(
                  '#markup' => l($label, 'node/' . $items[$delta]['target_id'], array('language' => $lang, 'attributes' => array('class' => $classes))),
                );
              }
            }
            break;
        }
        // Multiple field wrapper.
        if (($field['cardinality'] == -1) && ($formatter != 'link_button_block')) {
          if ($formatter = 'link_button_two_column') {
            $element['#prefix'] = '<div class="btn-group btn-group-row-two">';
          }
          else {
            $element['#prefix'] = '<div class="btn-group">';
          }
          $element['#suffix'] = '</div>';
        }
        break;

      // Listing title item.
      case 'link_listing_title':
        $element = _nexteuropa_formatters_link_listing_title_field_formatter_view($field, $instance, $items, $display, $formatter, $element);
        break;

      case 'entity_reference_section':
        // Preconfigure entityreference_field_formatter_view().
        // section__item
        $display['type'] = 'entityreference_entity_view';
        $element = entityreference_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display);
        foreach ($element as $delta => $item) {
          $key_of_node = key($element[$delta]['node']);
          $element[$delta]['node'][$key_of_node]['#prefix'] = '<div class="section__item">';
          $element[$delta]['node'][$key_of_node]['#suffix'] = '</div>';
        }

        // Multiple field wrapper.
        if ($field['cardinality'] == -1) {
          $element['#prefix'] = '<div class="section section--row-two">';
          $element['#suffix'] = '</div>';
        }
        break;
    }
  }
  return $element;
}

/**
 * Helper function returns render array of type link for a tag item.
 *
 * @param string $item_title
 *   The title of the link.
 * @param string $item_link
 *    The href value of the link.
 *
 * @see theme_link()
 *
 * @return array
 *    Render array constructing a link.
 */
function _nexteuropa_formatters_tags_item_link($item_title, $item_link) {
  return array(
    '#type' => 'link',
    '#title' => $item_title,
    '#href' => $item_link,
    '#options' => array(
      'attributes' => array(
        'class' => array('tags__item'),
      ),
    ),
  );
}

/**
 * Helper function to link listing title field view.
 */
function _nexteuropa_formatters_link_listing_title_field_formatter_view($field, $instance, $items, $display, $formatter, $element) {
  foreach ($items as $delta => $item) {

    switch ($field['type']) {
      case 'link_field':
        // Set attribute from formatter settings.
        $formatter_class_default = _nexteuropa_formatters_field_formatter_view_classes($formatter);
        $title_item_modifier = $display['settings']['nexteuropa_title_item_modifier'];
        $title_item_link_modifier = $display['settings']['nexteuropa_title_item_link_modifier'];

        if (isset($title_item_link_modifier) && $title_item_link_modifier !== '') {
          $item['attributes']['class'] = $formatter_class_default . ' ' . $title_item_link_modifier;
        }
        else {
          $item['attributes']['class'] = $formatter_class_default;
        }

        $element[$delta] = array(
          '#theme' => 'link_formatter_link_default',
          '#element' => $item,
          '#field' => $instance,
          '#display' => $display,
        );

        if (isset($title_item_modifier) && $title_item_modifier !== '') {
          $element[$delta]['#prefix'] = '<div class="listing__item ' . $title_item_modifier . '">';
          $element[$delta]['#suffix'] = '</div>';
        }
        else {
          $element[$delta]['#prefix'] = '<div class="listing__item">';
          $element[$delta]['#suffix'] = '</div>';
        }
        break;

      case 'taxonomy_term_reference':
        $title_item_modifier = $display['settings']['nexteuropa_title_item_modifier'];
        $title_item_link_modifier = $display['settings']['nexteuropa_title_item_link_modifier'];
        $term = entity_metadata_wrapper('taxonomy_term', taxonomy_term_load($item['tid']));

        $element[$delta] = array(
          '#theme' => 'link',
          '#text' => $term->name->value(),
          '#path' => $term->field_core_top_task_link->url->value(),
          '#options' => array(
            'attributes' => array(
              'title' => $term->name->value(),
            ),
          ),
          '#field' => $instance,
          '#display' => $display,
        );

        if (isset($title_item_link_modifier) && $title_item_link_modifier !== '') {
          $element[$delta]['#options']['attributes']['class'] = 'listing__item-link' . ' ' . $title_item_link_modifier;
        }
        else {
          $element[$delta]['#options']['attributes']['class'] = 'listing__item-link';
        }

        if (isset($title_item_modifier) && $title_item_modifier !== '') {
          $element[$delta]['#prefix'] = '<div class="listing__item ' . $title_item_modifier . '">';
          $element[$delta]['#suffix'] = '</div>';
        }
        else {
          $element[$delta]['#prefix'] = '<div class="listing__item">';
          $element[$delta]['#suffix'] = '</div>';
        }
        break;
    }
  }
  if ($field['cardinality'] == -1) {
    $list_modifiers = $display['settings']['nexteuropa_title_listing_modifier'];
    if ($list_modifiers !== '') {
      $element['#prefix'] = "<div class='listing listing--title " . $list_modifiers . "'>";
    }
    else {
      $element['#prefix'] = '<div class="listing listing--title">';
    }
    $element['#suffix'] = '</div>';
    return $element;
  }
  return $element;
}

/**
 * Implements hook_field_formatter_info_alter().
 */
function nexteuropa_formatters_field_formatter_info_alter(&$info) {
  $info['entityreference_entity_view']['settings'] += array(
    'show_translations' => '',
    'nexteuropa_listing_columns' => 'default',
    'nexteuropa_listing_modifier' => '',
    'nexteuropa_listing_wrapper_modifier' => '',
  );
  $info['link_listing_title']['settings'] += array(
    'nexteuropa_title_listing_modifier' => '',
    'nexteuropa_title_item_modifier' => '',
    'nexteuropa_title_item_link_modifier' => '',
  );
}

/**
 * Implements hook_field_formatter_settings_form_alter().
 */
function nexteuropa_formatters_field_formatter_settings_form_alter(&$settings_form, $context) {
  global $_nexteuropa_formatters_listing_view_modes;

  if (
    isset($context['instance']['display'][$context['view_mode']]['type']) &&
    $context['instance']['display'][$context['view_mode']]['type'] == 'entityreference_entity_view' &&
    $context['instance']['display'][$context['view_mode']]['settings']['view_mode'] == 'file'
  ) {
    $display = $context['instance']['display'][$context['view_mode']];
    $settings = $display['settings'];
    $settings_form['show_translations'] = array(
      '#title' => t('Show file translations'),
      '#description' => t('In additional to the normal default display of the file, the user also see the translations of the file.'),
      '#type' => 'checkbox',
      '#size' => 1,
      '#default_value' => $settings['show_translations'],
    );
  }

  if (
    isset($context['instance']['display'][$context['view_mode']]['type']) &&
    $context['instance']['display'][$context['view_mode']]['type'] == 'entityreference_entity_view' &&
    in_array($context['instance']['display'][$context['view_mode']]['settings']['view_mode'], $_nexteuropa_formatters_listing_view_modes)
  ) {
    $display = $context['instance']['display'][$context['view_mode']];
    $settings = $display['settings'];
    $settings_form['nexteuropa_listing_columns'] = array(
      '#type' => 'select',
      '#title' => t('BEM: Listing layout'),
      '#options' => array(
        'default' => t('Default'),
        'two_columns' => t('Two Columns'),
        'three_columns' => t('Three Columns'),
        'row_two' => t('Row with two items'),
        'row_three' => t('Row with three items'),
      ),
      '#default_value' => $settings['nexteuropa_listing_columns'],
    );

    $settings_form['nexteuropa_listing_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('BEM: Listing Modifier'),
      '#default_value' => $settings['nexteuropa_listing_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );

    $settings_form['nexteuropa_listing_wrapper_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('BEM: Listing Wrapper Modifier'),
      '#default_value' => $settings['nexteuropa_listing_wrapper_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );
  }
  elseif ($context['instance']['display'][$context['view_mode']]['type'] == 'link_listing_title') {
    $display = $context['instance']['display'][$context['view_mode']];
    $settings = $display['settings'];

    $settings_form['nexteuropa_title_listing_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('List modifier'),
      '#default_value' => $settings['nexteuropa_title_listing_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );

    $settings_form['nexteuropa_title_item_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('Item modifier'),
      '#default_value' => $settings['nexteuropa_title_item_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );

    $settings_form['nexteuropa_title_item_link_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('Item link modifier'),
      '#default_value' => $settings['nexteuropa_title_item_link_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );
  }
}

/**
 * Implements hook_field_formatter_settings_summary_alter().
 */
function nexteuropa_formatters_field_formatter_settings_summary_alter(&$summary, $context) {
  global $_nexteuropa_formatters_listing_view_modes;

  if (
    $context['instance']['display'][$context['view_mode']]['type'] == 'entityreference_entity_view' &&
    $context['instance']['display'][$context['view_mode']]['settings']['view_mode'] == 'file'
  ) {
    $display = $context['instance']['display'][$context['view_mode']];
    $settings = $display['settings'];

    $file_settings = array(
      'Show file translations' => 'show_translations',
    );

    foreach ($file_settings as $label => $option) {
      if (isset($settings[$option])) {
        if (!empty($summary)) {
          $summary .= '<br />';
        }
        if ($settings[$option] == 1) {
          $settings[$option] = t('yes');
        }
        $summary .= $label . ': ' . $settings[$option];
      }
    }
  }

  if (
    $context['instance']['display'][$context['view_mode']]['type'] == 'entityreference_entity_view' &&
    in_array($context['instance']['display'][$context['view_mode']]['settings']['view_mode'], $_nexteuropa_formatters_listing_view_modes)
  ) {
    $display = $context['instance']['display'][$context['view_mode']];
    $settings = $display['settings'];
    if (isset($settings['nexteuropa_listing_columns'])) {
      if (!empty($summary)) {
        $summary .= '<br />';
      }
      $summary .= t('BEM: List layout: %columns', array('%columns' => $settings['nexteuropa_listing_columns']));
    }

    if (isset($settings['nexteuropa_listing_modifier']) && !empty($settings['nexteuropa_listing_modifier'])) {
      if (!empty($summary)) {
        $summary .= '<br />';
      }
      $summary .= t('BEM: Listing Modifier: %modifier', array('%modifier' => $settings['nexteuropa_listing_modifier']));
    }

    if (isset($settings['nexteuropa_listing_wrapper_modifier']) && !empty($settings['nexteuropa_listing_wrapper_modifier'])) {
      if (!empty($summary)) {
        $summary .= '<br />';
      }
      $summary .= t('BEM: Listing Wrapper Modifier: %wrapper_modifier', array('%wrapper_modifier' => $settings['nexteuropa_listing_wrapper_modifier']));
    }
  }
  elseif ($context['instance']['display'][$context['view_mode']]['type'] == 'link_listing_title') {
    $display = $context['instance']['display'][$context['view_mode']];
    $settings = $display['settings'];

    $modifiers = array(
      'List modifier' => 'nexteuropa_title_listing_modifier',
      'Item modifier' => 'nexteuropa_title_item_modifier',
      'Item link modifier' => 'nexteuropa_title_item_link_modifier',
    );

    foreach ($modifiers as $label => $modifier) {
      if (isset($settings[$modifier])) {
        if (!empty($summary)) {
          $summary .= '<br />';
        }
        $summary .= $label . ': ' . $settings[$modifier];
      }
    }
  }
}

/**
 * Implements hook_preprocess_field().
 */
function nexteuropa_formatters_preprocess_field(&$variables) {
  if (isset($variables['element']['#formatter'])) {

    // Convenient access to the important elements of the $variables.
    $entity_type = $variables['element']['#entity_type'];
    $field_name  = $variables['element']['#field_name'];
    $bundle      = $variables['element']['#bundle'];
    $view_mode   = $variables['element']['#view_mode'];

    switch ($variables['element']['#formatter']) {

      case 'entityreference_entity_view':

        // Fetch the instance settings and default display settings.
        $info = field_info_instance($entity_type, $field_name, $bundle);
        $formatter_settings = $info['display']['default']['settings'];
        if (isset($info['display'][$view_mode]['settings'])) {
          $formatter_settings = $info['display'][$view_mode]['settings'] + $formatter_settings;
        }
        // Make the setting available in the field template.
        $variables['nexteuropa_listing_columns'] = $formatter_settings['nexteuropa_listing_columns'];
        $variables['nexteuropa_listing_modifier'] = $formatter_settings['nexteuropa_listing_modifier'];
        $variables['nexteuropa_listing_wrapper_modifier'] = $formatter_settings['nexteuropa_listing_wrapper_modifier'];

        // Attach file translations when required.
        if ($formatter_settings['show_translations'] == 1) {
          foreach ($variables['items'] as $item_key => $item) {
            $variables['items'][$item_key]['#suffix'] = _nexteuropa_formatters_attach_translations($item);
          }
        }
        break;

    }
  }
}

/**
 * Helper to theme the markup of file translations.
 */
function _nexteuropa_formatters_attach_translations($item) {
  $node = node_load(key($item['node']));
  return theme('nexteuropa_file_translations', array('node' => $node));
}

/**
 * Implements hook_ds_fields_info().
 */
function nexteuropa_formatters_ds_fields_info($entity_type) {
  $fields = array();

  // President.
  $fields['cwt_team_president'] = array(
    'title' => t('Team: President (View: team members, president)'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'ui_limit' => array('team|*'),
    'function' => '_nexteuropa_formatters_theme_ds_team_field',
    'properties' => array(
      'view_machine_name' => 'team_members',
      'view_display' => 'block_1',
    ),
  );

  // Team role.
  $fields['cwt_team_role'] = array(
    'title' => t('Team: Role (View: team members, commissioners hierarchy, role arg)'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'ui_limit' => array('team|*'),
    'function' => '_nexteuropa_formatters_theme_ds_team_field',
    'properties' => array(
      'view_machine_name' => 'team_members',
      'view_display' => 'block_2',
      'views_arguments' => array('role'),
    ),
  );

  // Team project team.
  $fields['cwt_team_project_team'] = array(
    'title' => t('Team: Project team (View: team members by domain)'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'ui_limit' => array('team|*'),
    'function' => '_nexteuropa_formatters_theme_ds_team_field',
    'properties' => array(
      'view_machine_name' => 'team_members_by_domain',
      'view_display' => 'block',
    ),
  );

  // Team name.
  $fields['cwt_team_name'] = array(
    'title' => t('Team: Name (View: team members, commissioners hierarchy, name arg)'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'ui_limit' => array('team|*'),
    'function' => '_nexteuropa_formatters_theme_ds_team_field',
    'properties' => array(
      'view_machine_name' => 'team_members',
      'view_display' => 'block_3',
      'view_arguments' => array('name'),
    ),
  );

  return array('node' => $fields);
}

/**
 * Helper function to display test title.
 */
function _nexteuropa_formatters_theme_ds_team_field($field) {
  $view_machine_name = isset($field['properties']['view_machine_name']) ? $field['properties']['view_machine_name'] : NULL;
  $view_display = isset($field['properties']['view_display']) ? $field['properties']['view_display'] : NULL;
  $view_arguments = isset($field['properties']['view_arguments']) ? $field['properties']['view_arguments'] : NULL;

  if ($view_machine_name) {
    // Load: Views: team members, Commissioners Hierarchy.
    $view = views_get_view($view_machine_name);
    $view->set_display($view_display);
    $view->set_arguments($view_arguments);
    $view->pre_execute();
    $view->execute();
    return $view->render();
  }

  return FALSE;
}
