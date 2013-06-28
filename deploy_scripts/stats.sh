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

  #printf "nodes : \t\t\t\t";
  node=`drush sqlq --extra="-N" "select count(*) as nodes from node"`

  #printf "comments : \t\t\t\t";
  comment=`drush sqlq --extra="-N" "select count(*) as comments from comment"`

  #printf "node types : \t\t\t\t";
  types=`drush sqlq --extra="-N" "select count(*) as 'content types' from node_type"`

  #printf "users : \t\t\t\t";
  users=`drush sqlq --extra="-N" "select count(*) as users from users"`

  #printf "watchdog : \t\t\t\t";
  watchdog=`drush sqlq --extra="-N" "select count(*) as watchdog from watchdog"`

  #printf "modules enabled \t\t\t";
  modules=`drush sqlq --extra="-N" "select count(*) as 'modules enabled' from system where type = 'module' and status = 1"`

  echo "|$2|$node|$comment|$types|$users|$watchdog|$modules|"
   
}

loop_on_target_subsites_report "${drupal_path}" ${target} 
exit 0
