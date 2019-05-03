Multisite Registration
======================

The feature Registration is a module to allow and track user registrations for
events, or just for any drupal content type.
Contributors can create contents and allow (or not) users registrations to
these contents. They can manage the registrations list, registrations settings
(allowed places, start and end dates), manage
a waiting list and send mail to all the registered users.

# Installation

- `multisite_registration_standard` should be enabled only on sites running on
standard Multisite profile.
- `multisite_registration_og` should be enabled only on sites running on
community Multisite profile.

As the other multisite features, you can enable it from the feature sets page,
url: admin/structure/feature-set, or by drush commands.

# Usage

**Attention**: the `registration_views` module, which is required by both
modules above, has a quite an unorthodox way of exposing relation Views plugins:
in order for its relation Views handlers not to be displayed as broken or
missing on Views UI it requires at least one field of type `registration` to be
added to at least one content type.
Site builders should add at least one `registration` field in order for the
Multisite Registration modules to work correctly.

## As administrator

### Add registration field
Add a registration field to a content type from the "manage fields" page of the
content type. Add a new field of type Registration. Once the field is added,
users can register to each instance of the content type.

When a content is being created, it can be chosen to enable/disable registration
option.
- Choose multisite_registration to enable the registration field.
- Choose --Disable registration-- to disable registration field.

### Manage registrations
Administrators have access to a new tab "manage registrations" when editing a
content. It gives access to the management interface of the registrations of
the content.

#### settings
- capacity: maximum numbers of registrants.
- scheduling: automatically open and close the registrations by choosing an
opendate and a close date.
- reminder: choose a date and configure a message to send a reminder to all the
registrants.
- spaces allowed: maximum number of spaces allowed for each registration.
- wait list capacity: enable a wait list and define the limit of this list.

### registrations
Registrantions list page. From this page thy can be viewed, edited or deleted
registrations. It is also shown (at the top of the list) the amount of places
in total and remaining.

### email registrants
Create and send an email to all the registrants.

## As authenticated user
Authenticated users can register to a content by clicking the "Register" button
that appears in a content  with  registrations enabled.

### Options
- "the registration is for": user can register himself or a third person. The
options available are: Myself, Other account (to register a user who is already
member of the site), Other person (to register an external user, not member of
the site).
- spaces: amount of places user wants to take, the module allows user to
register several places per registration. Under the spaces, a sentence shows the
remaining spaces available and the amount of places that the user can register.
