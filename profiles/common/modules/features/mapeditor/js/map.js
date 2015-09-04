/**
 * @file
 * Provides custom functionality as input for Webtools' load.js.
 */

L.custom = {
  init: function (obj, params) {

    // Defines map height.
    obj.style.minHeight = map_height;

    // Creates map object.
    var map = L.map(obj, mapeditor_map);

    // Defines custom Icon.
    var mapeditorBaseIcon = L.Icon.extend({
      options: {
        // iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + settings.icon + '.png',
        shadowUrl: '//europa.eu/webtools/services/map/images//marker-shadow.png',
        iconSize: [25, 41],
        shadowSize: [41, 41],
        iconAnchor: [20, 41],
        shadowAnchor: [20, 40],
        popupAnchor: [-3, -76]
      }
    });

    var mapeditorIcon = new mapeditorBaseIcon({iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + settings.icon + '.png'});

    L.icon = function (options) {
      return new L.Icon(options);
    };

    // Sets the tiles.
    var tileLayer = L.wt.tileLayer(mapeditor_map.map).addTo(map);

    // Adds GeoJson formatted features to map.
    // L.geoJson(features).addTo(map);
    var geojson = L.geoJson(features, {
      onEachFeature: onEachFeature,
      pointToLayer: function (feature, latlng) {
        return L.marker(latlng, {icon: mapeditorIcon});
      }
    })

    // Fits the map to the available features.
    if (settings.fitbounds == 1) {
      var padding = parseInt(settings.padding);
      map.fitBounds(geojson.getBounds(), {padding: [padding, padding]});
    }

    geojson.addTo(map);

    // Creates pop up event and defines popup content for each feature.
    function onEachFeature(feature, layer) {
      if (feature.properties && feature.properties.popupContent) {
        if (settings.popup) {
          layer.bindInfo(feature.properties.popupContent)
        }
        else {
          layer.bindPopup(feature.properties.popupContent);
        }
      }
    }

    // Adds attribution if set.
    if (mapeditor_map.attributionControl == 1) {
      var gj = L.geoJson();
      gj.getAttribution = function () {
        return mapeditor_map.attribution;
      };
      gj.addTo(map);
    }

    // Adds country highlighting.
    if (typeof settings.country_highlight !== 'undefined') {
      var country_options = {
        style: function (feature) {
          return {
            fillColor: "#0065a2",
            weight: 2,
            opacity: 1,
            color: "#0065a2",
            fillOpacity: 0.15,
            dashArray: '0'
          };
        }
      };
      var countries = L.wt.countries([{
        "level": 0,
        "countries": settings.country_highlight
      }], country_options).addTo(map);
    }

    // Processes next components.
    $wt._queue("next");

  }
};
