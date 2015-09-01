/**
 * @file
 * Provides custom functionality as input for Webtools' load.js.
 */

L.custom = {
  init: function (obj, params) {

    // Defines height of the map.
    obj.style.minHeight = map_height;

    // Initializes the map object.
    var map = L.map(obj, mapeditor_map);

    // Sets the tiles.
    var tileLayer = L.wt.tileLayer(mapeditor_map.map).addTo(map);

    // Defines custom actions for predefined options.
    var nuts_options = {
      style: function (feature) {
        return {
          fillColor: "#C8E9F2",
          weight: 1,
          opacity: 1,
          color: "#0065B1",
          fillOpacity: 0.9
        };
      },
      onEachFeature: function (feature, layer) {
        var id = (feature.properties.NUTS_ID || feature.properties.CNTR_ID);
        var customEvents = {
          click: function (e) {
            window.location.href = mapeditor_nuts[id].url;
          }
        };
        layer.on({
          click: customEvents.click
        });
      }
    };

    // Adds countries as Nuts to map.
    var nuts = L.wt.countries([{
      "level": 0,
      "countries": mapeditor_nuts_keys
    }], nuts_options).addTo(map);

    // Adds attribution if set.
    if (mapeditor_map.attributionControl == 1) {
      var gj = L.geoJson();
      gj.getAttribution = function () {
        return mapeditor_map.attribution;
      };
      gj.addTo(map);
    }

    // Processes next components.
    $wt._queue("next");

  }
};
