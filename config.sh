#!/bin/bash

#Default values
webroot='/ec/webroot'
db_user='fpfis'
db_pass='dev'
db_host='localhost'
db_port=3306
db_admin_user='fpfis'
db_admin_pass='dev'
account_name='admin'
account_pass='pass'
account_mail='cyril.champagne@ext.ec.europa.eu'
site_mail='cyril.champagne@ext.ec.europa.eu'
baseurl='http://fpfis-dev.net1.cec.eu.int/multisite_drupal_mct_1'
verbose=0
force=0
install_profile='multisite_drupal_standard'
solr_server_url='http://fpfis-dev.net1.cec.eu.int:8080/solr/multisite'
solr_server_name='multisite solr server'
apachesolr_attachments_tika_jar='tika-app-1.1.jar'
apachesolr_attachments_tika_path='/home/fpfis/util/bin'
apachesolr_attachments_jav ='/usr/bin/java'

if [ "$subsite_installation" == "yes" ]; then
	subsite_name="$subsite"
	subsite_db_name="multisite_drupal_mct_1_${subsite_name}"
	subsite_db_host='localhost'
	if [ -f "subsites/${subsite}/config.sh" ]; then
		source "subsites/${subsite}/config.sh"
	fi
	subsite_db_url="mysqli://${subsite_db_user}:${subsite_db_pass}@${subsite_db_host}/${subsite_db_name}"
fi

# php-cli command
php="php"

# used to create the URL pattern from the subsite name (%s) - the best
# explanation for this parameter is bootstrap.inc's conf_path() function
cluster_subsite_url_pattern='fpfis-dev.net1.cec.eu.int.multisite_drupal_mct_1.%s';

# used to create the path of the conf directory from the subsite name (%s),
# relatively to the sites/ directory
cluster_subsite_dir='%s'

# Do we need to provide Drupal with an array associating URL patterns to conf directory?
update_drupal_sites_list="yes"
# in what file do we provide this information?
drupal_sites_list="sites.php"
# Note: we may provide a sites.php file next to this configuration file


