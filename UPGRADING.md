# NextEuropa Core platform version 2.4.0

## Content of the release

 The release focuses on few improvements.
 [The full change log is available here](CHANGELOG.md)
 
  * TODO: add changelog.
 

## Site Owners : What you need to know before you upgrade from 2.3 to 2.4:

### Module changes and steps to upgrade

The following modules have been moved
  - media_avportal

The following modules have been removed from the stack
  - node_export

The following modules has been removed from the *hard config*:
  - TODO: add list of removed modules

This means they are still available but you can now disable them for once if 
you don't need them.
  

The following modules have been upgraded and bring significant changes:

 - entity_translation
   The module updates include a new translation option for vocabularies and a change in the active language api.

***
## Devops : How to upgrade

### Before upgrading to 2.4.0

*Before moving a subsite to the new code base*, you need to perform the following steps:

#### Uninstall node_export module

 * From ticket NEPT-591

```
$ drush dis node_export -y
$ drush pmu node_export -y

```

#### Handle schedulled dates for articles

 * From ticket NEPT-1025

Check if there are articles having scheduled publish or unpublish dates.
If so, take note of the dates as it will be necessary to manually set them again.


### After-upgrade steps

Once the above steps are completed and the site is in the 2.4.0 codebase,
proceed with the following steps:

#### Update database

  Run the following commands:

```
$ drush rr
$ drush updb
```

  You will get the following warnings

```
The following module has moved within the file system: media_avportal. 
```

#### Manual check

  * Check the admin/reports/status_en for red flags.

#### Handle schedulled dates for articles

 * From ticket NEPT-1025

See related step in Before upgrade steps.
If there were articles having scheduled publish or unpublish dates, set them again.
