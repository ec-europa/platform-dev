/**
 * @file
 * Provides custom functionality as input for load.js.
 *
 * Sets up map data and settings that are activated in ne_map.js. Depends on
 * map_layer.js.
 */

// Checks for node layers, adds node features to map and layer control.
// Checks for node layers, adds geoJson features from to map and prepares layer
// control. Layers and layer control are activated in ne_map.js. The Leaflet
// L.marker method can be used which accepts geoJson features as input.
if (typeof Drupal.settings.node_layers !== 'undefined') {

  // Create layers array if none.
  if (typeof layers_to_control == 'undefined') {
    var layers_to_control = [];
  }

  // Create layers to enable array if none.
  if (typeof layers_to_enable == 'undefined') {
    var layers_to_enable = [];
  }

  // Creates group to be able to fit map to bounds later.
  if (typeof group == 'undefined') {
    var group = new L.featureGroup;
  }

  var node_layers = Drupal.settings.node_layers;
  var arrayLength = node_layers.length;
  for (var i = 0; i < arrayLength; i++) {
    var id = node_layers[i].id;

    // Sets markers color and clustering.
    var cluster = (node_layers[i].layer_settings.clustering.cluster_markers == 1) ? true : false;
    var markers_options = {
      "color": node_layers[i].layer_settings.icon.icon,
      "cluster": cluster
    }

    // Sets custom popup.
    if (node_layers[i].layer_settings.popup.show_popup) {
      if (node_layers[i].layer_settings.popup.popin) {
        markers_options.onEachFeature = function (feature, layer) {
          layer.bindInfo(feature.properties.popupContent)
        }
      }
      else {
        markers_options.onEachFeature = function (feature, layer) {
          layer.bindPopup(feature.properties.popupContent);
        }
      }
    }

    // Creates the map layer.
    id = L.wt.markers({"type": "FeatureCollection", "features": node_layers[i].features}, markers_options);

    // Create a marker layer that can be used to get the bounds.
    var geojson = L.geoJson(node_layers[i].features, {
      pointToLayer: function (feature, latlng) {
        return L.marker(latlng);
      }
    });

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

        // Adds the layer to a group to be able to fit map to bounds later.
        group.addLayer(geojson);
      }
    }

    // Adds all layers to the layercontrol.
    if (typeof node_layers[i].layer_settings.control.show_in_control != 'undefined') {
      if (node_layers[i].layer_settings.control.show_in_control == '1') {
        layers_to_control.push({"label": node_layers[i].label, "layer": id});
      }
    }
  }
}
