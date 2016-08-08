<?php
/**
 * @file
 * Provides functionality for the map entity.
 */

/**
 * Provides map entity properties and content.
 */
class MapController extends EntityAPIController {

  /**
   * Creates map entity and adds common properties such as author.
   */
  public function create(array $values = array()) {
    global $user;
    $values += array(
      'title' => '',
      'description' => '',
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'uid' => $user->uid,
    );
    return parent::create($values);
  }

  /**
   * Builds the content for displaying the map.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('map', $entity);
    $content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));

    // Sets defaults for theming properties like fields.
    $field_defaults = array(
      '#theme' => 'field',
      '#access' => TRUE,
      '#label_display' => 'hidden',
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

    $settings = new MapSettings();
    $settings->customize(drupal_json_decode($wrapper->settings->value()));

    // @todo prevent this.
    $settings = $settings->settings;

    // Creates the render array for the map.
    $map = new MapBuild($settings);

    // Adds custom JavaScripts defined by the map layers.
    // @todo figure out how to pass only the active map layer's js.
    $custom_js = array();
    $map_layers = module_invoke_all('layer_info');
    foreach ($map_layers as $map_layer) {
      $custom_js[] = $map_layer['custom_js'];
    }

    // Adds the map layer JavaScript as first (needs to be listed before any
    // other custom scripts).
    // @todo find decent solution.
    if (module_exists('ec_mapeditor_layer')) {
      $map_layer_js = base_path() . drupal_get_path('module', 'ec_mapeditor_layer') . "/js/map_layer.js?v=" . rand(0, 33333);
      $custom_js[] = $map_layer_js;
    }

    $ec_mapeditor_js = base_path() . drupal_get_path('module', 'ec_mapeditor') . "/js/map.js?v=" . rand(0, 33333);
    $custom_js[] = $ec_mapeditor_js;
    $map->setMoreCustomJs($custom_js);
    $content['map'] = $map->build;
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }

}

/**
 * Extends entity for map.
 */
class Map extends Entity {

  /**
   * Provides default label.
   */
  protected function defaultLabel() {
    return $this->title;
  }

  /**
   * Provides uri to view the stand alone map.
   */
  protected function defaultUri() {
    return array('path' => 'map/' . $this->identifier());
  }

}

/**
 * UI controller for map layer type.
 */
class MapUIController extends EntityDefaultUIController {

  // @codingStandardsIgnoreStart
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage maps.';
    return $items;
  }
  // @codingStandardsIgnoreEnd

}

/**
 * Provides map render array.
 *
 * This class constructs the build Drupal render array with the necessary
 * JavaScript and markup for the EC map service.
 */
class MapBuild {

  // Holds filename of custom JavaScript to be passed to load.js.
  private $customJs;

  /**
   * Defines defaults for the map construction (both geofield and NUTS).
   */
  public function __construct($settings) {
    $this->build = array();

    // Loads map service via load.js (general JavaScript service).
    $load_js = variable_get('ec_mapeditor_webtools_environment', EC_MAPEDITOR_WEBTOOLS_ENVIRONMENT);
    $element = array(
      '#type' => 'markup',
      '#markup' => "<script async src='$load_js' type='text/javascript'></script>",
    );
    drupal_add_html_head($element, 'async_script');

    // Prepares general map definitions and settings for JavaScript usage.
    // @todo fix different usages of height.
    $this->build['#attached']['js'][] = array(
      'data' => array(
        'settings' => $settings,
      ),
      'type' => 'setting',
    );
  }

  /**
   * Sets filename of custom JavaScript to be passed to load.js.
   *
   * @ todo. synch with setMoreCustomJs. Check if still in use.
   */
  public function setCustomJs($custom_js) {
    $this->customJs = $custom_js;

    // Defines which custom JavaScript file to provide to load.js.
    $js_path = base_path() . drupal_get_path('module', 'ec_mapeditor') . "/js/$this->customJs?v=" . rand(0, 33333);
    $options = drupal_json_encode(array(
      'service' => 'map',
      'custom' => $js_path,
    ));
    $this->build['load_js_vars'] = array(
      '#type' => 'markup',
      '#markup' => "<script type='application/json'>${options}</script>",
    );
  }

  /**
   * Sets filename of custom JavaScript to be passed to load.js.
   *
   * @todo. synch with setCustomJS.
   */
  public function setMoreCustomJs($custom_js) {

    // Defines which custom JavaScript file to provide to load.js.
    $options = drupal_json_encode(array(
      'service' => 'map',
      'custom' => $custom_js,
    ));
    $this->build['load_js_vars'] = array(
      '#type' => 'markup',
      '#markup' => "<script type='application/json'>${options}</script>",
    );
  }

  /**
   * Adds map features as JavaScript attachment to the build array.
   */
  public function setFeatures($features) {
    $this->build['#attached']['js'][] = array(
      'data' => array(
        'features' => $features,
      ),
      'type' => 'setting',
    );
  }

}
