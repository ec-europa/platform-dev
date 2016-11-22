<?php

/**
 * @file
 * Provides functionality for the Map layer entity.
 */

/**
 * Extends creation and displaying map layer entity.
 */
class MapLayerController extends EntityAPIController {

  /**
   * Extends creation of map layer entity.
   */
  public function create(array $values = array()) {
    global $user;
    $values += array(
      'title' => '',
      'description' => '',
      'settings' => '',
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'uid' => $user->uid,
    );
    return parent::create($values);
  }

  /**
   * Provides per view mode content for displaying the map layer entity.
   */
  public function buildContent($entity, $view_mode = 'map_layer', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('map_layer', $entity);
    switch ($view_mode) {

      // Defines content when viewing a map layer in the default view mode.
      case 'default':
        $content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));

        // Sets defaults for theming properties like fields.
        $field_defaults = array(
          '#theme' => 'field',
          '#access' => TRUE,
          '#label_display' => 'above',
          '#view_mode' => 'default',
          '#language' => LANGUAGE_NONE,
          '#field_type' => 'text',
          '#entity_type' => 'map_layer',
          '#bundle' => $entity->type,
        );

        // Themes description like default field.
        $content['description'] = array(
          '#weight' => 0,
          '#field_name' => 'field_fake_description',
          '#title' => t('Description'),
          '#items' => array(array('value' => $entity->description)),
          '#formatter' => 'text_default',
          0 => array(
            '#markup' => check_plain($entity->description),
          ),
        ) + $field_defaults;

        // Themes settings like default field.
        $content['settings'] = array(
          '#title' => t('Settings'),
          '#field_name' => 'field_fake_settings',
          '#items' => array(array('value' => $entity->settings)),
          '#formatter' => 'text_default',
          0 => array(
            '#markup' => check_plain($entity->settings),
          ),
        ) + $field_defaults;

        break;

      // Defines output for the map_layer view mode (adapted for the EC webtools
      // JavaScript library).
      case 'map_layer':

        // Allows other modules to change the content of the map. Each map
        // layer type can live in its own module.
        drupal_alter('layer_content', $content, $wrapper, $entity);

        break;
    }
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }

}

/**
 * Extends create and save functions of map layer type entity.
 */
class MapLayerTypeController extends EntityAPIControllerExportable {

  /**
   * Create map layer type.
   */
  public function create(array $values = array()) {
    $values += array(
      'label' => '',
      'description' => '',
    );
    return parent::create($values);
  }

  /**
   * Save map layer type.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);

    // Rebuilds menu registry. We do not call menu_rebuild directly, but set
    // variable that indicates rebuild in the end.
    // @see http://drupal.org/node/1399618
    variable_set('menu_rebuild_needed', TRUE);
  }

}

/**
 * UI controller for map layer type.
 */
class MapLayerTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  // @codingStandardsIgnoreStart
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Map layer types.';
    return $items;
  }
  // @codingStandardsIgnoreEnd

}

/**
 * Map layer class.
 */
class MapLayer extends Entity {

  /**
   * Provides the label for the map layer entity.
   */
  protected function defaultLabel() {
    return $this->title;
  }

  /**
   * Provides uri to view a map layer.
   */
  protected function defaultUri() {
    return array('path' => 'map-layer/' . $this->identifier());
  }

}

/**
 * Map layer type class.
 */
class MapLayerType extends Entity {
  public $type;
  public $label;
  public $weight = 0;

  /**
   * Constructs map layer type entity.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'map_layer_type');
  }

  /**
   * Checks if entity type is locked.
   */
  public function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }

}

/**
 * Defines the inline entity form for the map layer entity.
 */
class MapLayerInlineEntityFormController extends EntityInlineEntityFormController {

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   *
   * @todo figure out how to merge / cooperate stand alone form.
   */
  public function entityForm($entity_form, &$form_state) {

    $entity_form['#tree'] = TRUE;

    // Fetches settings from settings field of current entity.
    $map_layer = $entity_form['#entity'];

    // Loads settings.
    $settings = new MapLayerSettings();
    if (!empty($map_layer->settings)) {
      $settings->customize(drupal_json_decode($map_layer->settings));
    }
    // @todo. how to prevent this?
    $settings = $settings->settings;

    // Defines label field.
    $entity_form['name'] = array(
      '#title' => t('Label'),
      '#type' => 'textfield',
      // @todo make consistent use of lable or title
      '#default_value' => isset($map_layer->title) ? $map_layer->title : '',
      '#description' => t('Name of the map layer. This will be used in the layer control.'),
      '#required' => TRUE,
      '#weight' => -50,
    );

    // Provides checkboxes to define how the layer is shown in the layer
    // control.
    $control_form_element = _ec_mapeditor_custom_map_form_elements(array('control'), $settings);
    $entity_form += $control_form_element;

    // Adds custom field API fields.
    field_attach_form('map_layer', $map_layer, $entity_form, $form_state);

    // Adds custom form elements defined by the active map layer sub module.
    $type = $map_layer->type;
    $map_layers = module_invoke_all('layer_info');
    $elements = $map_layers[$type]['form_elements'];
    $custom_form_elements = _ec_mapeditor_custom_map_form_elements($elements, $settings);
    $entity_form += $custom_form_elements;

    // Allow modules to alter the map layer inline entity form.
    $type = $map_layer->type;
    drupal_alter('layer_form', $entity_form, $settings, $type);

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);
    $map_layer = $entity_form['#entity'];
    $settings = array();

    // Fetches values of form elements of map layer and stores them in a
    // settings array.
    $map_layers = module_invoke_all('layer_info');
    $elements = $map_layers[$map_layer->type]['form_elements'];
    foreach ($elements as $element) {
      foreach ($map_layer->$element as $key => $value) {
        $settings[$element][$key] = $value;
      }
    }

    // Sets the generic layer settings.
    $settings['control'] = $map_layer->control;

    // Adds values of custom field the settings.
    $settings = _ec_mapeditor_layer_save_settings($settings, $form_state);

    // Stores the layer settings in json (different settings per layer type).
    $map_layer->settings = drupal_json_encode($settings);

    // Updates last change date.
    $map_layer->changed = REQUEST_TIME;
    $map_layer->title = $map_layer->name;
  }

  /**
   * Overrides EntityInlineEntityFormController::save().
   */
  public function save($entity, $context) {
    $entity->save();
  }

}
