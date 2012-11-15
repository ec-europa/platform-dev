#!/bin/bash
# set -x
current_script="$(readlink -f $0)"
script_dir="$(dirname "${current_script}")"

source "${HOME}/.bash_profile"
source "${script_dir}/lib/functions.sh"

function usage {
	output "Usage: $0 <drupal-directory> <reporting-directory> <target>"
	output '    drupal-directory is a Drupal base directory, i.e. a directory hosting the index.php file'
	output '    reporting-directory is the directory where reports shall be generated'
	output '    target is either a list of 1 to n subsites, or "@sites" for all known subsites'
}

# Simple arguments check
drupal_path=$1
shift
report_directory=$1
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

	report_file="${report_directory}/delivery_reporting_${subsite}_$(date '+%Y%m%d').txt"
	touch "${report_file}"
	if [ $? -ne 0 ]; then
		echo "Error: cannot write to the report file ${report_file}."
		subsite_status="nok"
		return
	fi

	# Report header
	(
		echo "# DRUPAL DELIVERY REPORT"
		echo "# This report was generated on $(date '+%Y-%m-%d') at $(date '+%H:%M:%S')"
		echo "# for the Drupal multisite instance under "
		echo "# ${drupal_path}"
		echo "# more specifically for the subsite named \"${subsite}\"".
		echo ""
	) > "${report_file}"

	# features-diff any feature that needs review
	grep_features 'Needs review' | while read feature; do
		(
			echo "The \"${feature}\" feature needs review."
			echo "Running drush features-diff for feature \"${feature}\"..."
		) | tee -a "${report_file}"
		run_drush features-diff "${feature}" | report_output >> "${report_file}"
		rc=$?
		if [ $rc -ne 0 ]; then
			echo "Error: drush features-diff ${feature} returned non-zero (${rc})"
			subsite_status="nok"
		fi
		echo ""
	done
}

loop_on_target_subsites "${drupal_path}" ${target} | timestamped_output
exit 0
