#!/bin/bash

#----------------#
#    INCLUDES    #
#----------------#

script_dir=$(readlink -f "$(dirname "$O")")

if [ ! -f "${script_dir}/config.sh" ]; then
	echo "No config file found at ${script_dir}/config.sh"
	exit 255
else
	if [ -f "${script_dir}/config.$(hostname --short).sh" ]; then
		source "${script_dir}/config.$(hostname --short).sh"
	else
		source "${script_dir}/config.sh"
	fi
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
Syntax : $(basename "$0") [ARGS] SITE-NAME\n
\t-?,-h, --help\t\tPrint this message\n
\t-i, \tDefine the installation profile to use\n
\t-s, \tDefine the subfolder name for a new site instance\n
\t-k, --devel\tInclude devel build make\n
\t-v, --verbose\t\tSet the script in verbose mode\n
\t-f, \t\tForce the installation without any request to user input\n
\t\t\t\t(Take care, it might delete automatically your database)\n
\t-d, \t\t\tDefine drush options\n
\t-b, \t\tDefine svn basepath options\n
\t-t, \t\tDefine svn tag version options\n
"

# Configuration of the script
while getopts "i:b:t:d:s:vcrfhk?-:" option; do
        #Management of the --options
        if [ "$option" = "-" ]; then
                case $OPTARG in
                        help) option=h ;;
						drush_options)=d ;;
                        verbose) option=v ;;
						force) force=f ;;
						install_profile) option=i ;;
						devel) option=k ;;
						svn_basepath) option=b ;;
						svn_tag_version) option=t ;;
						subdirectory) option=s ;;
            color)option=c;;
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
				k) devel=1 ;;
				i) install_profile=$OPTARG ;;
				b) svn_basepath=$OPTARG ;;
				t) svn_tag_version=$OPTARG ;;
				s) subdirectory=$OPTARG ;;
        c) color=0 ;;
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

if [ -f "${script_dir}/colors.sh" ] && [ "$color" != 0 ]; then
	source "${script_dir}/colors.sh"
fi
#------------------------#
#     ARGUMENTS CHECK    #
#------------------------#

# Site name
site_name=$BASH_ARGV
if [ -z "${site_name}" ]; then
	_exit_with_message 230 "No site name was given !!"
fi

# Profile name 
if [ "${install_profile}" != 'multisite_drupal_communities' ] && [ "${install_profile}" != 'multisite_drupal_standard' ]; then 
	_exit_with_message 220 "Profile name ${IRed}${install_profile} ${White}is incorrect${Color_Off}" 
fi

# Get current configuration
current_dir=$(pwd)
__echo "Set ${UWhite}current directory${White} to ${Cyan}${current_dir}${Color_Off}"

# set working directory, now we work under tmp directory on current_dir
working_dir="${current_dir}/tmp/${site_name}"
__echo "Set ${UWhite}working directory${White} to ${Cyan}${working_dir}${Color_Off}"

# create tmp directory if not exist
if [ ! -e "${current_dir}/tmp" ] ; then
	mkdir "${current_dir}/tmp" || _exit_with_message 190 "${Yellow}Unable to create tmp_directory ${IRed}${current_dir}/tmp${Color_Off}"
	__fix_perms -R "${current_dir}/tmp"
fi

# Set up the drush option
if [ "${force}" = 1 ] ; then
	drush_options="${drush_options} -y"
fi
__echo "Set ${UWhite}drush${White} options ${Cyan}${drush_options}${Color_Off}"

# set DB connection
db_name="$site_name"
__echo "Set ${UWhite}DB URL${White} to ${Cyan}mysqli://${db_user}:DB_PASS@${db_host}:${db_port}/${db_name}${Color_Off}"
db_url="mysqli://${db_user}:${db_pass}@${db_host}:${db_port}/${db_name}"

# create database if not exist
_create_database

# Set up target directory 
if [ -n "${subdirectory}" ]; then 
	if [ ! -e "${webroot}/${subdirectory}" ] ; then
		mkdir "${webroot}/${subdirectory}" || _exit_with_message 190 "${Yellow}Unable to create subdirectory ${IRed}${webroot}/${subdirectory}${Color_Off}"
	fi
	base_path="${base_path}/${subdirectory}"
	webroot="${webroot}/${subdirectory}"
fi

# cleanup target directory
if [ -d "${webroot}/${site_name}" ] ; then
	__echo "${Yellow}The target directory ${IRed}${webroot}/${site_name}${Yellow} already exist, it will be deleted.${Color_Off}" 'warning'
	_continue
        chmod 744 -R "${webroot}/${site_name}"
	rm -Rf "${webroot}/${site_name}"  
	__echo "Removing the folder ${Cyan}$webroot/${site_name} done.${Color_Off}" 'status'
fi

# cleanup existing working directory
if [ -d "${working_dir}" ] ; then
	__echo "Removing existing working directory..."
	__fix_perms -R "${working_dir}"
	rm -Rf "${working_dir}"
	__echo "Done." 'status'
fi

# cleanup tmp directory
if [ -d "${working_dir}_sources_tmp" ] ; then
  rm -Rf "${working_dir}_sources_tmp"
  __echo "Temp directory cleared." 'status'
