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


## Once above is complete, proceed with the subsite upgrade.

Then run the following commands, in relation to 
- NEPT-182
- NEPT-102


```
$ drush updb
$ drush cc all
$ drush rr
```

You will get the following warnings

```
The following module has moved within the file system: 
multisite_drupal_features_set_standard 
```

```
The following module has moved within the file system: tmgmt_poetry. 
```

## After update.php has run edit settings.php
 
 -For ticket NEPT-182
 
 For each subsite upgrade that was already using , you need to remove the 
 variable array 'poetry_service' from the setttings.php file
 Write down the values of 'callback_user', 'callback_password', 'poetry_user',
   'poetry_password', you may need them for next step.
  
 ```
 $conf['poetry_service'] = array(
  [...]
 );
 ```
 
 CEM needs to be informed that the "website_identifier" value must be set.

## Manual configuration

- Check the admin/reports/status_en for red flags, especially on the DGT 
connector lines.
If you see "The local connector credentials are not set. Please contact 
COMM EUROPA MANAGEMENT." you need to insert into the connector the credential 
info that were previously in the settings.php file.


Go to admin/config/regional/tmgmt_translator/manage/poetry_en and fill it the 
values you saved in previous step.


## Manual testing on playgound
- If the subsite is using the DGT connector, some test translations should be 
sent against the connector playground environment.


## Recommendation
For ticket NEPT-36 please read [our recommendation on Jira](https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-36)

