(function ($) {
  Drupal.behaviors.toolbox = {
    attach: attach
  };

  function attach(context, settings) {

    var map = L.map('geofield_geojson_map', {}).setView([51.505, -0.09], 13);
    L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
       attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(map);

    drawnItems = L.featureGroup().addTo(map);
    // loaded GeoJSON map
    if(settings.nexteuropa_geojson.map) {
      loadedmap = jQuery.parseJSON(settings.nexteuropa_geojson.map);
      drawnItems = L.geoJson(loadedmap).addTo(map);

      i = 0;
      for(key in drawnItems._layers) {
        layer_properties = drawnItems._layers[key].feature.properties;
        popup_content = buildPopupContent(key, layer_properties.label, layer_properties.description);
        drawnItems._layers[key].bindPopup(popup_content);
        i++;
      }
      map.fitBounds(drawnItems.getBounds());
    }

    function buildPopupContent(leaflet_id, name, description) {
      var content = '<div id="popup_' + leaflet_id + '">';
      content = content + '<h4 class="popup_name">' + name + '</h4>';
      content = content + '<p class="popup_description">' + description + '</p>';
      content = content + '</div>';
      return content;
    }
  }

})(jQuery);

