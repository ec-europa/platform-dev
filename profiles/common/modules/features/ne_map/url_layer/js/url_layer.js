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

// Checks for URL layers, adds URLs to map and prepares layer control. Layers
// and layer control are activated in ne_map.js. With URLs the EC corporate
// L.wt.markers method can be used which accepts public URLs as input.
if (typeof Drupal.settings.url_layers !== 'undefined') {
  var url_layers = Drupal.settings.url_layers;

  // Cycles through URL to fetch settings and URLs.
  var arrayLength = url_layers.length;
  for (var i = 0; i < arrayLength; i++) {
    var id = url_layers[i].id;

    // Sets markers color and clustering.
    var cluster = (url_layers[i].layer_settings.clustering.cluster_markers == 1) ? true : false;
    var markers_options = {
      "color": url_layers[i].layer_settings.icon.icon,
      "cluster": cluster
    }

    // Sets custom popup.
    if (url_layers[i].layer_settings.popup.show) {
      if (url_layers[i].layer_settings.popup.popin == 0) {
        markers_options.onEachFeature = function (feature, layer) {
          layer.bindPopup("<h3>" + feature.properties.name + "</h3>" + feature.properties.description);
        }
      }
    }

    // Collects the layers that are marked "enabled" to be activated in
    // ne_map.js.
    id = L.wt.markers(url_layers[i].urls, markers_options);
    if (typeof url_layers[i].layer_settings.enabled != 'undefined') {
      if (url_layers[i].layer_settings.enabled.enabled == '1') {
        layers_to_enable.push({"label": url_layers[i].label, "layer": id});
      }
    }

    // Adds all layers to the layercontrol.
    layers.push({"label": url_layers[i].label, "layer": id});
  }
}
