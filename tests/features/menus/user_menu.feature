Feature: User menu
  In order to easily access the important functionality
  As an administrative user
  I want to have links to the most important pages in my user menu

  @api
  Scenario Outline: Test user menu as administrator
    Given I am logged in as a user with the "administrator" role and I have the following fields:
    | field_firstname | Myrrine |
    | field_lastname  | Augusta |
    When I am on the homepage
    And I click "<link>"
    Then I should see the heading "<heading>"

    # Currently the platform doesn't have a default homepage, so the heading
    # "Page not found" appears after logging out and being redirected to the
    # homepage.
    Examples:
      | link                     | heading                  |
      | My workbench             | My Workbench             |
      | My account               | Myrrine Augusta          |
      | Manage translation tasks | Manage Translation Tasks |
      | Translate                | Translate                |
      | Log out                  | Page not found           |

  @api
  Scenario Outline: Test user menu as editorial team member
    Given I am logged in as a user with the "editorial team member" role and I have the following fields:
    | field_firstname | Yami   |
    | field_lastname  | Vígdís |
    When I am on the homepage
    And I click "<link>"
    Then I should see the heading "<heading>"

    # Currently the platform doesn't have a default homepage, so the heading
    # "Page not found" appears after logging out and being redirected to the
    # homepage.
    Examples:
      | link         | heading        |
      | My workbench | My Workbench   |
      | My account   | Yami Vígdís    |
      | Log out      | Page not found |

  @api
  Scenario Outline: Test user menu as editor
    Given I am logged in as a user with the "editor" role and I have the following fields:
    | field_firstname | Cornelia   |
    | field_lastname  | Polyhymnia |
    When I am on the homepage
    And I click "<link>"
    Then I should see the heading "<heading>"

    # Currently the platform doesn't have a default homepage, so the heading
    # "Page not found" appears after logging out and being redirected to the
    # homepage.
    Examples:
      | link         | heading             |
      | My workbench | My Workbench        |
      | My account   | Cornelia Polyhymnia |
      | Log out      | Page not found      |
