//jQuery(document).ready(function($){
(function ($) {


    Drupal.behaviors.toolbox = {
        attach: attach
    };

    function attach(context, settings) {

console.log(settings);
console.log(settings.nexteuropa_geojson.map);


  /* var osmUrl = 'http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
      osmAttrib = '&copy; <a href="http://openstreetmap.org/copyright">OpenStreetMap</a> contributors',
      osm = L.tileLayer(osmUrl, {maxZoom: 18, attribution: osmAttrib});
      map = new L.Map('mymap', {layers: [osm], center: new L.LatLng(51.505, -0.04), zoom: 13}),*/

  var map = L.map('geofield_geojson_map', {}).setView([51.505, -0.09], 13);
  L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
     attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
  }).addTo(map);

  drawnItems = L.featureGroup().addTo(map);
  console.log(map);
  console.log($('.field-type-geofield-geojson textarea').val());
  // loaded GeoJSON map
//  if($('.field-type-geofield-geojson textarea').val().length > 0) {
//    loadedmap = jQuery.parseJSON($('.field-type-geofield-geojson textarea').val());
if(settings.nexteuropa_geojson.map) {
    loadedmap = jQuery.parseJSON(settings.nexteuropa_geojson.map);
    drawnItems = L.geoJson(loadedmap).addTo(map);

    i = 0;
    for(key in drawnItems._layers) {
      drawnItems._layers[key].bindPopup(drawnItems._layers[key].feature.properties.label);
      create_label(key, drawnItems._layers[key].feature.properties.label);
      i++;
    }
    console.log(drawnItems);
    map.fitBounds(drawnItems.getBounds());
  }

  map.addControl(new L.Control.Draw({
   draw : {
        position : 'topleft',
        polygon : true,
        polyline : true,
        rectangle : true,
        circle : false

    },
      edit: { featureGroup: drawnItems }
  }));

    map.on('draw:created', function(e) {
      var type = e.layerType,
      layer = e.layer;

      var geoJSON = layer.toGeoJSON();
      feature = layer.feature;

      console.log(type);

      if (type === 'marker') {
      }

      if (type === 'polygon') {
      }
    
      //layer.bindPopup('<h1>Blank popup</h1>');

      drawnItems.addLayer(layer);
      create_label(layer._leaflet_id, "");

      // update GeoJSON field
      geojson_map = drawnItems.toGeoJSON();
      $('.field-type-geofield-geojson textarea').text(JSON.stringify(geojson_map));


    });


map.on('draw:deleted', function (e) {
    var layers = e.layers._layers;
    var leaflet_id = Object.keys(layers)[0];
    $('#label_wrapper_'+leaflet_id).remove();
 });



function create_label(leaflet_id, content) {
  var myinput = '<div id="label_wrapper_'+leaflet_id+'" class="leaflet_label_wrapper"><input class="leaflet_label" name="myField" type="text" id="L'+leaflet_id+'">';
  myinput = myinput + '<a data-label-id="'+leaflet_id+'" class="remove-label" title="Delete labels."><span class="glyphicon glyphicon-remove" aria-hidden="true"></span></a></div>';

  $('#geofield_geojson_map_wrapper').append(myinput);

 $('#L'+leaflet_id).val(content);

 $('#L'+leaflet_id).change(function() {
   layer = map._layers[leaflet_id];
   
   layer.bindPopup($("#L"+leaflet_id).val());
   layer._popup.setContent($("#L"+leaflet_id).val())
   layer._popup.update();
   layer.openPopup();

   // update GeoJSON field
   geojson_map = drawnItems.toGeoJSON();
   i = 0
   for(key in drawnItems._layers) {
     geojson_map.features[i].properties.label = drawnItems._layers[key]._popup.getContent(); 
     i++;
   }
   $('.field-type-geofield-geojson textarea').text(JSON.stringify(geojson_map));
 });

 $('#L'+leaflet_id).focus(function() {
   layer = map._layers[leaflet_id];
   console.log(layer);
   //layer.setOpacity(1);
   //layer.togglePopup();
   layer.openPopup();

   if(layer._latlngs)
     map.setView(layer._latlngs[0]);
   else
     map.setView(layer.getLatLng());
   layer.setStyle({color:'#00FF33'});
   //layer.setStyle({fillcolor:'#00FF33'});
 });

 $('#L'+leaflet_id).blur(function() {
   layer = map._layers[leaflet_id];
   //layer.setOpacity(1);
   //layer.togglePopup();
   layer.closePopup();
   layer.setStyle({color:'#f06eaa'});
   //layer.setOpacity(0.5);
 }); 

 $('.remove-label').click(function() {
   layer = map._layers[$(this).attr('data-label-id')];
   layer.closePopup();
   layer.unbindPopup();
   //$('#label_wrapper_'+leaflet_id).remove();
   $('#L'+leaflet_id).val('');
 });

}


} 


})(jQuery);

