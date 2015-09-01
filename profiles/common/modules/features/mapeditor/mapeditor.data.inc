<?php

/**
 * @file
 * Provides data (NUTS or coordinates) for Mapeditor Map.
 */

/**
 * Class providing data (NUTS or coordinates) for a map.
 *
 * This class constructs the nuts or features arrays that are displayed in
 * maps.
 */
class MapeditorMapData {

  /**
   * Defines defaults.
   */
  public function __construct() {
    $this->data = NULL;
    $this->nuts = array();
    $this->nuts_regions_field_name = NULL;
  }

  /**
   * Processes CSV data as build ready NUTS.
   */
  public function setNuts($data, $source) {
    switch ($source) {
      case 'csv':
        $lines = explode("\n", $data);
        $csv_data = array();
        foreach ($lines as $line) {
          if (isset($line[0])) {
            $csv_data[] = str_getcsv($line);
          }
        }
        foreach ($csv_data as $item) {
          $nut = strtoupper($item[0]);
          $title = check_plain($item[1]);
          $url = $item[2];
          $this->nuts[$nut] = array(
            'title' => $title,
            'url' => $url,
          );
        }
        break;

      case 'entities':
        foreach ($data as $map_item) {
          $wr_map_item = entity_metadata_wrapper('node', $map_item);
          $field_name = $this->nuts_regions_field_name;
          if (_mapeditor_fieldcheck($field_name, $wr_map_item)) {

            // @todo . replace w nuts code when JS can handle that.
            $code = $wr_map_item->$field_name->nuts_country->value();
            $nuts_keys[] = $code;
            if (_mapeditor_fieldcheck('name', $wr_map_item)) {
              $this->nuts[$code]['title'] = $wr_map_item->name->value();
            }
            if (_mapeditor_fieldcheck('title', $wr_map_item)) {
              $this->nuts[$code]['title'] = $wr_map_item->title->value();
            }
            if (_mapeditor_fieldcheck('url', $wr_map_item)) {
              $this->nuts[$code]['url'] = $wr_map_item->url->value();
            }
          }
        }
        break;
    }
  }

  /**
   * Return NUTS in build ready format.
   */
  public function getNuts() {
    return $this->nuts;
  }

  /**
   * Return NUTS in build ready format.
   */
  public function setNutsRegionsFieldName($name) {
    $this->nuts_regions_field_name = $name;
  }

}
