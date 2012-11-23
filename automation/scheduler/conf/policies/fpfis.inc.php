<?php
/**
	This file provides sensible default values for the FPFIS Multisite
	installation policy. Administrators should not modify this file directly.
	Instead, they should override adequate values in a fpfis.local.inc.php file.
*/

// MySQL user accounts are restricted to client machines (automatically
// determined by the policy) plus some machines you may specify here (for
// management purpose, typically).
FPFISPolicyConfig::set('mysql_default_machines', array('localhost', 'management-machine.local.domain'));

// control the mail sent to require the creation of a database
FPFISPolicyConfig::set('mysql_creation_mail_returnpath', 'multisite-team@organization.com');
FPFISPolicyConfig::set('mysql_creation_mail_from', 'multisite-team@organization.com');
FPFISPolicyConfig::set('mysql_creation_mail_to', 'helpdesk@organization.com');
FPFISPolicyConfig::set('mysql_creation_mail_cc', 'multisite-team@organization.com, john.smith@organization.com, alice@organization.com, bob@organization.com');
FPFISPolicyConfig::set('mysql_creation_mail_subject', 'Multisite: database creation request');
FPFISPolicyConfig::set('mysql_creation_mail_body', '[Ticket to the MySQL team]

Hello,

Could you create the following database and user account on @mysql_instance?
  * username: @mysql_username
  * password: please choose a strong password and provide us with it through https://some-host.local.domain/provide_mysql_password
    * Note: the TLS certificate is not valid (self-signed): this is normal.
  * client machines: @client_machines
  * with all privileges on a new database named @mysql_db_name

Please also grant all privileges on the created database to management-user@management-machine.local.domain. Thanks in advance.

Regards,
The Multisite team');

// control the mail sent when it appears the database was not created after a specific delay
FPFISPolicyConfig::set('mysql_creation_reminder_delay', 86400);
FPFISPolicyConfig::set('mysql_creation_reminder_from', 'multisite-team@organization.com');
FPFISPolicyConfig::set('mysql_creation_reminder_to', 'multisite-team@organization.com');
FPFISPolicyConfig::set('mysql_creation_reminder_subject', 'Multisite: database creation request still pending for %s (reminder #%d)');
FPFISPolicyConfig::set('mysql_creation_reminder_body', 'Hello,

 It appears the database creation request is still pending for the "@subsite_name" subsite.');

// control the drush install phase
FPFISPolicyConfig::set('drush_log_dir', realpath('logs'));
FPFISPolicyConfig::set('default_install_profile', 'multisite_drupal_standard');
FPFISPolicyConfig::set('admin_account_name', 'admin');
FPFISPolicyConfig::set('admin_account_initial_password', 'fill me');
FPFISPolicyConfig::set('site_mail', 'multisite-team@organization.com');
FPFISPolicyConfig::set('private_files_relpath', 'private_files');

// the admin password is changed right after the drush install
FPFISPolicyConfig::set('admin_account_final_password', 'redefine me in fpfis.local.inc.php (seriously!)');

