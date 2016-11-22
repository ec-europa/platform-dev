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
    var tileLayer = L.wt.tileLayer("gray").addTo(map);

    // Defines example features.
    var features = [
    {
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
    },

    {"type":"Feature","properties":{"name":"jasjdasjdkjdksajd","description":"saxsa"},"geometry":{"type":"Polygon","coordinates":[[[22.6563,49.4333],[22.6563,52.316],[28.5449,52.316],[28.5449,49.4333],[22.6563,49.4333]]]}},

    {
      "type":"Feature",
      "properties":{
        "name":"Eastern block",
        "popupContent":"Eastern block"
      },
      "geometry":{
        "type":"Polygon",
        "coordinates": [
          [
            [13.6563,49.4333],
            [13.6563,52.316],
            [19.5449,52.316],
            [19.5449,49.4333],
            [13.6563,49.4333]
          ]
        ]
      }
    },
     {
        "type": "Feature",
        "properties": {
          "name": "Man-of-war",
          "popupContent": "Some place in Denmark"
        },
        "geometry": {
          "type": "Point",
          // 55.686724,12.570072,copenhagen,"Copenhagen, Copenhagen Municipality,
          // Capital Region of Denmark, DK",,MapQuest Open,city/town.
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
    }
    ];

    var markers_options = {
      "color": 'green',
      "cluster": false
    }

    var markers = L.wt.markers({
      "type": "FeatureCollection",
      "features": features
    }, markers_options);
    markers.addTo(map);

    var group = new L.featureGroup;
    // Create a marker layer that can be used to get the bounds.
    var geojson = L.geoJson(features, {
      pointToLayer: function (feature, latlng) {
        return L.marker(latlng);
      }
    });
    group.addLayer(geojson);
    map.fitBounds(group.getBounds(), {padding: [30,30]});

    var kml = L.wt.markers(["http://europa.eu/webtools/test/data/geojson.js"], {
      color: "orange",
      cluster: false
    }).addTo(map);
    // kml.fitBounds();.
    // Creates pop up event and defines popup content for each feature.
    function onEachFeature(feature, layer) {
      // Does this feature have a property named popupContent?
      if (feature.properties && feature.properties.popupContent) {
        layer.bindPopup(feature.properties.popupContent);
      }
    }

    // Defines custom actions for predefined options.
    var countries_options = {
      style: function (feature) {
        return {
          fillColor: "yellow",
          weight: 2,
          opacity: 0.5,
          color: "black",
          fillOpacity: 0.5,
          dashArray: '0'
        };
      },
      onEachFeature: function (feature, layer) {
        var id = (feature.properties.NUTS_ID || feature.properties.CNTR_ID);
        var customEvents = {
          click: function (e) {
            window.location.href = countries[id].url;
          }
        };
        layer.on({
          click: customEvents.click
        });
      }
    };

    var countries = {
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
    var countries_keys = ["NL", "BE", "DE", "EL", "IE", "SE"];

    // Adds countries as Nuts to map.
    var countries2 = L.wt.countries([{
      "level": 0,
      "countries": countries_keys
    }], countries_options).addTo(map);

    // Adds features using L.geojson.
    var features2 = {
        "type":"FeatureCollection",
        "features":[
        {
          "type":"Feature",
          "properties":{
            "name":"sadfsdf",
            "description":"sdaf"
          },
          "geometry":{
            "type":"Point",
            "coordinates":[
               21.4453,
               40.4051
            ]
          }
        },
        {
          "type":"Feature",
          "properties":{
             "name":"Eastern block",
             "description":"Eastern block"
          },
          "geometry":{
            "type":"Polygon",
            "coordinates": [
              [
                [-12.6563,-49.4333],
                [-12.6563,-52.316],
                [-18.5449,-52.316],
                [-18.5449,-49.4333],
                [-12.6563,-49.4333]
              ]
            ]
          }
        }
      ]
    };
    var geojson2 = L.geoJson(features2, {
      pointToLayer: function (feature, latlng) {
        return L.marker(latlng);
      }
    });
    geojson2.addTo(map);

    // Processes next components.
    $wt._queue("next");

  }
};
