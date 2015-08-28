(function ($) {

  Drupal.behaviors.toolbox = {
    attach: attach
  };

  function attach(context, settings) {
    var lat = settings.nexteuropa_geojson.settings.fs_default_map_center['lat'];
    var lng = settings.nexteuropa_geojson.settings.fs_default_map_center['lng'];
    var map = L.map('geofield_geojson_map', {}).setView([lat, lng], 13);

    // Create map.
    L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
      attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(map);

    drawnItems = L.featureGroup().addTo(map);

    // Loaded GeoJSON map.
    if(settings.nexteuropa_geojson.map) {
      loadedMap = jQuery.parseJSON(settings.nexteuropa_geojson.map);
      drawnItems = L.geoJson(loadedMap).addTo(map);

      for(key in drawnItems._layers) {
        // Create popups.
        layer_properties = drawnItems._layers[key].feature.properties;
        popup_content = buildPopupContent(key, layer_properties.label, layer_properties.description);
        drawnItems._layers[key].bindPopup(popup_content);
        // Only add inputs elements if the popups are not pre-populated.
        if(settings.nexteuropa_geojson.settings.fs_objects.prepopulate_label.prepopulate == 0) {
          // Create forms elements to manage popups content.
          create_label(key, layer_properties.label, layer_properties.description);
        }
      }
      // Focus on map elements.
      map.fitBounds(drawnItems.getBounds());
    }

    var marker_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['marker'] == 0 ? false : true;
    var polygon_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['polygon'] == 0 ? false : true;
    var polyline_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['polyline'] == 0 ? false : true;
    var rectangle_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['rectangle'] == 0 ? false : true;  

    // Create map control.
    var drawControl = new L.Control.Draw({
      draw : {
        position : 'topleft',
        polygon : polygon_setting,
        polyline : polyline_setting,
        rectangle : rectangle_setting,
        marker: marker_setting,
        circle : false
      },
      edit: { featureGroup: drawnItems }
    });

    map.addControl(drawControl);

    // Manage a map objects counter.
    var objects_count = 0;

    // Manage the event : when a new object is put on the map.
    map.on('draw:created', function(e) {
      if(objects_count < settings.nexteuropa_geojson.settings.fs_objects.objects_amount) {
        var type = e.layerType,
        layer = e.layer;

        var geoJSON = layer.toGeoJSON();
        feature = layer.feature;

        objects_count++;

        // Add the layer object to the map.
        drawnItems.addLayer(layer);

        // Only add inputs elements if the popups are not pre-populated.
        if(settings.nexteuropa_geojson.settings.fs_objects.prepopulate_label.prepopulate == 0)
          create_label(layer._leaflet_id, "", "");
        else {
          // prepopulate the popups with the title and body content
          name = $( "input[name*='title_field']" ).val();
          for (var c in CKEDITOR.instances) {
            description = CKEDITOR.instances[c].getData();
            break;
          }
          createPopup(layer._leaflet_id, name, description);
        }

        // Update GeoJSON field.
        updateGeoJsonField();
        //geojson_map = drawnItems.toGeoJSON();
        //$('#geofield_geojson textarea').text(JSON.stringify(geojson_map));
      }
    });


    // Manage the event : when an object is removed from the map.
    map.on('draw:deleted', function (e) {
        var layers = e.layers._layers;
        var leaflet_id = Object.keys(layers)[0];
        $('#label_wrapper_'+leaflet_id).remove();
        objects_count--;
    });

    // Create inputs (and their related events) to manage popups contents.
    function create_label(leaflet_id, label, description) {
      var myinput = '<div id="label_wrapper_'+leaflet_id+'" class="leaflet_label_wrapper"><input class="leaflet_label" name="myField" type="text" id="L'+leaflet_id+'">';
      myinput = myinput + '<textarea rows="2" class="leaflet_description" id="T'+leaflet_id+'"/>';
      myinput = myinput + '<a data-label-id="'+leaflet_id+'" class="remove-label" title="Delete labels."><span class="glyphicon glyphicon-trash" aria-hidden="true"></span></a></div>';

      $('#geofield_geojson_map_wrapper').append(myinput);
      $('#L'+leaflet_id).val(label);
      $('#T'+leaflet_id).val(description);

      // manage change event on input elements
      $('#L'+leaflet_id+', #T'+leaflet_id).change(function() {
        /*layer = map._layers[leaflet_id];

        popup_content = buildPopupContent(leaflet_id, "", "");
  
        layer.bindPopup(popup_content);
        layer._popup.setContent(popup_content);
        layer._popup.update();
        layer.openPopup();
        */
        createPopup(leaflet_id, "", "");
        updateGeoJsonField();
      });

      // Manage focus event on input elements.
      $('#L'+leaflet_id).focus(function() {
        layer = map._layers[leaflet_id];
        layer.openPopup();

        // Focus the map on the map object.
        if(layer._latlngs)
          map.setView(layer._latlngs[0]);
        else
          map.setView(layer.getLatLng());
        //layer.setStyle({color:'#00FF33'});
      });

      // Manage blur event on input elements.
      $('#L'+leaflet_id).blur(function() {
        layer = map._layers[leaflet_id];
        layer.closePopup();
        //layer.setStyle({color:'#f06eaa'});
      }); 

      // Manage the removal of a label.
      $('.remove-label').click(function() {
        layer = map._layers[$(this).attr('data-label-id')];
        layer.closePopup();
        layer.unbindPopup();
        $('#L'+leaflet_id).val('');
      });
    }

    function updateGeoJsonField() {
      geojson_map = drawnItems.toGeoJSON();
      i = 0
      for(key in drawnItems._layers) {
        // check if the popups must be populated or not
        if(settings.nexteuropa_geojson.settings.fs_objects.prepopulate_label.prepopulate == 0) {
          name = $('#L'+key).val();
          description = $('#T'+key).val();
        }
        else {
          name = $( "input[name*='title_field']" ).val();
          for (var c in CKEDITOR.instances) {
            description = CKEDITOR.instances[c].getData();
            break;
          }
        }
        //geojson_map.features[i].properties.label = drawnItems._layers[key]._popup.getContent();
        geojson_map.features[i].properties.label = name;
        geojson_map.features[i].properties.description = description;
        i++;
      }
      $('#geofield_geojson textarea').text(JSON.stringify(geojson_map));
    }

    function updatePopups() {
    
    }

    function buildPopupContent(leaflet_id, name, description) {
      var content = '<div id="popup_' + leaflet_id + '">';
      content = content + '<h4 class="popup_name">' + name + '</h4>';
      content = content + '<p class="popup_description">' + description + '</p>';
      content = content + '</div>';
      return content;
    }

    function createPopup(leaflet_id, name, description) {
      layer = map._layers[leaflet_id];
      popup_content = buildPopupContent(leaflet_id, name, description);
      layer.bindPopup(popup_content);
      layer._popup.setContent(popup_content);
      layer._popup.update();
      layer.openPopup();            
    } 

  } 

})(jQuery);

