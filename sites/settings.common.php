 <?php
 $_SERVER['HTTP_HOST'] = 'webgate.ec.europa.eu';
 $_SERVER['SERVER_NAME'] = 'webgate.ec.europa.eu';
 $_SERVER['HTTPS'] = 'on';
 $_SERVER['SERVER_PORT'] = '';
  
 multisite_subsite = trim(@$multisite_subsite);
 if (strlen($multisite_subsite)) {
   $base_url = 'https://webgate.ec.europa.eu/multisite/' . $multisite_subsite;
   ini_set('session.cookie_path', '/multisite/' . $multisite_subsite);
   $conf['site_frontpage'] = 'content/welcome-your-site';
 } else {
   $base_url = 'https://webgate.ec.europa.eu/multisite';
   ini_set('session.cookie_path', '/multisite');
 }
 $conf['apachesolr_attachments_java'] = realpath(dirname(__FILE__) . '/../../../util/java/current/bin/java');
 $conf['cache'] = 1;
 $conf['file_chmod_directory'] = 02775;
 $conf['video_cron'] = FALSE;
