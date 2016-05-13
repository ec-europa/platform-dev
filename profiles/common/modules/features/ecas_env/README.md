Ecas env Feature
======================

The module aims to provide an authentication method to Drupal using ECAS

Installation
------------

The feature needs to be enabled by an administrator, it is not available in feature set.

Usage
-----

When feature is enabled, a button 'Ecas Login' is available on each page.
The button redirects the user to the ECAS login screen.
After credentials are rightly submitted, a user page is created and user is redirected to that page.
An entry is created in the authmap table:

| aid | uid | authname | module |
|-----|----:|----------|--------|
|   1 |   6 | leperde  | ecas   |
|-----|-----|----------|--------|


The profile page is pre filled with the following fields in readonly mode.
  >First name
  >Last name
  >E-mail address
  >Creator

The logout link is replaced with the ecaslogout link.

The feature provides the 'Administer ECAS' permission which is granted to 'administator' role.

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