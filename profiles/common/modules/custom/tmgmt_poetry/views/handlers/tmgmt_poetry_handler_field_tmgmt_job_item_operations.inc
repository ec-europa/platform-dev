<?php

/**
 * Change tmgmt_handler_field_tmgmt_job_item_operations Class to not show "delete" operation.
 */
class tmgmt_poetry_handler_field_tmgmt_job_item_operations extends tmgmt_handler_field_tmgmt_job_item_operations {

  function render($values) {

    $item = $this->get_value($values);
    $element = array();
    $element['#theme'] = 'links';
    $element['#attributes'] = array('class' => array('inline'));
    $uri = $item->uri();
    if ($item->getCountTranslated() > 0 && entity_access('accept', 'tmgmt_job_item', $item)) {
      $element['#links']['review'] = array(
        'href' => $uri['path'],
        'query' => array('destination' => current_path()),
        'title' => t('review'),
      );
    }
    // Do not display view on unprocessed jobs.
    elseif (!$item->getJob()->isUnprocessed()) {
      $element['#links']['view'] = array(
        'href' => $uri['path'],
        'query' => array('destination' => current_path()),
        'title' => t('view'),
      );
    }
    return drupal_render($element);
  }

}
