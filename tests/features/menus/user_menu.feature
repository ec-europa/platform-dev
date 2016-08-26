@api
Feature: User menu
  In order to easily access the important functionality
  As an administrative user
  I want to have links to the most important pages in my user menu

  @api
  Scenario Outline: Test user menu as administrator
    Given I am logged in as a user with the "administrator" role and I have the following fields:
    | first name      | Myrrine |
    | last name       | Augusta |


    When I am on the homepage
    And I click "<link>"
    Then I should see the heading "<heading>"

    Examples:
      | link                     | heading                  |
      | My workbench             | My Workbench             |
      | My account               | Myrrine Augusta          |
      | Manage translation tasks | Manage Translation Tasks |
      | Translate                | Translate                |
      | Log out                  | Welcome to NextEuropa    |

  @api
  Scenario Outline: Test user menu as editorial team member
    Given I am logged in as a user with the "editorial team member" role and I have the following fields:
    | first name      | Yami   |
    | last name       | Vígdís |

    When I am on the homepage
    And I click "<link>"
    Then I should see the heading "<heading>"

    Examples:
      | link         | heading               |
      | My workbench | My Workbench          |
      | My account   | Yami Vígdís           |
      | Log out      | Welcome to NextEuropa |

  @api
  Scenario Outline: Test user menu as editor
    Given I am logged in as a user with the "editor" role and I have the following fields:
    | first name      | Cornelia   |
    | last name       | Polyhymnia |

    When I am on the homepage
    And I click "<link>"
    Then I should see the heading "<heading>"

    Examples:
      | link         | heading               |
      | My workbench | My Workbench          |
      | My account   | Cornelia Polyhymnia   |
      | Log out      | Welcome to NextEuropa |

  @api
  Scenario Outline: Test that editors and editorial team members cannot access translation links
    Given I am logged in as a "<role>"
    When I am on the homepage
    Then I should not see the link "Manage translation tasks"
    And I should not see the link "Translate"

    Examples:
      | role                  |
      | editor                |
      | editorial team member |
