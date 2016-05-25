/**
 * @file
 * Provides generic map layer functionality.
 */

// Defines the layer control switch for the sidebar if there are layers that
// need control (switch on off).
if (typeof layers_to_control != 'undefined') {
  if (layers_to_control.length > 0) {

    // Defines layers control.
    var layersControl = [
    {
      "label": "Layers",
      "checkbox": layers_to_control
    }
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
}