fi

#svn conf
if [ "$svn_basepath" = "trunk" ] || [ "$svn_basepath" = "tags" ] || [ "$svn_basepath" = "branches" ]; then
	svn=1
fi

#----------------------#
#     BUILD SOURCES    #
#----------------------#

# get own source from svn ?
if [ "${svn}" = 1 ] ; then 
	# files to retrieve from SVN (we don't recover all files, eg custom subsite is useless)
	svn_files=(
		"profiles"
		"sites/all"
		"sites/default"
		"patches"
	)
	# build svn_path
	if [ "$svn_basepath" = "trunk" ] ; then
		svn_path="${svn_url}/${svn_basepath}"
	else
		svn_path="${svn_url}/${svn_basepath}/${svn_tag_version}/source"
	fi
	__echo "Set ${UWhite}SVN repository${White} path to ${Cyan}${svn_path}${Color_Off}"
	own_source_path="${working_dir}_sources_tmp"
	__echo "Set ${UWhite}own_source_path${White} path to ${Cyan}${own_source_path}${Color_Off}"
	_get_svn_sources 
else
	own_source_path="${current_dir}"
  __echo "Set ${UWhite}own_source_path${White} path to ${Cyan}${own_source_path}${Color_Off}"
fi

# Get Drupal core and contributed sources using makefile
_get_make_sources "${own_source_path}/profiles/${install_profile}/build.make"

#  makefile for devel modules
if [ "${devel}" = 1 ] ; then
	_get_make_sources "${own_source_path}/profiles/devel.make"
fi

# copy own source (svn or local) to working dir
cp -R "${own_source_path}/profiles/multisite_drupal_core" "${working_dir}/profiles"
cp -R "${own_source_path}/profiles/${install_profile}" "${working_dir}/profiles"
cp -R "${own_source_path}/sites/all/modules/" "${working_dir}/sites/all"
cp -R "${own_source_path}/sites/all/themes" "${working_dir}/sites/all"
cp -R "${own_source_path}/sites/all/libraries" "${working_dir}/sites/all"
cp -R "${own_source_path}/sites/default/files/" "${working_dir}/sites/default/files/"
cp "${own_source_path}/sites/default/proxy.settings.php" "${working_dir}/sites/default/"	

# move under working directory to install site
cd "${working_dir}"

#-----------------------#
#     APPLY PATCHES     #
#-----------------------#

# we assume the script is in the patches directory
#patch_dir=$(readlink -f patches)
patch_dir="${own_source_path}/patches"

patch_dir_core="${patch_dir}/multisite_drupal_core"
#__echo "$patch_dir_core" 'error'
# BACKPORT version <=1.6 : if $patch_dir_core not found we apply patches directly from $patch_dir folder
if [ ! -e "$patch_dir_core" ]; then 
	__echo "Applying core patches from ${Cyan}$patch_dir${White} to ${Cyan}${site_name}${Color_Off}"
	_apply_patches "$patch_dir"
else
	# core patchs patch
	__echo "Applying core patches from ${Cyan}${patch_dir_core}${White} to ${Cyan}${site_name}${Color_Off}"
	_apply_patches "$patch_dir_core"
	
	# profile patchs
	patch_dir_profile="${patch_dir}/${install_profile}"
	if [ ! -e "$patch_dir_profile" ]; then 
		__echo "Applying profil patches from ${Cyan}${patch_dir_profile}${White} to ${Cyan}${site_name}${Color_Off}"
		_apply_patches "$patch_dir_profile"
	fi
fi

if [ "${htaccess_rewrite_base}" = 1 ] ; then
	sed -i "s@# RewriteBase /drupal@RewriteBase /fpfis/multisite/${subdirectory}/${site_name}@" .htaccess
fi


#-----------------#
#     INSTALL     #
#-----------------#
# install and configure the drupal instance
drush ${drush_options}  si "$install_profile" --db-url="$db_url" --account-name="$account_name" --account-pass="$account_pass" --site-name="${site_name}" --site-mail="$site_mail"  1>&2

#----------------#
#     CONFIG     #
#----------------#

# set solR config
_setsolrconf

#inject data

_inject_data "${own_source_path}/profiles/${install_profile}/inject_data.php"

#set alias for CodeSniffer
alias codercs='phpcs --standard=sites/all/modules/contributed/coder/coder_sniffer/Drupal/ruleset.xml --extensions=php,module,inc,install,test,profile,theme'

#flush cache and rebuild access
_node_access_rebuild 

#solr indexation
__echo "Run solr indexation.."
drush ${drush_options} solr-index

#run cron
__echo "Run drupal cron..."
drush cron

#remove links from the linkchecker
_setlinkcheckerconf

mkdir "${working_dir}/sites/default/files/private_files"

# cleanup && move to target directory
if [ "${svn}" = 1 ] ; then 
	rm -Rf "${own_source_path}"
fi
mv "${working_dir}" "${webroot}"
__fix_perms "${webroot}"

__echo "\nSite installed on ${IBlue}${webroot}/${site_name}${Color_Off}" 'status'




