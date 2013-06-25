#!/bin/bash
# set -x
current_script="$(readlink -f $0)"
script_dir="$(dirname "${current_script}")"

source "${HOME}/.bash_profile"
source "${script_dir}/lib/functions.sh"

function usage {
	output "Usage: $0 change-role|restore-role <drupal-directory> <target>"
	output '    drupal-directory is a Drupal base directory, i.e. a directory hosting the index.php file'
	output '    target is either a list of 1 to n subsites, or "@sites" for all known subsites'
}

# Simple arguments check
action=$1
shift
drupal_path=$1
shift
target=$@
[ -z "${drupal_path}" ] && usage && exit 50
[ -z "${target}" ] && usage && exit 48
[ "${action}" != "change-role" -a "${action}" != "restore-role" ] && usage && exit 46

function do_action {
	# we suppose the SQL queries are going to fail
	subsite_state="nok"

	# change role
	if [ "${action}" == 'change-role' ]; then
		# revoke administrator permissions
    drush scr "${script_dir}/lib/deploy_change_permissions.php" --action='revoke' || return
		echo 'Roles changed'
	fi

	# restore role
	if [ "${action}" == 'restore-role' ]; then
    # restore administrator permissions
    drush scr "${script_dir}/lib/deploy_change_permissions.php" --action='grant' || return
		echo 'Roles restored'
	fi

	# if everything went well, set subsite_state to ok so the default
	# implementation of end_subsite takes it into account
	subsite_state="ok"
}

loop_on_target_subsites "${drupal_path}" ${target} | timestamped_output
exit 0
