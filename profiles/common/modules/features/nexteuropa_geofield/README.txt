INTRODUCTION
------------
This module provides 
- a new field type (geofield geoJSON) to store geoJSON data
- a widget with an interactive map and tools to add objects on the map   
- the geojson data (in json format) can be get through an URL : node/X/geojson

REQUIREMENTS
------------
The libraries leaflet and leaflet.draw are required.


CONFIGURATION
-------------
In a content type, add a new file of type geofield geoJSON.
In the field settings, you can : 
- provide a default map center (longitude, latitude)
- define the map objects allowed on the map
- set the maximum number of objects on the map

If the number of objects is set to 1, new options are available.
You can choose which fields of the content can be used to prepopulate the 
popup label of the map object.


RESTRICTIONS
------------
Only ONE geofield geoJSON is managed on a content type.
