#!/bin/bash

source config.sh

mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "drop database $2;" 1>&2
mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "create database $2;" 1>&2

mkdir $webroot/$1/sites/$baseurl.$1.$2
cd $webroot/$1
ln -s . $2
cp sites/default/default.settings.php sites/$baseurl.$1.$2/settings.php
mkdir $webroot/$1/sites/$baseurl.$1.$2/files
chmod 777 sites/$baseurl.$1.$2/settings.php
chmod 777 sites/$baseurl.$1.$2/files

cd $webroot/$1/sites/$baseurl.$1.$2

master_site_name=$1
site_name=$2
db_url="mysqli://${db_user}:${db_pass}@${db_host}:${db_port}/${site_name}"

#drush si subsite_standard --uri=http://$baseurl/$1/$2  --db-url=$db_url/$2 --account-name=$account_name --account-pass=$account_pass --site-name=$2 --site-mail=$site_mail
#drush si --uri=http://$baseurl/$1/$2 --db-url=$db_url --account-name=$account_name --account-pass=$account_pass --site-name=$2 --site-mail=$site_mail
#drush si --db-url=$db_url --account-name=$account_name --account-pass=$account_pass --site-name=$2 --site-mail=$site_mail
drush si multisite_drupal_standard -y --sites-subdir=$baseurl.$1.$2 --db-url=$db_url --account-name=$account_name --account-pass=$account_pass --site-name=$2 --site-mail=$site_mail 1>&2

#solR config
drush solr-set-env-url $solr_server_url
drush sqlq "UPDATE apachesolr_environment SET name = '${solr_server_name}' WHERE env_id = 'solr'"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','page')"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','article')"

#flush cache and rebuild access
drush cc all
drush php-eval 'node_access_rebuild();'
#inject data
drush scr "${webroot}/${master_site_name}/profiles/${install_profile}/inject_data.php"
#solr indexation
drush solr-index