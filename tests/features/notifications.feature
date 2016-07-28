@api
Feature: Notifications features
  In order to be informed of content updates
  As a anonymous or authenticated user
  I can subscribe to new content

  Background:
    Given these modules are enabled
      | modules       |
      | multisite_notifications_code |

  Scenario: Anonymous users can subscribe to content
    Given I am an anonymous user
    When I go to "/"

