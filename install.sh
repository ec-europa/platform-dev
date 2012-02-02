#!/bin/bash

source config.sh

function __echo {	
	if [ "${verbose}" = 1 ] ; then
		echo $@
	fi
}

usage="Installation of multisite instance\n
Syntax : $(basename $0) [ARGS] SITE-NAME\n
\t-?,-h, --help\t\tPrint this message\n
\t-v, --verbose\t\tSet the script in verbose mode\n
\t-f, --force\t\tForce the installation without any request to user input\n
\t\t\t(Take care, it might delete automatically \n
Connection information\n
\t-u, --db-user\t\tSet the database user\n
\t-p, --db-pass\t\tSet the database password\n
\t-H, --db-host\t\tSet the database host\n\n
\t-P, --db-port\t\tSet the database port\n\n
Configuration of the site\n
\t-r, --web-root\t\tDefine the web root\n
\t-a, --account\t\tDefine the account name for the administrator\n
\t-e, --account-email\tDefine the email address for the administrator\n
\t-m, --site-email\t\tDefine the site email\n
\t-b, --base-url\t\tDefine the base URL of the site\n"


# Configuration of the script
while getopts "u:p:H:P:a:e:n:b:vfh?-:" option; do
        #Management of the --options
        if [ "$option" = "-" ]; then
                case $OPTARG in
                        help) option=h ;;
                        verbose) option=v ;;
						force) force=f ;;
                        dbuser) option=u ;;
                        dbpass) option=p ;;
                        dbhost) option=H ;;
                        dbport) option=P ;;
                        account) option=a ;;
                        account-email) option=e ;;
						web-root) option=r ;;
                        site-email) option=m ;;
                        base-url) option=b ;;
                        *)
                                echo "[ERROR] Unknown option --$OPTARG"
                                exit 1
                                ;;
                esac
        fi
        case $option in
                u) db_user=$OPTARG ;;
                p) db_pass=$OPTARG ;;
                H) db_host=$OPTARG ;;
                P) db_port=$OPTARG ;;
                a) account=$OPTARG ;;
                e) account_mail=$OPTARG ;;
				r) webroot=$OPTARG ;;
                m) site_mail=$OPTARG ;;
                b) baseurl=$OPTARG ;;
                v) verbose=1 ;;
				f) force=1 ;;
                \?|h)
                        echo -e $usage
                        exit 0
                        ;;
                :)
                        echo "[ERROR] Missing arguments for -$OPTARG"
                        exit 1
                        ;;
                ?)
                        echo "[ERROR] Unknown option -$option"
                        exit 1
                        ;;
        esac
done

site_name=$BASH_ARGV
db_url="mysqli://${db_user}:${db_pass}@${db_host}:${db_port}/${site_name}"
__echo "Set DB URL to ${db_url}"

# Get current configuration
current_dir=$(pwd)
__echo "Set current directory to ${current_dir}"
working_dir="${current_dir}/${site_name}"
__echo "Set working directory to ${working_dir}"

# Remove existing working directory
if [ -d "${working_dir}" ] ; then
	__echo -n "Removing existing working directory..."
	rm -rf ${working_dir}
	__echo "done"
fi

#build the drupal instance
__echo `drush make profiles/multisite_drupal_core/build.make ${site_name}`

mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "drop database ${site_name};"
mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "create database ${site_name};"

chmod -R 777 ${site_name}/sites/default
cp -R profiles/multisite_drupal_core ${site_name}/profiles
cp -R profiles/subsite_standard ${site_name}/profiles
cp -R profiles/subsite_communities ${site_name}/profiles
cp -R modules ${site_name}/sites/all
cp -R features ${site_name}/sites/all/modules
cp -R themes ${site_name}/sites/all
cp -R files/ ${site_name}/sites/default/files/


# we assume the script is in the patches directory
patch_dir=$(readlink -f patches)

# we assume the patch directory is located in patches, i.e. one level below the Drupal root directory
__echo "Applying patches from ${patch_dir} to ${site_name}"

cd ${site_name}

if [ $? != 0 ] ; then
	__echo "Unable to change directory to ${site_name}" 
	exit 20
fi


for patch_file in "${patch_dir}/"*.patch "${patch_dir}/"*.diff; do
	test -f "${patch_file}" || continue 
	__echo -n "Attempting to apply ${patch_file}..."
	patch -p0 -b -i "${patch_file}" 1>&2
	__echo "done"
done

#install and configure the drupal instance
drush_option=
if [ "${force}" = 1 ] ; then
	drush_option="-y"
fi
drush si ${drush_option} multisite_drupal_core --db-url=$db_url --account-name=$account_name --account-pass=$account_pass --site-name=${site_name} --site-mail=$site_mail

mkdir "${working_dir}/sites/default/files/private_files"
chmod -R 777 "${working_dir}/sites/default/files"

mkdir "${working_dir}/sites/all/libraries"
#cd sites/all/libraries
cd "${working_dir}/sites/all/modules/contributed/ckeditor"
rm -rf "${working_dir}/sites/all/modules/contributed/ckeditor/ckeditor"
wget -P "${working_dir}/sites/all/modules/contributed/ckeditor/" http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.tar.gz
tar xvzf "${working_dir}/sites/all/modules/contributed/ckeditor/ckeditor_3.6.2.tar.gz" 1>&2
rm "${working_dir}/sites/all/modules/contributed/ckeditor/ckeditor_3.6.2.tar.gz"

if [ -d "${webroot}/${site_name}" ] ; then
	__echo -n "Removing the folder $webroot/${site_name}..."
	rm -rf "${webroot}/${site_name}";
	__echo done
fi

mv "${working_dir}" $webroot
