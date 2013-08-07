#!/bin/bash
if [ "$#" -lt 1 ];
then
  echo "usage: $0 <site name>"
  exit 42
fi

source config.sh

function __echo {	
	if [ "${verbose}" = 1 ] ; then
		echo $@
	fi
}

site_name=$BASH_ARGV
if [ -z "${site_name}" ];
then
  echo "WARNING: no site name was given !!"
  exit 42
fi



db_url="mysqli://${db_user}:${db_pass}@${db_host}:${db_port}/${site_name}"
__echo "Set DB URL to ${db_url}"

#install and configure the drupal instance
cd "${webroot}/${site_name}"
install_profile=`drush sqlq --extra="-N" "select name from system where status = 1 and filename like '%.profile'"`
chmod u+w -R sites/default
rm sites/default/settings.php

drush --php="/usr/bin/php" --yes si $install_profile --db-url=$db_url --account-name=$account_name --account-pass=$account_pass --site-name=${site_name} --site-mail=$site_mail  1>&2

#solR config
drush solr-set-env-url $solr_server_url
drush sqlq "UPDATE apachesolr_environment SET name = '${solr_server_name}' WHERE env_id = 'solr'"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','page')"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','article')"

#flush cache and rebuild access
drush cc all
drush php-eval 'node_access_rebuild();'
#inject data
drush vset tmp_base_url "${subdirectory}/${site_name}"
drush scr "profiles/${install_profile}/inject_data.php"
drush vdel --exact --yes tmp_base_url

#set solr tika variables
drush vset apachesolr_attachments_tika_jar "${apachesolr_attachments_tika_jar}"
drush vset apachesolr_attachments_tika_path "${apachesolr_attachments_tika_path}"
drush vset apachesolr_attachments_java "${apachesolr_attachments_java}"

#set FPFIS_common libraires path
#drush php-eval "define('FPFIS_COMMON_LIBRARIES_PATH',${FPFIS_common_libraries});"


#remove links from the linkchecker scanning process
drush sqlq "delete FROM linkchecker_link"
drush sqlq "delete FROM linkchecker_node"

#solr indexation
drush solr-index

#run cron
drush cron
