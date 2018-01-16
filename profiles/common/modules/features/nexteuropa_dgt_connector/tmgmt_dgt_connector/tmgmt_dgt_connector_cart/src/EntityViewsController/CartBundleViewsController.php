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
    $data['cart_bundle']['target_languages']['field']['handler'] = 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleField';

    $data['cart_bundle']['cart_bundle_items_titles'] = array(
      'title' => t('Bundle items titles'),
      'help' => t('The titles list of related CartItems entities.'),
      'real field' => 'cbid',
      'field' => array(
        'handler' => 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleItemsTitlesDynamicField',
      ),
    );

    $data['cart_bundle']['cart_bundle_items_form_link'] = array(
      'title' => t('Bundle items link'),
      'help' => t('The list of CartItems entities for a given CartBundle.'),
      'real field' => 'cbid',
      'field' => array(
        'handler' => 'Drupal\\tmgmt_dgt_connector_cart\\ViewsHandler\\CartBundleItemsFormLinkDynamicField',
      ),
    );

    return $data;
  }

}
