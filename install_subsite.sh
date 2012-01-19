#!/bin/bash

source config.sh

mysql -u root -p -e "drop database $2;"
mysql -u root -p -e "create database $2;"

mkdir $webroot/$1/sites/$baseurl.$1.$2
cd $webroot/$1
ln -s . $2
cp sites/default/default.settings.php sites/$baseurl.$1.$2/settings.php
chmod 777 sites/$2/settings.php
chmod 777 sites/$2/files

#drush si subsite_standard --uri=http://$baseurl/$1/$2  --db-url=$db_url/$2 --account-name=$account_name --account-pass=$account_pass --site-name=$2 --site-mail=$site_mail
drush si subsite_communities --sites-subdir=$baseurl.$1.$2 --db-url=$db_url/$2 --account-name=$account_name --account-pass=$account_pass --site-name=$2 --site-mail=$site_mail