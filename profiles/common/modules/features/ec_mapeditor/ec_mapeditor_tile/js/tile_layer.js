/**
 * @file
 * Provides custom functionality as input for load.js.
 *
 * Sets up map data and settings that are activated in map.js.
 * Depends on ec_mapeditor_layer.js.
 */

// Checks for tile layers, adds tiles to map and prepares layer control. Layers
// and layer control are activated in map.js. With tiles the EC
// corporate L.wt.tileLayer method can be used which accepts tile names as
// input.
if (typeof Drupal.settings.tile_layers !== 'undefined') {

  // Create layers array if none.
  if (typeof layers_to_control == 'undefined') {
    var layers_to_control = [];
  }

  // Create layers to enable array if none.
  if (typeof layers_to_enable == 'undefined') {
    var layers_to_enable = [];
  }

  var tile_layers = Drupal.settings.tile_layers;

  // Cycles through URL to fetch settings and URLs.
  var arrayLength = tile_layers.length;
  for (var i = 0; i < arrayLength; i++) {
    var id = tile_layers[i].id;

    var options = [];
    options.attribution = tile_layers[i].label;

    // Defines some tiles that arent supported in L.wt.tileLayer yet.
    switch (tile_layers[i].layer_settings.tiles.tiles) {
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
        id = L.wt.tileLayer(tile_layers[i].layer_settings.tiles.tiles, options);
    }

    // Collects the layers that are marked "enabled" to be activated in
    // map.js.
    if (typeof tile_layers[i].layer_settings.control.enabled != 'undefined') {
      if (tile_layers[i].layer_settings.control.enabled == '1') {
        layers_to_enable.push({"label": tile_layers[i].label, "layer": id});
      }
    }
    // Adds all layers to the layercontrol.
    if (typeof tile_layers[i].layer_settings.control.show_in_control != 'undefined') {
      if (tile_layers[i].layer_settings.control.show_in_control == '1') {
        layers_to_control.push({"label": tile_layers[i].label, "layer": id});
      }
    }
  }
}
