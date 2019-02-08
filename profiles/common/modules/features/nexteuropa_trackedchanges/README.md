The "NextEuropa Tracked Changes" feature provides editorial teams with change tracking capabilities in 
WYSIWYG fields.


Table of content:
=================
- [Installation](#installation)
- [Proposed features](#features)
- [Configuration](#configuration)
- [Disabling](#disabling)

# Installation

The feature is proposed through a Drupal custom module and is available with the NextEuropa platform.

They are 2 ways to activate the feature:
1. Like any Drupal modules; via the "Modules" admin page or with the Drush command);
2. Like a "Feature set" through the Feature set admin page (path: admin/structure/feature-set_en).<br />
Then, Enable the "WYSIWYG Tracked Changes" feature and click on the "Validate" button.

[Go to top](#table-of-content)

# Proposed features

Beside the change tracking function, it proposes different features:

## An additional WYSIWYG profile 

It is called "Full HTML + Change tracking" that is a clone of the "Full HTML" profile
supplied with the NextEuropa platform with the "change tracking" buttons of the 
[CKEditor LITE](https://www.drupal.org/project/ckeditor_lite) project;
 
## Change tracking button configuration
A configuration page allowing to:
- Enable/disable the "change tracking" buttons in the different WYSIWYG profiles;
- Control the display and the activation of these buttons on the content creation/edit form;

## Possibilities to define a workflow for tracked changes workflow. 

It is possible to define when tracked changes **must** be validated before:
- Changing the content status to "Published", in the case of the default Drupal publishing process;
- Saving a new content revision with a new moderation state, in the case of a Workbench moderation workflow.

## "Content tracked changes" page

A page accessible by content administrator (permission: "Administer content" + "Use Highlight changes block") that 
allows consulting the list of entities (content but also other entity types) where the system has detected tracked changes.

From this page, the user can access to the listed entity page or to one of its translations.

### Note

For sites that had already the change tracking activate, the first time that this page is accessed, the system will 
scan all content entities in order to detect all tracked changes that could already exist. The scan results is used to
generate the list.

After, the scanning process will happen during the Site Drupal cron executions, every hour. The scanning frequency inside
cron executions can be changed through the module configuration (see 
[Configure the tracked changes scanning process](#configure-the-tracked-changes-scanning-process) section).
 

[Go to top](#table-of-content)

# Configuration


## Tracked changes buttons settings: availability of change tracking buttons

The "WYSIWYG tracked changes" form accessible via the admin menu (Configuration / Content Authoring / WYSIWYG profiles
/ WYSIWYG tracked changes / Tracked changes buttons settings).

It allows configuring 3 items:
1. Which WYSIWYG profile(s) must have Change Tracking buttons available or not. 
By clicking on the "enable tracked changes buttons" link, you add the 6 "Change Tracking" buttons to the WYSIWYG toolbar.
2. The accessibility of "Change Tracking" buttons on the content **creation** forms;
3. The activation of the change tracking on all WYSIWYG fields of the content **edit** forms.<br />
**Note**: This setting overwrites the configuration of CKEditor LITE on which this module is based.  
The CKEditor LITE one allows forcing the activation of change tracking on all WYSIWYG fields in all cases. 
Here, the tracking change can be activated on the edit form; even if it is no set like that for CKEditor LITE.

### WARNING

The interface allows removing buttons from WYSIWYG profiles but it does it only if no WYSIWYG field that uses
this profile contain any tracked changes.
If tracked changes exist, the action is blocked until all of them are accepted or rejected.

### RECOMMENDATIONS

- Avoid making accessible change tracking buttons on content creation form. The change tracking functions does not work 
correctly when it is activated on a field that has no default value.<br />
In the NextEuropa platform, this option is checked as is in its configuration.
- The function can meet some running time problem on some browser like IE11 when the change tracking is enabled on 
several WYSIWYG fields of the same entity (content). <br />
Try as much as possible to avoid enabling it on too much fields of the same entity by default.
  


## Tracked changes workflow settings

The "WYSIWYG tracked changes" form accessible via the admin menu (Configuration / Content Authoring / WYSIWYG profiles
/ WYSIWYG tracked changes / Tracked changes workflow settings).

The interface allows to set moderation states where the content saving must be blocked when tracked changes are detected
in it.

It has 3 parts:
1. "Block if status is true": it concerns contents that do not follow the workbench moderation workflow.<br />
When it is checked, it will be impossible to save a content with the "Published" status if tracked changes have been
detected in its WYSIWYG fields.
2. "Block the saving for these Workbench Moderation states": it concerns contents that follow the workbench moderation 
workflow.<br />
When a moderation state is checked, it will be impossible to save a content in this moderation state if tracked changes 
have been detected in its WYSIWYG fields.
3. "Tracked changes table refresh frequency": it is not directly related to the tracked changes workflow but to the table
listing entities (contents + other Drupal entities) containing tracked changes.<br />
It sets the frequency in seconds for refreshing data displayed in this table.

### Note

For working with other features of the NextEuropa platform, "Block if status is true" and the "Validated" and "Published" states
of "Block the saving for these Workbench Moderation states" are checked by default for the following reasons:

- With CKEditor LITE, tracked changes are hidden before displaying published contents. The display can be incorrect when the 
HTML structure of a WYSIWYG field is complex. It is a limitation of the CKEditor LITE module.<br />
This is reason why the "Block if status is true" and the "Published" state of "Block the saving for these Workbench Moderation states" 
are checked by default in the NextEuropa platform settings.
- Tracked changes are not fully supported by the Poetry translation system. For this reason, the "Validated" state of "Block the 
saving for these Workbench Moderation states" is also checked by default in the NextEuropa platform settings.

## Configure the tracked changes scanning process

The "WYSIWYG tracked changes" form accessible via the admin menu (Configuration / Content Authoring / WYSIWYG profiles
/ WYSIWYG tracked changes / Tracked changes logs status).

During the Drupal cron execution, entities that are not of the node types are scanned in order to detected any tracked changes in
their WYSIWYG fields. The results will feed the list displayed ["Content tracked changes"](#content-tracked-changes-page) page.
 
The form allows:

- Setting the frequency in seconds of the scanning execution inside Drupal cron execution.<br />
Ex.: If the value is 3600 and Drupal cron are executed every 30 minutes, the scanning will be executed every 2 cron executions.
- Forcing the scanning execution by clicking on the "Force scanning".


[Go to top](#table-of-content)

# Disabling

As for the installation, there are 2 ways for disabling and uninstalling the feature:
1. Like any Drupal modules; via the "Modules" admin page or with the Drush command);
2. Like a "Feature set" through the Feature set admin page (path: admin/structure/feature-set_en).

## WARNING

### Disabling via the web interface under condition

The disabling action is blocked if tracked changes are detected in the latest draft revision of a content or in any 
other entities.

It is so until all tracked changes are accepted or rejected in all entities.

### Disabling via Drush or via a hook_update are not recommended.

It is still possible to disable the module through Drush but it is not recommended because like
all modules related to WYSIWYG features, the Drush disabling process does not allow implementing check on field values
in order to stop the disabling or to clean values of change tracking tags.

If you disabling the module without ensuring all tracked changes have been cleaned, the related HTML tags (&lt;span&gt;) will 
remain and could cause bad content display.

If you use a hook_update to disable it, please integrate in it a process that scans WYSIWYG fields to detect those kind of tags,
and that implements appropriate actions (Disabling stop or Field value cleaning).

### After disabling the feature

After disabling the feature, you will notice that the "Full HTML + Change tracking" text format is still active but renamed
"**Full HTML (Change tracking feature disabled)**".

Doing so helps to:
 - Avoid display problems because of the text format missing 
 - Leave the time to choose how to deal with fields where 
this text format was set.

[Go to top](#table-of-content)
