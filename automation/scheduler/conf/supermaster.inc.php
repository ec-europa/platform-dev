<?php
// should avoid any locales-related complaining
putenv('LANG=C');
date_default_timezone_set('Europe/Luxembourg');
$supermaster_server = 'localhost';
$supermaster_user = 'supermaster';
$supermaster_password = 'fillme';
$supermaster_database = 'multisite_supermaster';
$scheduler_pid_file = realpath(dirname(__FILE__)) . '/../run/scheduler.pid';
$scheduler_long_execution_delay = 3600;
