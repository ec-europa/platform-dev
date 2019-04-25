# These tests are temporarily disabled, the editorial workflow functionality is
# broken after NextEuropa was merged into Multisite.
# See https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-4249
@wip
Feature: Content translation
  In order to translate my content
  As part of the editorial team
  I want to be able to create, request and edit translations.

  @api
  Scenario Outline: A user with 'contributor' group role can access the "Translate" tab on a content page
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    Given I am logged in as a user with the '<role>' role
    And I have the 'contributor' role in the 'Global editorial team' group
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    And I click "Translate"
    Then I should see "English"
    And I should see "French"
    And I should see "German"
    And I should see the link "edit"

  Examples:
    | role               |
    | editor             |
    | contributor        |
    | authenticated user |

  @api
  Scenario Outline: Content is translatable only if its moderation state is "Published" or "Validated"
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    Given I am logged in as a user with the '<role>' role
    And I have the 'publisher' role in the 'Global editorial team' group
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    And I click "Edit draft"
    And I select "<status>" from "Moderation state"
    And I press "Save"
    And I click "Translate"
    Then I should see "English"
    And I should see "French"
    And I should see "German"
    And I should see the link "add"

  Examples:
    | role               | status       |
    | editor             | Validated    |
    | contributor        | Published    |
    | authenticated user | Validated    |

  @api
  Scenario Outline: User can translate content by accessing the "Translate" tab
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    Given I am logged in as a user with the '<role>' role
    And I have the 'publisher' role in the 'Global editorial team' group
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    And I click "Edit draft"
    And I select "<status>" from "Moderation state"
    And I press "Save"
    And I click "Translate"
    And I click "add"
    And I fill in "Title" with "Translated page title"
    And I press "Save"
    And I click "Translate"
    Then I should see "Page title"
    And I should see "Translated page title"

  Examples:
    | role               | status       |
    | editor             | Validated    |
    | contributor        | Published    |
    | authenticated user | Validated    |


  @api
  Scenario Outline: User can request translation only for content marked as "Published" or "Validated"
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    Given I am logged in as a user with the '<role>' role
    And I have the 'publisher' role in the 'Global editorial team' group
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    And I click "Edit draft"
    And I select "<status>" from "Moderation state"
    And I press "Save"
    And I go to "node/add/page"
    And I fill in "Title" with "Page title in draft"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    And I go to "admin/tmgmt/sources/workbench_moderation_node"
    Then I should see the link "Page title"
    And I should not see the link "Page title in draft"

  Examples:
    | role               | status       |
    | editor             | Validated    |
    | contributor        | Published    |
    | authenticated user | Validated    |
