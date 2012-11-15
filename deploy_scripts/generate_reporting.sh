#!/bin/bash
# set -x
current_script="$(readlink -f $0)"
script_dir="$(dirname "${current_script}")"

source "${HOME}/.bash_profile"
source "${script_dir}/lib/functions.sh"

function usage {
	output "Usage: $0 <reporting-directory> <drupal-directory> <target>"
	output '    reporting-directory is the directory where reports shall be generated'
	output '    drupal-directory is a Drupal base directory, i.e. a directory hosting the index.php file'
	output '    target is either a list of 1 to n subsites, or "@sites" for all known subsites'
}

# Simple arguments check
report_directory=$1
shift
drupal_path=$1
shift
target=$@
[ -z "${drupal_path}" ] && usage && exit 50
[ -z "${target}" ] && usage && exit 48
[ -z "${report_directory}" ] && usage && exit 46

# Check the provided report directory
if [ ! -d "$report_directory" ]; then
	exitWithErrorMessage 44 "The provided report directory ($report_directory) does not appear to exist."
fi
# Ensure this path is absolute so we can chdir without this path to lose its sense
report_directory=$(readlink -f "${report_directory}")

function do_action {
	drupal_path=$1
	subsite=$2

	report_file="${report_directory}/reporting_${subsite}_$(date '+%Y%m%d').txt"
	touch "${report_file}"
	if [ $? -ne 0 ]; then
		echo "Error: cannot write to the report file ${report_file}."
		subsite_status="nok"
		return
	fi

	# Status Report header
	(
		echo "# DRUPAL STATUS REPORT"
		echo "# This report was generated on $(date '+%Y-%m-%d') at $(date '+%H:%M:%S')"
		echo "# for the Drupal multisite instance under "
		echo "# ${drupal_path}"
		echo "# more specifically for the subsite named \"${subsite}\"."
		echo ""
	) > "${report_file}"

	(
		run_drush features-components node
		run_drush field-info types
		run_drush field-info fields
		run_drush features-list
		run_drush pm-list
		run_drush views-list
		run_drush features-components views_view
		run_drush features-components taxonomy
		run_drush sql-query 'SELECT tid, vid, name FROM taxonomy_term_data;'
		run_drush features-components variable
		run_drush features-components context
		run_drush features-components user_role
		run_drush features-components user_permission
		run_drush sql-query 'SELECT * FROM custom_breadcrumb;'
		run_drush features-components menu_links
	) | report_output >> "${report_file}"

	report_diff_file="${report_directory}/reporting_${subsite}_diff_$(date '+%Y%m%d').txt"
	touch "${report_diff_file}"
	if [ $? -ne 0 ]; then
		echo "Error: cannot write to the report file ${report_diff_file}."
		subsite_status="nok"
		return
	fi

	# Diff Report header
	(
		echo "# DRUPAL DIFF REPORT"
		echo "# This report was generated on $(date '+%Y-%m-%d') at $(date '+%H:%M:%S')"
		echo "# for the Drupal multisite instance under "
		echo "# ${drupal_path}"
		echo "# more specifically for the subsite named \"${subsite}\"."
		echo ""
	) > "${report_diff_file}"

	# features-diff any enabled feature
	grep_features 'Enabled' | while read feature; do
		run_drush features-diff "${feature}"
	done | report_output >> "${report_diff_file}"
}

loop_on_target_subsites "${drupal_path}" ${target} | timestamped_output
exit 0
