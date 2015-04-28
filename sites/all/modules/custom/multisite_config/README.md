/*! \mainpage Multisite Configuration API

\section desc_sec Description

Multisite configuration API is provided by core team, to allow every developers on Multisite to access common helper tools.

\section how_read_sec How to read that API?

In <a href="namespaces.html"><strong>Namespaces</strong></a> section, you can find the list of currently avilable classes. By opening the corresponding Config file you get a detailed list of available functions for that class.

In <a href="functions.html"><strong>Data fields</strong></a> section, you can find a complete list of available functions.

\section how_use_sec How to use and improve that API?

Multisite Configuration API classes extends <code>\\%Drupal\\multisite_config\\ConfigBase</code> class and are namespaced by <code>\\%Drupal\\:module</code>, while the actual class is always named <code>Config</code>.

To use that API in a third-party module, you have to:
1. Add <code>registry_autoload[] = PSR-4</code> to .info file
2. Call any function you want by using its class name (see exemple)

To add new configuration API you have to:
1. Edit a configuration class described above under <code>./src</code> directory (or create a new one when needed)
2. Update API documentation (or request for update)

\subsection exemple_subsec Exemple

Given a module named <strong>foo</strong>:

<strong>foo.info will look like:</strong>

<pre>
name = Foo module
description = Foo module description.
core = 7.x
version = 7.x-1.0-dev
project = foo

dependencies[] = multisite_config
registry_autoload[] = PSR-4
</pre>
<hr />
<strong>foo/src/Config.php will look like:</strong>

<pre>
namespace %Drupal\\foo;

use %Drupal\\multisite_config\\ConfigBase;

class Config extends ConfigBase {

  public function someMethod($arg) {
    return $arg;
  }

}
</pre>
<hr />
<strong>Service can then be accessed by calling:</strong>

<code>
$foo = multisite_config_service('foo')->someMethod('foo');
</code>

