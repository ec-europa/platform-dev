<?php
/**
 * @file
 * Definition of views_handler_area_f_a_q_collapsible_menu.
 */

/**
 * Views area handler to show (expand all/collapse all) menu for the FAQ list.
 */
class views_handler_area_f_a_q_collapsible_menu extends views_handler_area {
  /**
   * Return the collapsile menu.
   */
  public function render($empty = FALSE) {
    // Add a bit of jQuery to make it work.
    drupal_add_js(drupal_get_path('module', 'nexteuropa_faq') . '/faq.js');

    $output = '';

    // Build extra menu item for this view.
    $attributes = array(
      'type' => 'expand',
      'action_bar' => 'first',
      'btn_group' => 'first',
      'class' => array('action-expand'),
    );
    $output .= l(t('Expand all'), '<nolink>', array('attributes' => $attributes));
    $attributes = array(
      'type' => 'collapse',
      'btn_group' => 'last',
      'class' => array('action-collapse'),
    );
    $output .= l(t('Collapse all'), '<nolink>', array('attributes' => $attributes));

    return $output;
  }

}
