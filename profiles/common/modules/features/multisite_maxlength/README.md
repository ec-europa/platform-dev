Multisite Maxlength Feature
======================

Multisite Maxlength is a feature that provides to fields of a content type the
functionality of limiting and validating their maximum length in the edit form,
before submission, and showing a counter displaying the number of characters left
before the maximum length is reached.

# Installation

The feature can be activated using the feature set menu
(/admin/structure/feature-set).

As it is needed to configure a field's settings in a content-type to enable
this functionality, which is usually reserved to the administrator role, only
users with the administrator role can activate this functionality to show a
counter with characters left to reach the field maximum length.

# Usage

## Field types

Widgets currently accepted are:
- Text area (multiple rows)
- Text area with a summary
- Text field

## Activation
Administrators can activate this functionality at the field settings edition
page, which can be reached from the 'manage fields' tab of the content type
settings form. There are two different set ups for this functionality depending
on the widget type:

### Text field
This is the easiest option. You only have to tick the checkbox in order to
activate the counter, which will use the maximum length value of the field.
It is possible to customize the message that will be shown with the counter.

### Text area and Text area with a summary
For these widgets there are more options. In this case, you have to
enter a value into the 'Maximum length' setting to activate the counter.
If this field is left empty, the counter won't be activated.

Additional settings:

- Force text truncate:
  Check this option if you want the html (or the text) that the user
  inserts into the field to be truncated.

- Truncate HTML:
  Check this option if the input field may contain html text and you want to
  truncate it safely. This will also overwrite the maxlength validation from
  core, so that it will strip the tags before checking the length.

## Additional information

### JS Counter
By default the count does not show for UID 1 (admin) and the Administrator role.
They have the permission 'bypass max length' assigned by default.