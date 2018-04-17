@api
Feature: Content editing as administrator
  In order to manage the content on the website
  As an administrator
  I want to be able to create, edit and delete content

  Background:
    Given I am logged in as a user with the 'administrator' role
    And the module is enabled
    | modules            |
    | ec_world_countries |

  # @theme_wip
  #They appear several notices about pager template that make the test fail in ec_europa theme.
  Scenario: See and filter the list of countries
    When I go to "/ec-world-countries"
    Then I should see the text "EC world countries"
    # And  I should see the button "Refine results"
    And  I should see "Algeria"
    And  I should see "Africa" in the "Algeria" row
    And  I should see "Albania"
    And  I should see "Europe" in the "Albania" row
    And  I should see "AL" in the "Albania" row
    And  I should have the following options for "edit-name":
      | options       |
      | Africa        |
      | Asia          |
      | Europe        |
      | North America |
      | Oceania       |
      | South America |
    When I select "Africa" from "edit-name"
    And  I press "Refine results"
    Then I should see "Algeria"
    But  I should not see "Albania"

  @javascript
  Scenario: Create EC world countries as administrator
    When I go to "/admin/structure/taxonomy/ec_world_countries"
    And  I click "Add term"
    And  I fill in "edit-name" with "Home"
    And  I fill in the rich text editor "edit-description-value" with "Description for Home"
    And  I fill in "edit-iso-3166-1-alpha-2-code-und-0-value" with "HO"
    And  I press "Save"
    Then I should see the text "Created new term Home."

  @javascript
  Scenario: Edit EC world countries as administrator
    When I go to "/admin/structure/taxonomy/ec_world_countries"
    And  I click "edit" in the "Albania" row
    And  I fill in the rich text editor "edit-description-value" with "Description for Albania"
    And  I press "Save"
    Then I should see the text "Updated term Albania"
