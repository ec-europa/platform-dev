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

// Create tile layers array if none.
if (typeof tile_layers == 'undefined') {
  var tile_layers = [];
}

// Checks for tile layers, adds tiles to map and prepares layer control. Layers
// and layer control are activated in ne_map.js. With tiles the EC corporate
// L.wt.tileLayer method can be used which accepts tile names as input.
if (typeof Drupal.settings.tile_layers !== 'undefined') {
  var tile_layers = Drupal.settings.tile_layers;

  // Cycles through URL to fetch settings and URLs.
  var arrayLength = tile_layers.length;
  for (var i = 0; i < arrayLength; i++) {
    var id = tile_layers[i].id;

    var options = [];
    options.attribution = tile_layers[i].label;

    // Collects the layers that are marked "enabled" to be activated in
    // ne_map.js. Some tiles arent supported in L.wt.tileLayer yet.
    switch (tile_layers[i].layer_settings.tile_layer.tile_layer) {
      case 'countrynames_europe':
        id = L.tileLayer('//europa.eu/webtools/maps/tiles/countrynames_europe/{z}/{y}/{x}', options);
        break;
      case 'citynames_europe':
        id = L.tileLayer('//europa.eu/webtools/maps/tiles/citynames_europe/{z}/{y}/{x}', options);
        break;
      case 'roadswater_europe':
        id = L.tileLayer('//europa.eu/webtools/maps/tiles/roadswater_europe/{z}/{y}/{x}', options);
        break;
      case 'countryboundaries_world':
        id = L.tileLayer('//europa.eu/webtools/maps/tiles/countryboundaries_world/{z}/{y}/{x}', options);
        break;
      default:
        id = L.wt.tileLayer(tile_layers[i].layer_settings.tile_layer.tile_layer, options);
    }
    if (typeof tile_layers[i].layer_settings.enabled != 'undefined') {
      if (tile_layers[i].layer_settings.enabled.enabled == '1') {
        layers_to_enable.push({"label": tile_layers[i].label, "layer": id});
      }
    }

    // Adds all layers to the layercontrol.
    tile_layers.push({"label": tile_layers[i].label, "layer": id});
  }
}
