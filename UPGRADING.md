# NextEuropa Core platform version 2.4.0

## Content of the release

 The release focuses on few improvements.
 [The full change log is available here](https://github.com/ec-europa/platform-dev/releases/download/2.4.0/CHANGELOG.md)
 
  * Files entity metadata ("description", "caption") are translatable
  * The theme for the status messages is overridable
  * The access to the alert message for administrators is managed with the "view alert message" permission
  * The "Ec_resp" theme is only enabled at the platform installation; the active theme can be changed later
  * NextEuropa Last Update module: Provides a common point to retrieve the last update date for a page. 
  * Apache Solr: Administrator role can modify the Module configuration through the dedicated admin interface
  * Media WYSIWYG: Possibility to add a Media in a WYSIWYG field without being embedded in a container. <br />
    It is obtained by selecting the "WYSIWYG" display mode in the "Add Media" pop-up
  * DGT Connector: The requested delivery date is always displayed in any display of the translation request (list or view)
  * Publishing scheduler: the scheduler mechanism for the "Article" content type has been aligned on the "Basic page" one
  * Administration language negotiation: [contributed module](https://www.drupal.org/project/administration_language_negotiation) 
    is now available in the platform.

## Site Owners: What you need to know before you upgrade from 2.3 to 2.4:

### Module changes and steps to upgrade

The following modules have been moved
  - media_avportal, the platform uses the [contributed version](https://www.drupal.org/project/media_avportal)

The following modules have been removed from the stack
  - node_export

The following modules have been upgraded and bring significant changes:

 - entity_translation
   The module updates include a new translation option for vocabularies and a change in the active language api.
 - libraries
   The module update includes an interface listing the registered libraries
 - media
   The module is officially stable. Its upgrade requires an upgrade of file_entity and entity_translation that is included in this release
 - workbench_moderation
   The platform moves to the version 3 of the module which implements a new logic to manage moderated revisions.<br />
   This logic based on the [Drafty module](https://www.drupal.org/project/drafty)

### Scheduler mechanism of the Article content

In the previous version, the "Article" content type used a custom scheduling mechanism that is incompatible with Workbench moderation.

Then, it has been replaced by the one supplied by the "[Scheduler](https://www.drupal.org/project/scheduler)" and "[Scheduler Workbench Integration](https://www.drupal.org/project/scheduler_workbench)" modules.

The impacts on the existing sites are:

 1. Custom fields, I.E. "field_article_publication_date" and "field_article_unpublish_on", attached to the custom scheduler has been removed from the "Article" content type
 2. Scheduled publishing/unpublishing set on "articles" before the upgrade will be lost and are to be defined again after the upgrade. 
 
#### Recommendations

**Before the upgrade**, identify all articles with a scheduled publishing/unpublishing.

**After the upgrade**, Re-define the scheduling parameters for each listed "article" as follow:

  1. Edit the article;
  2. Click on the "Metadata" vertical tab;
  3. Click on "Scheduling options";
  4. Fill "Publish on" and/or "Unpublish on" fields;
  5. Save the content.

### Administration language negotiation

The module is available but not enabled during the upgrade. 

So, it must be explicitly enabled on the site.  


## Devops: How to upgrade

### Before upgrading to 2.4.0

**Before moving a subsite to the new code base**, you need to perform the following steps:

 * From **ticket NEPT-1025**:
   - Ensuring that site owners have taken note of the "Scheduler mechanism of the Article content" section (see previous chapter).
 

 * From **ticket NEPT-591**:

```
$ drush dis node_export -y
$ drush pmu node_export -y

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
