<?php
/**
 * @file
 * Hooks provided by this module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Acts on map_layer being loaded from the database.
 *
 * This hook is invoked during $map_layer loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $map_layer entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_map_layer_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a $map_layer is inserted.
 *
 * This hook is invoked after the $map_layer is inserted into the database.
 *
 * @param MapLayer $map_layer
 *   The $map_layer that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_map_layer_insert(MapLayer $map_layer) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('map_layer', $map_layer),
      'extra' => print_r($map_layer, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a $map_layer being inserted or updated.
 *
 * This hook is invoked before the $map_layer is saved to the database.
 *
 * @param MapLayer $map_layer
 *   The $map_layer that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_map_layer_presave(MapLayer $map_layer) {
  $map_layer->name = 'foo';
}

/**
 * Responds to a $map_layer being updated.
 *
 * This hook is invoked after the $map_layer has been updated in the database.
 *
 * @param MapLayer $map_layer
 *   The $map_layer that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_map_layer_update(MapLayer $map_layer) {
  db_update('mytable')
    ->fields(array('extra' => print_r($map_layer, TRUE)))
    ->condition('id', entity_id('map_layer', $map_layer))
    ->execute();
}

/**
 * Responds to $map_layer deletion.
 *
 * This hook is invoked after the $map_layer has been removed from the database.
 *
 * @param MapLayer $map_layer
 *   The $map_layer that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_map_layer_delete(MapLayer $map_layer) {
  db_delete('mytable')
    ->condition('pid', entity_id('map_layer', $map_layer))
    ->execute();
}

/**
 * Act on a map_layer that is being assembled before rendering.
 *
 * @param $map_layer
 *   The map_layer entity.
 * @param $view_mode
 *   The view mode the map_layer is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $map_layer->content prior to rendering. The
 * structure of $map_layer->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_map_layer_view($map_layer, $view_mode, $langcode) {
  $map_layer->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for map_layers.
 *
 * @param $build
 *   A renderable array representing the map_layer content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * map_layer content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the map_layer rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_map_layer().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
function hook_map_layer_view_alter($build) {
  if ($build['#view_mode'] == 'default' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}

/**
 * Acts on map_layer_type being loaded from the database.
 *
 * This hook is invoked during map_layer_type loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of map_layer_type entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_map_layer_type_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a map_layer_type is inserted.
 *
 * This hook is invoked after the map_layer_type is inserted into the database.
 *
 * @param MapLayerType $map_layer_type
 *   The map_layer_type that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_map_layer_type_insert(MapLayerType $map_layer_type) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('map_layer_type', $map_layer_type),
      'extra' => print_r($map_layer_type, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a map_layer_type being inserted or updated.
 *
 * This hook is invoked before the map_layer_type is saved to the database.
 *
 * @param MapLayerType $map_layer_type
 *   The map_layer_type that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_map_layer_type_presave(MapLayerType $map_layer_type) {
  $map_layer_type->name = 'foo';
}

/**
 * Responds to a map_layer_type being updated.
 *
 * This hook is invoked after the map_layer_type has been updated in the database.
 *
 * @param MapLayerType $map_layer_type
 *   The map_layer_type that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_map_layer_type_update(MapLayerType $map_layer_type) {
  db_update('mytable')
    ->fields(array('extra' => print_r($map_layer_type, TRUE)))
    ->condition('id', entity_id('map_layer_type', $map_layer_type))
    ->execute();
}

/**
 * Responds to map_layer_type deletion.
 *
 * This hook is invoked after the map_layer_type has been removed from the database.
 *
 * @param MapLayerType $map_layer_type
 *   The map_layer_type that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_map_layer_type_delete(MapLayerType $map_layer_type) {
  db_delete('mytable')
    ->condition('pid', entity_id('map_layer_type', $map_layer_type))
    ->execute();
}

/**
 * Define default map_layer_type configurations.
 *
 * @return
 *   An array of default map_layer_type, keyed by machine names.
 *
 * @see hook_default_map_layer_type_alter()
 */
function hook_default_map_layer_type() {
  $defaults['main'] = entity_create('map_layer_type', array(
    // …
  ));
  return $defaults;
}

/**
 * Alter default map_layer_type configurations.
 *
 * @param array $defaults
 *   An array of default map_layer_type, keyed by machine names.
 *
 * @see hook_default_map_layer_type()
 */
function hook_default_map_layer_type_alter(array &$defaults) {
  $defaults['main']->name = 'custom name';
}
