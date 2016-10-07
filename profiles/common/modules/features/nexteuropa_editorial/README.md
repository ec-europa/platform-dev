The "Editorial" feature supplies default settings and permissions linked to
editorial features of the Next Europa platform based on "OG" and "Workbench moderation" modules.

It also contains alterations of:
* The automatic assignment of the "editorial team member" role to
 users that join an editorial team organic group;
* The "Roles" field of the user edit form in order to allow selecting only the
 "editorial team member" role;
* The content saving process in order to block it if "CKEditor LITE" tracked
  changes are present in its WYSIWYG fields, depending on its workbench
  moderation state or status.

# Important

* Concerning content, this module is designed for supporting the
 "Entity translation" module but not the "Content translation" one.
* Concerning changes tracking controls, only nodes having a simple field
 structure are supported; no support for field collection is foreseen.

# Installation

The module is activated when the platform is installed.

# Configuration

The module by default sets some permissions and variables used by the different
editorial features.
So, it is possible to set workbench moderation states that are not possible if
tracked changes exist in WYSIWYG fields (**"Block the saving for these
Workbench Moderation states"** checkboxes).

It is also possible to set if the content saving must be blocked when the flag 
"Published" is checked (**"Block if status"** is true checkbox) in the case of 
contents of a type without workbench moderation activated or if no states are 
selected in the other field.

They can be modified on this administration page:
Configuration > Content authoring > MULTISITE WYSIWYG > WYSIWYG workflow settings
(path: "admin/config/content/multisite_wysiwyg/workbench_en");

The form contains 2 sections:
* "Set when content with tracking change cannot be saved.": Sets if content saving 
must be blocked or not, when the "Published" checkbox is checked while tracked changes 
are detected in some WYSIWYG fields.
This setting is only applicable for content types that do not use Workbench moderation workflow 
(no applicable moderation state). 
<br>By default, this option is checked.
* "Block the saving for these Workbench Moderation states": Sets moderation states for which the
content saving must be blocked when tracked changes are detected in some WYSIWYG fields.
<br>By default, the saving is blocked for "Validated" and "Published" when tracked changes 
are detected in some WYSIWYG fields.

# Remark for editors: Tracking changes

Depending on the feature configuration options for a given content workflow 
status (ex. published), saving progress could be blocked if tracked changes are 
not validated in the current revision **or one of the translations**.

In order to save content for configured workflow statuses, editors must
accept or reject tracked changes if those are present, or change the
content state.
