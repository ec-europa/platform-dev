<?php

namespace Drupal\tmgmt_dgt_connector_cart\EntityViewsController;

use EntityDefaultViewsController;

/**
 * Custom class to extend EntityDefaultViewsController.
 */
class CartBundleViewsController extends EntityDefaultViewsController {

  /**
   * {@inheritdoc}
   */
  public function views_data() {
    $data = parent::views_data();

    // Changing the handler type for date fields.
    $data['cart_bundle']['created']['field']['handler'] =
    $data['cart_bundle']['changed']['field']['handler'] = 'views_handler_field_date';

    // Injecting the custom handler for the target languages.
    $data['cart_bundle']['target_languages']['field']['handler'] = 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleLanguagesField';

    $data['cart_bundle']['cart_bundle_info'] = array(
      'title' => t('Bundle information'),
      'help' => t('Information related to the bundle.'),
      'real field' => 'cbid',
      'field' => array(
        'handler' => 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleInfoField',
      ),
    );

    $data['cart_bundle']['cart_bundle_table'] = array(
      'title' => t('Bundle table'),
      'help' => t('A table with the properties of the bundle.'),
      'real field' => 'cbid',
      'field' => array(
        'handler' => 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleTableField',
      ),
    );

    $data['cart_bundle']['cart_bundle_items_form_link'] = array(
      'title' => t('Bundle actions'),
      'help' => t('List of actions to perform on a Cart Bundle.'),
      'real field' => 'cbid',
      'field' => array(
        'handler' => 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleActionsField',
      ),
    );

    $data['cart_bundle']['cart_bundle_items_count'] = array(
      'title' => t('Bundle items character count'),
      'help' => t('The sum of all characters of related CartItem entities.'),
      'real field' => 'cbid',
      'field' => array(
        'handler' => 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleItemsCountDynamicField',
      ),
    );

    return $data;
  }

}
