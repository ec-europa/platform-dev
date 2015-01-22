#!/bin/bash

# function.sh file
# used by "install.sh" script


function __echo {
	if [ -z "$2" ]; then 
		type='notice'
	else
		type=$2
	fi

	if [ "${verbose}" = 1 ] ||  [ "$type" != "notice" ]  ; then	
		MSG="$1"
		colmax=$(tput cols) 
		#colmax=`expr $colmax `
		colmax="$((colmax)) - 5"
		NORMAL=$(tput sgr0)
		case "$type" in
			'error')
			COLOR=$(tput setaf 1)
				STATUS="[error]"
			;;
			'status') 
				COLOR=$(tput setaf 2)
				STATUS="[ok]"
			;;
			'warning') 
				COLOR=$(tput setaf 3)
				STATUS="[warning]"
			;;
			'notice')
				STATUS="[notice]"
				COLOR=$(tput sgr0)

			;;
		esac 
		STATUSCOLOR="$COLOR${STATUS}$NORMAL"
        MSG_LENGTH=$(echo $MSG | sed "s/\\\e\[[014]\?;\?[0-9]*m//g")
		let COL="${colmax}-${#MSG_LENGTH}+${#STATUSCOLOR}-${#STATUS}"
		echo -en "$MSG"
		printf "%${COL}s\n"  "$STATUSCOLOR"
	fi
}

function _continue {
	if [ "${force}" = 1 ] ; then
		__echo "${Yellow}Force continu...${Color_Off}" 'warning'
	else
		read -p  "Do you want to continue? [y/n]" goon 
		if [[ $goon = 'n' ]];
		then
			exit 42
		else 
			if [[ $goon != 'y' ]];then
			_continue
			fi
		fi	
	fi
}

function _exit_with_message {
	rc=$1
	shift
	__echo "$@" 'error'
	exit "$rc"
}

function _apply_patches {
	patch_folder=$1
	
	if [ ! -e "$patch_folder" ]; then 
		__echo "${Yellow}Patch folder not found on ${IRed}$patch_folder${Color_Off}" 'warning'
		_continue
	else
		# define patch options
		if [ "${force}" = 1 ] ; then
			patch_options="-f"
		fi
		# apply all patch from ${patch_folder}
		for patch_file in "${patch_folder}/"*.patch "${patch_folder}/"*.diff; do
			test -f "${patch_file}" || continue
			__echo "Attempting to apply ${Cyan}$(basename ${patch_file})${Color_Off}"
			patch $patch_options -p0 -b -i "${patch_file}" 1>&2
			__echo "Done"
		done
	fi
}

# retrieve files from SVN
# use $svn_path, $svn_basepath, $svn_tag_version
function _get_svn_sources {
		__echo "Getting sources from svn at ${Cyan}${svn_path}${Color_Off}"
		# get credentials
		if [ -z "${svn_username}" ]; then 
			echo -n "SVN username:" 
			read svn_username
		fi
		if [ -z "${svn_password}" ]; then 
			echo -n "SVN password:" 
			read -s svn_password
		fi
		
		__echo "Test SVN path ${Cyan}${svn_path}${Color_Off}"
		# Test SVN path
		svn info --non-interactive --username="${svn_username}" --password="${svn_password}" "${svn_path}"
		error=$?
		if [ $error -ne 0 ]; then
			__echo "${Yellow}Repository ${IRed}${svn_path}${Yellow} could not be found${Color_Off}" 'warning'
			_continue
		fi
		
		# SVN files export 
		__echo "Export source code from SVN"
		for file in ${svn_files[*]}; do
			__echo "Export ${Cyan}${file}${Whyte} from SVN${Color_Off}"
			svn export --non-interactive --force --username="${svn_username}" --password="${svn_password}" "${svn_path}/${file}" "${own_source_path}/${file}"
		done 
}


function __fix_perms {
	[ -e "$1" ] && chmod ug+w,o-w "$1"
}
	
# retrieve files from drupal.org
# use $drush_options, $working_dir
function _get_make_sources {
	makefile_path=$1

	# Run drush make
	drush ${drush_options} make --force-complete "${makefile_path}" "${working_dir}" 1>&2
	
	# error ?
	error=$?
	if [ $error -ne 0 ]; then
		__echo "Drush make ${IRed}${makefile_path}${White}exited with error${Color_Off}" "error"
		_continue
	fi
	
	# move to ${working_dir} and cleanup
	__echo "Drush make ${Cyan}${makefile_path}${White} done${Color_Off}" "status"
}

function _create_database {
	mysql -h "${db_host}" -P "${db_port}" -u "$db_user" --password="$db_pass" -e  "USE ${db_name};" 2> /tmp/error.logextract
	if grep -q "ERROR 1049 (42000) at line 1: Unknown database '${db_name}'" /tmp/error.logextract ; then
		mysql -h "${db_host}" -P "${db_port}" -u "$db_user" --password="$db_pass" -e "create database ${db_name};" 1>&2
		__echo "Database ${Cyan}${db_name}${White} created${Color_Off}" 'status'
	else 
		__echo "${Yellow}Database ${IRed}${db_name}${Yellow} already existing, it will be dropped...${Color_Off}" 'warning'
		_continue 
		mysql -h "${db_host}" -P "${db_port}" -u "$db_user" --password="$db_pass" -e "drop database ${db_name};" 2>/dev/null
		mysql -h "${db_host}" -P "${db_port}" -u "$db_user" --password="$db_pass" -e "create database ${db_name};" 2>/dev/null
		__echo "Database ${Cyan}${db_name}${White} recreated${Color_Off}" 'status'
	fi
	rm -f "/tmp/error.logextract"
}

# set solr settings
function _setsolrconf {
	drush solr-set-env-url  "$solr_server_url"
	drush sqlq "UPDATE apachesolr_environment SET name = '${solr_server_name}' WHERE env_id = 'solr'"
	#set solr tika variables
	drush vset apachesolr_attachments_tika_jar "${apachesolr_attachments_tika_jar}"
	drush vset apachesolr_attachments_tika_path "${apachesolr_attachments_tika_path}"
	drush vset apachesolr_attachments_java "${apachesolr_attachments_java}"
}

function _setlinkcheckerconf {
	__echo "Cleanup linkchecher links..."
	drush sqlq "delete FROM linkchecker_link"
	drush sqlq "delete FROM linkchecker_node"
}

function _inject_data {
	__echo "Insert data..."
	__echo "Set ${UWhite}tmp_base_url${White} to ${Cyan}${base_path}/${site_name}${Color_Off}"
	drush vset tmp_base_url "/${base_path}/${site_name}"
	drush scr "$1" 
	drush vdel --exact --yes tmp_base_url
}

function _node_access_rebuild {
	__echo "Run flush cache all..."
	drush ${drush_options} cc all
	__echo "Run node_access_rebuild()...."
	drush ${drush_options} php-eval 'node_access_rebuild();'
}
