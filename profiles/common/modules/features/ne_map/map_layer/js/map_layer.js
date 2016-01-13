/**
 * @file
 * Provides generic map layer functionality.
 */

// Create layers array if none.
if (typeof layers == 'undefined') {
  var layers = [];
}

// Create layers array if none.
if (typeof control_tile_layers == 'undefined') {
  var control_tile_layers = [];
}

// @todo remove duplicate
// Defines custom Icon.
var defaultIcon = L.Icon.extend({
  options: {
    iconUrl: '//europa.eu/webtools/services/map/images/marker-icon-blue.png',
    shadowUrl: '//europa.eu/webtools/services/map/images//marker-shadow.png',
    iconSize: [25, 41],
    shadowSize: [41, 41],
    iconAnchor: [20, 41],
    shadowAnchor: [20, 40],
    popupAnchor: [-3, -76]
  }
});

// Defines layers control.
var layersControl = [
  {
    "label": "Layers",
    "checkbox": layers
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
