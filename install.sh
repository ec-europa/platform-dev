#!/bin/bash

source config.sh

drush make profiles/multisite_drupal_core/build.make $1

mysql -u root -p -e "drop database $1;"
mysql -u root -p -e "create database $1;"

chmod -R 777 $1/sites/default
cp -R profiles/multisite_drupal_core $1/profiles
cp -R profiles/subsite_standard $1/profiles
cp -R profiles/subsite_communities $1/profiles
cp -R modules $1/sites/all
cp -R features $1/sites/all/modules
cp -R themes $1/sites/all
cp -R files/ $1/sites/default/files/
cd $1

drush si multisite_drupal_core --db-url=$db_url/$1 --account-name=$account_name --account-pass=$account_pass --site-name=$1 --site-mail=$site_mail

mkdir sites/default/files/private_files
chmod -R 777 sites/default/files

mkdir sites/all/libraries
#cd sites/all/libraries
cd sites/all/modules/contributed/ckeditor
rmdir ckeditor
wget http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.tar.gz
tar xvf ckeditor_3.6.2.tar.gz
rm ckeditor_3.6.2.tar.gz

cd ../../../../../..
mv $1 $webroot

