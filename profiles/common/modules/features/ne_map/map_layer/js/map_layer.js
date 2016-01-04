// Create layers array if none.
if (typeof layers == 'undefined') {
  var layers = [];
}
var layers_to_enable = [];

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
    "checkbox": tile_layers
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

// Defines layers panel in sidebar.
//    // @todo figure out if needed
// if (layers.length > 0) {
//  var layers_control = L.wt.control(layersControl);
//}
