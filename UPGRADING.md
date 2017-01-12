# NextEuropa Core platform version 2.3.0

## Content of the release

 The release focuses on few improvements.
 [The full change log is available here](CHANGELOG.md)
 
  * Web frontend cache control in Drupal using varnish
  * First steps in performance improvements using aggregation and CDN
  * DGT connector as a feature 
  * Tracked changes as a feature
  * Contact module is no longer mandatory but is available as a feature
  * Feature set standard as a feature
 

## Site Owners : What you need to know before you upgrade from 2.2 to 2.3:

### Modules removed and steps to upgrade

The following modules have been removed from the stack
  - css_injector
  - js_injector

The following modules has been removed from the *hard config*:
  - contact
  - ckeditor_lite
  - apachesolr_search

This means they are still available but you can now disable them for once if 
you don't need them.
  
#### Contact
If you need to use the module contact, you can either:
- Enable the feature 'Contact'
- Add the module 'contact' as a dependency to your code

If you do not need to use that module, you can either:
- Add a hook_update in your code, where you disable it
- If you have no custom code, request Maintenance team to disable the module.

Only after processing one of these steps will your site be considered as 
'upgraded'.

#### ckeditor_lite
To use the module ckeditor_lite, you can either:
- Enable the feature 'Tracked changes'
- Add the module 'ckeditor_lite' as a dependency to your code

If you do not need to use that module, you can either:
- Add a hook_update in your code, where you disable it (after making sure there 
are no pending tracked changes on your site)
- Disable the feature set 'Tracked changes'

Note:
You won't be able to disable the feature 'Tracked changes' if your have 
unvalidated tracked changes on your site. Instead you'll be prompted with a 
list of pages where you first need to accept/reject changes.
[Before doing anything, pleas consult the README file!](nexteuropa_trackedchanges/README.md)

#### apachesolr_search

If you need to use the module apachesolr_search, you can :
- Add the module 'apachesolr_search' as a dependency to your code. 
 *Please make sure the dependency is added before any dependency that includes 
 a call to multisite_drupal_toolbox_config_solr_bundle*

If you do not need to use that module, you can:
- Add a hook_update in your code, where you disable it 
  Make sure to also remove all calls to 
  multisite_drupal_toolbox_config_solr_bundle

Only after processing one of these steps will your site be considered as 
'upgraded'.

#### css_injector and js_injector have been removed

In relation to ticket NEPT-36 js_injector and css_injector modules have been 
removed.
If you were using this feature, please read our upgrade recommendation:

```
 Move the code added into these module into css or js files.
 Link these files from inside the info file of your theme, or inside your module using one of these notations :
```

 For css
```
 A- If the css is used by the theme, copy the css rules in a css stylesheet and include it in the theme.info file

   stylesheets[all][] = "css/mystylesheet.css"

   If you are using a theme provided by the core platform, you need to create a subtheme in order to add an extra css file.
   Read https://www.drupal.org/docs/7/theming/creating-a-sub-theme

  B- If the css is used by a module (specific css required by a specific functionality), the css file should be added to the module.

  There are several methods
 
    1- To attach css to just a form, use :
http://api.drupal.org/api/drupal/developer!topics!forms_api_reference.html/7#attached

     $form'#attached'['css'] = array(
       drupal_get_path('module', 'yourmodulename') . '/css/pathtomyfile.css',
     );

    2- To attach css to the whole website when the module is active, add this 
    to the module info file:

      stylesheets[all][] = css/pathtomyfile.css

    3- To add the file dynamically in a given function call, add this to your 
    code:

      drupal_add_css($path);
```
For javascript
```
  1- To attach js to just a form, use :
http://api.drupal.org/api/drupal/developer!topics!forms_api_reference.html/7#attached

    $form'#attached'['js'] = array(
      drupal_get_path('module', 'yourmodulename') . '/js/pathtomyfile.js',
    );

  2- To attach js to the whole website when the module is active, add this to the module info file:
    
    scripts[] = "js/myjavascript.js"

  3- To add the file dynamically in a given function call, add this to your code:

    drupal_add_js($path);
 
Please also read
https://api.drupal.org/api/drupal/includes!common.inc/function/drupal_process_attached/7.x
```
Only after processing one of these steps will your site be considered as 
'upgraded'.

### CEM role has been created

A new user role has been added, only this role can enable DGT connector feature.
 
After upgrading, the feature "nexteuropa_feature_set" will be enabled.

A new set of permission is defined there for CEM user role, that is in charge
of enabling the DGT Connector feature.

You cannot disable "nexteuropa_feature_set", an additional QA check will be 
 added to block code that tries to disable it.

### New DGT Connector feature

 A new feature 'DGT connector' will be enabled for Websites that are using 
the DGT connector (poetry) services.

 When upgrading to 2.3.0, CEM should fill in the new field "website-identifier".
 
 The value of this field will be appended to all translation job requests sent 
 to DGT
 
* Examples of site identifiers:
  - NE-CMS: Creative europe 
  - NE-CMS: EC Europa Info 
  - NE-CMS: Erasmus+ 
  - NE-CMS: Organic farming
  - NE-CMS: EUROPA EU
  - NE-CMS: Agriculture
  - NE-CMS: EC Belgium
  - NE-CMS: N-Lex
  - NE-CMS: EC Ireland

Please note that if you are using the DGT connector, some test translations 
should be sent against the connector playground environment after upgrading, to
ensure the settings have been correctly migrated.

***
## Devops : How to upgrade

### Before upgrading to 2.3.0

*Before moving a subsite to the new code base*, you need to run the following
 drush commands on the site you will upgrade in 2.2 :
 
 * For ticket NEPT-36

```
$ drush dis css_injector js_injector -y
$ drush pm-uninstall css_injector js_injector -y

```

#### common.settings.php

  * For ticket NEPT-182
  
  *Before running the first upgrade to 2.3.0*, you have to set the endpoints in 
  the common.settings.php file in 2.3.0
  
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

#### flexible_purge
In relation to ticket MULTISITE-14601, please remove from 2.3.0 the duplicated 
'flexible_purge' module that can be found inside sites/all/modules


### Once above steps are completed, proceed with the subsite upgrade.

Then run the following commands:

```
$ drush rr
$ drush updb
```

You will get the following warnings

```
The following module has moved within the file system: 
multisite_drupal_features_set_standard 
```

```
The following module has moved within the file system: tmgmt_poetry. 
```

## After updb has run edit settings.php of the upgraded site
 
 -For ticket NEPT-182
 
 For each subsite upgrade that was already using the DGT connector , you need 
 to remove the  variable array 'poetry_service' from the setttings.php file
 
 Write down the values of 'callback_user', 'callback_password', 'poetry_user',
   'poetry_password', you may need them for next step.
  
 ```
 $conf['poetry_service'] = array(
  [...]
 );
 ```
 
 Once the upgrade is complete, CEM needs to be informed that the 
 "website_identifier" value must be set.
 In order to communicate this to CEM, please create a ticket in MULTISITE and 
 assign it to user "Support SMT Jira".

## Manual check

- Check the admin/reports/status_en for red flags, especially on the DGT 
connector lines.

If you see *"The local connector credentials are not set. Please contact 
COMM EUROPA MANAGEMENT."* it means there was an issue in the updb. You will 
need to insert into the connector the credential info that were previously in 
the settings.php file here 
admin/config/regional/tmgmt_translator/manage/poetry_en .



