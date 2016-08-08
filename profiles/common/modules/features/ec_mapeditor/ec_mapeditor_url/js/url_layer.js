/**
 * @file
 * Provides custom functionality as input for load.js.
 *
 * Sets up map data and settings that are activated in map.js. Depends on
 * map_layer.js.
 */

// Checks for URL layers, adds URLs to map and prepares layer control. Layers
// and layer control are activated in map.js. With URLs the EC corporate
// L.wt.markers method can be used which accepts public URLs as input.
if (typeof Drupal.settings.url_layers !== 'undefined') {
  var url_layers = Drupal.settings.url_layers;

  // Create layers array if none.
  if (typeof layers_to_control == 'undefined') {
    var layers_to_control = [];
  }

  // Create layers to enable array if none.
  if (typeof layers_to_enable == 'undefined') {
    var layers_to_enable = [];
  }

  // Creates group to be able to fit map to bounds later.
  if (typeof wt_bounds_group == 'undefined') {
    var wt_bounds_group = [];
  }

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
    if (url_layers[i].layer_settings.popup.show_popup) {
      if (url_layers[i].layer_settings.popup.popin == 0) {
        markers_options.onEachFeature = function (feature, layer) {
          layer.bindPopup("<h3>" + feature.properties.name + "</h3>" + feature.properties.description);
        }
      }
    }

    // Collects the layers that are marked "enabled" to be activated in
    // map.js.
    id = L.wt.markers(url_layers[i].urls, markers_options);

    // Collects the layers that are marked "enabled" to be activated in
    // map.js.
    if (typeof url_layers[i].layer_settings.control.enabled != 'undefined') {
      if (url_layers[i].layer_settings.control.enabled == '1') {
        layers_to_enable.push({"label": url_layers[i].label, "layer": id});

        // Adds the layer to a group to be able to fit map to bounds later.
        wt_bounds_group.push(id);
      }
    }

    // Adds all layers to the layercontrol.
    if (typeof url_layers[i].layer_settings.control.show_in_control != 'undefined') {
      if (url_layers[i].layer_settings.control.show_in_control == '1') {
        layers_to_control.push({"label": url_layers[i].label, "layer": id});
      }
    }
  }
}
