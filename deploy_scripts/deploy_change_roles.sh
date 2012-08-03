#!/bin/bash
source $HOME/.bash_profile
function exitWithErrorMessage {
	rc=$1
    shift
    echo $@
    exit $rc
}
function usage {
    echo "Usage: $0 <config-name> change-role|restore-role"
}


master_path=$1
[ -z "${master_path}" ] && usage && exit 50
       
cd  "${master_path}/sites" || exitWithErrorMessage 40 "Unable to chdir to ${master_path}/sites"
php -r 'include("sites.php");  
foreach($sites as $s) print "$s\n";' 2> /dev/null | sort -u | while read subsite; do
	cd "$subsite" || continue 
        
	# change role -------------------------------------------------------------------------
	if [ $2 = 'change-role' ] ; then
		#backup users_roles table 
		drush sql-dump --data-only --result-file=users_roles_backup.sql --tables-key=users_roles
		#duplicate users_roles table
		drush sqlq "CREATE TABLE users_roles_backup LIKE users_roles;INSERT users_roles_backup SELECT * FROM users_roles;"
		#change all users roles / affect maintenance roles
		drush scr "deploy_cancel_roles.php"
		echo "roles changed"
	fi

	# restore role -------------------------------------------------------------------------
	if [ $2 = 'restore-role' ] ; then
		#retore users role
		drush sqlq "TRUNCATE users_roles;INSERT users_roles SELECT * FROM users_roles_backup;DROP TABLE users_roles_backup"
		rm users_roles_backup.sql
		echo "roles restored"
	fi            
  
	cd  "${master_path}/sites"
done

