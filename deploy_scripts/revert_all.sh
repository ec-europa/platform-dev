#!/bin/bash
# set -x
current_script="$(readlink -f $0)"
script_dir="$(dirname "${current_script}")"

source "${HOME}/.bash_profile"
source "${script_dir}/lib/functions.sh"

function usage {
	output "Usage: $0 <drupal-directory> <target>"
	output '    drupal-directory is a Drupal base directory, i.e. a directory hosting the index.php file'
	output '    target is either a list of 1 to n subsites, or "@sites" for all known subsites'
}

# Simple arguments check
drupal_path=$1
shift
target=$@
[ -z "${drupal_path}" ] && usage && exit 50
[ -z "${target}" ] && usage && exit 48

function do_action {
	get_shared_features "multisite_settings_core cce_basic_config" | while read feature; do
		run_drush features-revert --force --yes "${feature}"
	done
}

loop_on_target_subsites "${drupal_path}" ${target} | timestamped_output
exit 0
