#!/bin/bash
# 2 options : 
# change-role
# restore-role

#source config.sh

usage="Deploy change roles\n
Syntax : \n
\tchange-role\tChange all users roles, affect maintenance roles\n
\trestore-role\tRestore users roles\n"

if [ $# = 0 ] ; then
  echo -e $usage
  exit 1
fi

# change role -------------------------------------------------------------------------
if [ $1 = 'change-role' ] ; then
  #backup users_roles table 
  #mysqldump -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" $1 users_roles > deploy_scripts/users_roles_backup.sql
  drush sql-dump --data-only --result-file=users_roles_backup.sql --tables-key=users_roles
  
  #duplicate users_roles table
  #mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "USE $1;CREATE TABLE users_roles_backup LIKE users_roles;INSERT users_roles_backup SELECT * FROM users_roles;"
  drush sqlq "CREATE TABLE users_roles_backup LIKE users_roles;INSERT users_roles_backup SELECT * FROM users_roles;"
  
  #change all users roles / affect maintenance roles
  drush scr "deploy_scripts/deploy_cancel_roles.php"
  echo "roles changed"
fi

# restore role -------------------------------------------------------------------------
if [ $1 = 'restore-role' ] ; then
  #retore users role
  #mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "USE $1;TRUNCATE users_roles;INSERT users_roles SELECT * FROM users_roles_backup;DROP TABLE users_roles_backup"
  drush sqlq "TRUNCATE users_roles;INSERT users_roles SELECT * FROM users_roles_backup;DROP TABLE users_roles_backup"
  rm users_roles_backup.sql
  echo "roles restored"
fi
