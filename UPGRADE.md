# NextEuropa Core platform version 2.3.0

## Content of the release

 The release focuses on few improvements.
 [The full change log is available here](CHANGELOG.md)
 
  * Web frontend cache control in Drupal using varnish
  * First steps in performance improvements using aggregation and CDN
  * DGT connector as a feature 
  * Tracked changes as a feature
 

## Before you upgrade from 2.2 to 2.3

### Drush commands

Before moving a subsite to the new code base, you need to run the following
 drush commands:
 
 *For ticket NEPT-36

```
$ drush dis css_injector js_injector -y
$ drush pm-uninstall css_injector js_injector -y

```

## common.settings.php

  -For ticket NEPT-182
  *Before running the first upgrade to 2.3.0*, you have to set the endpoints in 
  the common.settings.php file
  
  Adding to the common.settings.php file is only to be done once before the 
  first site upgrade.
  
  Here is the information that needs to be added in common.settings.php *on 
 playground*

```
  $conf['poetry_service'] = array(
       'address' => 'http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
       'method' => 'requestService',
     );

```
 
  Here is the information that needs to be added in common.settings.php *on 
 production*

```
  $conf['poetry_service'] = array(
      'address' => 'http://intragate.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'method' => 'requestService',
    );

```

## settings.php
 
 -For ticket NEPT-182
 
 For each subsite upgrade, you need to remove the variable array 
 'poetry_service' from the setttings.php file
 Write down the values of 'callback_user', 'callback_password', 'poetry_user',
   'poetry_password', you may need them for next step.
  
 ```
 $conf['poetry_service'] = array(
  [...]
 );
 ```
 
## Once above is complete, proceed with the subsite upgrade.

Then run the following commands, in relation to 
- NEPT-182
- NEPT-102


```
$ drush updb
$ drush cc all
$ drush rr
```

## Manual testing on playgound

- Check the admin/reports/status_en for red flags, especially on the DGT 
connector lines.
- If the subsite is using the DGT connector, some test translations should be 
sent against the connector playground environment.

