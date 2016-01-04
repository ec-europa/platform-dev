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
 * Acts on ne_map being loaded from the database.
 *
 * This hook is invoked during $ne_map loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $ne_map entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_ne_map_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a $ne_map is inserted.
 *
 * This hook is invoked after the $ne_map is inserted into the database.
 *
 * @param Map $ne_map
 *   The $ne_map that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_ne_map_insert(Map $ne_map) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('ne_map', $ne_map),
      'extra' => print_r($ne_map, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a $ne_map being inserted or updated.
 *
 * This hook is invoked before the $ne_map is saved to the database.
 *
 * @param Map $ne_map
 *   The $ne_map that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_ne_map_presave(Map $ne_map) {
  $ne_map->name = 'foo';
}

/**
 * Responds to a $ne_map being updated.
 *
 * This hook is invoked after the $ne_map has been updated in the database.
 *
 * @param Map $ne_map
 *   The $ne_map that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_ne_map_update(Map $ne_map) {
  db_update('mytable')
    ->fields(array('extra' => print_r($ne_map, TRUE)))
    ->condition('id', entity_id('ne_map', $ne_map))
    ->execute();
}

/**
 * Responds to $ne_map deletion.
 *
 * This hook is invoked after the $ne_map has been removed from the database.
 *
 * @param Map $ne_map
 *   The $ne_map that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_ne_map_delete(Map $ne_map) {
  db_delete('mytable')
    ->condition('pid', entity_id('ne_map', $ne_map))
    ->execute();
}

/**
 * Act on a ne_map that is being assembled before rendering.
 *
 * @param $ne_map
 *   The ne_map entity.
 * @param $view_mode
 *   The view mode the ne_map is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $ne_map->content prior to rendering. The
 * structure of $ne_map->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_ne_map_view($ne_map, $view_mode, $langcode) {
  $ne_map->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for ne_maps.
 *
 * @param $build
 *   A renderable array representing the ne_map content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * ne_map content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the ne_map rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_ne_map().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
function hook_ne_map_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}
