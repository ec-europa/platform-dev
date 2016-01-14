/**
 * @file
 * Provides custom functionality as input for load.js.
 *
 * Sets up map data and settings that are activated in ne_map.js. Depends on
 * map_layer.js.
 */

// Create layers array if none.
if (typeof layers == 'undefined') {
  var layers = [];
}

// Create layers to enable array if none.
if (typeof layers_to_enable == 'undefined') {
  var layers_to_enable = [];
}

// Checks for node layers, adds node features to map and layer control.
// Checks for node layers, adds geoJson features from to map and prepares layer
// control. Layers and layer control are activated in ne_map.js. The Leaflet
// L.marker method can be used which accepts geoJson features as input.
if (typeof Drupal.settings.node_layers !== 'undefined') {
  var node_layers = Drupal.settings.node_layers;
  var arrayLength = node_layers.length;
  for (var i = 0; i < arrayLength; i++) {
    var node_layer = node_layers[i];
    var color = node_layers[i].layer_settings.icon.icon;

    // Creates clustered marker layer.
    if (node_layer.layer_settings.clustering.cluster_markers == 1) {
      var id = new PruneClusterForLeaflet();
      id.BuildLeafletClusterIcon = function (cluster) {
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
        c += ' prunecluster-' + color;
        return new L.DivIcon({
          html: "<div><span>" + cluster.population + "</span></div>",
          className: c,
          iconSize: L.point(iconSize, iconSize)
        })
      }
      var index;
      var features = node_layers[i].features;
      for (index = 0; index < features.length; ++index) {
        var lon = features[index].geometry.coordinates[0];
        var lat = features[index].geometry.coordinates[1];
        var marker = new PruneCluster.Marker(lat, lon);
        marker.data.name = features[index].properties.name;
        marker.data.icon = L.icon({
          iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + color + '.png',
          shadowUrl: '//europa.eu/webtools/services/map/images//marker-shadow.png'
        });
        marker.data.popup = features[index].properties.popupContent;
        id.RegisterMarker(marker);
      }

    }

    // Creates non clustered marker layer.
    else {
      var id = node_layers[i].id;
      var id = L.geoJson(node_layers[i].features, {
        onEachFeature: function (feature, layer) {
          if (node_layers[i].layer_settings.popup.show_popup) {
            if (node_layers[i].layer_settings.popup.popin) {
              layer.bindInfo(feature.properties.popupContent)
            }
            else {
              layer.bindPopup(feature.properties.popupContent);
            }
          }
        },
        pointToLayer: function (feature, latlng) {

          // Sets custom marker icon if defined in the feature.
          if (typeof color !== 'undefined') {
            var icon = new defaultIcon({iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + color + '.png'});
          }
          else {
            var icon = defaultIcon;
          }
          return L.marker(latlng, {icon: icon});
        }
      });
    }

    // Adds layer attribution if set.
    // @todo. attrib texts gets overwritten when multiple layers of same type.
    if (typeof node_layers[i].layer_settings.attribution != 'undefined') {
      if (node_layers[i].layer_settings.attribution.attributionControl == '1') {
        var attribution = node_layers[i].layer_settings.attribution.attribution;
        id.getAttribution = function () {
          return window.attribution;
        };
      }
    }

    // Collects the layers that are marked "enabled" to be activated in
    // ne_map.js.
    if (typeof node_layers[i].layer_settings.control.enabled != 'undefined') {
      if (node_layers[i].layer_settings.control.enabled == '1') {
        layers_to_enable.push({"label": node_layers[i].label, "layer": id});
      }
    }

    // Adds all layers to the layercontrol.
    if (typeof node_layers[i].layer_settings.control.show_in_control != 'undefined') {
      if (node_layers[i].layer_settings.control.show_in_control == '1') {
        layers.push({"label": node_layers[i].label, "layer": id});
      }
    }
  }
}
