#!/bin/bash
# for debug purposes
set -x
script_dir=$(readlink -f $(dirname "$O"))

function fix_perms {
	[ -e "$1" ] && chmod ug+w,o-w "$1"
}

function exit_with_message {
	rc=$1
	shift
	echo $@
	exit $rc
}

# arguments *cough*parsing*cough*
subsite=$2
parent=$1
[ -z "${parent}" ] && exit_with_message 240 "You must provide the name of the parent Drupal instance"
[ -z "${subsite}" ] && exit_with_message 230 "You must provide a subsite"

if [ ! -f "${script_dir}/config.sh" ]; then
	echo "No config file found at ${script_dir}/config.sh"
	exit 250
fi
export subsite_installation=yes
source "${script_dir}/config.sh"
echo "Will install ${subsite_name} under ${parent} using $subsite_db_url"

mysql -u "${db_admin_user}" -p"${db_admin_pass}" -e "drop database ${subsite_db_name};"
mysql -u "${db_admin_user}" -p"${db_admin_pass}" -e "create database ${subsite_db_name};"

echo "chdir to $webroot/$parent"
cd $webroot/$parent/sites || exit_with_message 145 "Unable to chdir into $webroot/$parent/sites"
# /!\ now working in the "sites" subdirectory of the master site directory

# Generate the URL pattern for the provided subsite name
subsite_url_pattern=$(printf "$cluster_subsite_url_pattern" "${subsite}")
subsite_dir=$(printf "${cluster_subsite_dir}" "${subsite}")

echo "creating directory ${subsite_dir}"
mkdir -p ${subsite_dir} || exit 140 "Unable to create ${subsite_dir} in $(pwd)"

echo "generating ${subsite_dir}/settings.php from default.settings.php"
fix_perms ${subsite_dir}/settings.php
cp default/default.settings.php ${subsite_dir}/settings.php || exit_with_message 130 "Unable to create ${subsite_dir}/settings.php"

echo "creating 'files' subdirectory for ${subsite}"
local_subsite_files_directory="${subsite_dir}/files"
fix_perms ${local_subsite_files_directory}
mkdir -p ${local_subsite_files_directory} || exit_with_message 120 "Unable to create ${local_subsite_files_directory} in $(pwd)"
mkdir -p "${local_subsite_files_directory}/private_files" || exit_with_message 118 "Unable to create ${local_subsite_files_directory}/private_files in $(pwd)"
fix_perms ${local_subsite_files_directory}

echo "Filling 'files' subdirectory with default images"
cp -a "default/files/default_images" "${subsite_dir}/files/"

if [  "$update_drupal_sites_list" == "yes" ]; then
	# we must provide Drupal with the "URL pattern to conf directory" mapping
	
	if [ "$drupal_sites_list" != "sites.php" ]; then
		# we will not provide this information into the standard sites.php
		# therefore, we may want to provide our own sites.php file
		if [ -f "${script_dir}/sites.php" ]; then
			echo "Overwriting sites.php"
			cp "${script_dir}/sites.php" "sites.php"
		fi
	fi
	
	sites_php=${drupal_sites_list:-sites.php}
	echo "Filling ${sites_php}"
	[ ! -f "${sites_php}" ] && echo '<?php' > "${sites_php}"
	printf "\$sites['%s'] = '%s';\n" "$subsite_url_pattern" "${subsite_dir}" >> "${sites_php}"
fi

echo "creating ${subsite} subsite itself"
cd ..
if [ ! -s "${subsite}" ]; then
	ln -s . "${subsite}"
fi
# /!\ now working in the master site directory
drush si multisite_drupal_standard --sites-subdir="${subsite_dir}" --db-url="${subsite_db_url}" --account-name=$account_name --account-pass=$account_pass --site-name=$subsite --site-mail=$site_mail

# echo "completing settings.php"
fix_perms "sites/${subsite_dir}"
fix_perms "sites/${subsite_dir}/settings.php"
# perl one-liner printing its entire stdin at the second line of the parsed file
perl -i -ple 'BEGIN{ @l = <STDIN>; } print @l if ($. == 2)' "sites/${subsite_dir}/settings.php" <<EOF
\$multisite_subsite = '${subsite}';
include(dirname(__FILE__) . '/../settings.common.php');
EOF

#solR config
cd "sites/${subsite_dir}"
drush solr-set-env-url $solr_server_url
drush sqlq "UPDATE apachesolr_environment SET name = '${solr_server_name}' WHERE env_id = 'solr'"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','page')"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','article')"

#flush cache and rebuild access
drush cc all
drush php-eval 'node_access_rebuild();'
#inject data
drush scr "${webroot}/${parent}/profiles/${install_profile}/inject_data.php"
#solr indexation
drush solr-index
