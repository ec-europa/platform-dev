#!/bin/bash
source $HOME/.bash_profile

function exitWithErrorMessage {
    rc=$1
    shift
    echo $@
    exit $rc
}

function usage {
    echo "Usage: $0 <config-name> <reporting-directory>"
}
report_directory=$2

if [ -d "$report_directory" ]; then
	echo "$report_directory";
	
else
	
	echo "Unknowned directory $report_directory";
       usage
	exit 50		      
fi

master_path=$1
[ -z "${master_path}" ] && usage && exit 50
       
cd  "${master_path}/sites" || exitWithErrorMessage 40 "Unable to chdir to ${master_path}/sites"
php -r 'include("sites.php"); 
foreach($sites as $s) print "$s\n";' 2> /dev/null | sort -u | while read subsite; do
        cd "$subsite" || continue
              drush status >> reporting_$subsite`date +%y%m%d`.txt
		drush fc node >> reporting_$subsite`date +%y%m%d`.txt
		drush field-info types >> reporting_$subsite`date +%y%m%d`.txt
		drush field-info fields >> reporting_$subsite`date +%y%m%d`.txt
		drush fl >> reporting_$subsite`date +%y%m%d`.txt
		drush pml >> reporting_$subsite`date +%y%m%d`.txt
		drush vl >> reporting_$subsite`date +%y%m%d`.txt
		drush fc views_view >> reporting_$subsite`date +%y%m%d`.txt
		drush fc taxonomy >> reporting_$subsite`date +%y%m%d`.txt
		drush sqlq 'SELECT tid, vid, name FROM taxonomy_term_data;' >> reporting_$subsite`date +%y%m%d`.txt
		drush fc variable >> reporting_$subsite`date +%y%m%d`.txt
		drush fc context >> reporting_$subsite`date +%y%m%d`.txt
		drush fc user_role >> reporting_$subsite`date +%y%m%d`.txt
		drush fc user_permission >> reporting_$subsite`date +%y%m%d`.txt
		drush sqlq 'SELECT * FROM custom_breadcrumb;' >> reporting_$subsite`date +%y%m%d`.txt
		drush fc menu_links >> reporting_$subsite`date +%y%m%d`.txt
		drush fl | grep Enabled | sed '1d' | perl -ple 's,([^ ]) ([^ ]),\1_\2,g'  | awk '{print $2}' >> feature_list.txt
		for line in $(cat feature_list.txt)
		do
		   echo  "--- $line ------" >> reporting_"$subsite"_diff_`date +%y%m%d`.txt
		   drush fd "$line" >> reporting_"$subsite"_diff_`date +%y%m%d`.txt
		done
		rm -f feature_list.txt
		mv  reporting_"$subsite"_diff_`date +%y%m%d`.txt  reporting_"$subsite"_diff`date +%y%m%d%T`.txt              
              mv reporting_"$subsite"_diff`date +%y%m%d%T`.txt $report_directory
              mv reporting_$subsite`date +%y%m%d`.txt $report_directory

        cd  "${master_path}/sites"
done
