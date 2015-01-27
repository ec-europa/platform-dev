Tests for NextEuropa
====================

This folder contains tests for the NextEuropa profile.

## Installing dependencies

The first step is to install the dependencies using Composer:
```
$ cd tests
$ composer install
```

## Configuring your environment

Behat depends on a few configurations which are environment specific, such as
the base URL and the root path of the Drupal installation. These are stored as a
JSON array in the $BEHAT_PARAMS environment variable. Behat will look for this
variable and use that in addition to the settings in the `behat.yml` file.

Setting the environment variable can be done in two ways: either manually or by
executing the `config.sh` script.

### Manual configuration

Execute the following line, making sure to replace "http://localhost" and
"/var/www/myproject" with your own base URL and root path:
```
$ export BEHAT_PARAMS='{"extensions":{"Behat\\MinkExtension":{"base_url":"http://localhost"},"Drupal\\DrupalExtension":{"drupal":{"drupal_root":"/var/www/myproject"}}}}'
```

### Automatic configuration

First execute the `config.sh` script. This will ask you for your base URL and
root path:
```
$ ./config.sh
```

The script will then generate the configuration and save this to the file
`config.local`. Once you have this file on your system you can source it to set
the environment variable:
```
$ source config.local
```

## Running the tests

Finally run the tests:
```
$ ./bin/behat
```
