/**
 * @file
 * Code for nexteuropa_geofield.edit.js file.
 */

(function ($) {

    Drupal.behaviors.toolbox = {
        attach: attach
    };

  function attach(context, settings) {

    $('#geofield_geojson_map', context).once('geofield-geojson-map', function () {

      var lat = settings.nexteuropa_geojson.settings.fs_default_map_center['lat'];
      var lng = settings.nexteuropa_geojson.settings.fs_default_map_center['lng'];
      var map = L.map('geofield_geojson_map', {}).setView([lat, lng], 13);

      $(document).ready(function() {
        if (context == document) {
          // If there are vertical tabs the widget should refresh when swapping
          // between them.
          if ($('.vertical-tabs').length > 0 && $('.vertical-tabs-panes').length > 0) {
            var refresh = function() {
              $('.vertical-tabs-panes').find('.vertical-tabs-pane').each(function(key, pane) {
                // Check pane is visible and refresh widget if it is.
                if ($(pane).is(':visible')) {
                  map.invalidateSize();
                  if (settings.nexteuropa_geojson.map) {
                    map.fitBounds(drawnItems.getBounds());
                  }
                  else {
                    map.setView([lat, lng], 13);
                  }
                }
              });
            };
            // Refresh current vertical tab.
            refresh();
            // Refresh when changing to a different vertical tab.
            $('.vertical-tabs').find('.vertical-tab-button').each(function(key, tab) {
              $(tab).find('a').bind('click', refresh);
            });
          }
        }
      });

      // Get all the necessary DOM objects.
      // If there is only one defined object on the map, get the fields used to
      // populate the popup.
      if (settings.nexteuropa_geojson.settings.fs_objects.objects_amount == 1) {
        name_field = settings.nexteuropa_geojson.settings.fs_objects.fs_prepopulate.name_populate;
        description_field = settings.nexteuropa_geojson.settings.fs_objects.fs_prepopulate.description_populate;
      }

      // Manage a map objects counter.
      var objects_count = 0;

      // Create map.
      L.tileLayer(
        'http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
          attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
        }
      ).addTo(map);

      drawnItems = L.featureGroup().addTo(map);

      // Load the GeoJSON data to build the map.
      if (settings.nexteuropa_geojson.map) {
        loadedMap = jQuery.parseJSON(settings.nexteuropa_geojson.map);
        drawnItems = L.geoJson(loadedMap).addTo(map);
        // Popups are not pre-populated.
        if (settings.nexteuropa_geojson.settings.fs_objects.objects_amount > 1) {
          for (key in drawnItems._layers) {
            // Create forms elements to manage popups content.
            layer_properties = drawnItems._layers[key].feature.properties;
            createLabel(key, layer_properties.name, layer_properties.description);
            objects_count++;
          }
          updateGeoJsonField();
          updatePopups();
        }

        // Focus on map elements.
        map.fitBounds(drawnItems.getBounds());
        // Fix zoom to 16 when there is one object on the map.
        if (settings.nexteuropa_geojson.settings.fs_objects.objects_amount == 1) {
          map.fitBounds(drawnItems.getBounds(), {maxZoom:16});
        }
        else {
          map.fitBounds(drawnItems.getBounds());
        }
      }

      if (settings.nexteuropa_geojson.settings.fs_objects.objects_amount == 1) {
        // Popups are pre-populated with the conteny title and body.
        name_obj = getFieldObject(name_field);
        name_obj.change(
          function() {
            updateGeoJsonField();
            updatePopups();
          }
        );
        $('#geofield_geojson_map').click(
          function() {
            updateGeoJsonField();
            updatePopups();
          }
        );
        CKEDITOR.on(
          'instanceReady', function(ev) {
            description_obj = getFieldObject(description_field);
            description_obj.on(
              'change', function() {
                updateGeoJsonField();
                updatePopups();
              }
            );
            updatePopups();
          }
        );
      }

      // Get map controls settings.
      var marker_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['marker'] == 0 ? false : true;
      var polygon_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['polygon'] == 0 ? false : true;
      var polyline_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['polyline'] == 0 ? false : true;
      var rectangle_setting = settings.nexteuropa_geojson.settings.fs_objects.objects['rectangle'] == 0 ? false : true;

      // Create map control.
      var drawControl = new L.Control.Draw(
        {
          draw : {
            position : 'topleft',
            polygon : polygon_setting,
            polyline : polyline_setting,
            rectangle : rectangle_setting,
            marker: marker_setting,
            circle : false
          },
          edit: { featureGroup: drawnItems }
        }
      );

      map.addControl(drawControl);

      // Manage the event : when a new object is put on the map.
      map.on(
        'draw:created', function(e) {
          if (objects_count < settings.nexteuropa_geojson.settings.fs_objects.objects_amount) {
            var type = e.layerType,
            layer = e.layer;

            var geoJSON = layer.toGeoJSON();
            feature = layer.feature;

            objects_count++;

            // Add the layer object to the map.
            drawnItems.addLayer(layer);

            // Only add inputs elements if the popups are not pre-populated.
            if (settings.nexteuropa_geojson.settings.fs_objects.objects_amount > 1) {
              createLabel(layer._leaflet_id, "", "");
            }
            else {
              // Prepopulate the popups with the title and body content.
              name = getFieldValue(name_field);
              description = getFieldValue(description_field);
              createPopup(layer._leaflet_id, name, description);
            }
            // Update GeoJSON field.
            updateGeoJsonField();
          }
          else {
            alert("The Maximum number of items on the map is limited to " + settings.nexteuropa_geojson.settings.fs_objects.objects_amount);
          }
        }
      );

      // Manage the event : when an object is removed from the map.
      map.on(
        'draw:deleted', function (e) {
          var layers = e.layers._layers;
          var leaflet_id = Object.keys(layers)[0];
          $('#label_wrapper_' + leaflet_id).remove();
          objects_count--;
          updateGeoJsonField();
        }
      );

      /**
       * Create 2 inputs (and their related events) to manage popups contents.
       *
       * @param {Number} leaflet_id
       *   ID of the leaflet layer.
       * @param {String} name
       *   Title of the popup.
       *
       * @return {String} description
       *   The content of the popup.
       */
      function createLabel(leaflet_id, name, description) {
        var myinput = '<div id="label_wrapper_' + leaflet_id + '" class="leaflet_label_wrapper"><div class="label_title"><label>Name</label><input class="leaflet_label form-text" name="myField" type="text" id="L' + leaflet_id + '"></div>';
        myinput = myinput + '<div class="label_description"><label>Description</label><textarea rows="2" class="leaflet_description form-textarea" id="T' + leaflet_id + '"/>';
        myinput = myinput + '<a data-label-id="' + leaflet_id + '" class="remove-label ui-icon ui-icon-closethick" title="Remove popup"></a></div></div>';

        $('#geofield_geojson_map_wrapper').append(myinput);
        $('#L' + leaflet_id).val(name);
        $('#T' + leaflet_id).val(description);

        // Manage change event on input elements.
        $('#L' + leaflet_id + ', #T' + leaflet_id).change(
          function() {
            updateGeoJsonField();
            updatePopups();
          }
        );

        // Manage focus event on input elements.
        $('#L' + leaflet_id + ', #T' + leaflet_id).focus(
          function() {
            layer = map._layers[leaflet_id];
            layer.openPopup();

            // Focus the map on the map object.
            if (layer._latlngs) {
              map.setView(layer._latlngs[0]);
            }
            else {
              map.setView(layer.getLatLng());
            }
          }
        );

        // Manage blur event on input elements.
        $('#L' + leaflet_id + ', #T' + leaflet_id).blur(
          function() {
            layer = map._layers[leaflet_id];
            layer.closePopup();
          }
        );

        // Manage the removal of a label.
        $('.remove-label').click(
          function() {
            layer = map._layers[$(this).attr('data-label-id')];
            layer.closePopup();
            layer.unbindPopup();
            $('#L' + $(this).attr('data-label-id')).val('');
            $('#T' + $(this).attr('data-label-id')).val('');
            updateGeoJsonField();
          }
        );
      }

      /**
       * Update the GeoJSON field that contents the geoJSON data by checking all
       * elements in the map object.
       */
      function updateGeoJsonField() {
        geojson_map = drawnItems.toGeoJSON();
        i = 0
        for (key in drawnItems._layers) {
          // Check if the popups must be populated by input fields.
          if (settings.nexteuropa_geojson.settings.fs_objects.objects_amount > 1) {
            name = $('#L' + key).val();
            description = $('#T' + key).val();
          }
          else {
            name = getFieldValue(name_field);
            description = getFieldValue(description_field);
          }
          geojson_map.features[i].properties.name = name;
          geojson_map.features[i].properties.description = description;
          // Format Lat and Lng, only 4 decimals.
          if (geojson_map.features[i].geometry.type == 'Point') {
            for (id in geojson_map.features[i].geometry.coordinates) {
              geojson_map.features[i].geometry.coordinates[id] = parseFloat(geojson_map.features[i].geometry.coordinates[id].toFixed(4));
            }
          }
          else {
            for (id in geojson_map.features[i].geometry.coordinates[0]) {
              geojson_map.features[i].geometry.coordinates[0][id][0] = parseFloat(geojson_map.features[i].geometry.coordinates[0][id][0].toFixed(4));
              geojson_map.features[i].geometry.coordinates[0][id][1] = parseFloat(geojson_map.features[i].geometry.coordinates[0][id][1].toFixed(4));
            }
          }
          i++;
        }
        $("textarea[name*=geofield_geojson]").text(JSON.stringify(geojson_map));
      }

      /**
       * Update all the popups on the map by checking all elements in the map
       * object.
       */
      function updatePopups() {
        geojson_map = drawnItems.toGeoJSON();
        i = 0;
        for (key in drawnItems._layers) {
          if (settings.nexteuropa_geojson.settings.fs_objects.objects_amount > 1) {
            name = $('#L' + key).val();
            description = $('#T' + key).val();
          }
          else {
            name = getFieldValue(name_field);
            description = getFieldValue(description_field);
          }
          if (name != "" || description != "") {
            createPopup(key, name, description);
          }
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

      /**
       * Create the popup object and bind it to a map layer.
       *
       * @param {Number} leaflet_id
       *   ID of the leaflet layer of the popup.
       * @param {String} name
       *   Title of the popup.
       *
       * @return {String} description
       *   The content of the popup.
       */
      function createPopup(leaflet_id, name, description) {
        layer = map._layers[leaflet_id];
        popup_content = buildPopupContent(leaflet_id, name, description);
        layer.bindPopup(popup_content);
        layer._popup.setContent(popup_content);
        layer._popup.update();
      }

      /**
       * Get the DOM object of an input field.
       *
       * @param {String} field
       *   Name of the field.
       *
       * @return {String}
       *   The DOM object of the field.
       */
      function getFieldObject(field) {
        switch (field) {
          case "title_field":
            obj = $("input[name*='title']");
            break;

          case "body":
            for (var c in CKEDITOR.instances) {
              obj = CKEDITOR.instances[c];
              break;
            }
            break;

          default:
            obj = $("input[name*=" + field + "]");
        }
        return obj;
      }

      /**
       * Get the value of a input field.
       *
       * @param {String} field
       *   Name of the field.
       *
       * @return {String}
       *   The value of the field.
       */
      function getFieldValue(field) {
        switch (field) {
          case "title_field":
            value = $("input[name*='title']").val();
            break;

          case "body":
            for (var c in CKEDITOR.instances) {
              value = CKEDITOR.instances[c].getData();
              break;
            }
            break;

          default:
            value = $("input[name*=" + field + "]").val();
        }
        return value;
      }

    });

  }
})(jQuery);
