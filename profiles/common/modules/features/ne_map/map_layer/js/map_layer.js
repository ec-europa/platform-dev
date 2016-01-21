/**
 * @file
 * Provides generic map layer functionality.
 */

// Create tile layers array if none.
if (typeof control_tile_layers == 'undefined') {
  var control_tile_layers = [];
}

// Defines the layer control switch for the sidebar if there are layers that
// need control (switch on off).
if (layers_to_control.length > 0) {

  // Defines layers control.
  var layersControl = [
    {
      "label": "Layers",
      "checkbox": layers_to_control
    },
    {
      "label": "Tiles",
      "checkbox": control_tile_layers
    },
  ];

  // Hides the layers panel by default.
  var layers_panel = L.wt.sidebar({
    "layers": {
      "tooltip": "Layers",
      "panel": layersControl,
      "display": false
    }
  });
}
