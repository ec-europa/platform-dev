The "Multisite WYSIWYG" feature provides default settings for the WYSIWYG features available in the NextEuropa platform.

The WYSIWYG feature available on the platform is based on the [WYSIWYG module](https://www.drupal.org/project/wysiwyg) and 
[CKEditor](http://ckeditor.com/).


Table of content:
=================
- [Installation](#installation)
- [Proposed features](#features)
- [Configuration](#configuration)

# Installation

The feature is enabled by default in the NextEuropa platform.


[Go to top](#table-of-content)

# Proposed features

Beside the default settings definition, it contains a mechanism that allows inserting a CSS file specific to the widget 
of WYSIWYG fields.
This CSS file can style the field widget content and allows contributors to see what they are typing like it will be displayed in the front-end.

The difference between this mechanism and what the "WYSIWYG" module proposes is that it is based on the automatic detection of the CSS file 
(see the [next section](#configuration)).

# Configuration
 
As it is a feature, the settings are applied with the module activation.
 
If you need to apply a specific CSS file to the WYSIWYG field widgets, you just have to store it:
* Under a "wysiwyg" repository placed at the root of the your default theme;
* With "editor.css" as file name.

[Go to top](#table-of-content)