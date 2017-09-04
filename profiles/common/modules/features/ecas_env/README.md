Ecas env Feature
======================

The module aims to provide an authentication method to Drupal using ECAS

Installation
------------

The feature needs to be enabled by an administrator, it is not available in feature set.
The path to the library version is defined for all instances as $util_dir . '/phpcas/CAS.php'

*However* that path can be overriden by setting a new value to 'FPFIS_ECAS_PATH' in your settings.php
If no value constant is defined for FPFIS_ECAS_PATH, the library path will fallback to custom modules ecas/libraries subfolder.

Usage
-----

When feature is enabled, a button 'Ecas Login' is available on each page.
The button redirects the user to the ECAS login screen.
After credentials are rightly submitted, a user page is created and user is redirected to that page.
An entry is created in the authmap table:

| aid | uid | authname | module |
|-----|----:|----------|--------|
|   1 |   6 | leperde  | ecas   |

<dl>
<dt>The profile page is pre filled with the following fields in readonly mode.</dt>
  <dd>First name</dd>
  <dd>Last name</dd>
  <dd>E-mail address</dd>
  <dd>Creator</dd>
</dl>

The logout link is replaced with the *ecaslogout* link.

The feature provides the *Administer ECAS* permission which is granted to 'administator' role.

The feature provides 3 configuration screens

### Settings
#### Assurance Level of the application
Which kind of users may log into the application.
#### Default domain
Default is to not force a domain
#### Account Request URL
#### Change Password URL
#### Debug mode
When enabled, each attempt will be logged to the phpCas.log file
IE: if you enter '%file_public%/phpCas.log' in the textfield, you will be
able to view the log output on /build/%file_public%/phpCas.log
#### User account status (first login)
Activate or block user at the time his account is created.
#### Login message
Customise the information message shown when user logged in
#### Warning message
Customise the warning message shown when user's account is not active.
#### Update the user's mail address
Does the email address from ECAS needs to be saved in the profile.
If not, which email should be.
#### Integration with the "core user fields"
Map ecas fields with Drupal field names
##### Firstname
##### Lastname
##### Mail address
##### Use the shared "FPFIS Common" library

### Extra settings
This screens allow to configure the email sent went access is denied.

### Import users settings
The feature provides a user import functionality
admin/people/import_en

Debugging
---------
The feature ecas_env uses the libraries located in
custom/ecas/libraries/phpcas/CAS/Client.php
You can create an account and use it to test on website that are set up as LOW
in the "Assurance Level of the application".
To create an external account go to
https://webgate.ec.europa.eu/cas/eim/external/register.cgi
Change the domain to 'External' and fill in the fields.