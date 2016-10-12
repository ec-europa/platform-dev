<?php
/**
 * @file
 * Definition of CachePurgeRuleEntityUIController.
 */

/**
 * Entity UI controller for cache purge rules.
 */
class CachePurgeRuleEntityUIController extends EntityDefaultUIController {

  /**
   * {@inheritdoc}
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    array_unshift($additional_header, t('Paths to Purge'));
    array_unshift($additional_header, t('Content Type'));

    $headers = parent::overviewTableHeaders($conditions, $rows, $additional_header);

    // We remove the 'Label' header, because our entity has no meaningful label.
    array_shift($headers);

    return $headers;
  }

  /**
   * {@inheritdoc}
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    array_unshift($additional_cols, preg_replace("/[\r\n]+/", ", ", $entity->paths));

    $content_type_names = node_type_get_names();
    $content_type_label = $content_type_names[$entity->content_type];
    array_unshift($additional_cols, $content_type_label);

    $row = parent::overviewTableRow($conditions, $id, $entity, $additional_cols);

    // We remove the 'Label' row, because our entity has no meaningful label.
    array_shift($row);

    return $row;
  }

  /**
   * {@inheritdoc}
   */
  public function overviewTable($conditions = array()) {

    $render = parent::overviewTable($conditions);

    // Add a unique id to the table. This will make it easier to target it
    // in acceptance tests.
    $render['#attributes']['id'] = 'frontend-cache-purge-rules';

    return $render;
  }

}
