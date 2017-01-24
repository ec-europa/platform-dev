# These tests are temporarily disabled, the editorial workflow functionality is
# broken after NextEuropa was merged into Multisite.
# See https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-4249
@api
Feature: Editorial workflow
  In order to control how content is handled on the website
  As the head of the editorial staff
  I want to define the content staging actions individual staff members can perform

  @wip
  Scenario: A user with 'contributor' group role cannot publish nodes
    # This is a regression test for a privilege escalation bug. An authenticated
    # user was able to set the moderation state of a newly created node when she
    # was assigned the 'contributor' group role.
    # See https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5241
    Given I am logged in as a user with the 'authenticated user' role
    And I have the 'contributor' role in the 'Global editorial team' group
    When I go to "node/add/page"
    Then I should not see the text 'Moderation state'

  @wip
  Scenario Outline: Available moderation transitions for contributor
    Given I am logged in as a user with the '<role>' role
    And I have the 'contributor' role in the 'Global editorial team' group
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    Then I should see "View draft"
    And I should see "Edit draft"
    When I click "Edit draft"
    Then I should have the following options for 'Moderation state':
      | options         |
      | Draft (Current) |
      | Needs Review    |
    But I should not have the following options for 'Moderation state':
      | options   |
      | Validated |
      | Published |
      | Expired   |

    Examples:
      | role               |
      | editor             |
      | contributor        |
      | authenticated user |

  @wip
  Scenario Outline: Available moderation transitions for validator
    Given I am logged in as a user with the '<role>' role
    And I have the 'validator' role in the 'Global editorial team' group
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    Then I should see "View draft"
    And I should see "Edit draft"
    When I click "Edit draft"
    Then I should have the following options for 'Moderation state':
      | options         |
      | Draft (Current) |
      | Needs Review    |
      | Validated       |
    But I should not have the following options for 'Moderation state':
      | options   |
      | Published |
      | Expired   |

    Examples:
      | role               |
      | editor             |
      | contributor        |
      | authenticated user |

  @wip
  Scenario Outline: Available moderation transitions for publisher
    Given I am logged in as a user with the '<role>' role
    And I have the 'publisher' role in the 'Global editorial team' group
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I select "Global editorial team" from "Groups audience"
    And I press "Save"
    Then I should see "View draft"
    And I should see "Edit draft"
    When I click "Edit draft"
    Then I should have the following options for 'Moderation state':
      | options         |
      | Draft (Current) |
      | Needs Review    |
      | Validated       |
      | Published       |
      | Expired         |

    Examples:
      | role               |
      | editor             |
      | contributor        |
      | authenticated user |

  Scenario: User role "editorial team member" cannot be assigned via the UI.
    Given I am logged in as a user with the "administrator" role
    When I am on "admin/people"
    Then I should not have the following options for "edit-operation":
      | options               |
      | editorial team member |
    When I am on "user"
    And I click "Edit"
    Then the "editorial team member" checkbox should be disabled
