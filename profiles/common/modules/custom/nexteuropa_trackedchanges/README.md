The "NextEuropa Tracked Changes" feature provides editorial teams with change tracking capabilities in 
WYSIWYG fields.


Table of content:
=================
- [Installation](#installation)
- [Proposed features](#features)
- [Configuration](#configuration)
- [Disbaling](#disabling)

# Installation

The feature is proposed through a Drupal custom module and is available with the NextEuropa platform.

They are 2 ways to activate the feature:
1. Like any Drupal modules (Via the "Modules" admin page or with the Drush command);
2. Like a "Feature set" through the Feature set admin page (path: admin/structure/feature-set_en).<br />
Then, Enable the "WYSIWYG Tracked Changes" feature and click on the "Validate" button.

[Go to top](#table-of-content)

# Proposed features

beside the change tracking function, it proposes different features:

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

### Warning

The interface allows removing buttons from WYSIWYG profiles but it does it only if no WYSIWYG field that uses
this profile does no contain any tracked changes.
If tracked changes exist, the removing is blocked until all of them are accepted or rejected.

### RECOMMENDATIONS

- Avoid to make accessible change tracking buttons on content creation form. The change tracking functions does not work 
correctly when it is activated on a field that has no default value.
- Try to limit the use the feature as much as possible.  


## Tracked changes workflow settings



[Go to top](#table-of-content)

# Recommendations

[Go to top](#table-of-content)