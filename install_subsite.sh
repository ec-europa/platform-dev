#!/bin/bash

#----------------#
#    INCLUDES    #
#----------------#

script_dir=$(readlink -f $(dirname "$O"))

if [ ! -f "${script_dir}/config.sh" ]; then
	echo "No config file found at ${script_dir}/config.sh"
	exit 255
else
source "${script_dir}/config.sh"
fi
if [ ! -f "${script_dir}/functions.sh" ]; then
	echo  "No functions file found at ${script_dir}/functions.sh"
	exit 255
else
source "${script_dir}/functions.sh"
fi

#---------------------#
#     ARGUMENTS GET   #
#---------------------#

usage="Installation of multisite instance\n
Syntax : $(basename $0) [ARGS] SITE-NAME\n
\t-?,-h, --help\t\tPrint this message\n
\t-p, \tDefine the parent installation name\n
\t-i, \tDefine the installation profile to use the parent site\n
\t-s, \tDefine the subfolder for a new site instance\n
\t-c, \tDefine the custom subsite (projet) name\n
\t-v, --verbose\t\tSet the script in verbose mode\n
\t-f, --force\t\tForce the installation without any request to user input\n
\t\t\t\t(Take care, it might delete automatically your database)\n
\t-d, \t\t\tDefine drush options\n
"

# Configuration of the script
while getopts "i:b:t:d:p:c:vrsfhk?-:" option; do
        #Management of the --options
        if [ "$option" = "-" ]; then
                case $OPTARG in
                        help) option=h ;;
						drush_options)=d ;;
                        verbose) option=v ;;
						force) force=f ;;
						install_profile) option=i ;;
						subdirectory) option=s ;;
						subsite_parent_name) option=p ;;
						subsite_custom_subsite) option=c ;;
                        *)
                                echo "[ERROR] Unknown option --$OPTARG"
                                exit 1
                                ;;
                esac
        fi
        case $option in
				d) drush_options=$OPTARG ;;
                v) verbose=1 ;;
				f) force=1 ;;
				i) install_profile=$OPTARG ;;
				s) subdirectory=$OPTARG ;;
				p) subsite_parent_name=$OPTARG ;;
				c) subsite_custom_subsite=$OPTARG ;;
                \?|h)
                        echo -e $usage
                        exit 0
                        ;;
                :)
                        echo "[ERROR] Missing arguments for -$OPTARG"
                        exit 1
                        ;;
                ?)
                        echo "[ERROR] Unknown option -$option"
                        exit 1
                        ;;
        esac
done

#------------------------#
#     ARGUMENTS CHECK    #
#------------------------#

# site name
subsite_name=$BASH_ARGV
[ -z "${subsite_name}" ] && _exit_with_message 230 "You must provide a subsite."

# parent site name
[ -z "${subsite_parent_name}" ] && _exit_with_message 240 "You must provide the name of the parent_name Drupal instance."

# Set up parent directory
if [ -n "${subdirectory}" ]; then 
	parent_dir="${webroot}/${subdirectory}/${subsite_parent_name}"
	base_path="${base_path}/${subdirectory}/${subsite_parent_name}/${subsite_name}"
else
	parent_dir="${webroot}/${subsite_parent_name}"
	base_path="${base_path}/${subsite_parent_name}/${subsite_name}"
fi

# set DB connection
db_name="${subsite_parent_name}_${subsite_name}"
db_url="mysqli://${db_user}:${db_pass}@${db_host}:${db_port}/${db_name}"
__echo "Set DB URL to mysqli://${db_user}:DB_PASS@${db_host}:${db_port}/${db_name}"
_create_database

# Generate the URL pattern for the provided subsite name
subsite_url_pattern=$(printf "$subsite_cluster_url_pattern" "${subsite_name}")
subsite_dir=$(printf "${subsite_cluster_dir}" "${subsite_name}")

# cleanup target directory
if [ -d "${parent_dir}/sites/${subsite_dir}" ] ; then
	__echo "The folder '${parent_dir}/sites/${subsite_dir}' already exist, it will be deleted" 'warning'
	_continue
	#chmod 744 -R "${parent_dir}/sites/${subsite_dir}"
	rm -Rf "${parent_dir}/sites/${subsite_dir}"
	__echo "Removing the folder '${parent_dir}/sites/${subsite_dir}' done" 'status'
fi

# Set up the drush option
if [ "${force}" = 1 ] ; then
	drush_options="${drush_options} -y"
