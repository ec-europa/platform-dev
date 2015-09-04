/**
 * @file
 * Defines content for webtools map.
 */

L.custom = {
  init: function (obj, params) {

    // Defines map height.
    obj.style.minHeight = map_height;

    // Creates map object.
    var map = L.map(obj, {
      "center": [48, 9],
      "zoom": 4,
      "attributionControl": false,
      "loadingControl": true
    });

    // Defines tile layer.
    var tileLayer = L.wt.tileLayer("osmec").addTo(map);

    // Defines example features.
    var features = [{
      "type": "Feature",
      "properties": {
        "name": "Gunwalls",
        "popupContent": "Somewhere in Finland"
      },
      "geometry": {
        "type": "Point",
        // 60.166628,24.943508,helsinki,"Helsinki, Helsingin seutukunta,
        // Southern Finland, FI",,MapQuest Open,city/town.
        "coordinates": [24.943508, 60.166628]
      }
    }, {
      "type": "Feature",
      "properties": {
        "name": "Man-of-war",
        "popupContent": "Some place in Denmark"
      },
      "geometry": {
        "type": "Point",
        // 55.686724,12.570072,copenhagen,"Copenhagen, Copenhagen Municipality,
        // Capital Region of Denmark, DK",,MapQuest Open,city/town
        "coordinates": [12.570072, 55.686724]
      }
    }, {
      "type": "Feature",
      "properties": {
        "name": "Mizzen draught Hearties",
        "popupContent": "Tack Plate Fleet pirate run a shot across the bow crack Jennys tea cup hulk jolly boat boom poop deck sutler. List barkadeer mizzenmast carouser me pink take a caulk interloper belaying pin yard."
      },
      "geometry": {
        "type": "Point",
        // Adds lat long for a well known place, good for details.
        // 50.814232,4.412692,"beaulieu 25, oudergem","Avenue de Beaulieu
        // - de Beaulieulaan 25, Auderghem - Oudergem, Brussels-Capital,
        // Brussels-Capital, BE.
        "coordinates": [4.412692, 50.81423]
      }
    }];

    var LeafIcon = L.Icon.extend({
      options: {
        shadowUrl: '//europa.eu/webtools/services/map/images//marker-shadow.png',
        iconSize: [25, 41],
        shadowSize: [41, 41],
        iconAnchor: [25, 41],
        shadowAnchor: [20, 40],
        popupAnchor: [-3, -76]
      }
    });

    var greenIcon = new LeafIcon({iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-green.png'}),
      redIcon = new LeafIcon({iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-red.png'}),
      orangeIcon = new LeafIcon({iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-orange.png'});

    L.icon = function (options) {
      return new L.Icon(options);
    };

    // Adds GeoJson formatted features to map.
    L.geoJson(features, {
      onEachFeature: onEachFeature,
      pointToLayer: function (feature, latlng) {
        return L.marker(latlng, {icon: greenIcon});
      }
    }).addTo(map);

    // Creates pop up event and defines popup content for each feature.
    function onEachFeature(feature, layer) {
      // Does this feature have a property named popupContent?
      if (feature.properties && feature.properties.popupContent) {
        layer.bindPopup(feature.properties.popupContent);
      }
    }

    // Fits the map to the available features.
    var all_coordinates = [[60.166628, 24.943508], [55.686724, 12.570072], [50.81423, 4.412692]];
    map.fitBounds(all_coordinates, {padding: [30, 30]});

    // Defines custom actions for predefined options.
    var nuts_options = {
      style: function (feature) {
        return {
          fillColor: "#0065a2",
          weight: 2,
          opacity: 1,
          color: "#0065a2",
          fillOpacity: 0.15,
          dashArray: '0'
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

    var mapeditor_nuts = {
      "NL": {
        "title": "Netherlands",
        "url": "http:\/\/example.com"
      },
      "BE": {"title": "Belgium", "url": "http:\/\/example.com"},
      "DE": {"title": "Germany", "url": "http:\/\/example.com"},
      "EL": {"title": "Greece", "url": "http:\/\/example.com"},
      "IE": {"title": "Ireland", "url": "http:\/\/example.com"},
      "SE": {"title": "Sweden", "url": "http:\/\/example.com"}
    };
    var mapeditor_nuts_keys = ["NL", "BE", "DE", "EL", "IE", "SE"];

    // Adds countries as Nuts to map.
    var nuts = L.wt.countries([{
      "level": 0,
      "countries": mapeditor_nuts_keys
    }], nuts_options).addTo(map);

    // Adds attribution if set.
    if (map.attributionControl == 1) {
      var gj = L.geoJson();
      gj.getAttribution = function () {
        return map.attribution;
      };
      gj.addTo(map);
    }

    // Processes next components.
    $wt._queue("next");

  }
};
