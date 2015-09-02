/**
 * @file
 * Code for nexteuropa_geofield.edit.js file.
 */

(function ($) {

    Drupal.behaviors.toolbox = {
        attach: attach
    };

    function attach(context, settings) {
        var lat = settings.nexteuropa_geojson.settings.fs_default_map_center['lat'];
        var lng = settings.nexteuropa_geojson.settings.fs_default_map_center['lng'];
        var map = L.map('geofield_geojson_map', {}).setView([lat, lng], 13);

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
            if (settings.nexteuropa_geojson.settings.fs_objects.prepopulate_label.prepopulate == 0) {
                for (key in drawnItems._layers) {
                    // Create forms elements to manage popups content.
                    layer_properties = drawnItems._layers[key].feature.properties;
                    createLabel(key, layer_properties.label, layer_properties.description);
                    objects_count++;
                }
                updateGeoJsonField();
                updatePopups();
            }
            // Popups are pre-populated with the conteny title and body.
            else {
                $("input[name*='title']").change(
                    function() {
                        updateGeoJsonField();
                        updatePopups();
                        console.log($("input[name*='title']").val());
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
                        updatePopups();
                        for (var c in CKEDITOR.instances) {
                            CKEDITOR.instances[c].on(
                                'change', function() {
                                    updateGeoJsonField();
                                    updatePopups();
                                }
                            );
                            break;
                        }
                    }
                );
            }

            // Focus on map elements.
            map.fitBounds(drawnItems.getBounds());
        }

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
                    if (settings.nexteuropa_geojson.settings.fs_objects.prepopulate_label.prepopulate == 0) {
                        createLabel(layer._leaflet_id, "", "");
                    }
                    else {
                        // Prepopulate the popups with the title and body content.
                        name = $("input[name*='title']").val();
                        for (var c in CKEDITOR.instances) {
                            description = CKEDITOR.instances[c].getData();
                            break;
                        }
                        createPopup(layer._leaflet_id, name, description);
                    }

                    // Update GeoJSON field.
                    updateGeoJsonField();
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
     * @param {Number} leaflet_id
     *   id of the leaflet layer
     * @param {String} label
     *   title of the popup
     * @return {String} description
     *   the content of the popup
     */
        function createLabel(leaflet_id, label, description) {
            var myinput = '<div id="label_wrapper_' + leaflet_id + '" class="leaflet_label_wrapper"><input class="leaflet_label" name="myField" type="text" id="L' + leaflet_id + '">';
            myinput = myinput + '<textarea rows="2" class="leaflet_description" id="T' + leaflet_id + '"/>';
            myinput = myinput + '<a data-label-id="' + leaflet_id + '" class="remove-label" title="Delete labels."><span class="glyphicon glyphicon-trash" aria-hidden="true"></span></a></div>';

            $('#geofield_geojson_map_wrapper').append(myinput);
            $('#L' + leaflet_id).val(label);
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
                }
            );
        }

        /**
     * Update the GeoJSON field that contents the geoJson data by checking all elements in the map object.
     */
        function updateGeoJsonField() {
            geojson_map = drawnItems.toGeoJSON();
            i = 0
            for (key in drawnItems._layers) {
                // Check if the popups must be populated by the title and body content.
                if (settings.nexteuropa_geojson.settings.fs_objects.prepopulate_label.prepopulate == 0) {
                    name = $('#L' + key).val();
                    description = $('#T' + key).val();
                }
                else {
                    name = $("input[name*='title']").val();
                    for (var c in CKEDITOR.instances) {
                        description = CKEDITOR.instances[c].getData();
                        break;
                    }
                }
                geojson_map.features[i].properties.label = name;
                geojson_map.features[i].properties.description = description;
                i++;
            }
            $('#geofield_geojson textarea').text(JSON.stringify(geojson_map));
        }

        /**
     * Update all the popups on the map by checking all elements in the map object.
     */
        function updatePopups() {
            geojson_map = drawnItems.toGeoJSON();
            i = 0;
            for (key in drawnItems._layers) {
                if (settings.nexteuropa_geojson.settings.fs_objects.prepopulate_label.prepopulate == 0) {
                    name = $('#L' + key).val();
                    description = $('#T' + key).val();
                }
                else {
                    name = $("input[name*='title']").val();
                    for (var c in CKEDITOR.instances) {
                        description = CKEDITOR.instances[c].getData();
                        break;
                    }
                }
                createPopup(key, name, description);
            }
        }

        /**
     * Build the html content put in a popup.
     * @param {Number} leaflet_id
     *   id of the leaflet layer of the popup
     * @param {String} label
     *   title of the popup
     * @return {String} description
     *   the content of the popup
     */
        function buildPopupContent(leaflet_id, name, description) {
            var content = '<div id="popup_' + leaflet_id + '">';
            content = content + '<h4 class="popup_name">' + name + '</h4>';
            content = content + '<p class="popup_description">' + description + '</p>';
            content = content + '</div>';
            return content;
        }

        /**
     * Create the popup object and bind it to a map layer.
     * @param {Number} leaflet_id
     *   id of the leaflet layer of the popup
     * @param {String} label
     *   title of the popup
     * @return {String} description
     *   the content of the popup
     */
        function createPopup(leaflet_id, name, description) {
            layer = map._layers[leaflet_id];
            popup_content = buildPopupContent(leaflet_id, name, description);
            layer.bindPopup(popup_content);
            layer._popup.setContent(popup_content);
            layer._popup.update();
        }
    }
})(jQuery);
