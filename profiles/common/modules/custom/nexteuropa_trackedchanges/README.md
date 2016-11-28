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
An configuration page allowing to:
- Enable/disable the "change tracking" buttons in the different WYSIWYG profiles;
- Control the display and the activation of buttons on the content creation/edit form;

## Possibilities to define a workflow for tracked changes workflow. 

It is possible to define when tracked changes must be validated before:
- Changing the content status to "Published", in the case of the default Drupal publishing process;
- Saving a new content revision with a new moderation state, in the case of a Workbench moderation workflow.
 

[Go to top](#table-of-content)

# Configuration


## Tracked changes buttons settings: availability of change tracking buttons

The "WYSIWYG tracked changes" form accessible via the admin menu (Configuration / Content Authoring / WYSIWYG profiles
/ WYSIWYG tracked changes / Tracked changes buttons settings).

It allows configuring 3 items:
1. Which WYSIWYG profile(s) must have Change Tracking buttons available or not. 
By clicking on the "enable tracked changes buttons" link, you add the 6 "Change Tracking" buttons.
2. The accessibility of "Change Tracking" buttons on the content **creation** forms;
3. The activation of the change tracking on all WYSIWYG fields of the content **edit** forms.<br />
**Note**: This setting overwrites the configuration of CKEditor LITE on which this module is based.  
The CKEditor LITE one allows forcing the activation of change tracking on all WYSIWYG fields in all cases. 
Here, the tracking change can be activated on the edit form; even if it is no set like that for CKEditor LITE.

### WARNING

The interface allows removing buttons from WYSIWYG profiles but it does it only if no WYSIWYG field that uses
this profile does no contain any tracked changes.
If tracked changes exist, the removing is blocked until all of them are accepted or rejected.

### RECOMMENDATIONS

- Avoid to make accessible change tracking buttons on content creation form. The change tracking functions does not work 
correctly when it is activated on a field that has no default value.
- The function can meet some running time problem on some browser like IE11 when the change tracking is enabled on 
several WYSIWYG fields of the same entity (content). <br />
Try as much as possible to avoid enabling it on too much fields of the same entity by default.
  


## Tracked changes workflow settings

The interface allows to set publishing states where the content saving must be blocked when tracked changes are detected
in it.

It has 3 parts:
1. "Block if status is true": it concerns contents that do not follow the workbench moderation workflow.<br />
When it is checked, it will be impossible to save a content with the Published status if tracked changes have been
detected in its WYSIWYG fields.
2. "Block the saving for these Workbench Moderation states": it concerns contents that follow the workbench moderation 
workflow.<br />
When a moderation state is checked, it will be impossible to save a content in this moderation state if tracked changes 
have been detected in its WYSIWYG fields.
3. "Tracked changes table refresh frequency": it is not directly related to the tracked changes workflow but to the table
listing entities (contents + other Drupal entities) containing tracked changes.<br />
It sets the frequency in seconds for refreshing data displayed in this table.

### RECOMMENDATIONS

- Tracked changes are hidden before displaying published contents. It happens the display is not correct when the HTML structure 
of a WYSIWYG field is complex. It is a limitation of the CKEditor LITE module.<br />
Then, it is recommended to block the possibility to publishing content having tracked changes. 
- For the same reason as for published contents, it is recommended to block the saving to the "Validated" moderation state if
Poetry is used to translated contents.


[Go to top](#table-of-content)

# Disabling

As for the installation, there are 2 ways for disabling and uninstalling the feature:
1. Like any Drupal modules; via the "Modules" admin page or with the Drush command);
2. Like a "Feature set" through the Feature set admin page (path: admin/structure/feature-set_en).

## WARNING

The disabling is blocked if tracked changes are detected in the lastest draft revision of a content or in any 
other entities.

It is so until all tracked changes are accepted or rejected in all entities.

[Go to top](#table-of-content)