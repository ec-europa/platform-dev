<?php
require_once('lib/policyconfig.inc.php');
class FPFISPolicyConfig extends PolicyConfig {
	// well, nothing special at the moment.
};

function fpfis_install_policy_get_steps($subsite) {
	return(
		array(
			'declared' => 'fpfis_check_master',
			'master_checks_failed' => 'fpfis_do_nothing',
			'master_checks_ok' => 'fpfis_check_dbinstance',
			'dbinstance_checks_failed' => 'fpfis_do_nothing',
			'database_to_be_required' => 'fpfis_require_database',
			'database_required' => 'fpfis_check_required_database',
			'database_not_required' => 'fpfis_do_nothing',
			'dbinstance_checks_ok' => 'fpfis_check_database',
			'database_checks_failed' => 'fpfis_do_nothing',
			'database_checks_ok' => 'fpfis_drop_tables',
			'drop_tables_failed' => 'fpfis_do_nothing',
			'database_ready' => 'fpfis_create_files_dir',
			'files_dir_creation_failed' => 'fpfis_do_nothing',
			'files_dir_created' => 'fpfis_install_default_files',
			'default_files_failed' => 'fpfis_do_nothing',
			'default_files_installed' => 'fpfis_subsite_install',
			'subsite_install_failed' => 'fpfis_do_nothing',
			'subsite_installed' => 'fpfis_change_admin_password',
			'admin_password_failed' => 'fpfis_do_nothing',
			'admin_password_changed' => 'fpfis_register_subsite_master',
			'subsite_registered_master_failed' => 'fpfis_do_nothing',
			'subsite_registered_master' => 'fpfis_register_subsite_rewritemap',
			'subsite_registered_rewritemap_failed' => 'fpfis_do_nothing',
			'subsite_registered_rewritemap' => 'fpfis_adjust_subsite_settings',
			'subsite_settings_adjusted_failed' => 'fpfis_do_nothing',
			'subsite_settings_adjusted' => 'fpfis_configure_apachesolr',
			'apachesolr_configure_failed' => 'fpfis_do_nothing',
			'apachesolr_configured' => 'fpfis_enable_varnish',
			'varnish_enable_failed' => 'fpfis_do_nothing',
			'varnish_enabled' => 'fpfis_clear_subsite_caches',
			'caches_clear_failed' => 'fpfis_do_nothing',
			'caches_cleared' => 'fpfis_push_files_to_web_servers',
			'files_push_failed' => 'fpfis_do_nothing',
			'files_pushed' => 'fpfis_finalize_subsite_installation',
			constant('STATE_DONE') => 'fpfis_do_nothing',
		)
	);
}

function fpfis_do_nothing(&$subsite) {
	return(array('break' => TRUE));
}

