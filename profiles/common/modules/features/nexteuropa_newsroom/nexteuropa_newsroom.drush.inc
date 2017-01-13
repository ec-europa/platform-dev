<?php

/**
 * @file
 * Drush integration for the Newsroom module.
 */

/**
 * Implements hook_drush_command().
 */
function nexteuropa_newsroom_drush_command() {

  $items['newsroom-init'] = array(
    'description' => 'Initializes Newsroom importers.',
    'aliases' => array('nri'),
    'arguments' => array(
      'universe_id' => 'Newsroom Universe ID.',
    ),
  );

  return $items;
}

/**
 * Callback for the newsroom-init command.
 */
function drush_nexteuropa_newsroom_newsroom_init($universe_id = NULL) {
  if ($universe_id) {
    if (NewsroomHelper::validateUniverse($universe_id)) {
      variable_set('newsroom_universe_id', $universe_id);
      drush_print(dt('Newsroom Universe was found at: !universe', array('!universe' => NewsroomHelper::getUniverseUrl())));
      _nexteuropa_newsroom_admin_rebuild_importers();
    }
    else {
      return drush_set_error(dt('No Newsroom Universe was found!'));
    }
  }
  else {
    return drush_set_error(dt('No Newsroom Universe ID given.'));
  }
}
