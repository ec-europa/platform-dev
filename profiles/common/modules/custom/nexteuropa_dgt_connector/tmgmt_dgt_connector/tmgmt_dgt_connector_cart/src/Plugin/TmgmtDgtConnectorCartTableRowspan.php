<?php

/**
 * @file
 * Views handler display Table Rowspan.
 */

/**
 * Style plugin to merge duplicate row in table.
 *
 * @ingroup views_style_plugins
 */
class TmgmtDgtConnectorCartTableRowspan extends views_plugin_style_table {
  // @codingStandardsIgnoreStart: Default views methods can't be renamed.
  /**
   * Overwrite method option_definition().
   *
   * Add new option 'rowspan'.
   */
  function option_definition() {
    $options = parent::option_definition();

    // Option to merge duplicate rows in to one row.
    $options['rowspan'] = array('default' => TRUE);

    return $options;
  }

  /**
   * Overwrite method options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['rowspan'] = array(
      '#type' => 'checkbox',
      '#title' => t('Merge rows in table'),
      '#description' => t('Merge rows table that has same value (in a same group) use attribute !url', array('!url' => '<a href="http://www.w3schools.com/tags/att_td_rowspan.asp">rowspan.</a>')),
      '#default_value' => $this->options['rowspan'],
      '#weight' => 0,
    );
  }

  /**
   * Overwrite method render_grouping_sets().
   *
   * Merge all group in one table, then merge duplidate row to one row.
   */
  function render_grouping_sets($sets, $level = 0) {
    if (!empty($this->options['grouping'])) {
      if (!empty($this->options['rowspan'])) {
        $rows = $this->get_colspan_rows($sets);
        $sets = array(
          array(
            'group' => '',
            'rows' => $rows,
          ),
        );
        // Convert sets to one group.
        $this->options['grouping'] = array();
      }
    }

    return parent::render_grouping_sets($sets, $level);
  }

  /**
   * Convert grouping sets into table rows.
   *
   * @param array $sets
   *   Views grouping sets.
   * @param int $level
   *   Nesting level.
   * @param array $parent
   *   Parent set.
   *
   * @return array
   *   An array of rows in table.
   */
  protected function get_colspan_rows(array $sets, $level = 0, array $parent = array()) {
    $rows = array();
    $leaf_rows = array();
    $group_field_name = $this->options['grouping'][$level]['field'];

    foreach ($sets as $set) {
      $new_level = $level + 1;

      $leaf_rows = $this->_get_deepest_row($set);
      $leaf_rows_index = array_keys($leaf_rows);
      $first_index = $leaf_rows_index[0];
      $this->view->rowspan[$group_field_name][$first_index] = $leaf_rows_index;
      $row = reset($set['rows']);

      if (is_array($row) && isset($row['group'])) {
        $rows += $this->get_colspan_rows($set['rows'], $new_level, $set);
      }
      else {
        foreach ($set['rows'] as $index => $set_row) {
          $rows[$index] = $set_row;
        }
      }
    }

    return $rows;
  }

  /**
   * Get deepest rows in a group.
   *
   * @param array $set
   *   View grouping set.
   */
  protected function _get_deepest_row(array $set) {
    $row = reset($set['rows']);

    // Check set is a group or a row.
    if (is_array($row) && isset($row['group'])) {
      $result = array();
      foreach ($set['rows'] as $sub_set) {
        $subset_result = $this->_get_deepest_row($sub_set);
        $result += $subset_result;
      }

      return $result;
    }
    else {
      $_result = array();
      foreach ($set['rows'] as $row_index => $row) {
        $_result[$row_index] = $row;
      }

      return $_result;
    }
  }
  // @codingStandardsIgnoreEnd

}