function fpfis_check_master(&$subsite) {
	$reports = array();
	if (!is_object($subsite->master())) {
		$reports[] = 'unable to fetch master informations';
	} else {
		$local_master_files = $subsite->master()->path('files');
		if (!is_dir($local_master_files)) {
			$reports[] = 'The "files" parent directory of the master site does not appear to exist';
		} else {
			/// TODO check ability to write in that directory?
		}
		
		$local_master_sites = $subsite->master()->path('sites');
		if (!is_dir($local_master_sites)) {
			$reports[] = 'the "sites" directory of the master site does not appear to exist';
		} else {
			/// TODO check ability to write in that directory?
			
			foreach (array('sites.php', 'sites.list.php', 'settings.common.php', 'settings.common.post.php') as $file) {
				if (!is_file($local_master_sites . '/' . $file)) {
					$reports[] = sprintf('the "%s" file does not appear to exist', $file);
				}
			}
		}
		
		$local_rewritemap = $subsite->master()->path('rewritemap');
		if (!is_file($local_rewritemap)) {
			$reports[] = sprintf('the "%s" file does not appear to exist', $local_rewritemap);
		}
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'master_checks_failed' : 'master_checks_ok';
	return $return;
}

function fpfis_check_dbinstance(&$subsite) {
	$reports = array();
	if (!is_object($subsite->databaseInstance())) {
		$reports[] = 'unable to fetch database instance informations';
	} else {
		$hostname = $subsite->databaseInstance()->hostname();
		if (gethostbyname($hostname) == $hostname) {
			$reports[] = sprintf('unable to resolve database hostname "%s"', $hostname);
		}
		if (!strlen($subsite->databaseName())) {
			$reports[] = sprintf('no database name were provided for this subsite');
		}
		if (!strlen($subsite->databaseUsername())) {
			$reports[] = sprintf('no username were provided to reach the subsite database');
		}
	}
	
	$return = array('report' => $reports);
	if (count($reports)) {
		$return['break'] = TRUE;
		$return['new_state'] = 'dbinstance_checks_failed';
	} else {
		if (!strlen($subsite->databasePassword())) {
			// if the only missing information is the password, it means we
			// must require the database creation to the ISHS team
			$return['new_state'] = 'database_to_be_required';
		} else {
			$return['new_state'] = 'dbinstance_checks_ok';
		}
	}
	return $return;
}

function fpfis_require_database(&$subsite) {
	$default_machines = FPFISPolicyConfig::get('mysql_default_machines');
	$mail_returnpath = FPFISPolicyConfig::get('mysql_creation_mail_returnpath');
	$mail_from = FPFISPolicyConfig::get('mysql_creation_mail_from');
	$mail_to = FPFISPolicyConfig::get('mysql_creation_mail_to');
	$mail_cc = FPFISPolicyConfig::get('mysql_creation_mail_cc');
	$mail_subject = FPFISPolicyConfig::get('mysql_creation_mail_subject');
	$mail_body = FPFISPolicyConfig::get('mysql_creation_mail_body');
	$data = $subsite->data();
	
	if (isset($data['ishs_db_creation_request'])) {
		// It seems a request has already been issued; we prefer aborting here
		// rather than sending too much emails to ISHS.
		$return = array('new_state' => 'database_not_required');
		$return['report'] = sprintf('It seems a database creation request has already been sent to ISHS, aborting');
		$return['break'] = TRUE;
		return $return;
	}
	
	// fetch information required to compose the mail
	$tokens['mysql_instance'] = sprintf('%s:%s', $subsite->databaseInstance()->hostname(), $subsite->databaseInstance()->port());
	$tokens['mysql_username'] = $subsite->databaseUsername();
	$web_hostnames = $default_machines;
	foreach ($subsite->master()->cluster()->webServers() as $web_server) {
		$web_hostnames[] = $web_server['hostname'];
	}
	$tokens['client_machines'] = implode(', ', $web_hostnames);
	$tokens['mysql_db_name'] = $subsite->databaseName();
	
	// compose the mail
	foreach ($tokens as $name => $value) {
		$mail_body = str_replace('@' . $name, $value, $mail_body);
	}
	
	// send the mail
	$headers = 'From: ' . $mail_from . "\n";
	if (strlen($mail_cc)) $headers .= 'Cc: ' . $mail_cc;
	$parameters = '-f ' . $mail_from;
	mail($mail_to, $mail_subject, $mail_body, $headers, $parameters);
	
	// store the sent mail
	$data['ishs_db_creation_request']['timestamp'] = time();
	$data['ishs_db_creation_request']['to'] = $mail_to;
	$data['ishs_db_creation_request']['subject'] = $mail_subject;
	$data['ishs_db_creation_request']['body'] = $mail_body;
	$data['ishs_db_creation_request']['headers'] = $headers;
	$data['ishs_db_creation_request']['parameters'] = $parameters;
	$subsite->setData($data);
	
	// next step is "database required"
	$return = array('new_state' => 'database_required');
	$return['report'] = sprintf('A mail titled "%s" was sent to %s.', $mail_subject, $mail_to);
	$return['break'] = TRUE;
	return $return;
}

function fpfis_check_required_database(&$subsite) {
	$reminder_delay = FPFISPolicyConfig::get('mysql_creation_reminder_delay');
	$reminder_from = FPFISPolicyConfig::get('mysql_creation_reminder_from');
	$reminder_to = FPFISPolicyConfig::get('mysql_creation_reminder_to');
	$reminder_subject = FPFISPolicyConfig::get('mysql_creation_reminder_subject');
	$reminder_body = FPFISPolicyConfig::get('mysql_creation_reminder_body');
	
	if (strlen($subsite->databasePassword())) {
		// the password was provided
		return array(
			'new_state' => 'dbinstance_checks_ok',
			'report' => sprintf('the database password for %s was provided', $subsite->name())
		);
	} else {
		$return = array('new_state' => 'database_required', 'break' => TRUE);
		$data = $subsite->data();
		
		$reminder_count = 0;
		$last_date = $subsite->lastUpdateTimeStamp();
		if (isset($data['ishs_db_creation_reminder'])) {
			$reminder_count = count($data['ishs_db_creation_reminder']);
			$last_date = $data['ishs_db_creation_reminder'][$reminder_count - 1]['timestamp'];
		}
		
		if (time() >= $last_date + $reminder_delay) {
			// send a reminder
			/// FIXME not enough tokens here...
			$reminder_subject = sprintf($reminder_subject, $subsite->name(), $reminder_count + 1);
			$reminder_body = str_replace('@subsite_name', $subsite->name(), $reminder_body);
			$headers = 'From: ' . $reminder_from . "\n";
			$parameters = '-f ' . $reminder_from;
			mail($reminder_to, $reminder_subject, $reminder_body, $headers, $parameters);
			$data['ishs_db_creation_reminder'][]['timestamp'] = time();
		}
		
		$subsite->setData($data);
		return $return;
	}
}

function fpfis_check_database(&$subsite) {
	$reports = array();
	/// as soon as a password is provided, try connecting to the server and to the database
	if (!strlen($subsite->databasePassword())) {
		$reports[] = 'no password were provided to reach the subsite database';
	} else {
		$subsite_db_conn = new mysqli(
			$subsite->databaseInstance()->hostname(),
			$subsite->databaseUsername(),
			$subsite->databasePassword(),
			$subsite->databaseName(),
			$subsite->databaseInstance()->port()
		);
		if ($subsite_db_conn->connect_error) {
			$reports[] = sprintf(
				'unable to connect to %s: got the following error: %s',
				$subsite->connectionString(),
				$subsite_db_conn->connect_error
			);
		} else {
			$tests = array(
				array('query' => 'CREATE TABLE fpfis_test_table (foo int(11));', 'message' => 'table creation failed'),
				array('query' => 'INSERT INTO fpfis_test_table VALUES (42);', 'message' => 'data insertion failed'),
				array('query' => 'DELETE FROM fpfis_test_table WHERE foo = 42;', 'message' => 'data deletion failed'),
				array('query' => 'DROP TABLE fpfis_test_table;', 'message' => 'table deletion failed'),
			);
			foreach ($tests as $test) {
				$result = $subsite_db_conn->query($test['query']);
				if ($result !== TRUE) {
					$reports[] = sprintf('Database tests failed: %s', $test['message']);
					break;
				}
			}
			$subsite_db_conn->close();
		}
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'database_checks_failed' : 'database_checks_ok';
	return $return;
}

function fpfis_drop_tables(&$subsite) {
	$reports = array();
	
	$subsite_db_conn = new mysqli(
		$subsite->databaseInstance()->hostname(),
		$subsite->databaseUsername(),
		$subsite->databasePassword(),
		$subsite->databaseName(),
		$subsite->databaseInstance()->port()
	);
	if ($subsite_db_conn->connect_error) {
		$reports[] = sprintf(
			'unable to connect to %s: got the following error: %s',
			$subsite->connectionString(),
			$subsite_db_conn->connect_error
		);
	} else {
		$tables_list = array();
		$tables = $subsite_db_conn->query('SHOW TABLES;');
		if ($tables === FALSE) {
			$reports[] = 'unable to list tables';
		} else {
			while ($row = $tables->fetch_array(MYSQLI_NUM)) $tables_list[] = $row[0];
			foreach($tables_list as $table) {
				$result = $subsite_db_conn->query(sprintf('DROP TABLE %s;', $subsite_db_conn->real_escape_string($table)));
				if ($result !== TRUE) {
					$reports[] = sprintf('a problem occurred when dropping table %s', $table);
				}
			}
		}
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'drop_tables_failed' : 'database_ready';
	return $return;
}

function fpfis_create_files_dir(&$subsite) {
	$report = array();
	
	/// create the directory that will host the subsite's files
	$files_directory_path = sprintf('%s/%s/files', $subsite->master()->path('files'), $subsite->name());
	mkpath($files_directory_path);
	if (!is_dir($files_directory_path)) {
		$reports[] = sprintf('Unable to create files directory ( %s ) for subsite %s', $files_directory_path, $subsite->name());
	}
	
	/// create the directory that will host the subsite's private files
	$private_files_directory_path = sprintf('%s/%s', $files_directory_path, FPFISPolicyConfig::get('private_files_relpath'));
	mkpath($private_files_directory_path);
	if (!is_dir($private_files_directory_path)) {
		$reports[] = sprintf('Unable to create private files directory ( %s ) for subsite %s', $private_files_directory_path, $subsite->name());
	}
	
	/// create the directory that will host the subsite itself (settings.php + symlink to files directory)
	$subsite_directory_path = sprintf('%s/%s', $subsite->master()->path('sites'), $subsite->name());
	mkpath($subsite_directory_path);
	if (!is_dir($files_directory_path)) {
		$reports[] = sprintf('Unable to create subsite directory ( %s ) for subsite %s', $subsite_directory_path, $subsite->name());
	} else {
		/// create the symlink to the files directory
		if (!is_link($subsite_directory_path . '/files')) {
			if (!symlink($files_directory_path, $subsite_directory_path . '/files')) {
				$reports[] = sprintf('Unable to symlink %s -> %s for subsite %s', $subsite_directory_path, $files_directory_path, $subsite->name());
			}
		}
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'files_dir_creation_failed' : 'files_dir_created';
	return $return;
}

function fpfis_install_default_files(&$subsite) {
	$reports = array();
	$source = sprintf('%s/default/files/default_images', $subsite->master()->path('sites'));
	$destination = sprintf('%s/%s/files/', $subsite->master()->path('files'), $subsite->name());
	
	// we simply fork a cp command and expect 0 to be returned
	$command = sprintf("cp -a %s %s", escapeshellarg($source), escapeshellarg($destination));
	$copy = execute_command($command);
	if ($copy['code'] !== 0) {
		$reports[] = sprintf(
			"The following error(s) occurred when copying %s into %s:\n%s\nReturn-Code: %d",
			$source,
			$destination,
			$copy['output'],
			$copy['code']
		);
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'default_files_failed' : 'default_files_installed';
	return $return;
}

function fpfis_subsite_install(&$subsite) {
	$drush_log_dir = FPFISPolicyConfig::get('drush_log_dir');
	$next_state = 'subsite_installed';
	
	$reports = array();
	
	// prepare the drush command to be forked
	$tokens = array(
		'install_profile' => FPFISPolicyConfig::get('default_install_profile', 'multisite_drupal_standard'),
		'subsites_directory' => $subsite->name(),
		'subsite_db_url' => $subsite->connectionString(),
		'account_name' => FPFISPolicyConfig::get('admin_account_name'),
		'account_pass' => FPFISPolicyConfig::get('admin_account_initial_password'),
		'site_name' =>  $subsite->name(),
		'site_mail' => FPFISPolicyConfig::get('site_mail')
	);
	$command = 'drush si @install_profile --yes --sites-subdir=@subsites_directory --db-url="@subsite_db_url" --account-name=@account_name --account-pass=@account_pass --site-name=@site_name --site-mail=@site_mail';
	foreach ($tokens as $token => $value) {
		$command = str_replace('@' . $token, $value, $command);
	}
	
	// open a log file to store the drush output
	$drush_log_file = sprintf('%s/subsite_install.%s.%s.log', $drush_log_dir, $subsite->name(), date('Ymd.His'));
	$log_fh = fopen($drush_log_file, 'w');
	if (!$log_fh) {
		$reports[] = sprintf('Unable to open log file %s -- drush execution will not be logged.', $drush_log_file);
	}
	
	$previous_wd = getcwd();
	$wd = $subsite->master()->path('sites') . '/..';
	if (!chdir($wd)) {
		$reports[] = sprintf('unable to change working directory to %s', $wd);
		$next_state = 'subsite_install_failed';
	} else {
		$command_execution = execute_command($command);
		
		// log the drush output if possible
		if ($log_fh) {
			fwrite($log_fh, $command_execution['output']);
			fclose($log_fh);
		}
		
		if ($command_execution['code'] !== 0) {
			$reports[] = sprintf('the drush command exited with status code %d, considering the drush installation failed for subsite %s', $command_execution['code'], $subsite->name());
			$next_state = 'subsite_install_failed';
		}
	}
	chdir($previous_wd);
	
	$return = array('report' => $reports);
	if ($next_state != 'subsite_installed') $return['break'] = TRUE;
	$return['new_state'] = $next_state;
	return $return;
}

function fpfis_change_admin_password(&$subsite) {
	$admin_username = FPFISPolicyConfig::get('admin_account_name');
	$definitive_admin_password = FPFISPolicyConfig::get('admin_account_final_password');
	
	$reports = array();
	$next_state = 'admin_password_changed';
	
	$previous_wd = getcwd();
	$wd = $subsite->master()->path('sites') . '/' . $subsite->name();
	if (!chdir($wd)) {
		$reports[] = sprintf('unable to change working directory to %s', $wd);
		$next_state = 'admin_password_failed';
	} else {
		$command = sprintf('drush user-password %s', $admin_username);
		$command_execution = execute_command_with_stdin($definitive_admin_password . "\n", $command);
		if ($command_execution['code'] !== 0) {
			$reports[] = sprintf('the "user-password" drush command exited with status code %d for subsite %s', $command_execution['code'], $subsite->name());
			$next_state = 'admin_password_failed';
		}
	}
	chdir($previous_wd);
	
	$return = array('report' => $reports);
	if ($next_state != 'admin_password_changed') $return['break'] = TRUE;
	$return['new_state'] = $next_state;
	return $return;
}

function fpfis_register_subsite_master(&$subsite) {
	/// add the new subsite to the master's sites.list.php
	$reports = array();
	$next_state = 'subsite_registered_master';
	
	// compose the php line required for the master site to recognize the new subsite
	$php_line = sprintf('$sites[\'%s\'] = \'%s\';', $subsite->completeUrlPattern(), $subsite->name());
	
	$sites_list_path = $subsite->master()->path('sites') . '/sites.list.php';
	if (!file_exists($sites_list_path)) {
		$sites_list_fh = fopen($sites_list_path, 'w');
		if (!$sites_list_fh) {
			$reports[] = sprintf('unable to open new file %s', $sites_list_path);
			$next_state = 'subsite_registered_master_failed';
		} else {
			fwrite($sites_list_fh, "<?php\n");
			fwrite($sites_list_fh, $php_line . "\n");
			fclose($sites_list_fh);
		}
	} else {
		$sites_list_fh = fopen($sites_list_path, 'a');
		if (!$sites_list_fh) {
			$reports[] = sprintf('unable to open file %s for append', $sites_list_path);
			$next_state = 'subsite_registered_master_failed';
		} else {
			fwrite($sites_list_fh, $php_line . "\n");
			fclose($sites_list_fh);
		}
	}
	
	$return = array('report' => $reports);
	if ($next_state != 'subsite_registered_master') $return['break'] = TRUE;
	$return['new_state'] = $next_state;
	return $return;
}

function fpfis_register_subsite_rewritemap(&$subsite) {
	/// inscrire le sous-site dans la RewriteMap
	/// add the new subsite to the master's sites.list.php
	$reports = array();
	$next_state = 'subsite_registered_rewritemap';
	
	// compose the line required for Apache to handle incoming requests as expected
	$map_line = sprintf('%s    enabled', $subsite->name());
	
	$rewrite_map_path = $subsite->master()->path('rewritemap');
	$rewrite_map_fh = fopen($rewrite_map_path, 'a');
	if (!$rewrite_map_fh) {
		$reports[] = sprintf('unable to open file %s for append', $rewrite_map_path);
		$next_state = 'subsite_registered_rewritemap_failed';
	} else {
		fwrite($rewrite_map_fh, $map_line . "\n");
		fclose($rewrite_map_fh);
	}
	
	$return = array('report' => $reports);
	if ($next_state != 'subsite_registered_rewritemap') $return['break'] = TRUE;
	$return['new_state'] = $next_state;
	return $return;
}

function fpfis_adjust_subsite_settings(&$subsite) {
	/// Adjuste the settings.php file: insert the $multisite_subsite variable
	/// along with include statements for settings.common* files.
	$settings_path = $subsite->master()->path('sites') . '/' . $subsite->name() . '/settings.php';
	
	$reports = array();
	$next_state = 'subsite_settings_adjusted';
	chmod($settings_path, 0660);
	$settings_fh = fopen($settings_path, 'r+');
	if (!$settings_fh) {
		$reports[] = sprintf('unable to open file %s', $settings_path);
		$next_state = 'subsite_settings_adjusted_failed';
	} else {
		$first_line = fgets($settings_fh); // skip first line
		$configuration = stream_get_contents($settings_fh); // read the rest of the file
		fseek($settings_fh, strlen($first_line));
		fprintf($settings_fh, '$multisite_subsite = \'%s\';' . "\n", $subsite->name());
		fprintf($settings_fh, 'include(dirname(__FILE__) . \'/../settings.common.php\');' . "\n");
		fwrite($settings_fh, $configuration);
		fprintf($settings_fh, 'include(dirname(__FILE__) . \'/../settings.common.post.php\');' . "\n");
		fclose($settings_fh);
	}
	
	$return = array('report' => $reports);
	if ($next_state != 'subsite_settings_adjusted') $return['break'] = TRUE;
	$return['new_state'] = $next_state;
	return $return;
}

function fpfis_configure_apachesolr(&$subsite) {
	$solr_server_url = $subsite->solrInstance()->url();
	$solr_server_name = $subsite->solrInstance()->name();
	
	$reports = array();
	$commands = array(
		sprintf('solr-set-env-url "%s"', $solr_server_url),
		sprintf('sql-query "%s"', "UPDATE apachesolr_environment SET name = '${solr_server_name}' WHERE env_id = 'solr';"),
		sprintf('sql-query "%s"', "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','page'), ('solr','node','article');"),
	);
	foreach ($commands as $command) {
		$execution = drush_subsite($subsite, $command);
		foreach ($execution['reports'] as $report) $reports[] = $report;
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'apachesolr_configure_failed' : 'apachesolr_configured';
	return $return;
}

function fpfis_enable_varnish(&$subsite) {
	$execution = drush_subsite($subsite, 'en varnish');
	$return = array('report' => $execution['reports']);
	if (count($execution['reports'])) $return['break'] = TRUE;
	$return['new_state'] = count($execution['reports']) ? 'varnish_enable_failed' : 'varnish_enabled';
	return $return;
}

function fpfis_clear_subsite_caches(&$subsite) {
	$install_profile = FPFISPolicyConfig::get('default_install_profile', 'multisite_drupal_standard');
	
	$reports = array();
	$commands = array(
		'cc all',
		"php-eval 'node_access_rebuild();'",
		sprintf('scr "%s/../profiles/%s/inject_data.php"', $subsite->master()->path('sites'), $install_profile),
		'solr-index'
	);
	foreach ($commands as $command) {
		$execution = drush_subsite($subsite, $command);
		foreach ($execution['reports'] as $report) $reports[] = $report;
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'caches_clear_failed' : 'caches_cleared';
	return $return;
}

function fpfis_push_files_to_web_servers(&$subsite) {
	$reports = array();
	
	// paths to be synced
	$sync_path = array(
		$subsite->master()->path('sites') . '/sites.list.php',
		$subsite->master()->path('sites') . '/' . $subsite->name(),
		$subsite->master()->path('rewritemap')
	);
	
	foreach ($sync_path as $path) {
		$sync_command = $subsite->master()->cluster()->syncCommand($path);
		if (!strlen(trim($sync_command))) continue;
		$sync = execute_command($sync_command);
		if ($sync['code'] !== 0) {
			$reports[] = sprintf('The following sync command exited with status code %d: %s', $sync['code'], $sync_command);
		}
	}
	
	$return = array('report' => $reports);
	if (count($reports)) $return['break'] = TRUE;
	$return['new_state'] = count($reports) ? 'files_push_failed' : 'files_pushed';
	return $return;
}

function fpfis_finalize_subsite_installation(&$subsite) {
	// send mail to client ? test something?
	return(array('new_state' => constant('STATE_DONE')));
}
