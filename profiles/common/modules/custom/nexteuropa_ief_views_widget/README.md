NextEuropa Inline Entity Form Views Widget
==========================================

The module is meant to provide a more usable way of selecting existing
entities when working with Entity Reference fields using Inline Entity Form
widgets, by searching entities using a custom view instad of the default
autocomplete text field.

Installation
------------

### Views settings

The first step is to build the view you are going to use as filter.
To do so add a view using at least the following fields ("Master"
displays can be used too):

- Inline Entity Form selection: Content (or equivalent)
- Title (or equivalent)

For an optimal use be sure to have the following settings in place:

- Format: Table
- Use AJAX: Yes

After that, create an "Entity Reference" field, see Entity reference field settings,
and configure the "Inline Entity Form selection: Content" field
as follow:

- "Entity reference field": choose to which "Entity reference" field the
  current view will available for. Note: the chosen field should be
  using an "Inline Entity Form" widget.
- "Entity label field": choose which field, from the current view display,
  will be used as entity label. In a common situation you would set it
  to "Title" (or equivalent).

Save the view.

### Entity reference field settings

- Edit the "Entity Reference" field specified in the view above and check
  "Allow users to add existing nodes." option.
- Select the view you have just created in the "Use this view display to
  select an existing entity" select box.

Save the field.

Usage
-----

Visit the entity creation/editing page containing the "Entity Reference"
field above and, when clicking on "Add existing node" (or equivalent) you
should be able to use the view you created to search and select existing
entities.

Note: the view will be rendered according to its own internal settings,
meaning that, if there is no content on the site, it might not show up
at all. Same goes for the view access settings.
