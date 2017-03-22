@api @javascript @maximizedwindow @reset-nodes @communitites
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

  Scenario: Edit a purge rule.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /, /all-basic-pages |
    When I go to "/admin/config/frontend_cache_purge_rules"
    And I click "edit" next to the 1st cache purge rule
    Then the "Content Type" field should contain "page"
    And the radio button "A specific list of paths" is selected

  @moderated-content
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

  @moderated-content
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
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path              |
      | /                 |
      | /all-basic-pages  |
      | /more-basic-pages |

  @moderated-content
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

  @moderated-content
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

  @moderated-content
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

  @non-moderated-content
  Scenario: Create draft of a an editorial team.
    Given the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | /, /all-basic-pages |
      | page           | /more-basic-pages   |
      | editorial_team | /all-articles       |
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  @non-moderated-content
  Scenario: Immediately publish a new editorial team.
    Given the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | /, /all-basic-pages |
      | page           | /more-basic-pages   |
      | editorial_team | /all-articles       |
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path          |
      | /all-articles |

  @non-moderated-content
  Scenario: Publish an existing draft of an editorial team.
    Given the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | /, /all-basic-pages |
      | page           | /more-basic-pages   |
      | editorial_team | /all-articles       |
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I click "Publishing options"
    And I check the box "Published"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path          |
      | /all-articles |

  @non-moderated-content
  Scenario: Edit an existing draft of an editorial team.
    Given I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I fill in "Name" with "NextEuropa Platform Core Next generation"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  @non-moderated-content
  Scenario: Withdraw a published editorial team.
    Given I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    And the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | /, /all-basic-pages |
      | page           | /more-basic-pages   |
      | editorial_team | /all-articles       |
    When I click "Edit"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path          |
      | /all-articles |

  Scenario: Purge with wildcard pattern "*".
    Given the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         | /all-pages/*   |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge certain paths for the application tag "my-website"
    And the web front end cache will not use existing caches for the following paths:
      | Path                  |
      | /all-pages/foo        |
      | /all-pages/bar        |
      | /all-pages/foo_fr     |
      | /all-pages/bar_fr     |
      | /all-pages/foo-bar    |
      | /all-pages/foo-bar_fr |
      | /all-pages/foo_bar    |
      | /all-pages/foo_bar_fr |
    But the web front end cache will still use existing caches for the following paths:
      | Path                               |
      | /some-completely-irrelevant-page   |
      | /all_pages                         |
      | /all_pages_fr                      |
      | /all-pages_f                       |
      | /all-pages-fr                      |
      | /all-pages_pt-pt                   |
      | /all-pages/yet/another             |
      | /all-pages/yet/another-page        |
      | /all-pages/yet/another-page_fr     |
      | /all-pages/yet/another-page/inside |

  Scenario: Purge with multiple wildcard patterns "*" deeper in the path hierarchy.
    Given the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         | /all-pages/*/* |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge certain paths for the application tag "my-website"
    And the web front end cache will not use existing caches for the following paths:
      | Path                           |
      | /all-pages/yet/another         |
      | /all-pages/yet/another-page    |
      | /all-pages/yet/another-page_fr |
    But the web front end cache will still use existing caches for the following paths:
      | Path                                  |
      | /all-pages/foo                        |
      | /all-pages/foo                        |
      | /all-pages/yet/another-page/inside    |
      | /all-pages/yet/another-page/inside_fr |

  Scenario: Purge with wildcard pattern "?" to match language suffix.
    Given the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         | /all-pages_??  |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge certain paths for the application tag "my-website"
    And the web front end cache will not use existing caches for the following paths:
      | Path          |
      | /all-pages_fr |
      | /all-pages_po |
    But the web front end cache will still use existing caches for the following paths:
      | Path                |
      | /all-pages          |
      | /another_fr         |
      | /all_pages_fr       |
      | /all-pages_/page_fr |
      | /all-pages_f        |
      | /all-pages-fr       |
      | /all-pages_fre      |
      | /all-pages_pt-pt    |

  @purge-rule-type-node
  Scenario: Add a purge rule to clear paths of the node the action is performed on.
    When I go to "/admin/config/frontend_cache_purge_rules"
    And I click "Add cache purge rule"
    And I select "Basic page" from "Content Type"
    And I select the radio button "Paths of the node the action is performed on"
    And I press the "Save" button
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge                         |
      | Basic page   | paths of the node                      |

  @purge-rule-type-node
  Scenario: Edit a purge rule.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         |                     |
    When I go to "/admin/config/frontend_cache_purge_rules"
    And I click "edit" next to the 1st cache purge rule
    Then the "Content Type" field should contain "page"
    And the radio button "Paths of the node the action is performed on" is selected

  @moderated-content @purge-rule-type-node
  Scenario: Immediately publish a new page and purge its paths.
    Given the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         |                |
    When I go to "node/add/page"
    And I fill in "Title" with "frontend-cache-purge-publish-immediately"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                                 |
      | /content/frontend-cache-purge-publish-immediately_en |

  @moderated-content @purge-rule-type-node
  Scenario: Purge the paths of a basic page when it is withdrawn.
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | nl        |
      | de        |
    And I am viewing a multilingual "page" content:
      | language | title                                     | body                    |
      | en       | frontend-cache-purge-withdrawal           | Page to test withdrawal |
      | fr       | frontend-cache-purge-withdrawal-in-french | Page to test withdrawal |
      | nl       | frontend-cache-purge-withdrawal-in-dutch  | Page to test withdrawal |
    And the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         |                |
    When I click "Unpublish this revision"
    And I press the "Unpublish" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                        |
      | /content/frontend-cache-purge-withdrawal_en |
      | /content/frontend-cache-purge-withdrawal_fr |
      | /content/frontend-cache-purge-withdrawal_nl |

  @moderated-content @purge-rule-type-node
  Scenario: Purge the paths of a basic page when it is published via moderation.
    Given the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         |                |
    When I go to "node/add/page"
    And I fill in "Title" with "frontend-cache-purge-publication"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                         |
      | /content/frontend-cache-purge-publication_en |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Publish an editorial team.
    Given the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | editorial_team |                     |
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-editorial-team-publication"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                                        |
      | /content/frontend-cache-purge-editorial-team-publication_en |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Publish an existing draft of an editorial team.
    Given the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-editorial-team-publish-draft"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I click "Publishing options"
    And I check the box "Published"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path          |
      | /content/frontend-cache-purge-editorial-team-publish-draft_en |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Change the URL of a published editorial team.
    Given I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-editorial-team-change-alias"
    And I press "Save"
    And the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    When I click "Edit"
    And I uncheck the box "Generate automatic URL alias"
    And I fill in "frontend-cache-purge-editorial-team-custom-alias" for "URL alias"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                                 |
      | /frontend-cache-purge-editorial-team-custom-alias_en |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Edit an existing draft of an editorial team.
    Given the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    And I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I fill in "Name" with "NextEuropa Platform Core Next generation"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Withdraw a published editorial team.
    Given I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-withdraw-editorial-team"
    And I press "Save"
    And the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    When I click "Edit"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path          |
      | /content/frontend-cache-purge-withdraw-editorial-team_en |

  Scenario: Use basic authentication.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | /more-basic-pages   |
    When nexteuropa_varnish is configured to authenticate with user "usr" and password "pass"
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then the web front end cache received a request authenticated with user "usr" and password "pass"

  Scenario: Authentication failures are logged.
    Given the following cache purge rules:
      | Content Type | Paths to Purge    |
      | page         | /more-basic-pages |
    When nexteuropa_varnish is configured to authenticate with user "usr" and password "pass"
    And the web front end cache will refuse the authentication credentials
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then an error is logged with type "nexteuropa_varnish" and a message matching "Clear operation failed for target http://localhost:[0-9]*: 401 Unauthorized"

  Scenario: Paths to purge are logged.
    Given the following cache purge rules:
      | Content Type | Paths to Purge         |
      | page         | /more-basic-pages, /   |
      | page         | /even-more-basic-pages |
    When nexteuropa_varnish is configured to authenticate with user "usr" and password "pass"
    And the web front end cache will refuse the authentication credentials
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then an informational message is logged with type "nexteuropa_varnish" and a message matching "Clearing paths: /more-basic-pages, /, /even-more-basic-pages"
