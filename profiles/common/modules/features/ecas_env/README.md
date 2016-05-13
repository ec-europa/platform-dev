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

The profile page is pre filled with the following fields in readonly mode.
  *First name
  *Last name
  *E-mail address
  *Creator

The logout link is replaced with the ecaslogout link.

The feature provides the 'Administer ECAS' permission which is granted to 'administator' role.

The feature provides 3 configuration screens

### Settings
#### Assurance Level of the application
#### Default domain
#### Account Request URL
#### Change Password URL
#### Debug mode
#### User account status (first login)
#### Login message
#### Warning message
#### Update the user's mail address
#### Integration with the "core user fields"
##### Firstname
##### Lastname
##### Mail address
##### Force authentication
##### Use the shared "FPFIS Common" library

### Extra settings
This screens allow to configure the email sent went access is denied.

### Import users settings
The feature provides a user import functionality
admin/people/import_en