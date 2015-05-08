Multisite Configuration API
===========================

Multisite Configuration API classes extends \Drupal\multisite_config\ConfigBase class and
are namespaced by ```\Drupal\:module```, while the actual class is always named ```Config```.

Third-party modules can provide their own configuration API by:

1. Adding ```registry_autoload[] = PSR-4``` to their .info file
2. Creating the configuration class described above under ```./src``` directory.

For example, given a module named ```foo```:

```foo.info``` will look like:

```
name = Foo module
description = Foo module description.
core = 7.x
version = 7.x-1.0-dev
project = foo

dependencies[] = multisite_config
registry_autoload[] = PSR-4
```

```foo/src/Config.php``` will look like:

```
<?php

/**
 * @file
 * Contains \Drupal\foo\Config
 */

namespace Drupal\foo;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  public function someMethod($arg) {
    return $arg;
  }

}

```

Service can then be accessed by calling:

```
$foo = multisite_config_service('foo')->someMethod('foo');
```

