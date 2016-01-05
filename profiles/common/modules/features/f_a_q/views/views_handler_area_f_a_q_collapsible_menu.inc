<?php
/**
 * @file
 * Definition of views_handler_area_f_a_q_collapsible_menu.
 */

/**
 * Views area handler to display (expand all /collapes all) menu for the list of FAQ.
 */
class views_handler_area_f_a_q_collapsible_menu extends views_handler_area {

  function render($empty = FALSE) {
    // Add a bit of jQuery to make it work.
    drupal_add_js(drupal_get_path('module', 'f_a_q') . '/faq.js');

    $output = '';

    // Build extra menu item for this view.
    $attributes = array(
      'type' => 'expand',
      'action_bar' => 'first',
      'btn_group' => 'first',
      'class' => 'action-expand',
    );
    $output .= l(t('Expand all'), '', array('attributes' => $attributes));
    $attributes = array(
      'type' => 'collapse',
      'btn_group' => 'last',
      'class' => 'action-collapse',
    );
    $output .= l(t('Collapse all'), '', array('attributes' => $attributes));

    return $output;
  }

}
