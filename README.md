# NextEuropa

## Requirements

* Composer
* PHP Phar extension

## Install build system

Before we can build the NextEuropa platform we need to install the build system
itself. This can be done using composer:

```
$ composer install
```

## Customize build properties

Create a new file in the root of the project named `build.properties.local`
using your favourite text editor:

```
$ vim build.properties.local
```

This file will contain configuration which is unique to your development
machine. This is mainly useful for specifying your database credentials and the
username and password of the Drupal admin user so they can be used during the
installation.

Because these settings are personal they should not be shared with the rest of
the team. Make sure you never commit this file!

All options you can use can be found in the `build.properties.dist` file. Just
copy the lines you want to override and change their values. For example:

```
# The location of the Composer binary.
composer.bin = /usr/bin/composer

# The install profile to use.
platform.profile.name = multisite_drupal_standard

# Database settings.
drupal.db.name = my_database
drupal.db.user = root
drupal.db.password = hunter2

# Admin user.
drupal.admin.username = admin
drupal.admin.password = admin

# The base URL to use in Behat tests.
behat.base_url = http://nexteuropa.local
```

## Listing the available build commands

You can get a list of all the available Phing build commands ("targets") with a
short description of each target with the following command:

```
$ ./bin/phing
```

## Building a local development environment

```
$ ./bin/phing build-platform-dev
$ ./bin/phing install-platform
```

## Running Behat tests

The Behat test suite is located in the `tests/` folder. The easiest way to run
them is by going into this folder and executing the Behat binary which is
located in the `bin/` folder:

```
$ cd tests/
$ ../bin/behat
```

For your convenience a symlink to the Behat executable is present in the tests/
folder, so you can also run the tests like this:

```
$ cd tests/
$ ./behat
```

If you want to execute a single test, just provide the path to the test as an
argument. The tests are located in `tests/features/`:

```
$ cd tests/
$ ./behat features/content_editing.feature
```

If you have installed the development version (using the `build-platform-dev`
build target) then the tests can also be executed from the root folder of the
build:

```
$ cd build/
$ ../bin/behat
```
