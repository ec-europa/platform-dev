/**
 * @file
 * Code for nexteuropa_geofield.view.js file.
 */

(function ($) {
  Drupal.behaviors.toolbox = {
    attach: attach
  };

  function attach(context, settings) {

    $('#geofield_geojson_map', context).once('geofield-geojson-map', function () {

      var map = L.map('geofield_geojson_map', {}).setView([51.505, -0.09], 5);
      L.tileLayer(
        'http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
          attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
        }
      ).addTo(map);

      drawnItems = L.featureGroup().addTo(map);

      // Load GeoJSON map.
      if (settings.nexteuropa_geojson.map) {
        loadedmap = jQuery.parseJSON(settings.nexteuropa_geojson.map);
        drawnItems = L.geoJson(loadedmap).addTo(map);

        i = 0;
        for (key in drawnItems._layers) {
          layer_properties = drawnItems._layers[key].feature.properties;
          if (layer_properties.name || layer_properties.description) {
            popup_content = buildPopupContent(key, layer_properties.name, layer_properties.description);
            drawnItems._layers[key].bindPopup(popup_content);
          }
          i++;
        }
        // Fix zoom to 16 when there is one object on the map.
        if (i == 1) {
          console.log(drawnItems);
          map.fitBounds(drawnItems.getBounds(), {maxZoom:16});
        }
        else {
          map.fitBounds(drawnItems.getBounds());
        }
      }

      /**
       * Build the html content put in a popup.
       *
       * @param {Number} leaflet_id
       *   ID of the leaflet layer of the popup.
       * @param {String} name
       *   Title of the popup.
       *
       * @return {String} description
       *   The content of the popup.
       */
      function buildPopupContent(leaflet_id, name, description) {
        var content = '<div id="popup_' + leaflet_id + '">';
        content = content + '<h4 class="ecl-heading ecl-heading--h4 popup_name">' + name + '</h4>';
        content = content + '<p class="popup_description">' + description + '</p>';
        content = content + '</div>';
        return content;
      }

    });

  }
})(jQuery);
