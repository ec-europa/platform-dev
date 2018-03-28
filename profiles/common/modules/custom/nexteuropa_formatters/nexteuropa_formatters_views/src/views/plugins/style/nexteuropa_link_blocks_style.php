<?php

/**
 * @file
 * nexteuropa_links_block_style.php.
 */

/**
 * Views style plugin.
 *
 * @codingStandardsIgnoreFile
 */
class nexteuropa_link_blocks_style extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['type'] = array('default' => 'ul');
    $options['class'] = array('default' => '');
    $options['wrapper_class'] = array('default' => 'other_class');

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['type'] = array(
      '#type' => 'radios',
      '#title' => t('List type'),
      '#options' => array('ul' => t('Unordered list'), 'ol' => t('Ordered list')),
      '#default_value' => $this->options['type'],
    );
    $form['wrapper_class'] = array(
      '#title' => t('Wrapper class'),
      '#description' => t('The class to provide on the wrapper, outside the list.'),
      '#type' => 'textfield',
      '#size' => '30',
      '#default_value' => $this->options['wrapper_class'],
    );
    $form['class'] = array(
      '#title' => t('List class'),
      '#description' => t('The class to provide on the list element itself.'),
      '#type' => 'textfield',
      '#size' => '30',
      '#default_value' => $this->options['class'],
    );
  }

  /**
   * {@inheritdoc}
   */
  function render_grouping_sets($sets, $level = 0) {
    $output = '';
    foreach ($sets as $set) {
      $row = reset($set['rows']);
      // Render as a grouping set.
      if (is_array($row) && isset($row['group'])) {
        $output .= theme(views_theme_functions('views_view_grouping', $this->view, $this->display),
          array(
            'view' => $this->view,
            'grouping' => $this->options['grouping'][$level],
            'grouping_level' => $level,
            'items' => $set['rows'],
            'title' => $set['group'])
        );
      }
      // Render as a record set.
      else {
        if ($this->uses_row_plugin()) {
          foreach ($set['rows'] as $index => $row) {
            $this->view->row_index = $index;

            $text = $set['rows'][$index]->users_name;
            $path = 'user/' . $set['rows'][$index]->uid;
            $options['attributes']['class'][] = array(
              'ecl-link',
              'ecl-link--standalone',
              'ecl-link-block__link',
            );
            $set['rows'][$index] = theme('link', array('text' => $text, 'path' => $path , 'options' => $options));
          }
        }

        $output .= theme($this->theme_functions(),
          array(
            'view' => $this->view,
            'options' => $this->options,
            'grouping_level' => $level,
            'items' => $set['rows'],
            'title' => $set['group'])
        );
      }

    }
    unset($this->view->row_index);
    return $output;
  }

}