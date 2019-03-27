Ecas env Feature
======================

The Feature aims to provide an authentication method to Drupal using EU Login

# Table of content:

- [Installation](#installation)
  - [Webmaster](#webmaster)
- [Usage](#usage)
- [Debugging](#debugging)
  - [Development](#development-&-debugging)
  - [CA Certificate path](#ca-certificate-path)

# Installation
## Webmaster

The feature needs to be enabled by an administrator, it is not available in 
feature set.

Once the feature is enabled, you can access the EU login at the /ecas url.
You can create an account and use it to test on websites that are set up as LOW
in the "Assurance Level of the application".

To create an external account go to
https://webgate.ec.europa.eu/cas/eim/external/register.cgi
Change the domain to 'External' and fill in the fields.

The feature needs to be enabled by an administrator, it is not available in 
feature set.
The path to the library version is defined for all MULTISITE instances as 
$util_dir . '/phpcas/CAS.php'

*However* that path can be overridden by setting a new value to 
'FPFIS_ECAS_PATH' in your settings.php
If no value constant is defined for FPFIS_ECAS_PATH, the library path will 
fallback to the NextEuropa platform "vendor" repository (vendor/jasic/phpcas).

- After credentials are correctly submitted, a user page is created and user is 
redirected to that page.

- An entry is created in the authmap table:

| aid | uid | authname | module |
|-----:|----:|----------:|--------:|
|   1 |   6 | leperde  | ecas   |


- The profile page is pre-filled with the following fields in readonly mode.

   - First name
   - Last name
   - E-mail address
   - Creator

The logout link is replaced with the *ecaslogout* link.

The feature provides the *Administer ECAS* permission which is granted to 
'administator' role.

The feature provides 3 configuration screens

# Settings
## Assurance Level of the application
Which kind of users may log into the application.
## Default domain
Default is to not force a domain
@TODO explain usage
## Account Request URL
URL used to redirect the user to the EU Login account request service
## Change Password URL
URL given to an EU Login user when he tries to get his password back using the 
user/password page
## Debug mode
When enabled, each attempt will be logged to the phpCas.log file

IE: if you enter ```%file_public%/phpCas.log``` in the textfield, you will be
able to view the log output on ```/build/%file_public%/phpCas.log```
## User account status (first login)
Activate or block user at the time his account is created.
## Login message
Customize the information message shown when user logged in.
## Warning message
Customize the warning message shown when user's account is not active.
## Update the user's mail address
Does the email address from ECAS needs to be saved in the profile.
If not, which email should be.
## Integration with the "core user fields"
Maps EU Login fields with Drupal field names
  - Firstname
  - Lastname
  - Mail address
  - Use the shared "FPFIS Common" library

## Extra settings
These screens enables the configuration of an the email to be sent when access is denied.

## Import users settings
This feature provides a user import functionality
admin/people/import_en

Debugging
---------
In order to manage connections to the Ecas server (EU Login service), 
the feature depends on the **"Ecas"** module and the "**jasig/phpCAS**" library 
available from the "vendor" repository of the platform.

You can create an account and use it to test on website that are set up as LOW
in the "Assurance Level of the application".
To create an external account go to
https://webgate.ec.europa.eu/cas/eim/external/register.cgi
Change the domain to 'External' and fill in the fields.

### Local configuration for user_sync
To test the *user_sync* functionality against LDAP production server, 
you need to provide some extra configuration in your settings.php file

```
define('FPFIS_LDAP_SERVER_NAME', 'XXXX');
define('FPFIS_LDAP_SERVER_PORT', 'XXXXX');
define('FPFIS_LDAP_BASE_DN', 'XXXXX');
define('FPFIS_LDAP_BASE_DN_DG', 'XXXXX');
$ldap_password = 'XXXXX';
$fpfis_ldap_user = 'XXXXXX';
define('FPFIS_LDAP_USER_DN', sprintf('uid=%s,ou=TrustedApps,o=cec.eu.int', $fpfis_ldap_user));
define('FPFIS_LDAP_PASSWORD', $ldap_password);
```
The values can be retrieved from dorstenia server. Please contact Devops for
more information

Please also have a look at 
[dorstenia common settings doc](https://webgate.ec.europa.eu/CITnet/stash/projects/NEXTEUROPA/repos/fpfis-platform-settings/browse?at=dorstenia)
If you have more questions, please contact "COMM Europa Management"

The path to the library version is defined for all instances as $util_dir . 
'/phpcas/CAS.php'

*However* that path can be overriden by setting a new value to 'FPFIS_ECAS_PATH'
in your settings.php
If no value constant is defined for FPFIS_ECAS_PATH, the library path will 
fallback to custom modules ecas/libraries subfolder.
More information can be found in [the debugging section](#debugging)

## CA Certificate path
The variable "ecas_certificate_path" contains the path of the CA 
certificate of the EU Login server. The Eu login module can then use it in order to validate content sent from the EU 
Login server.

The Eu login module does not need it in order to run but it is nevertheless 
recommended to set it in the settings file of the site.


[Go to top](#table-of-content)

The feature EU Login (ecas_env) uses the libraries located in
custom/ecas/libraries/phpcas/CAS/Client.php and the module located in 
profiles/common/modules/custom/ecas
