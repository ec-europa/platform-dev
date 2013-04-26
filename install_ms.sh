#!/bin/bash
if [ "$#" -lt 2 ];
then
  echo "usage: $0 <profile> <site name>"
  exit 42
fi

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
\t\t\t\t(Take care, it might delete automatically your database)\n
Connection information\n
\t-u, --db-user\t\tSet the database user\n
\t-p, --db-pass\t\tSet the database password\n
\t-H, --db-host\t\tSet the database host\n
\t-P, --db-port\t\tSet the database port\n\n
Configuration of the site\n
\t-d, \t\t\tDefine drush options\n
\t-r, --web-root\t\tDefine the web root\n
\t-a, --account\t\tDefine the account name for the administrator\n
\t-e, --account-email\tDefine the email address for the administrator\n
\t-m, --site-email\tDefine the site email\n
\t-b, --base-url\t\tDefine the base URL of the site\n
\t-i, --install-profile\tDefine the installation profile to use\n
\t-t, --tag_version\tDefine the svn tag to install\n"


# Configuration of the script
while getopts "u:p:H:P:a:e:d:r:n:b:i:t:vfh?-:" option; do
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
						install_profile) option=i ;;
                        tag_version) option=t ;;
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
				d) drush_options=$OPTARG ;;
				r) webroot=$OPTARG ;;
                m) site_mail=$OPTARG ;;
                b) baseurl=$OPTARG ;;
                v) verbose=1 ;;
				f) force=1 ;;
				i) install_profile=$OPTARG ;;
                t) tag_version=$OPTARG ;;
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
if [ -z "${site_name}" ];
then
  echo "WARNING: no site name was given !!"
  exit 42
fi


#export svn repository
echo "Export from https://webgate.ec.europa.eu/CITnet/svn/MULTISITE/tags/${tag_version}/source pms_${site_name}"
svn export https://webgate.ec.europa.eu/CITnet/svn/MULTISITE/tags/1.3/source pms_${site_name}
pms_dir=$(pwd)
cd pms_${site_name}

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

# Set up the drush option
if [ "${force}" = 1 ] ; then
	drush_options="${drush_options} -y"
fi
__echo "Set drush options: ${drush_options}"

#build the drupal instance
drush ${drush_options} make profiles/$install_profile/build.make ${site_name} 1>&2

mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "drop database ${site_name};" 1>&2
mysql -h ${db_host} -P ${db_port} -u $db_user --password="$db_pass" -e "create database ${site_name};" 1>&2

chmod -R 777 ${site_name}/sites/default 
cp -R profiles/multisite_drupal_core ${site_name}/profiles
cp -R profiles/$install_profile ${site_name}/profiles

cp -R sites/all/modules/ ${site_name}/sites/all
cp -R sites/all/modules/features ${site_name}/sites/all/modules
cp -R sites/all/themes ${site_name}/sites/all
cp -R sites/default/files/ ${site_name}/sites/default/files/
cp sites/default/proxy.settings.php ${site_name}/sites/default/
cp -R sites/all/libraries ${site_name}/sites/all
cp -R deploy_scripts ${site_name}


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
drush --php="/usr/bin/php" ${drush_options} si $install_profile --db-url=$db_url --account-name=$account_name --account-pass=$account_pass --site-name=${site_name} --site-mail=$site_mail  1>&2

#solR config
drush solr-set-env-url $solr_server_url
drush sqlq "UPDATE apachesolr_environment SET name = '${solr_server_name}' WHERE env_id = 'solr'"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','page')"
drush sqlq "INSERT INTO apachesolr_index_bundles (env_id,entity_type,bundle) VALUES ('solr','node','article')"

#flush cache and rebuild access
drush cc all
drush php-eval 'node_access_rebuild();'
#inject data
drush vset tmp_base_url "/${site_name}"
drush scr "${working_dir}/profiles/${install_profile}/inject_data.php"
drush vdel --exact --yes tmp_base_url

#set solr tika variables
drush vset apachesolr_attachments_tika_jar "${apachesolr_attachments_tika_jar}"
drush vset apachesolr_attachments_tika_path "${apachesolr_attachments_tika_path}"
drush vset apachesolr_attachments_java "${apachesolr_attachments_java}"

#set FPFIS_common libraires path
#drush php-eval "define('FPFIS_COMMON_LIBRARIES_PATH',${FPFIS_common_libraries});"

mkdir "${working_dir}/sites/default/files/private_files"
chmod -R 777 "${working_dir}/sites/default/files"

if [ -d "${webroot}/${site_name}" ] ; then
	__echo -n "Removing the folder $webroot/${site_name}..."
    chmod -R 777 "${webroot}/${site_name}"
	rm -rf "${webroot}/${site_name}"
	__echo done
fi

#remove links from the linkchecker scanning process
drush sqlq "delete FROM linkchecker_link"
drush sqlq "delete FROM linkchecker_node"

mv "${working_dir}" $webroot

chmod -R 777 "${pms_dir}/pms_${site_name}"
rm -rf "${pms_dir}/pms_${site_name}"

cd "${webroot}/${site_name}"

#solr indexation
drush solr-index

#run cron
drush cron