fi
__echo "Set drush options: ${drush_options}"

__echo "chdir to ${parent_dir}/sites/"


cd "${parent_dir}/sites" || _exit_with_message 145 "Unable to chdir into ${parent_dir}/sites"
# /!\ now working in the "sites" subdirectory of the master site directory


#--------------------------#
#   BUILD SUBSITE SOURCES  #
#--------------------------#

# create subsite directory
__echo "creating directory ${subsite_dir}"
mkdir -p ${subsite_dir} || _exit_with_message 140 "Unable to create ${subsite_dir} in $(pwd)"

# generating settings.php 
__echo "generating ${subsite_dir}/settings.php from default.settings.php"
cp "default/default.settings.php" "${subsite_dir}/settings.php" || _exit_with_message 130 "Unable to create ${subsite_dir}/settings.php"
__fix_perms "${subsite_dir}/settings.php"

# setup files directory 
__echo "creating 'files' subdirectory for ${subsite_name}"
local_subsite_files_directory="${subsite_dir}/files"
__fix_perms "${local_subsite_files_directory}"
mkdir -p "${local_subsite_files_directory}" || _exit_with_message 120 "Unable to create ${local_subsite_files_directory} in $(pwd)"
mkdir -p "${local_subsite_files_directory}/private_files" || _exit_with_message 118 "Unable to create ${local_subsite_files_directory}/private_files in $(pwd)"
__fix_perms ${local_subsite_files_directory}
# get default file from parent site
__echo "Filling 'files' subdirectory with default images"
cp -a "default/files/default_images" "${subsite_dir}/files/"

# fill list of subsite on site.php 
if [  "$subsite_update_drupal_sites_list" == "yes" ]; then
	# we must provide Drupal with the "URL pattern to conf directory" mapping
	
	if [ "$subsite_drupal_sites_list" != "sites.php" ]; then
		# we will not provide this information into the standard sites.php
		# therefore, we may want to provide our own sites.php file
		if [ -f "${script_dir}/sites.php" ]; then
			__echo "Overwriting sites.php"
			cp "${script_dir}/sites.php" "sites.php"
		fi
	fi
	sites_php=${subsite_drupal_sites_list:-sites.php}
	__echo "Filling ${sites_php}"
	[ ! -f "${sites_php}" ] && echo '<?php' > "${sites_php}"
	printf "\$sites['%s'] = '%s';\n" "$subsite_url_pattern" "${subsite_dir}" >> "${sites_php}"
fi

__echo "creating ${subsite_name} subsite itself"
cd ..
if [ ! -s "${subsite_name}" ]; then
	ln -s . "${subsite_name}"
fi


# get custom subsite from SVN
if [ -n "${subsite_custom_subsite}" ]; then 
	svn_files=(
		"modules"
		"libraries"
		"themes"
		"files"
	)
	svn_path="${svn_url}/trunk/custom_subsites/${subsite_custom_subsite}"
	__echo "SVN repository path set to ${svn_path}"
	own_source_path="./${subsite_dir}"
	__echo "own_source_path path set to ${own_source_path}"
	_get_svn_sources
fi

#----------------------#
#   INSTALL SUBSITE    #
#----------------------#

# /!\ now working in the master site directory
drush si $install_profile --sites-subdir="${subsite_dir}" --db-url="${db_url}" --account-name="$account_name" --account-pass="$account_pass" --site-name="$subsite_name" --site-mail="$site_mail"

# echo "completing settings.php"
__fix_perms "sites/${subsite_dir}"
__fix_perms "sites/${subsite_dir}/settings.php"
# perl one-liner printing its entire stdin at the second line of the parsed file
#perl -i -ple 'BEGIN{ @l = <STDIN>; } print @l if ($. == 2)' "sites/${subsite_dir}/settings.php" <<EOF
#\$multisite_subsite = '${subsite_name}';
#include(dirname(__FILE__) . '/../settings.common.php');
#EOF

#-------------------#
#   CONFIG SUBSITE  #
#-------------------#

cd "sites/${subsite_dir}"

#solR config
_setsolrconf

#inject data
_inject_data "${parent_dir}/profiles/${install_profile}/inject_data.php"

#solr indexation
__echo "Run solr indexation.."
drush ${drush_options} solr-index

#run cron
__echo "Run drupal cron..."
drush ${drush_options} cron

#remove links from the linkchecker
_setlinkcheckerconf

__echo "Subsite '${subsite_name}' has been created. You can access it by using  'http://$parent_url/$subsite_name'