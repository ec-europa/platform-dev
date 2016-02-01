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
    $universe_url = NewsroomHelper::getUniverseUrl($universe_id);
    if (_nexteuropa_newsroom_validate_universe($universe_id)) {
      variable_set('newsroom_universe_id', $universe_id);
      drush_print(dt('Newsroom Universe was found at: !universe', array('!universe' => $universe_url)));
      _nexteuropa_newsroom_create_default_importers($universe_id, 'drush');
    }
    else {
      return drush_set_error(dt('No Newsroom Universe was found at: !universe', array('!universe' => $universe_url)));
    }
  }
  else {
    return drush_set_error('', 'No Newsroom Universe ID given.');
  }
}
