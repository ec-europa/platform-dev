INTRODUCTION
------------
This module provides 
- A new field type (geofield geoJSON) to store geoJSON data
- A widget with an interactive map and tools to add objects on the map   
- The geojson data (in json format) can be get through an URL : node/X/geojson

REQUIREMENTS
------------
The libraries leaflet and leaflet.draw are required.
Those libraries are part of the platform core.
Also read [WCM requirements](https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/WCM+-+GIS+fields)

CONFIGURATION
-------------
To get started add a new field of type geofield geoJSON to your content type.
In the field settings, you can : 

- Provide a default map center (longitude, latitude). If you don't Brussels will
show.

- Define the map objects allowed on the map. There are 4 types of objects:
  - polygon
  - rectangle
  - marker
  - polyline

- Set the maximum number of objects on the map.

If the number of objects is set to 1, new options are available.
You can choose which fields of the content can be used to prepopulate the 
popup label of the map object.

`Polygon`
Click the polygone icon, move your mouse on the map and click to mark each
side of the polygon.

`Rectangle`
Click the marker icon, move your mouse on the map, click to mark each corner of 
the rectangle.

`Marker`
Click the marker icon, move your mouse on the map, and click to drop the marker

`Polyline`
Click the polyline icon, move your mouse on the map, and click to mark the first
line point. Click as many times as you want to add points. When  you are done, 
click 'finish'.

`Remove an object`
To Remove an object, click on the bin icon, then click on the object to delete.
Finally, click on 'save' to confirm the removal, or on cancel.

`Popup window`
When you define a new object, a field is available under the map and allows
 you to enter the title and text to use as the object's popup window.

RESTRICTIONS
------------
Only ONE geofield geoJSON is managed on a content type.
