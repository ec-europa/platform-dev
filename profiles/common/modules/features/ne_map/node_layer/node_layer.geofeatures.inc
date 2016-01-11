<?php

/**
 * @file
 * Provides feature in geojson format for Mapeditor Map.
 */

/**
 * Class providing feature in geojson format for Mapeditor Map.
 */
class MapeditorGeoFeature {

  /**
   * Defines defaults.
   */
  public function __construct() {
    $this->data = array(
      'type' => 'Feature',
      'properties' => array(),
      'geometry' => array(),
    );
  }

  /**
   * Sets properties.
   */
  public function setProperties($name, $popupcontent) {
    $this->data['properties'] = array(
      'name' => $name,
      'popupContent' => $popupcontent,
    );
  }

  /**
   * Sets geometry.
   *
   * Currently 3 types are provided: points, linestrings and polygons. Each has
   * slightly different coordinates format.
   */
  public function setGeometry($type, $component) {
    switch ($type) {
      case 'Point':
        $this->data['geometry'] = array(
          'type' => 'Point',

          // Sets coordinates in GeoJSON format: X,Y (lon, lat).
          'coordinates' => array($component->getX(), $component->getY()),
        );
        break;

      case 'Polygon':
        $coordinates = array();
        $tmp = $component->getComponents();
        $points = $tmp[0]->getComponents();
        foreach ($points as $point) {

          // Sets coordinates in GeoJSON format: X,Y (lon, lat).
          $coordinates[] = array($point->getX(), $point->getY());
        }
        unset($points);
        $this->data['geometry'] = array(
          'type' => 'Polygon',
          'coordinates' => array($coordinates),
        );
        unset($coordinates);
        break;

      case 'LineString':
        $coordinates = array();
        $points = $component->getComponents();
        foreach ($points as $point) {

          // Sets coordinates in GeoJSON format: X,Y (lon, lat).
          $coordinates[] = array($point->getX(), $point->getY());
        }
        unset($points);
        $this->data['geometry'] = array(
          'type' => 'LineString',
          'coordinates' => $coordinates,
        );
        unset($coordinates);
        break;

    }
  }

}
