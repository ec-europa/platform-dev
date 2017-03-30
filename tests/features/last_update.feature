@api
Feature: Last Update
  In order to know the last update date on a page
  As a administrator
  I want to be able to add a block that shows the last update date of any given entity

Background:
  Given I am logged in as a user with the 'administrator' role
  And the module is enabled
    | modules                   |
    | nexteuropa_lastupdate |

Scenario: Administrators can add the last update block in a region
  When I visit "admin/structure/block"
  Then I should see the text "Last update date"

@RevertBlockConfiguration
Scenario: The last update doesn't show if a node is not published
  Given that the block "last_update" from module "nexteuropa_lastupdate" is assigned to the region "footer"
  When I go to "node/add/page"
  And I fill in "Title" with "Page title"
  And I press "Save"
  Then I should not see an ".last-update" element

@RevertBlockConfiguration
Scenario: The last update shows if a node is published
  Given that the block "last_update" from module "nexteuropa_lastupdate" is assigned to the region "footer"
  When I go to "node/add/page"
  And I fill in "Title" with "Page title"
  And I select "Published" from "Moderation state"
  And I press "Save"
  Then I should see "Last published" in the ".last-update" element


