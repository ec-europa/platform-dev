# prefix the given line with current date
function output {
	builtin echo $(date '+%F:%T') "$@"
}

# prefix each line of standard input with current date
function timestamped_output {
	# Using Perl to rewrite the output is better for performance than calling
	# the output function once per line
	perl -ple 'my ($sec,$min,$hour,$mday,$mon,$year) = localtime(time); printf(q[%d-%02d-%02d:%02d:%02d:%02d ], 1900 + $year, $mon + 1, $mday, $hour, $min, $sec)'
	# dummy version
	# while read line; do output "$line" done
}

# Strip out UTF-8 BOMs and ANSI escape sequences
function report_output {
	sed -r "s/\x1B\[([0-9]{1,3}((;[0-9]{1,3})*)?)?[m|K]//g; s/\xef\xbb\xbf//g;"
}

# Display an error message and exit; takes at least two parameters:
#   - the return code
#   - the message to be displayed before exiting
function exitWithErrorMessage {
	rc=$1
	shift
	echo "Error:" $@
	exit $rc
}

function change_to_drupal_sites_directory {
	drupal_path=$1
	cd "${drupal_path}/sites" || exitWithErrorMessage 40 "Unable to chdir to ${drupal_path}/sites"
}

function check_drupal_directory {
	drupal_path=$1
	if [ ! -d "${drupal_path}" ]; then
		exitWithErrorMessage 40 "${drupal_path} was provided as Drupal directory but does not appear to exist."
	fi
	if [ ! -f "${drupal_path}/index.php" ]; then
		exitWithErrorMessage 38 "${drupal_path} was provided as Drupal directory but does not appear to be one (no index.php)."
	fi
	if [ ! -d "${drupal_path}/sites" ]; then
		exitWithErrorMessage 37 "${drupal_path} was provided as Drupal directory but does not appear to be one (no sites/ subdirectory)."
	fi
	if [ ! -f "${drupal_path}/sites/sites.php" ]; then
		exitWithErrorMessage 35 "This script expects a sites.php file within ${master_path}/sites in order to determine the list of existing subsites."
	fi
}

function get_subsites_list {
	drupal_path=$1
	check_drupal_directory "${drupal_path}"
	(
		php -r 'include("'${drupal_path}'/sites/sites.php"); foreach ($sites as $s) print "$s\n";'
		# ensure the default sites (not necessarily listed within sites.php) is included
		echo 'default'
	) | sort -u
}

function get_target_subsites {
	drupal_path=$1
	shift
	target=$@
	if [ "${target}" == '@sites' ]; then
		get_subsites_list "${drupal_path}"
	else
		for subsite in ${target}; do
			echo "${subsite}"
		done
	fi
}

function begin_subsite {
	echo "================================================================================"
	echo "Now treating subsite ${subsite}..."
}

function end_subsite {
	if [ -z "$subsite_state" -o "$subsite_state" == "ok" ]; then
		echo "Everything went well."
	else
		echo "Caution: errors were reported."
	fi
}

# chdir to each subsite directory from the specified targets before calling the
# do_action function with two arguments:
#   - the Drupal directory path
#   - the subsite name
function loop_on_target_subsites {
	drupal_path=$1
	shift
	target=$@
	# treat each target subsite
	get_target_subsites "${drupal_path}" $target | while read subsite; do
		change_to_drupal_sites_directory "${drupal_path}"
		begin_subsite "${drupal_path}" "${subsite}"
		cd "${subsite}" &> /dev/null
		if [ $? -ne 0 ]; then
			echo "  Unable to change directory to ${subsite} (former subsite deleted or bad target specified?), skipping."
			continue
		fi
		do_action "${drupal_path}" "${subsite}" 2>&1 | sed 's,^,  ,'
		end_subsite "${drupal_path}" "${subsite}"
	done
}

# clone of the loop_on_target_subsites function dedicated for reporting
function loop_on_target_subsites_report {
   drupal_path=$1
   shift
   target=$@
   # treat each target subsite
   echo "||site||nodes||comments||node types||users||watchdog||modules enabled||"
   get_target_subsites "${drupal_path}" $target | while read subsite; do
       change_to_drupal_sites_directory "${drupal_path}"
       cd "${subsite}" &> /dev/null
       if [ $? -ne 0 ]; then
           echo "  Unable to change directory to ${subsite} (former subsite deleted or bad target specified?), skipping."
           continue
       fi
       do_action "${drupal_path}" "${subsite}" 2>&1
   done
}




# Run a query as drush sql-query would, but does so by relying on the mysql CLI
# client which achieves a better work when it comes to exit with a significant
# return code.
# Params:
#   - 1st parameter is the SQL query to be executed
#   - other parameters are passed to mysql
function drush_sql_query {
	query=$1
	shift
	echo "${query}" | $(drush sql-connect) $@
}

# Run a drush command, taking care to announce it before execution and check its
# return code
function run_drush {
	echo "Running drush $@..."
	drush "$@" | sed 's,^,  ,'
	rc=$?
	if [ "${rc}" -ne 0 ]; then
		echo "Error: drush $@ return non-zero (${rc})"
		subsite_status="nok"
	fi
}

# Parse the output of drush features-list to extract features matching a
# particular pattern
function grep_features {
	pattern=$1
	drush features-list | grep "${pattern}" | perl -ple 's,([^ ]) ([^ ]),\1_\2,g' | awk '{print $2}'
}

# get only shared features, except a given list as parameter
function get_shared_features {
	excluded_features=$(perl -e 'print join(q[, ], map { q["] . $_ . q["] } @ARGV);' "$@")
	drush sql-query --extra="-N" "SELECT name FROM system WHERE (filename LIKE 'sites/all/modules/features%' OR filename LIKE 'profiles/multisite_drupal_communities/modules/features%') AND status = 1 AND name NOT IN ('cce_basic_config', 'multisite_settings_core');"
}

# We also export the COLUMNS e.v. to prevent drush from wrapping its output
# since this might confuse our parsing, especially within grep_features.
export COLUMNS=150
