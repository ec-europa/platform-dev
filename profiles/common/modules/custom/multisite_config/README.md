/*! @mainpage Multisite Configuration API

@section desc_sec Description

Multisite configuration API is provided by core team, to allow every developers on Multisite to access common helper tools.

@section how_read_sec How to read that API?

In <a href="namespaces.html"><strong>Namespaces</strong></a> section, you can find the list of currently avilable classes. By opening the corresponding Config file you get a detailed list of available functions for that class.

In <a href="functions.html"><strong>Data fields</strong></a> section, you can find a complete list of available functions.

@section how_use_sec How to use and improve that API?

Multisite Configuration API classes extends <code>\\%Drupal\\multisite_config\\ConfigBase</code> class and are namespaced by <code>\\%Drupal\\:module</code>, while the actual class is always named <code>Config</code>.

To use that API in a third-party module, you have to:
-# Add <code>registry_autoload[] = PSR-4</code> to .info file
-# Call any function you want by using its class name (see example)

To add new configuration API you have to:
-# Edit a configuration class described above under <code>./src</code> directory (or create a new one when needed)
-# Update API documentation (or request for update)

@subsection example_subsec Example

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
<hr>
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
<hr>
<strong>Service can then be accessed by calling:</strong>

<code>
$foo = multisite_config_service('foo')->someMethod('foo');
</code>

@section how_ex_sec How to add examples?

For a better understanding, it is recomanded to add example for each usable function.<br>
Three steps are required to add example to a class:
- <strong>create a file</strong> called <em>example_[class name].cpp</em> in the same repository of your class' Config file<br>
Example:<br>
<code>
example_wysiwyg.cpp file, located in multisite_config\\lib\\Drupal\\wysiwyg
</code>

- in Config file, <strong>add \@example tag</strong> to indicate which file contains example for it.<br>
Example:<br>
<code>
\@example example_[class name].cpp<br>
This is an example of how to use the wysiwyg class.
</code>

- inside \@details tag, <strong>add \@includes tag</strong> to include example file<br>
Example:<br>
<code>
\@brief Helper functions to manage WYSIWYG<br>
\@details @include example_[class name].cpp
</code>

For a full example, check wysiwyg Config file
