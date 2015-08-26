(function ($) {
  Drupal.behaviors.toolbox = {
    attach: attach
  };

  function attach(context, settings) {

console.log(settings);


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
      drawnItems._layers[key].bindPopup(drawnItems._layers[key].feature.properties.label);
      i++;
    }
    console.log(drawnItems);
    map.fitBounds(drawnItems.getBounds());
  }
}


})(jQuery);

