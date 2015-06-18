#!/bin/bash

# install.sh script settings
webroot='/ec/dev/server/fpfis/webroot/sources'
subdirectory='' #fill only if the site must be installed in a subdirectory of the webroot
verbose=0 # 0 || 1
force=0 # 0 || 1
drush_options=""
htaccess_rewrite_base=1

# Database settings
db_user='fpfis'
db_pass='dev'
db_host='127.0.0.1'
db_port=3306

# Drupal settings
install_profile='multisite_drupal_standard' # multisite_drupal_standard || multisite_drupal_communities
account_name='admin'
account_pass='pass'
account_mail='DIGIT-FPFIS-SUPPORT@ec.europa.eu'
site_mail='DIGIT-FPFIS-SUPPORT@ec.europa.eu'
#baseurl="http://fpfis-dev.net1.cec.eu.int/multisite_training"
base_path="multisite" 

# Apache solr settings
solr_server_url='http://dorstenia.cc.cec.eu.int:8080/solr/drupal'
solr_server_name='multisite solr server'
apachesolr_attachments_tika_jar='tika-app-1.1.jar'
apachesolr_attachments_tika_path='/home/fpfis/util/bin'
apachesolr_attachments_java='/usr/bin/java'

# Sources settings
svn_basepath="" # trunk || branche || tag
svn_url="https://webgate.ec.europa.eu/CITnet/svn/MULTISITE" # useless with svn_folder=local 
svn_tag_version="1.7" # useless with svn_folder=local 


# --- specifics subsite variables for install_subsite.sh --- #
subsite_parent_name=''
subsite_custom_subsite=''
# used to create the URL pattern from the subsite name (%s) - the best
# explanation for this parameter is bootstrap.inc's conf_path() function
subsite_cluster_url_pattern='fpfis-dev.net1.cec.eu.int.multisite.multisite_training.%s';
# used to create the path of the conf directory from the subsite name (%s),
# relatively to the sites/ directory
subsite_cluster_dir='%s'
# Do we need to provide Drupal with an array associating URL patterns to conf directory?
subsite_update_drupal_sites_list="yes"
# in what file do we provide this information?
subsite_drupal_sites_list="sites.php"
# Note: we may provide a sites.php file next to this configuration file


