@api
Feature: Last Update
  In order to know the last update date on a page
  As a administrator
  I want to be able to add a block that shows the last update date of any given entity

Background:
  Given the module is enabled
    | modules               |
    | nexteuropa_lastupdate |
  And I am logged in as a user with the 'administrator' role

Scenario: Administrators can add the last update block in a region
  When I visit "admin/structure/block"
  Then I should see the text "Last update date"

@RevertBlockConfiguration @theme_wip
# It is in wip for the europa theme because it implies a step referring a
# region. This must be evaluate deeper before being able to know how to deal with.
Scenario: Check that the last update block is not shown if a node is not published
  Given that the block "last_update" from module "nexteuropa_lastupdate" is assigned to the region "footer"
  When I go to "node/add/page"
  And I fill in "Title" with "Page title"
  And I press "Save"
  Then I should not see an "nept_element:block:last-update" element

@RevertBlockConfiguration @theme_wip
# It is in wip for the europa theme because it implies a step referring a
# region. This must be evaluate deeper before being able to know how to deal with.
Scenario: Check that the last update block is shown if a node is published
  Given that the block "last_update" from module "nexteuropa_lastupdate" is assigned to the region "footer"
  When I go to "node/add/page"
  And I fill in "Title" with "Page title"
  And I select "Published" from "Moderation state"
  And I press "Save"
  Then I should see "Last published" in the "nept_element:block:last-update" element

Scenario Outline: Check that the last update block is shown in other cases (user/file)
  Given that the block "last_update" from module "nexteuropa_lastupdate" is assigned to the region "footer"
  When I go to "<url>"
  Then I should see "<sentence>" in the ".last-update" element

  Examples:
    | url                 | sentence      |
    | user                | Last accessed |
    | file/userdefaultpng | Last uploaded |
