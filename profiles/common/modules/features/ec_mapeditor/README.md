EC mapeditor
==============

EC mapeditor provides functionality for creating maps with the webtools map JavaScript library (https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Map).

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

## Installation and configuration
* Enabled the ec_mapeditor_layer module
* Go to People > Permissions (admin/people/permissions) and assign permissions for the EC mapeditor and map layer modules.
* Go to Structure > Feature sets (admin/structure/feature-set)
* Enable a layer type module (for example CSV layer)

## Usage
* Go to Structure > Map (admin/structure/maps) to create and edit maps.
* Go to Structure > Map layers (admin/structure/maps) to adminsiter map layers (you can create and edit them through the map edit form).

### Create a map
* Go to Structure > Map (admin/structure/maps).
* Click _Add map_
* Enter a name and description for the map
* Choose the map layer type and click _Add new entity_
* Enter the map layer details (can be different for eacht map layer type)
* Change the values for height, centering, zooming and attribution
* Click _Save map_

## Using map as field formatter

A field formatter is a setting for displaying field content. EC mapeditor provides a field formatter that allows displaying a latitude & longitude field as a map

* Select "Manage display" for the desired entity (node, user, taxonomy term, etc)
* In the select list "Format" of the field that contains the geo data (most often a geofield type field), choose "European Commission map"
* Click the cog wheel on the right to set the configuration options (such as tile, height, icon color, zoom levels et cetera)
* Click "Update" to update the settings
* Click "Save" to save the settings.
* Verify by viewing the entity.

## Credits
EC mapeditor is provided by DG Connect's web team.
Authors: Boris DOESBORG, Cedric ALLEN, Luca ARNAUDO
Maps is provided by DG Communication's Webtools team.
Acknowledgements: Laurent Jacques CORVELEYN, Christophe BRAIJE, Hannes REUTER
The feature has been proposed for generic use to the product owners of Next Europa.

## Copyright
* Background maps available in the Webtools feature can only be used on European Commission and inter-institutional websites. For more info:  Laurent Jacques CORVELEYN (COMM)
* Boundaries of countries and NUTS regions are copyright EuroGeographics and copyright UN-FAO and are for Inter-Institutional use only. For more info:  Hannes REUTER (ESTAT)
* Maps is provided by the Webtools team

## Contact persons
* DOESBORG Boris (CNECT) <Boris.DOESBORG@ext.ec.europa.eu>, developer, DG Connect
* ARNAUDO Luca (CNECT) <Luca.ARNAUDO@ec.europa.eu>, team leader, DG Connect

## Contributed modules
* Geofield http://drupal.org/project/geofield
* Entity API http://drupal.org/project/entity
* Entity reference http://drupal.org/project/entity_reference
* Inline entity form http://drupal.org/project/inline_entity_form

## More info
* EC mapeditor wiki://webgate.ec.europa.eu/fpfis/wikis/x/iKNDBg
* Presentation: https://docs.google.com/presentation/d/1U-7f0NXF9qhZqZb-MUbPR6Q3Z_2a68xy-g198ZO3atE/edit?usp=sharing
* Demo: https://www.youtube.com/playlist?list=PLITBVpXjSIMRHdgmz8C-BXhTwSjEjH0j5
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
