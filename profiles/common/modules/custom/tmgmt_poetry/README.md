Summary
=======

The TMGMT Poetry module allows the creation of translation managers
that make use of the European Commission Poetry translation services
(served by DGT).


Installation
============

- Install as usual, see http://drupal.org/node/70151 for further information.
- The settings.php of your project must contain the following variables filled
  with appropriate values:

```php
    $conf['poetry_service'] = array(
      'address' => 'http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'method' => 'requestService',
      'callback_user' => 'Callback',
      'callback_password' => 'CallbackPWD',
      'poetry_user' => 'Poetry',
      'poetry_password' => 'PoetryPWD',
    );
```

Manual test of Poetry translator
================================

To manually test the Poetry translator plugin without accessing the actual
DGT service enable the follow the steps below:

1. Enable the ```tmgmt_poetry_test``` module.
2. Set the address property to the newly available test endpoint:
```php
    $conf['poetry_service'] = array(
      'address' => 'http://your.local.base.url/profiles/multisite_drupal_standard/modules/custom/tmgmt_poetry/tests/tmgmt_poetry_test.wsdl',
      'method' => 'requestService',
      'callback_user' => 'Poetry',
      'callback_password' => 'PoetryPWD',
    );
```
   Notice that this refers to a Multisite standard profile, change relevant
   portion if necessary.
3. Request a new translation using the "TMGMT Poetry: Test translator" translator.
