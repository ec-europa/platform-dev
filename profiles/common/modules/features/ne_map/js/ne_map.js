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
      //var gj = L.geoJson();
      //gj.getAttribution = function () {
      //  return settings.attribution.attribution;
      //};
      //gj.addTo(map);
    }

    var tiles = L.wt.tileLayer(settings.tile_layer.tile_layer, options).addTo(map);


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

    // Checks for node layers, adds node features to map and layer control.
    // @todo merge with csv layers code??
    if (typeof Drupal.settings.node_layers !== 'undefined') {

      var node_layers = Drupal.settings.node_layers;


      var arrayLength = node_layers.length;
      for (var i = 0; i < arrayLength; i++) {
        var one_layer = node_layers[i];
        // Applies marker clustering.
        if (node_layers[i].cluster == 1) {
          var colour = node_layers[i].colour;
          var pruneCluster = new PruneClusterForLeaflet();
          pruneCluster.BuildLeafletClusterIcon = function (cluster) {
            var c = 'prunecluster prunecluster-';
            var iconSize = 38;
            var maxPopulation = this.Cluster.GetPopulation();
            if (cluster.population < Math.max(10, maxPopulation * 0.01)) {
              c += 'small';
            }
            else if (cluster.population < Math.max(100, maxPopulation * 0.05)) {
              c += 'medium';
              iconSize = 40;
            }
            else {
              c += 'large';
              iconSize = 44;
            }
            c += ' prunecluster-' + node_layers[i].colour;
            return new L.DivIcon({
              html: "<div><span>" + cluster.population + "</span></div>",
              className: c,
              iconSize: L.point(iconSize, iconSize)
            })
          }
          var index;
          var features = node_layers[i].features;
          if (settings.fitbounds == 1) {
            var geojson = L.geoJson(features);
            var padding = parseInt(settings.padding);
            map.fitBounds(geojson.getBounds(), {padding: [padding, padding]});
          }
          for (index = 0; index < features.length; ++index) {
            var lon = features[index].geometry.coordinates[0];
            var lat = features[index].geometry.coordinates[1];
            var marker = new PruneCluster.Marker(lat, lon);
            marker.data.name = features[index].properties.name;
            marker.data.icon = L.icon({
              iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + node_layers[i].colour + '.png',
              shadowUrl: '//europa.eu/webtools/services/map/images//marker-shadow.png'
            });
            marker.data.popup = features[index].properties.popupContent;
            pruneCluster.RegisterMarker(marker);
          }
          map.addLayer(pruneCluster);
          layers.push({"label": node_layers[i].label, "layer": pruneCluster});
        }
        else {

          var id = node_layers[i].id;
          var id = L.geoJson(node_layers[i].features, {
            onEachFeature: onEachFeature,
            pointToLayer: function (feature, latlng) {

              // Sets custom marker icon if defined in the feature.
              if (typeof node_layers[i].colour !== 'undefined') {
                var icon = new defaultIcon({iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + node_layers[i].colour + '.png'});
              }
              else {
                var icon = defaultIcon;
              }
              return L.marker(latlng, {icon: icon});
            }
          });

          // Puts the layers that are marked "enabled" on the map. The others can
          // be switched on or off using the layercontrol.
          if (node_layers[i].enabled == '1') {
            id.addTo(map);
          }

          // Adds all layers to the layercontrol.
          layers.push({"label": node_layers[i].label, "layer": id});
        }
      }
    }

    // Enables layers, layer and panel control when they are defined.
    // Cycles through list of layers waiting to be enabled.
    if (typeof layers_to_enable != 'undefined') {
      var arrayLength = layers_to_enable.length;
      for (var i = 0; i < arrayLength; i++) {
        layers_to_enable[i].layer.addTo(map);
      }
    }

    // Adds layers panel to sidebar when there are layers.
    if (typeof layers_panel != 'undefined') {
      layers_panel.addTo(map);
    }

    // Adds layers panel to sidebar when there are layers.
    // @todo figure out if needed
    //if (typeof layers_control != 'undefined') {
    //  //layers_control.addTo(map);
    //}

    // Creates pop up event and defines popup content for each feature.
    function onEachFeature(feature, layer) {
      if (feature.properties && feature.properties.popupContent) {
        if (settings.popup.popin) {
          layer.bindInfo(feature.properties.popupContent)
        }
        else {
          layer.bindPopup(feature.properties.popupContent);
        }
      }
    }

    // Processes the next component.
    $wt._queue("next");
  }
};
