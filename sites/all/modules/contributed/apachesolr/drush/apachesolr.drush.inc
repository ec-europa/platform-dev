<?php

/**
 * @file
 *   drush integration for apachesolr.
 */

/**
 * Implements hook_drush_command().
 *
 * @return array
 *   An associative array describing your command(s).
 */
function apachesolr_drush_command() {
  $items = array();

  $items['solr-delete-index'] = array(
    'callback' => 'apachesolr_drush_solr_delete_index',
    'description' => dt('Deletes the content from the index. Can take content types as parameters.'),
    'arguments' => array(
      'types' => dt('Optional. A space delimited list of content types to be deleted from the index.'),
    ),
    'examples' => array(
      'drush solr-delete-index node' => 'Delete all node content from the index.',
      'drush solr-delete-index node:article' => 'Delete all content of the article content type from the index.',
      'drush solr-delete-index node:article node:blog' => 'Delete all content of the article and blog content types from the index.',
    ),
  );
  $items['solr-mark-all'] = array(
    'callback' => 'apachesolr_drush_solr_mark_for_reindex',
    'description' => dt('Marks content for reindexing. Can take content types as parameters.'),
    'arguments' => array(
      'types' => dt('Optional. A space delimited list of content types to be marked for reindexing.'),
    ),
  );
  $items['solr-index'] = array(
    'callback' => 'apachesolr_drush_solr_index',
    'description' => dt('Reindexes content marked for (re)indexing.'),
  );
  $items['solr-search'] = array(
    'callback' => 'apachesolr_drush_solr_search',
    'description' => dt('Search the site for keywords using Apache Solr'),
    'arguments' => array(
      'keywords' => dt('One or more keywords, separated by spaces.'),
    ),
  );
  $items['solr-get-env-id'] = array(
    'callback' => 'apachesolr_drush_solr_get_env_id',
    'description' => dt('Get the default Apache Solr environment ID, or all IDs and names'),
    'arguments' => array(),
    'options' => array(
      'all' => array(
         'description' => 'List all environment IDs',
      ),
    ),
  );
  $items['solr-get-env-name'] = array(
    'callback' => 'apachesolr_drush_solr_get_env_name',
    'description' => dt('Get the Apache Solr environment name.'),
    'options' => array(
      'id' => array(
         'description' => 'Apache Solr environment ID to use (uses the default environment if not specified)',
      ),
    ),
  );
  $items['solr-get-env-url'] = array(
    'callback' => 'apachesolr_drush_solr_get_env_url',
    'description' => dt('Get the Apache Solr environment url.'),
    'options' => array(
      'id' => array(
         'description' => 'Apache Solr environment ID to use (uses the default environment if not specified)',
      ),
    ),
  );
  $items['solr-set-env-url'] = array(
    'callback' => 'apachesolr_drush_solr_set_env_url',
    'description' => dt('Set the url for an Apache Solr environment.'),
    'arguments' => array(
      'url' => dt('Apache Solr server url string.'),
    ),
    'required-arguments' => TRUE,
    'options' => array(
      'id' => array(
         'description' => 'Apache Solr environment ID to use (uses the default environment if not specified)',
      ),
    ),
  );
  $items['solr-variable-get'] = array(
    'description' => 'Get a list of Apache Solr environment variable names and values.',
    'arguments' => array(
      'name' => 'A string to filter the variables by. Variables that have any part of their name matching the string will b listed.',
    ),
    'examples' => array(
      'drush solr-vget' => 'List all variables and values.',
      'drush solr-vget user' => 'List all variables containing the string "user".',
    ),
    'options' => array(
      'id' => array(
         'description' => 'Apache Solr environment ID to use (uses the default environment if not specified)',
      ),
      'format' => array(
        'description' => 'Format to output the object. Use "print_r" for print_r (default), "export" for var_export, and "json" for JSON.',
        'example-value' => 'export',
      ),
      'pipe' => 'A synonym for --format=export. Useful for pasting into code.',
    ),
    'aliases' => array('solr-vget'),
  );
  $items['solr-variable-set'] = array(
    'description' => "Set an Apache Solr environment variable.",
    'arguments' => array(
      'name' => 'The name of a variable or the first few letters of its name.',
      'value' => 'The value to assign to the variable. Use \'-\' to read the object from STDIN.',
    ),
    'required-arguments' => TRUE,
    'options' => array(
      'id' => array(
         'description' => 'Apache Solr environment ID to use (uses the default environment if not specified)',
      ),
      'yes' => 'Skip confirmation if only one variable name matches.',
      'always-set' => 'Always skip confirmation.',
      'format' => array(
        'description' => 'Format to parse the object. Use "auto" to detect format from value (default), "string", "integer" or "boolean" for corresponding primitive type, and "json" for JSON.',
        'example-value' => 'boolean',
      ),
    ),
    'examples' => array(
      'drush solr-vset --yes apachesolr_read_only 1' => 'Set the apachesolr_read_only variable to 1. Skip confirmation if variable already exists.',
      'drush solr-vset pr TRUE' => 'Choose from a list of variables beginning with "pr" to set to (bool)true.',
      'php -r "print json_encode(array(\'drupal\', \'simpletest\'));"  | drush solr-vset --format=json project_dependency_excluded_dependencies -'=> 'Set a variable to a complex value (e.g. array)',
    ),
    'aliases' => array('solr-vset'),
  );
  $items['solr-variable-delete'] = array(
    'description' => "Delete an Apache Solr environment variable.",
    'arguments' => array(
      'name' => 'The name of a variable or the first few letters of its name.',
    ),
    'required-arguments' => TRUE,
    'options' => array(
      'id' => array(
         'description' => 'Apaches Solr environment ID to use (uses the default environment if not specified)',
      ),
      'yes' => 'Skip confirmation if only one variable name matches.',
      'exact' => 'Only delete the one variable that exactly matches the specified name.',
    ),
    'examples' => array(
      'drush solr-vdel apachesolr_read_only --id=solr2' => 'Delete the apachesolr_read_only variable for the solr2 environment.',
      'drush solr-vdel apa' => 'Choose from a list of variables beginning with "u" to delete.',
      'drush solr-vdel -y --exact apachesolr_read_only' => 'Delete variable, skipping confirmation.',
    ),
    'aliases' => array('solr-vdel'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param string $section
 *   A string with the help section (prepend with 'drush:')
 *
 * @return string
 *   A string with the help text for your command.
 */
function apachesolr_drush_help($section) {
  switch ($section) {
    case 'drush:solr-delete-index':
      return dt("Used without parameters, this command deletes the entire Solr index. Used with parameters for content type, it deletes just the content types that are specified. After the index has been deleted, all content will be indexed again on future cron runs.");
    case 'drush:solr-mark-all':
      return dt("Used without parameters, this command marks all of the content in the Solr index for reindexing. Used with paramters for content type, it marks just the content types that are specified. Reindexing is different than deleting as the content is still searchable while it is in queue to be reindexed. Reindexing is done on future cron runs.");
    case 'drush:solr-index':
      return dt("Reindexes content marked for (re)indexing. If you want to reindex all content or content of a specific type, use solr-reindex first to mark that content.");
    case 'drush:solr-search':
      return dt('Executes a search against the site\'s Apache Solr search index and returns the restults.');
    case 'error:APACHESOLR_ENV_ID_ERROR':
      return dt('Not a valid environment ID.');
  }
}

/**
 * Selectively delete content from the apachesolr index.
 *
 * Each argument is a filter on what to delete from the index.
 * They are of the form entity (to delete all content of that
 * entity) or entity:bundle (to delete all content of that
 * bundle).
 */
function apachesolr_drush_solr_delete_index() {
  module_load_include('inc', 'apachesolr', 'apachesolr.index');
  $args = func_get_args();
  $env_id = apachesolr_default_environment();

  if (count($args) > 0) {
    foreach ($args as $type) {
      $parts = explode(':', $type);
      if (count($parts) === 1) {
        apachesolr_index_delete_index($env_id, $type);
      }
      elseif (count($parts) == 2) {
        apachesolr_index_delete_index($env_id, $parts[0], $parts[1]);
      }
      else {
        drush_set_error('The syntax for each type is either entity or entity:bundle');
      }
    }
  }
  else {
    apachesolr_index_delete_index($env_id);
  }

  drush_print(t('Deleted the Solr index'));
}

function apachesolr_drush_solr_mark_for_reindex() {
  module_load_include('inc', 'apachesolr', 'apachesolr.index');
  $args = func_get_args();
  $env_id = apachesolr_default_environment();
  if (count($args) > 0) {
    foreach ($args as $type) {
      apachesolr_index_mark_for_reindex($env_id, $type);
    }
  }
  else {
    apachesolr_index_mark_for_reindex($env_id);
  }
  drush_print(t('Marked content for reindexing'));
}

function apachesolr_drush_solr_index() {
  module_load_include('inc', 'apachesolr', 'apachesolr.admin');
  module_load_include('inc', 'apachesolr', 'apachesolr.index');
  $env_id = apachesolr_default_environment();
  apachesolr_index_batch_index_remaining($env_id);
  drush_backend_batch_process();
}

function apachesolr_drush_solr_search() {
  $args = func_get_args();
  $keys = implode(' ', $args);
  foreach (apachesolr_search_search_execute($keys) as $result) {
    $output = 'node/' . $result['node']->entity_id . ' ' . dt('by @name (user/@uid)', array('@name' => strip_tags($result['user']), '@uid' => $result['node']->is_uid)) . "\n";
    $output .= dt('title: ') . $result['title'] . "\n";
    $output .= preg_replace('/[\s]+/', ' ', strip_tags($result['snippet'])) . "\n\n";
    drush_print($output);
  }
}

function apachesolr_drush_solr_get_env_id() {
  $all = drush_get_option('all');

  if ($all) {
    foreach (apachesolr_load_all_environments() as $id => $env) {
      drush_print(drush_format($env['name'], $id));
    }
  }
  else {
    $solr_env_id = apachesolr_default_environment();
    drush_print($solr_env_id);
  }
}

function apachesolr_drush_solr_get_env_name() {
  $env_id = drush_get_option('id', apachesolr_default_environment());
  try {
    $environment = _apachesolr_drush_environment_load_and_validate($env_id);
  }
  catch (Exception $e) {
    return drush_set_error('APACHESOLR_ENV_ID_ERROR', $e->getMessage());
  }
  drush_print($environment['name']);
}

function apachesolr_drush_solr_get_env_url() {
  $env_id = drush_get_option('id', apachesolr_default_environment());
  try {
    $environment = _apachesolr_drush_environment_load_and_validate($env_id);
  }
  catch (Exception $e) {
    return drush_set_error('APACHESOLR_ENV_ID_ERROR', $e->getMessage());
  }
  drush_print($environment['url']);
}

function apachesolr_drush_solr_set_env_url($url) {
  $env_id = drush_get_option('id', apachesolr_default_environment());
  try {
    $environment = _apachesolr_drush_environment_load_and_validate($env_id);
  }
  catch (Exception $e) {
    return drush_set_error('APACHESOLR_ENV_ID_ERROR', $e->getMessage());
  }
  $environment['url'] = $url;
  apachesolr_environment_save($environment);
}

/*** variable code - much of it copied from dush core **/

/**
 * Command callback.
 * List your site's variables.
 */
function drush_apachesolr_solr_variable_get($arg_name = NULL) {
  $output = NULL;

  $found = array();

  $env_id = drush_get_option('id', apachesolr_default_environment());
  try {
    $found = _apachesolr_drush_variable_like($env_id, $arg_name);
  }
  catch (Exception $e) {
    return drush_set_error('APACHESOLR_ENV_ID_ERROR', $e->getMessage());
  }

  foreach ($found as $name => $value) {
    drush_print_pipe(drush_format($value, $name, 'export'));
    drush_print(drush_format($value, $name));
  }

  if (empty($found)) {
    return drush_set_error('DRUSH_VARIABLE_ERROR', 'No matching variable found.');
  }
  else {
    return $found;
  }
}

/**
 * Command callback.
 * Set a variable.
 */
function drush_apachesolr_solr_variable_set($arg_name, $value) {
  $args = func_get_args();

  if (!isset($value)) {
    return drush_set_error('DRUSH_VARIABLE_ERROR', dt('No value specified.'));
  }

  $env_id = drush_get_option('id', apachesolr_default_environment());
  try {
    $found = _apachesolr_drush_variable_like($env_id, $arg_name, TRUE);
  }
  catch (Exception $e) {
    return drush_set_error('APACHESOLR_ENV_ID_ERROR', $e->getMessage());
  }

  $options[] = "$arg_name ". dt('(new variable)');
  $match = isset($found[$arg_name]);
  if (!$match && $found) {
    $options = array_merge($options, array_keys($found));
  }

  if ($value == '-') {
    $value = stream_get_contents(STDIN);
  }

  // If the value is a string (usual case, unless we are called from code),
  // then format the input
  if (is_string($value)) {
    $value = _apachesolr_drush_variable_format($value, drush_get_option('format', 'auto'));
  }

  // Format the output for display
  if (is_array($value)) {
    $display = "\n" . var_export($value, TRUE);
  }
  elseif (is_integer($value)) {
    $display = $value;
  }
  elseif (is_bool($value)) {
    $display = $value ? "TRUE" : "FALSE";
  }
  else {
    $display = '"' . $value . '"';
  }

  $name = NULL;
  if (drush_get_option('always-set', FALSE) || $match) {
    $name = $arg_name;
  }
  else {
    $choice = drush_choice($options, 'Enter a number to choose which variable to set.');
    if ($choice !== FALSE) {
      $name = ($choice == 0) ? $arg_name : $options[$choice];
    }
  }
  if ($name) {
    drush_op('apachesolr_environment_variable_set', $env_id, $name, $value);
    drush_log(dt('!name was set to !value', array('!name' => $name, '!value' => $display)), 'success');
  }
}

function _apachesolr_drush_variable_format($value, $format) {
  if ($format == 'auto') {
    if (is_numeric($value)) {
      $format = 'integer';
    }
    elseif (($value == 'TRUE') || ($value == 'FALSE')) {
      $format = 'bool';
    }
  }

  // Now, we parse the object.
  switch ($format) {
    case 'integer':
      $value = (integer)$value;
      break;

    case 'bool':
    case 'boolean':
      if ($value == 'TRUE') {
        $value = TRUE;
      }
      elseif ($value == 'FALSE') {
        $value = FALSE;
      }
      else {
        $value = (bool)$value;
      }
      break;

    case 'json':
      $value = drush_json_decode($value);
      break;
  }
  return $value;
}

/**
 * Command callback.
 * Delete a variable.
 */
function drush_apachesolr_solr_variable_delete($arg_name) {

  $env_id = drush_get_option('id', apachesolr_default_environment());
  // Look for similar variable names.
  try {
    $found = _apachesolr_drush_variable_like($env_id, $arg_name, TRUE);
  }
  catch (Exception $e) {
    return drush_set_error('APACHESOLR_ENV_ID_ERROR', $e->getMessage());
  }
  drush_log(dt('Using environment ID "!env_id"', array('!env_id' => $env_id)), 'success');
  $options = array_keys($found);

  if (drush_get_option('exact', FALSE)) {
    $options = isset($found[$arg_name]) ? array($arg_name) : array();
  }

  if (empty($options)) {
    drush_print(dt('!name not found.', array('!name' => $arg_name)));
    return '';
  }

  $name = NULL;
  if ((count($options) == 1) && drush_get_context('DRUSH_AFFIRMATIVE')) {
    $name = $arg_name;
  }
  else {
    $choice = drush_choice($options, 'Enter a number to choose which variable to delete.');
    if ($choice !== FALSE) {
      $name = $options[$choice];
    }
  }
  if ($name) {
    drush_op('apachesolr_environment_variable_del', $env_id, $name);
    drush_log(dt('!choice was deleted.', array('!choice' => $name)), 'success');
  }
}

/**
 * Load an environment from an id and validate the result.
 *
 * @throws Exception
 */
function _apachesolr_drush_environment_load_and_validate($env_id) {
  $environment = apachesolr_environment_load($env_id);
  if (!$environment) {
    throw new Exception(dt('!env_id is not a valid environment ID.', array('!env_id' => $env_id)));
  }
  drush_log(dt('Using environment ID: "!env_id"', array('!env_id' => $env_id)), 'success');
  return $environment;
}

/**
 * Search for similar variable names.
 *
 * @throws Exception
 */
function _apachesolr_drush_variable_like($env_id, $arg = NULL, $starts_with = FALSE) {
  $found = array();
  $environment = _apachesolr_drush_environment_load_and_validate($env_id);
  if (!isset($arg)) {
    return $environment['conf'];
  }
  if ($starts_with) {
    $pattern = "/^{$arg}/i";
  }
  else {
    $pattern = "/{$arg}/i";
  }
  foreach ($environment['conf'] as $name => $value) {
    // Find all variable that start with $arg.
    if (preg_match($pattern, $name)) {
      $found[$name] = $value;
    }
  }
  return $found;
}

