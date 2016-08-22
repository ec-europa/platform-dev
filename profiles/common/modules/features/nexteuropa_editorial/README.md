The "Editorial" feature supplies default settings and permissions linked to
editorial features of the Next Europa platform based on "OG" and "Workbench moderation" modules.

It also contains alterations of:
* The automatically assignment of the "editorial team member" role to
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
tracked changes exists in WYSIWYG fields ("Block the saving for these
Workbench Moderation states" checkboxes).
It is also possible to set if content types that have not workbench moderation
activated or if no states are selected below ("Block if status" is true checkbox).

They can be modified on this administration page:
Configuration > Content authoring > MULTISITE WYSIWYG > WYSIWYG workflow settings
(path: "admin/config/content/multisite_wysiwyg/workbench_en");

# Remark for editors: Tracking changes

Depending on settings made in "WYSIWYG workflow settings", content saving can be
blocked if tracked changes managed by the module "CKEditor LITE" module exist in
"WYSIWYG" fields of this content or in one of these translations.

In order to unblock the saving,editors must validate or refuse tracked changes
where they are present.
