<?php
$script_filepath = __FILE__;
$script_dirpath = dirname($script_filepath);
chdir($script_dirpath . '/..');

require('lib/helpers.inc.php');
define('STATE_DONE', 'done');
// each time this script is run, every incomplete subsite will get the right to run up to $max_steps steps
define('MAX_SUBSITE_STEPS_PER_RUN', 1);
require('conf/supermaster.inc.php');
if (file_exists('conf/supermaster.local.inc.php')) {
	require('conf/supermaster.local.inc.php');
}
require('lib/drupalsubsite.class.php');

connect_to_supermaster_database();
foreach(DrupalSubSite::fetchIncompleteSubSites() as $incomplete_subsite) {
	$install_policy = $incomplete_subsite->installPolicy();
	if (!load_install_policy($install_policy)) {
		// error management (boring yet must-have)
		continue;
	}
	
	$steps_function = $install_policy . '_install_policy_get_steps';
	$steps = $steps_function($incomplete_subsite);
	
	$remaining_steps = constant('MAX_SUBSITE_STEPS_PER_RUN');
	while ($remaining_steps > 0) {
		$next_function = $steps[$incomplete_subsite->state()];
		if (!function_exists($next_function)) {
			// error management (boring yet must-have)
			break;
		}
		
		$result = $next_function($incomplete_subsite); // of course, this thingie is passed by reference
		if ($result['report']) {
			// gather data for the report that will be sent/stored/whatever at the end of the script (just boring)
			var_dump($result['report']);
		}
		$incomplete_subsite->setState($result['new_state']);
		$incomplete_subsite->saveState();
		
		// install steps may state it is not needed to keep calling them for this run
		if (isset($result['break'])) break;
		
		// maybe the work is simply finished?
		if ($result['new_state'] == constant('STATE_DONE')) break;
		
		-- $remaining_steps;
	}
}
