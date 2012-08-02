#!/bin/bash
source $HOME/.bash_profile
function exitWithErrorMessage {
    rc=$1
    shift
    echo $@
    exit $rc
}
function usage {
    echo "Usage: $0 <config-name> "
}


master_path=$1
[ -z "${master_path}" ] && usage && exit 50
       
cd  "${master_path}/sites" || exitWithErrorMessage 40 "Unable to chdir to ${master_path}/sites"
php -r 'include("sites.php"); 
foreach($sites as $s) print "$s\n";' 2> /dev/null | sort -u | while read subsite; do
        cd "$subsite" || continue        
		drush updatedb
        cd  "${master_path}/sites"
done
