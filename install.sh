#!/bin/bash

source config.sh

current_dir=$(pwd)
__echo "Set current directory to ${current_dir}"
working_dir="${current_dir}/${site_name}"
__echo "Set working directory to ${working_dir}"

#build the drupal instance
drush make profiles/multisite_drupal_core/build.make ${site_name}

mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "drop database ${site_name};"
mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "create database ${site_name};"

chmod -R 777 ${site_name}/sites/default
cp -R profiles/multisite_drupal_core ${site_name}/profiles
cp -R profiles/subsite_standard ${site_name}/profiles
cp -R profiles/subsite_communities ${site_name}/profiles
cp -R modules ${site_name}/sites/all
cp -R features ${site_name}/sites/all/modules
cp -R themes ${site_name}/sites/all
cp -R files/ ${site_name}/sites/default/files/


# we assume the script is in the patches directory
patch_dir=$(readlink -f patches)

# we assume the patch directory is located in patches, i.e. one level below the Drupal root directory
__echo "Applying patches to from ${patch_dir} to ${site_name}..."

cd ${site_name}

if [ $? != 0 ] ; then
	__echo "Unable to change directory to ${site_name}" 
	exit 20
fi


for patch_file in "${patch_dir}/"*.patch "${patch_dir}/"*.diff; do
	test -f "${patch_file}" || continue 
	__echo "Attempting to apply ${patch_file}..."
	__echo `patch -p0 -b -i "${patch_file}"`
done

#install and configure the drupal instance
drush si multisite_drupal_core --db-url=$db_url --account-name=$account_name --account-pass=$account_pass --site-name=${site_name} --site-mail=$site_mail

mkdir "${working_dir}/sites/default/files/private_files"
chmod -R 777 "${working_dir}/sites/default/files"

mkdir "${working_dir}/sites/all/libraries"
#cd sites/all/libraries
cd "${working_dir}/sites/all/modules/contributed/ckeditor"
rm -rf "${working_dir}/sites/all/modules/contributed/ckeditor/ckeditor"
wget -P "${working_dir}/sites/all/modules/contributed/ckeditor/" http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.tar.gz
tar xvzf "${working_dir}/sites/all/modules/contributed/ckeditor/ckeditor_3.6.2.tar.gz"
rm "${working_dir}/sites/all/modules/contributed/ckeditor/ckeditor_3.6.2.tar.gz"

mv "${current_dir}/{site_name}" $webroot
