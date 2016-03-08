Nexteuropa map
==============

Nexteuropa map provides functionality for creating maps with the webtools map JavaScript library (https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Map).

It allows users to create a map in a familiar Drupal UI. You can add several layers in a map.

## Features
* Creating maps with settings for tiles, height, center, zooming, marker bounding, attribution.
* Creating map layer with data from different sources, with settings for marker color, layer switch control, popup behaviour, clustering.
* Map field formatter to output geofields as a webtools Map
* Admin UI for managing maps.
* Admin UI for managing map layers.

## Layer types

A couple of layer types (map layer bundles) will be included:
* URL layer. Layer that fetches map data from external URLs (KML or GeoJSON).
* Country layer. Layer that creates map data (country outlines) from country codes. Each country can be styled individually.
* Nodes layer. Layer that fetches map data from drupal nodes.
* Tile layer. Layer that provides additional background images (tiles)).
* CSV layer. Layer that fetches map data from a CSV field (table with latitude, longitude, title and URL column).

## User stories

* As an anonymous user I can view maps
* As an editor I can create a map with multiple layers that can be enabled using the map layer control
* As an editor I can create map layers by entering URLs (kml GeoJSON)
* As an editor I can create map layers by entering country codes
* As an editor I can create map layers by entering CSV data with lat and lon
* As an editor I can create map layers by choosing background tiles (from EC tile server)
* As an editor I can create map layers by selecting nodes from the Drupal website
* As an administrator I can create Views that display as a map
* As an administrator I can configure a field so that it displays as a map
* As an administrator I can set the defaults for creating maps

## Contact persons
* Role, Name, Dept.
* Product owner, Some one ,DG Connect
* Coordinator, Luca Arnaudo, DG Connect
* Implementor, Boris Doesborg, DG Connect

## Contributed modules
* Geofield http://drupal.org/project/geofield
* Entity API http://drupal.org/project/entity
* Entity reference http://drupal.org/project/entity_reference
* Inline entity form http://drupal.org/project/inline_entity_form

## More info
* Nexteuropa map wiki://webgate.ec.europa.eu/fpfis/wikis/x/iKNDBg
* Corporate Map JavaScript library
  * https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Map
  * Demo's:
    * http://europa.eu/webtools/test/demo.htm?demo=demo
    * http://www.development.ec.europa.eu/fpfis/webtools/braijch/demo/map/?demo=kml_6
    * http://europa.eu/webtools/test/data/kml_demo.kml?toto=tutu
    * http://europa.eu/webtools/test/data/geojson.js
* Drupal contrib Leaflet module https://drupal.org/projects/leaflet
* Leaflet http://leaflet.js
  * https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Maps
  * http://ec.europa.eu/ipg/services/interactive_services/maps/index_en.htm
  * https://webgate.ec.europa.eu/fpfis/wikis/x/-MNDBg
