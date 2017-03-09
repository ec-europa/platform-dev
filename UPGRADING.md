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
  - TODO: add list of removed modules

The following modules has been removed from the *hard config*:
  - TODO: add list of removed modules

This means they are still available but you can now disable them for once if 
you don't need them.
  

***
## Devops : How to upgrade

### Before upgrading to 2.4.0

*Before moving a subsite to the new code base*, you need to perform the following steps:

#### Step 1

  TODO: Add step descriptions

 * From ticket NEPT-391

```
$ drush dis nexteuropa_varnish flexible_purge  -y
$ drush pm-uninstall nexteuropa_varnish  -y
$ drush pm-uninstall flexible_purge  -y

```

 * From ticket NEPT-391

```
$ drush dis nexteuropa_varnish flexible_purge  -y
$ drush pm-uninstall nexteuropa_varnish  -y
$ drush pm-uninstall flexible_purge  -y

```

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
