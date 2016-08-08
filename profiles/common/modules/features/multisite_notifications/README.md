Summary
=======

The multisite notifications feature allows user to stay informed of new content
via email.

Installation
============

Install using Features set page.

What are notifications ?
========================
A notification is a way to get informed about updates of the site's content.
Notifications can be received per update or in digest mode.
The feature is based on
[Subscriptions contributed module](https://www.drupal.org/project/subscriptions)
[Subscriptions documentation](https://www.drupal.org/node/344030)

What kind of notifications are handled ?
========================================
Authenticated users can subscribe to notifications, and manage the way their
notifications are handled.

-Authenticated users :
They can subscribe to a specific content (a given article, a given page etc..)
if they wish to be informed about changes on that content.
They can also subscribe to all content of a certain type, all content linked to
a given taxonomy, all new content or comments.
It is possible to subscribe to the content of a given author.

How to subscribe/unsubscribe ?
==============================
From a content (e.g. wiki page, news...), a link "Subscribe" appears at the
bottom of the page.
Subscribing to that content is made by opening this fieldset, selecting the
information you want to follow and click 'save'.
Same process is followed to unsubscribe.
Once subscribed, the user gets an email each time a change is made on this
content.

How to follow up notifications ?
================================
To follow up on you subscriptions you need to access the 'subscription' tab on
your account page.
Choose "Subscriptions" tab to see subscriptions organized in several tabs :
    "Overview" to see quickly how many subscriptions user has defined ;
    NB : This first tab can be hidden to the user by checking the Hide the
    Overview page from your users checkbox in the settings page
    (Administration » Configuration » System » Subscriptions » Overview)
    Warning: it is important to clear the cache after you have changed the value
    of that check box

Users can temporarily deactivate notifications in the 'Delivery of
notifications' subset of fields.
Users can decide to automatically subscribe to new or updated content/comments,
be notified of their own updates and receive notifications in a 'digest mode'.
Users can choose the frequency of notifications reception.
Intervals are set up by administrators on
`/admin/config/system/subscriptions/intervals_en`

"Pages/Thread" to view a list of all specific subscriptions and their interval
of notifications.
Users can also see when was the latest update made to a content.
"Content types" to view generic subscriptions by type of content.
"Categories" to view the subscriptions by vocabulary terms (ex tags, keywords,
categories, subjects..).
"Groups" to follow all the updates of a community you are a member of (you
cannot follow a community if you are not member of that community, even if this
is a public community).
As administrator it is possible to subscribe users in bulk.
Users that have been subscribed to a content/content type/community will still
have the possibility to unsubscribe from their profile page.
From the user list, check user names and select 'Subscribe the selected users
to...', click 'Update'.
Instructions on bulk subscriptions are displayed on the screen, do not yet
click 'Done' ! but browse to one of the types of subscriptions you wish to
apply in bulk.

Example : to subscribe those 4 users to the article content type, go to the
'Content types' sub-tab and check the 'Article' check box.
Click 'Save' and perform more bulk subscriptions (to Categories or Groups) if
necessary.
Once you are done click 'Done'.

Manage subscriptions settings
=============================

Administrators have the possibility to manage subscriptions settings from the
'subscriptions' configuration menu item
( Administration » Configuration » System » Subscriptions ).

Site settings
-------------

    Filter content types that are available for subscription;
    Filter vocabularies for which term subscriptions are available;
    Display of the subscriptions sub-form on node pages
    Visibility of the subscriptions fieldset/link
    Availability of the 'By Author' subscription
    Definition of the 'From' email address for the email notifications
    Settings related to cron usage of 'Notifications'
    Logging/Tracking options

Subscription block
------------------

    Define the content of the emails sent for subscriptions and unsubscriptions

User defaults
-------------

    Administrators can disable the 'Overview' subscription tab of the users.
    Administrators can implement the auto-subscription to new or updated
    content/comments for new users
    Administrators can implement notification of new posts by default for new
    users
    Administrators can implement digest mode by default for new users
    Administrators can implement a default notification interval for new users
    Administrators can decide to show to user/hide from user interval
    configuration select box (by default or enforced)

Intervals

    Administrators can define new intervals of notifications (defined in number
    of seconds)

Anonymous subscriptions
=======================
This feature has been removed from the feature.

How to test the feature locally
===============================
In order to test the notifications feature on your VPS on EC network, you must
set as sender this email address
`automated-notifications@nomail.ec.europa.eu`
This is done in the 'Mail Settings' section on
`/admin/config/system/subscriptions_en`
You need to run cron to trigger the mail sending.