/**
 * @file
 * Provides custom functionality as input for Webtools' load.js.
 */

L.custom = {

  init: function (obj, params) {

    // Sets variables from Drupal JS settings.
    var settings = Drupal.settings.settings;

    // Defines the map.
    var map = L.map(obj, {
        "center": [settings.center.lat, settings.center.lon],
        "zoom": settings.zoom.initialZoom,
        "minZoom": settings.zoom.minZoom,
        "maxZoom": settings.zoom.maxZoom,
        "dragging": settings.dragging,
        "touchZoom": settings.touchZoom,
        "scrollWheelZoom": settings.scrollWheelZoom
      }
    );

    // Creates the tile layer in the map.
    var options = [];

    // Adds attribution if set.
    // @todo fix attribution mess.
    if (settings.attribution.attributionControl == 1) {
      options.attribution = settings.attribution.attribution;
    }

    var tiles = L.wt.tileLayer(settings.tiles.tiles, options).addTo(map);

    // Defines custom Icon.
    var defaultIcon = L.Icon.extend({
      options: {
        iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + settings.icon.icon + '.png',
        shadowUrl: '//europa.eu/webtools/services/map/images//marker-shadow.png',
        iconSize: [25, 41],
        shadowSize: [41, 41],
        iconAnchor: [20, 41],
        shadowAnchor: [20, 40],
        popupAnchor: [-3, -76]
      }
    });

    // Enables layers, layer and panel control when they are defined.
    // Cycles through list of layers waiting to be enabled.
    if (typeof layers_to_enable != 'undefined') {
      var arrayLength = layers_to_enable.length;
      for (var i = 0; i < arrayLength; i++) {

        // @todo check possible issue addlayer vs addto
        // map.addLayer(layers_to_enable[i].layer);.
        layers_to_enable[i].layer.addTo(map);
      }
    }

    // Adds layers panel to sidebar when there are layers.
    if (typeof layers_panel != 'undefined') {
      layers_panel.addTo(map);
    }

    // Processes the next component.
    $wt._queue("next");
  }
};
