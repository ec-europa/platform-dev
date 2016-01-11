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

// Checks for CSV layers, adds CSV features to map and layer control.
// Checks for CSV layers, adds geoJson features from to map and prepares layer
// control. Layers and layer control are activated in ne_map.js. The Leaflet
// L.marker method can be used which accepts geoJson features as input.
if (typeof Drupal.settings.csv_layers !== 'undefined') {
  var csv_layers = Drupal.settings.csv_layers;
  var arrayLength = csv_layers.length;
  for (var i = 0; i < arrayLength; i++) {
    var id = csv_layers[i].id;
    var id = L.geoJson(csv_layers[i].features, {
      onEachFeature: function (feature, layer) {
        if (csv_layers[i].layer_settings.popup.show_popup) {
          if (csv_layers[i].layer_settings.popup.popin) {
            layer.bindInfo(feature.properties.popupContent)
          }
          else {
            layer.bindPopup(feature.properties.popupContent);
          }
        }
      },
      pointToLayer: function (feature, latlng) {

        // Sets custom marker icon if defined in the feature.
        if (typeof csv_layers[i].layer_settings.icon.icon !== 'undefined') {
          var icon = new defaultIcon({iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-' + csv_layers[i].layer_settings.icon.icon + '.png'});
        }
        else {
          var icon = defaultIcon;
        }
        return L.marker(latlng, {icon: icon});
      }
    });

    // Adds layer attribution if set.
    // @todo. attrib texts gets overwritten when multiple layers of same type.
    if (typeof csv_layers[i].layer_settings.attribution != 'undefined') {
      if (csv_layers[i].layer_settings.attribution.attributionControl == '1') {
        var attribution = csv_layers[i].layer_settings.attribution.attribution;
        id.getAttribution = function () {
          return window.attribution;
        };
      }
    }

    // Collects the layers that are marked "enabled" to be activated in
    // ne_map.js.
    if (typeof csv_layers[i].layer_settings.control.enabled != 'undefined') {
      if (csv_layers[i].layer_settings.control.enabled == '1') {
        layers_to_enable.push({"label": csv_layers[i].label, "layer": id});
      }
    }

    // Adds all layers to the layercontrol.
    if (typeof csv_layers[i].layer_settings.control.show_in_control != 'undefined') {
      if (csv_layers[i].layer_settings.control.show_in_control == '1') {
        layers.push({"label": csv_layers[i].label, "layer": id});
      }
    }
  }
}
