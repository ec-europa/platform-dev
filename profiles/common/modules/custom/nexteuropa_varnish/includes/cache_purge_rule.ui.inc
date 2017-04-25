<?php
/**
 * @file
 * Definition of CachePurgeRuleEntityUIController.
 */

use Drupal\nexteuropa_varnish\PurgeRuleType;

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
    $paths_cell_content = '<em>' . t('paths of the node') . '</em>';

    if ($entity->type() == PurgeRuleType::PATHS) {
      $paths_cell_content = check_plain(implode(', ', $entity->paths()));
    }

    array_unshift($additional_cols, $paths_cell_content);

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

  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['title'] = t('Purge rules');
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    return $items;
  }

  /**
   * {@inheritdoc}
   */
  public function entityFormSubmitBuildEntity($form, &$form_state) {
    // We clear the purge rules cache entries related to the content type.
    $content_type = $form_state['values']['content_type'];
    cache_clear_all('nexteuropa_varnish_get_node_purge_rules_' . $content_type, 'cache_nexteuropa_varnish');
    return parent::entityFormSubmitBuildEntity($form, $form_state);
  }

}
