#!/bin/bash
current_script="$(readlink -f $0)"
script_dir="$(dirname "${current_script}")"

source "${HOME}/.bash_profile"
source "${script_dir}/lib/functions.sh"

function usage {
	output "Usage: $0 <backup-directory> <drupal-directory> <target>"
	output '    reporting-directory is the directory where reports shall be generated'
	output '    drupal-directory is a Drupal base directory, i.e. a directory hosting the index.php file'
	output '    target is either a list of 1 to n subsites, or "@sites" for all known subsites'
}

# Simple arguments check
backup_directory=$1
shift
drupal_path=$1
shift
target=$@
[ -z "${drupal_path}" ] && usage && exit 50
[ -z "${target}" ] && usage && exit 48
[ -z "${backup_directory}" ] && usage && exit 46

# Check the provided report directory
if [ ! -d "$backup_directory" ]; then
	exitWithErrorMessage 44 "The provided backup directory ($backup_directory) does not appear to exist."
fi
# Ensure this path is absolute so we can chdir without this path to lose its sense
backup_directory=$(readlink -f "${backup_directory}")

function do_action {
	drupal_path=$1
	subsite=$2

	dsc_output=$(drush sql-connect)
	db_name=$(echo "${dsc_output}" | perl -nle 'print $1 if m/--database=([^ ]+)/')

	backup_file="${backup_directory}/${db_name}.sql.gz"
	touch "${backup_file}" && chmod 600 "${backup_file}"
	if [ $? -ne 0 ]; then
		echo "Error: cannot write to the backup file ${backup_file}."
		subsite_status="nok"
		return
	fi

	echo "Saving ${db_name}..."
	mysql_cmd_no_db=$(echo "${dsc_output}" | perl -ple 's/--database=([^ ]+)//; s/^mysql/mysqldump/;')
	$mysql_cmd_no_db --hex-blob --skip-extended-insert --skip-complete-insert --routines "${db_name}" > "${backup_file}"
	if [ $? -ne 0 ]; then
		echo "Error: mysqldump exited with non-zero return code."
		subsite_status="nok"
		return
	fi
	chmod 400 "${backup_file}"
}

loop_on_target_subsites "${drupal_path}" ${target} | timestamped_output
exit 0
