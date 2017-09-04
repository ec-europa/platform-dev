<?php
/**
 * @file
 * Definition of PiwikRuleEntityUIController.
 */

namespace Drupal\nexteuropa_piwik\EntityDefaultUIController;

use \EntityDefaultUIController;

/**
 * Entity UI controller for the Next Europa PIWIK rules.
 */
class PiwikRuleEntityUIController extends EntityDefaultUIController {

  /**
   * {@inheritdoc}
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    // Rule path type header.
    array_unshift($additional_header, t('Path type'));
    // Rule paths header.
    array_unshift($additional_header, t('Path'));
    // Rule language header.
    array_unshift($additional_header, t('Language'));
    // Rule section header.
    array_unshift($additional_header, t('Section'));

    // Get the parent table headers.
    $headers = parent::overviewTableHeaders($conditions, $rows, $additional_header);

    return $headers;
  }

  /**
   * {@inheritdoc}
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    // Rule paths row.
    array_unshift($additional_cols, $entity->rule_path_type);
    // Rule paths row.
    array_unshift($additional_cols, $entity->rule_path);
    // Rule language row.
    array_unshift($additional_cols, $entity->rule_language);
    // Rule section row.
    array_unshift($additional_cols, $entity->rule_section);

    // Get the parent table row.
    $row = parent::overviewTableRow($conditions, $id, $entity, $additional_cols);

    return $row;
  }

  /**
   * {@inheritdoc}
   */
  public function overviewTable($conditions = array()) {
    $render = parent::overviewTable($conditions);

    // Add a unique id to the table. This will make it easier to target it
    // in acceptance tests.
    $render['#attributes']['id'] = 'next-europa-piwik-rules';

    return $render;
  }

  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['title'] = t('Advanced PIWIK rules');
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    return $items;
  }

}
