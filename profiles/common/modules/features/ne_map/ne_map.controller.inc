<?php

class MapController extends EntityAPIController {

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

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('ne_map', $entity);
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
          '#markup' => check_plain($entity->description)
        )
      ) + $field_defaults;

    // Themes settings like default field.
    $content['settings'] = array(
        '#title' => t('Settings'),
        '#field_name' => 'field_fake_settings',
        '#items' => array(array('value' => $entity->settings)),
        '#formatter' => 'text_default',
        0 => array('#markup' => check_plain($entity->settings))
      ) + $field_defaults;

    $settings = new NEMapSettings();
    $settings->customize(drupal_json_decode($wrapper->settings->value()));

    // @todo prevent this
    $settings = $settings->settings;

    // Builds the map.
    $map = new MapBuild($settings);

    // Defines custom JavaScripts to be passed to load.js.
    $custom_js = array();



    // Allow modules to alter the map build.
    drupal_alter('ne_map_build_content', $custom_js);
//    // @todo find decent solution.
    if(module_exists('map_layer')) {
      $map_layer_js = base_path() . drupal_get_path('module', 'map_layer') . "/js/map_layer.js?v=" . rand(0, 33333);
      $custom_js[] = $map_layer_js;
    }

    $ne_map_js = base_path() . drupal_get_path('module', 'ne_map') . "/js/ne_map.js?v=" . rand(0, 33333);
    $custom_js[] = $ne_map_js;
    $map->setMoreCustomJs($custom_js);
    $content['map'] = $map->build;
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}

/**
 * Map class.
 */
class Map extends Entity {
  protected function defaultLabel() {
    return $this->title;
  }

  protected function defaultUri() {
    return array('path' => 'map/' . $this->identifier());
  }
}

/**
 * UI controller for map layer type.
 */
class MapUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage maps.';
    return $items;
  }
}


/**
 * Class providing build definitions for a map.
 *
 * This class constructs the build drupal render array with the necessary
 * JavaScript and markup for the EC map service. It can provide geofield or
 * NUTS maps.
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
    $load_js = variable_get('webtools_environment', NE_MAP_WEBTOOLS_ENVIRONMENT);
    $element = array(
      '#type' => 'markup',
      '#markup' => "<script async src='$load_js' type='text/javascript'></script>",
    );
    drupal_add_html_head($element, 'async_script');

    // Prepares general map definitions and settings for JavaScript usage.
    // @todo fix different usages of height


    $this->build['#attached']['js'][] = array(
      'data' => array(
        'settings' => $settings,
      ),
      'type' => 'setting',
    );
  }

  /**
   * Sets filename of custom JavaScript to be passed to load.js.
   * @ todo. synch with setMoreCustomJs
   *
   */
  public function setCustomJs($custom_js) {
    $this->customJs = $custom_js;

    // Defines which custom JavaScript file to provide to load.js.
    $js_path = base_path() . drupal_get_path('module', 'mapeditor') . "/js/$this->customJs?v=" . rand(0, 33333);
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
   * @ todo. synch with setCustomJS
   */
  public function setMoreCustomJs($custom_js) {
//    $this->customJs = $custom_js;

    // Defines which custom JavaScript file to provide to load.js.
//    $js_path = base_path() . drupal_get_path('module', 'mapeditor') . "/js/$this->customJs?v=" . rand(0, 33333);
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
   * Defines map build array for geofield map data (coordinates).
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
