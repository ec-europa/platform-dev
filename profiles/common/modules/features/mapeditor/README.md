# Mapeditor

## Description
Mapeditor provides functionality for creating maps with the corporate Map JavaScript library. 
Mapeditor is based on the Drupal contrib module Leaflet (and Leaflet Views) and re-uses many of its code.

## Features
* Content type Mapeditor map with content filters (by node type and taxonomy term) and map settings (marker color, zoom levels, etc.).
* Integration with the corporate Map JavaScript library.
* Create maps with NUTS regions (based on the NUTS regions vocabulary that is included in the EC world countries features)
* View style plugin
* Field formatter for geofields (http://drupal.org/project/geofield)
* View mode "Pop-up" that can be used for the map pop-ups.
* Admin UI to set defaults.
* Sub module EC Geocoder provides a geocoder button on geofields that allows fetching coordinates from the corporate geocoding service.
* Sub module Mapmock that provides fake users and content for generating and testing maps. This module is not needed nor recommended on production websites.

## Pre-requisites
To use webtools js libraries several conditions must be met:

* Webtools load.js must be loaded as https:// . http:// will result in access denied.
* The domain names should contain ec.europa.eu . E.g. http://mapper.val.ec.europa.eu. Other domain names will reuslt in access denied.
* For the staging server include the wtenv parameters wtenv=acc in the url. E.g. http://mapper.val.ec.europa.eu/node/12?wtenv=acc . If missing it results in access denied.
* For the staging server: login through browser with htaccess username and password. Otherwise, you know what happens.

## Mapeditor configuration & usage

### Configuration
1. Enable the module mapeditor
2. Optionally enable the module Mapeditor Views if you want to create Views as maps
3. Configure the module via Administration > Configuration > System > Mapeditor > Mapeditor settings (http://example.com/admin/config/system/mapeditor/settings)
4. Enter the correct url for the corporate webtool JavaScript map library
5. In Mapeditor data choose the content types that will be available as filter in the Mapeditor Map content type
6. In Mapeditor data choose the vocabularies that will be available as filters in the Mapeditor Map content type
7. Check "Show unpublished" if you want to show unpublished content in a map
8. Click "Save configuration" to save the settings

### Creating a map node
1. Create a map node via Administration > Content > Add content > Map (by mapeditor) (http://example.com/node/add/mapeditor-map)
2. Enter a title for the map
3. Choose type of data (latitude and longitude or NUTS)
4. Choose map data (site content or CSV)
5. Choose the type of content from where to fetch data or enter data in the CSV data text area
6. Optionally cahnge the default maps settings for tiles, zoom levels et cetera
7. Optionally enter a body text for the map
8. Click Save to save the map

### Using map as field formatter
A field formatter is a setting for displaying field content. Mapeditor provides a field formatter that allows displaying a latitude & longitude field as a map

1. Select "Manage display" for the desired entity (node, user, taxonomy term, etc)
2. In the select list "Format" of the field that contains the geo data, choose "European Commission map"
3. Click the cog wheel on the right to set the configuration options (such as tile, height, icon color, zoom levels et cetera)
4. Click "Update" to update the settings
5. Click "Save" to save the settings.
6. Verify by viewing the entity.

### Create a map using Views
1. (If not already done) enable the module "Mapeditor views"
2. Create a View via Administration > Structure > Views
3. Add a field (of the type Geofield) that holds a latitude and longitude (this must be a Geofield field)
4. Set the view's Format to "Mapeditor Map", and choose the Geo data field you just added (see previous step)
5. Choose the view mode for the pop-ups. Optionally, Mapeditor provides a view mode pop-up for this purpose.
6. Optinally, set additional configuration options (such as tile, height, icon color, zoom levels et cetera)
7. Customize the filtering, sorting etc. of the view in the usual way (for example remove pagination because this makes less sense with a map)
8. Click Save to save your settings.

## Geocoder configuration & usage

### Configuration
1. Enabled the module ec_geocoder if you wish to use the geocoding functionality
2. Configure the module at http://example.com/admin/config/system/mapeditor/settings
3. Configure the module via Administration > Configuration > System > EC geocoder > EC geocoder settings (http://example.com/admin/config/system/ec_geocoder/settings)
4. Enter the correct url for the corporate geocoder service
5. Choose a minimum quality for the results (results lower than this value are discarded)
6. Click "Save configuration" to save the settings

### Using geocoder
To use geocoder in an entity (node, taxonomy term, user, etc.) you need:

- address field (provided by the addressfield module)
- latitude & longitude field  (provided by the geofield module)

1. Enter an address in the address field
2. Click "Geocode" (under the latitude & longitude field)
3. If the geocoder service returns a result then the values are entered in in the latitude & longitude field

## User stories
* As a anonymous user I can view maps
* As a contributor I can create a maps (as ordinary content items (nodes)) in a 2 or 3 simple steps.
* As an editor I can create & moderate maps
* As an editor I can create NUTS maps
* As a webmaster I can create views that display as a map.
* As a webmaster I can format a field so that it displays as a map.
* As a webmaster I can set the defaults for creating maps

## Contact persons
* Role, Name, Dept.
* Product owner, Some one ,DG Connect
* Coordinator, Luca Arnaudo, DG Connect
* Implementor, Boris Doesborg, DG Connect

## Contributed modules
* Geofield http://drupal.org/project/geofield

## More info
* Corporate Map JavaScript library
  * https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/MAP
  * http://europa.eu/webtools/test/demo.htm?demo=demo
* Mapeditor on the CITNET wiki https://webgate.ec.europa.eu/fpfis/wikis/x/iKNDBg
* Drupal contrib Leaflet module https://drupal.org/projects/leaflet
* Leaflet http://leaflet.js
