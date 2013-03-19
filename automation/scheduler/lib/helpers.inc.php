<?php
function say($string) {
	printf("[%s] %s\n", date('%F:%T'), $string);
}

function exitWithMessage($rc, $string) {
	say($string);
	exit($rc);
}

function connect_to_supermaster_database() {
	global $supermaster_server;
	global $supermaster_user;
	global $supermaster_password;
	global $supermaster_database;
	global $db_conn;
	$db_conn = mysqli_connect($supermaster_server, $supermaster_user, $supermaster_password);
	if (!$db_conn) {
		exitWithMessage(250, 'Unable to connect to the MySQL server hosting the supermaster database');
	}
	if (!mysqli_select_db($db_conn, $supermaster_database)) {
		exitWithMessage(240, 'Unable to select the supermaster database');
	}
}

function load_install_policy($policy_name) {
	$policy_conf = 'conf/policies/' . $policy_name . '.inc.php';
	$policy_local_conf = 'conf/policies/' . $policy_name . '.local.inc.php';
	$policy_file = 'lib/policies/'  . $policy_name . '.inc.php';
	if (!file_exists($policy_file)) {
		return FALSE;
	}
	require_once($policy_file);
	
	// most policies will ship a default configuration file...
	if (file_exists($policy_conf)) {
		require_once($policy_conf);
	}
	
	// ... and most administrators will override it "locally".
	if (file_exists($policy_local_conf)) {
		require_once($policy_local_conf);
	}
	return function_exists($policy_name . '_install_policy_get_steps');
}

function mkpath($path) {
	if(@mkdir($path) or file_exists($path)) return TRUE;
	return(mkpath(dirname($path)) and mkdir($path));
}

function execute_command($command, $command_redirections = '< /dev/null 2>&1') {
	$return = array('command' => $command, 'code' => -1, 'output' => '');
	$proc_res = popen($command . ' ' . $command_redirections, 'r');
	if ($proc_res === FALSE) return $return;
	$return['output'] = stream_get_contents($proc_res);
	$return['code'] = pclose($proc_res);
	return $return;
}

function execute_command_with_stdin($stdin_content, $command, $command_redirections = '2>&1') {
	$return = array('command' => $command, 'code' => -1, 'output' => '');
	$proc_res = proc_open(
		$command . ' ' . $command_redirections,
		array(
			0 => array('pipe', 'r'),
			1 => array('pipe', 'w'),
		),
		$pipes
	);
	if ($proc_res === FALSE) return $return;
	
	// we send our content to the process stdin
	fwrite($pipes[0], $stdin_content);
	fclose($pipes[0]);
	
	// we read its stdout (+stderr since we use 2>&1 by default)
	$return['output'] = stream_get_contents($pipes[1]);
	
	// eventually, we get its return code:
	$return['code'] = proc_close($proc_res);
	return $return;
}

/**
 * @param $subsite Subsite the drush command will be applied to
 * @param $command Drush command to be executed (without the leading "drush")
 * @return an array with the following interesting keys:
 *   * chdir: boolean, whether the chdir() to the susbsite succeeded
 *   * reports: array of warning/error messages to be reported administrators
 *   * command: the executed command
 *   * code: the exit status of the executed command
 *   * output: the output (stdout+stderr) of the executed command
 */
function drush_subsite($subsite, $command) {
	// save original working directory
	$previous_wd = getcwd();
	
	$return = array('reports' => array());
	$wd = $subsite->master()->path('sites') . '/' . $subsite->name();
	$return['chdir'] = chdir($wd);
	if (!$return['chdir']) {
		$return['reports'][] = sprintf('unable to change working directory to %s', $wd);
	} else {
		$command = 'drush ' . $command . ' --yes';
		$command_execution = execute_command($command);
		if ($command_execution['code'] !== 0) {
			$return['reports'][] = sprintf('the following drush command exited with status code %d for subsite %s: %s', $command_execution['code'], $subsite->name(), $command);
		}
		$return += $command_execution;
	}
	
	// restore original working directory
	chdir($previous_wd);
	
	return $return;
}
