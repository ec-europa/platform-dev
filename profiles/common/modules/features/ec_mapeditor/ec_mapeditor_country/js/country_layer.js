/**
 * @file
 * Provides custom functionality as input for load.js.
 *
 * Sets up map data and settings that are activated in map.js. Depends on
 * map_layer.js.
 */

// Checks for country layers, adds country features to map and layer control.
// Checks for country layers, adds GeoJSON features from to map and prepares layer
// control. Layers and layer control are activated in map.js. The Leaflet
// L.marker method can be used which accepts GeoJSON features as input.
if (typeof Drupal.settings.country_layers !== 'undefined') {

  // Create layers to control array if none.
  if (typeof layers_to_control == 'undefined') {
    var layers_to_control = [];
  }

  // Create layers to enable array if none.
  if (typeof layers_to_enable == 'undefined') {
    var layers_to_enable = [];
  }

  var country_layers = Drupal.settings.country_layers;
  var arrayLength = country_layers.length;
  for (var i = 0; i < arrayLength; i++) {
    var id = country_layers[i].id;

    // Fetches country codes.
    // @todo check if Object.keys can be used for older browsers.
    var countries = country_layers[i].countries;
    var country_keys = Object.keys(countries);
    var settings = country_layers[i].layer_settings;

    // Defines options for the L.wt.countries method.
    var options = {
      label: settings.style.show_label ? true : false,
      style: function (feature) {
        var code = (feature.properties.CNTR_ID);
        var style = window.settings.style;
        var fill_color = style.fill_color;
        if (typeof countries[code].fill_color != 'undefined') {
          fill_color = countries[code].fill_color;
        }
        return {
          fillColor: fill_color,
          weight: style.border_weight,
          opacity: style.border_opacity,
          color: style.border_color,
          dashArray: style.dash_array,
          fillOpacity: style.fill_opacity
        };
      },
      onEachFeature: function (feature, layer) {
        var code = (feature.properties.CNTR_ID);
        var customEvents = {
          click: function (e) {

            // @todo implement webtools method of linking.
            window.location.href = countries[code].url;
          }
        };
        layer.on({
          click: customEvents.click
        });
      }
    };

    // Sets the nuts level.
    // @todo. Make nuts level work on a per country level.
    var nuts_level = 0;
    if (typeof country_layers[i].layer_settings.nuts.level != 'undefined') {
      nuts_level = country_layers[i].layer_settings.nuts.level;
    }
    var id = L.wt.countries([{"level": nuts_level, "countries": country_keys}], options);

    // Adds layer attribution if set.
    // @todo. attrib texts gets overwritten when multiple layers of same type.
    if (typeof country_layers[i].layer_settings.attribution != 'undefined') {
      if (country_layers[i].layer_settings.attribution.attributionControl == '1') {
        var attribution = country_layers[i].layer_settings.attribution.attribution;
        id.getAttribution = function () {
          return window.attribution;
        };
      }
    }

    // Collects the layers that are marked "enabled" to be activated in
    // map.js.
    if (typeof country_layers[i].layer_settings.control.enabled != 'undefined') {
      if (country_layers[i].layer_settings.control.enabled == '1') {
        layers_to_enable.push({"label": country_layers[i].label, "layer": id});
      }
    }

    // Adds all layers to the layercontrol.
    if (typeof country_layers[i].layer_settings.control.show_in_control != 'undefined') {
      if (country_layers[i].layer_settings.control.show_in_control == '1') {
        layers_to_control.push({"label": country_layers[i].label, "layer": id});
      }
    }
  }
}
