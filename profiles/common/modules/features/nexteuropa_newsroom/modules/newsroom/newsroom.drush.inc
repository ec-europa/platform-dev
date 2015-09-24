<?php
/**
 * @file
 * Drush integration for the Newsroom module.
 */

/**
 * Implements hook_drush_command().
 */
function newsroom_drush_command() {

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
function drush_newsroom_init($universe_id = NULL) {
  if ($universe_id) {
    $universe_url = NEWSROOM_URL . $universe_id;
    if (_newsroom_validate_universe($universe_id)) {
      variable_set('newsroom_universe_id', $universe_id);
      drush_print(dt('Newsroom Universe was found at: !universe', array('!universe' => $universe_url)));
      _newsroom_create_default_importers($universe_url, 'drush');
    }
    else {
      return drush_set_error(dt('No Newsroom Universe was found at: !universe', array('!universe' => $universe_url)));
    }
  }
  else {
    return drush_set_error('', 'No Newsroom Universe ID given.');
  }
}
