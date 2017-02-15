The "NextEuropa Nagios" feature provides custom integration with the Nagios
integration server.


Table of content:
=================
- [Installation](#installation)
- [Configuration](#configuration)

# Installation

The feature is proposed through a Drupal custom feature and is available with the NextEuropa platform.

The feature can only be enabled by the DevOps team who are in charge of enabling it in the appropiate sites.

[Go to top](#table-of-content)

# Configuration

Once installed the module can be configured by accesing the following path:

 * admin/config/system/nagios

## Setting up a unique ID

Most of the basic configuration is already configured by default.
However in order for Nagios to be able to reach the site a unique ID must be set. 
See Nagios configuration for more information on how to create a unique ID.

## Drupal configuration

For more information, refer to the Nagios module Readme.txt
  
## Nagios configuration

The Nagios service must be properly configured in order to start receiving information from a Drupal site.

The following steps are taken from the Nagios module Readme.txt and changed to cater for the specific
needs of the NE platform.

1. Copy the check_drupal script in the nagios-plugin directory to your Nagios plugins
   directory (e.g. /usr/lib/nagios/plugins).
   
   Depending on your Linux distribution, you may need to alter the PROGPATH variable
   in check_drupal to the correct location for Nagios utils.sh script.

2. Change the commands.cfg file for Nagios to include the following:

   Nagios 2.x:

   define command{
     command_name  check_drupal
     command_line  /usr/lib/nagios/plugins/check_drupal -H $HOSTADDRESS$ -U $ARG1$ -t $ARG2$ -v $ARG3$ -m $ARG4$
   }

   Nagios 3.x:

   define command{
     command_name  check_drupal
     command_line  /usr/lib/nagios/plugins/check_drupal -H $HOSTADDRESS$ -U $ARG1$ -t $ARG2$ -v $ARG3$ -m $ARG4$
   }

   You can add the -S option for hosts that use https.

   If you are monitoring multiple Drupal instances set up as virtual hosts, you
   may have to use $HOSTNAME$ instead of $HOSTADDRESS$ in the command_line
   parameter.

3. Create a hostgroup for the hosts that run Drupal and need to be monitored.
   This is normally in a hostgroups.cfg file.

   define hostgroup {
     hostgroup_name  drupal-servers
     alias           Drupal servers
     members         yoursite.example.com, mysite.example.com
   }

4. Defined a service that will run for this host group

   Nagios 2.x:

   define service{
     hostgroup_name         drupal-servers
     service_description    DRUPAL
     check_command          check_drupal!-U "unique_id" -t 2 -v SAU
     use                    generic-service
     notification_interval  0 ; set > 0 if you want to be renotified
   }

   Nagios 3.x:

   define service{
     hostgroup_name         drupal-servers
     service_description    DRUPAL
     check_command          check_drupal!unique_id!2!SAU
     use                    generic-service
     notification_interval  0 ; set > 0 if you want to be renotified
   }

Here is an explanation of some of the options:

-U "unique_id"
  This parameter is required.
  It is a unique identifier that is send as the user agent from the Nagios check_drupal script,
  and has to match what the Drupal Nagios module has configured.  Both sides have to match,
  otherwise, you will get "unauthorized" errors. The best way is to generate an MD5 or SHA1
  string from a combination of data, such as date, city, company name, ...etc. For example:

  $ echo "2003-Jan-17 Waterloo, Canada Honda" | md5sum

  The result will be something like this:

  645666c39f06514528987278c4071d85  -

  The resulting hash is hard enough to deduce, and gives a first level protection against snooping.

-t 2
  This parameter is optional.
  This means that if the Drupal site does not respond in 2 seconds, an error will be reported
  by Nagios. Increase this value if you site is really slow.
  The default is 2 seconds.

-P nagios
  This parameter is optional.
  For a normal site where Drupal is installed in the web server's DocumentRoot, leave this unchanged.
  If you installed Drupal in a subdirectory, then change nagios to sub_directory/nagios
  The default is the path nagios.

-v variable
  This parameter is optional.
  This parameter allows to receive a single variable from the ones available in the Drupal site.
  
-m module
   This parameter is optional.
   This parameter allows to receive all the variables available for a single module
   in the Drupal site.

[Go to top](#table-of-content)
