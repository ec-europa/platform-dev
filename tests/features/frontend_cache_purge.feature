@api @javascript @maximizedwindow
Feature:
  In order to make new or updated content quickly available to the public
  Or to urgently hide content again from the public
  As a site administrator
  I can define rules to flush the web front end cache (e.g. Varnish)

  Background:
    Given these modules are enabled
      | modules            |
      | nexteuropa_varnish |
    And "my-website" is configured as the purge application tag
    And I am logged in as a user with the "administrator" role

  Scenario: View purge rules.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
      | page         | /more-basic-pages   |
      | article      | /all-articles       |
    When I go to "/admin/config/frontend_cache_purge_rules"
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge      |
      | Basic page   | /, /all-basic-pages |
      | Basic page   | /more-basic-pages   |
      | Article      | /all-articles       |

  Scenario: Add a purge rule.
    When I go to "/admin/config/frontend_cache_purge_rules"
    And I click "Add cache purge rule"
    And I select "Basic page" from "Content Type"
    And I fill "Paths" with:
      """
      /
      /all-basic-pages
      /yet-another-page
      """
    And I press the "Save" button
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge                         |
      | Basic page   | /, /all-basic-pages, /yet-another-page |

  Scenario: Remove a purge rule.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
      | page         | /more-basic-pages   |
      | article      | /all-articles       |
    When I go to "/admin/config/frontend_cache_purge_rules"
    And I click "delete" next to the 2nd cache purge rule
    And I press the "Confirm" button
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge      |
      | Basic page   | /, /all-basic-pages |
      | Article      | /all-articles       |

  Scenario: Create a draft.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
      | page         | /more-basic-pages   |
      | article      | /all-articles       |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  Scenario: Immediately publish a new page.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
      | page         | /more-basic-pages   |
      | article      | /all-articles       |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path              |
      | /                 |
      | /all-basic-pages  |
      | /more-basic-pages |

  Scenario: Moderate a page.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
      | page         | /more-basic-pages   |
      | article      | /all-articles       |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Needs Review" from "state"
    And I press the "Apply" button
    Then the web front end cache was not instructed to purge any paths

  Scenario: Publish a page with moderation.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
      | page         | /more-basic-pages   |
      | article      | /all-articles       |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path              |
      | /                 |
      | /all-basic-pages  |
      | /more-basic-pages |

  Scenario: Withdraw a published page.
    Given I am viewing a multilingual "page" content:
      | language | title            | body                       |
      | en       | Test purge rules | Page to test unpublication |
    And the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
      | page         | /more-basic-pages   |
      | article      | /all-articles       |
    When I click "Unpublish this revision"
    And I press the "Unpublish" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                    |
      | /                       |
      | /all-basic-pages        |
      | /more-basic-pages       |
