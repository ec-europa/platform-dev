<?php

namespace Drupal\tmgmt_dgt_connector_cart\EntityUIController;

use EntityDefaultUIController;

/**
 * Entity UI controller for the Next Europa PIWIK rules.
 */
class CartBundleEntityUIController extends EntityDefaultUIController {

  /**
   * {@inheritdoc}
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    array_unshift($additional_header, t('Created'));
    array_unshift($additional_header, t('Changed'));
    array_unshift($additional_header, t('Target languages'));
    array_unshift($additional_header, t('UID'));
    array_unshift($additional_header, t('TMGMT Job ID'));
    array_unshift($additional_header, t('Status'));

    // Return the parent table headers with additional headers.
    return parent::overviewTableHeaders($conditions, $rows, $additional_header);
  }

  /**
   * {@inheritdoc}
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    array_unshift($additional_cols, $entity->created);
    array_unshift($additional_cols, $entity->changed);
    array_unshift($additional_cols, $entity->target_languages);
    array_unshift($additional_cols, $entity->uid);
    array_unshift($additional_cols, $entity->tjid);
    array_unshift($additional_cols, $entity->status);

    // Return the parent table row with additional columns.
    return parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
  }

  /**
   * {@inheritdoc}
   */
  public function overviewTable($conditions = array()) {
    $render = parent::overviewTable($conditions);
    // Add a unique id to the table. This will make it easier to target it
    // in acceptance tests.
    $render['#attributes']['id'] = 'tmgmt_dgt_connector_cart_bundle';

    return $render;
  }

  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['title'] = t('Cart Bundles');
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    return $items;
  }

}
