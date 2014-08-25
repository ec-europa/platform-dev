Clients for Drupal Services REST Servers
==========================================

This module contains client connection types for connecting to Services module
on Drupal (http://drupal.org/project/services), for endpoints using the REST
server.

The remote Drupal site you are connecting to needs Services version 7.x-3.5 or
higher.

Setting up a client
--------------------

At admin/settings/clients, choose the type of connection you want to create.
The Drupal-specific options are as follows:

- Service username, password: the details for a Drupal user on the remote site.

It's a very good idea to go to the test page for your connection and try the
various actions such as logging in and retrieving a node. These show you exactly
what is returned from the remote server.

Setting up Services
------------------

Your Services endpoint must have:

- under 'Edit':
  - 'Session authentication' enabled
- under 'Server':
  - the 'json' response formatter enabled
  - the following Request parsing options enabled:
    - 'application/json'
    - 'application/x-www-form-urlencoded'
- under 'Resources
  - the user resource's login action enabled
  - the user resource's token action enabled
  - any other resources you want to use

API
-------------------

The parameters for clients_connection_call() are different from the XMLRPC
connections:

clients_connection_call(CONNECTION NAME, RESOURCE PATH, HTTP METHOD, DATA);

Examples:

try {
  // 'my_connection' is the machine name of the connection.
  $result = clients_connection_call('my_connection', 'node/1', 'GET');
}
catch (Exception $e) {
  // Something went wrong; it's up to you to display an error.
  // This is the error message, if any:
  $message = $e->getMessage();
}

Subsequent examples omit the try/catch block for brevity:

$result = clients_connection_call('my_connection', 'node/1', 'POST', $data);

You can also call the makeRequest() method on the connection:

$connection = clients_connection_load('my_connection');
$result = $connection->makeRequest('node/1', 'GET');

The 'user/register' service is a special case (and 'entity_user/register' if you
are using Services Entity). Functionally, this is identical in Services to
'user/create'. For both services, access is granted either if the
user is anonymous, or if the user has the 'administer users' permission (see
_user_resource_access()). To keep things simple, Clients assumes that for the
'user/register' services you intend to be anonymous, and for the 'user/create'
you are logging in as normal.

