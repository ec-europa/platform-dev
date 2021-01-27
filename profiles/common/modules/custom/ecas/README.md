Ecas module
======================



- [Hooks provided](#hooks-provided)
- [Dependencies](#dependencies)
- [Other modules](#other-modules)
- [Usage](#usage)

[Go to top](#table-of-content)



## CA Certificate path
The variable "ecas_certificate_path" contains the path of the CA 
certificate of the EU Login server. The Eu login module can then use it in order to validate content sent from the EU 
Login server.

The Eu login module does not need it in order to run but it is nevertheless 
recommended to set it in the settings file of the site.

# Hooks provided
- hook_info_ecas_update : invoked during the ecas login, when the user account 
is updated. This hook enables the injection of custom modifications into the user 
account regarding the user info returned from LDAP.

parameters :
$user : user account
$user_info : user infos get from the LDAP

- hook_ecas_full_logout_parameters_alter : invoked during the ecas logout 
process. It allows the alteration of the params ($params) sent to the phpCAS::logout 
function.
parameters :
$params : array of parameters sent to the phpCAS::logout function

- hook_ecas_extra_filter_alter : invoked during the login process. It processes user
filtering and prevents the authentification of users related 
to custom constraints.
parameters :
$ecas_name : ecas username
$account : user account
$ecas_goto : url destination after the login
For example : by forcing $ecas_name to NULL and $account to FALSE, the login is blocked 
and the user is set as anonymous.

- hook_ecas_assurance_levels_alter : invoked when the assurance level is 
requested. It enables the alteration of the ecas assurance level. 

parameters: $ecas_assurance_level

- hook_ecas_domains_alter : invoked when the ecas domains are requested, it 
allows to alters the ecas domains.
parameters :
$ecas_domains

- hook_ecas_LDAP_info_alter : invoked before getting info from LDAP, it allows
the alteration of the list of fields extracted from LDAP
parameters :
$LDAP_info : array of LDAP fields
Ex : $LDAP_info = array('sn', 'givenname', 'dg', 'sourceorganisation', 
'departmentnumber');


# Dependencies
The 3 modules use
- the phpCAS library
- the FPFIS COMMON library
Both will be included from the FPFIS_COMMON_LIBRARIES_PATH, which has to be
defined, typically in settings.php

## FPFIS COMMON library :
This is a php library used for all the php applications of the flexible plateform (FPFIS).
The important data in this library for the EU Login module are :
- EU Login settings (url, port, ...)
- LDAP settings (credentials, base DN, ...)

## Drupal Dependencies :

- ECAS : Provides single sign-on EU Login
Required by:
-- ECAS extra (enabled),
-- ECAS import users (enabled)
- ECAS extras : Provides extra features to the EU Login module
Requires:
-- ECAS (enabled),
-- Views (enabled),
Chaos tools (enabled),
Views Bulk Operations (enabled),
Entity API (enabled)
- ECAS import users : Create users accounts from EU Login accounts (in LDAP).
Requires:
ECAS (enabled)


## Other modules
### core ECAS module :
This module allows a user to login to a drupal instance with an EU Login account.
During the first login, the module creates a drupal account with the data from 
the LDAP (username, password, email, ...).
With drupal 6 the module was compatible with the modules node_profile, profile 
to store users data in users profiles, nodes and CCK fields.

With drupal 7, the module must populated the following fields related to user 
accounts :

- user-user-field_firstname

- user-user-field_lastname

### ecas_import_users :
This module allows the system to browse the LDAP directory, import users accounts and 
create related users accounts.
Same updates as the core module. This module must populate the following fields 
related to user accounts during a user account creation :

- user-user-field_firstname

- user-user-field_lastname

### ecas_extra :
This module enables moderation of the access to a drupal instance with EU Login 
accounts.
The new users that logged in for the first time with their ecas accounts are 
put in a pending list and must wait for the validation of a moderator. An email is sent when the account is authorized
or rejected.
The module needs the following drupal modules : views, views bulk operation.

### ecas_group_sync :
This module allows mappings between LDAP fields and users accounts settings :

- for the standard multisite : it provides a mapping between users DG and drupal
roles
- for the community multisite : it provides a mapping between DG and og roles in
communities

- release 2.6.x allows to improve security level of sites which allow logging in
using 1AF. When the array 'ecas_whitelisted_user_roles' is present in the
settings.php file, EU login will only allow 1AF for a user if all her/his roles
are included. An empty array will force 2AF on all users.
This variable should be set in the settings.php file of the site.

Usage
-----

More information can be found in the [readme of feature "ecas_env"](../../features/ecas_env/README.md)
