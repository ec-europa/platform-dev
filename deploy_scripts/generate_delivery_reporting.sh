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
		drush fl | grep "Needs review" | cut -f 1 | perl -ple 's,([^ ]) ([^ ]),\1_\2,g'  | awk '{print $2}' >> feature_list_nr.txt
		for line in $(cat feature_list_nr.txt)
		do
			echo $line;
			for param in "$@"
			do
				if [ $# -gt 2 ]; then
                               	if [ "$param" == $line ]; then
                                     echo "$line	found as Needs review" >> $2/delivery_reporting_"$subsite"_`date +%y%m%d`.txt
                                     drush fd $line >> $2/delivery_reporting_"$subsite"_`date +%y%m%d`.txt
					fi

				fi
			done
		   
		done
		rm -f feature_list_nr.txt	

        	cd  "${master_path}/sites"
	done
echo "End of process"
