# Drush Updater: Automated Drupal updates

[![Build Status](https://travis-ci.org/jfhovinne/updater.svg?branch=8.x-1.x)](https://travis-ci.org/jfhovinne/updater)

A Drush command to update a website instance by executing available "updaters".

An updater is a PHP function which is executed during execution of the Drush `update-website` command.
The Drush command keeps track of updaters already executed, so they are not executed twice on the same Drupal instance.

Updaters have access to usual Drupal APIs and other Drush commands.

This is useful when you want to test and automate your updates and deployments, e.g. after developing a new feature, since updaters are simple PHP scripts that can be included in your feature branches.

Example usage is putting the site in maintenance mode, enabling a module, creating taxonomy terms, publishing a page and putting the site back online.

Code is lightweight and integrates well in a continuous integration / continuous deployment workflow.
It is an alternative to available Drupal update/deployment tools, as it does not require a module to be created, and is Drupal 7 and 8 compatible already.

Project page on drupal.org: [Updater](https://www.drupal.org/project/updater)

## Installation

### Using Drush

```
drush dl updater
cd /path/to/updater
composer install --no-dev
```

### Using Composer

From the website root:

```
composer require jfhovinne/updater
drush cc drush
```

## Usage

```php
drush update-website --path=/path/to/my/updaters
```

In the above example, the `drush update-website` command will search for updaters in the `/path/to/my/updaters` directory.
It will search for files with filenames starting with `updater-` and ending with `.php`, then for functions having the same name as the filename, adding `_update` in the end.

Filenames are sorted alphabetically, so `updater-0001-test.php` will be loaded - and its updater executed - before `updater-0002-another-test.php`.
There is only one updater per file, while each file can contain other PHP functions.

The default path to search for updaters is `{DRUPAL_ROOT}/sites/all/drush/updaters`.

You can also point to a specific updater file, for instance:

```php
drush update-website --path=/path/to/my/updaters/updater-0001-test.php
```

### Examples

If file `/path/to/my/updaters/updater-0001-test.php` contains the function `updater_0001_test_update`, this function will be executed.

```php
<?php

function updater_0001_test_update() {
  // Create the webmaster role and assign it the 'administer nodes' permission
  drush_invoke_process('@self', 'role-create', array('webmaster'));
  drush_invoke_process('@self', 'role-add-perm', array('webmaster', 'administer nodes'));
}
```

If file `/path/to/my/updaters/updater-0002-another-test.php` contains the function `updater_0002_another_test_update`, this function will be executed.

```php
<?php

function updater_0002_another_test_update() {
  // Drupal 7 only
  // Put the site in maintenance mode, add terms to the Tags vocabulary
  // then disable the maintenance mode
  drush_invoke_process('@self', 'vset', array('maintenance_mode', '1'));

  $vocab = taxonomy_vocabulary_machine_name_load('tags');
  $values = array(
    'module',
    'theme',
    'distribution'
  );

  foreach($values as $value) {
    $term = (object) array(
      'name' => $value,
      'vid' => $vocab->vid,
    );
    taxonomy_term_save($term);
  }
  drush_invoke_process('@self', 'vset', array('maintenance_mode', '0'));
}
```

If you want to test an updater, and not set it as executed, the update function should return FALSE.

```php
<?php

function updater_0003_testing_update() {
  drush_invoke_process('@self', 'cset', array(
    'system.site',
    'page.front',
    '/node/1',
  ));
  return FALSE;
}
```

More updater examples can be found in the [testing project](https://github.com/jfhovinne/updater-testing/tree/master/src/updaters).
