@api @javascript @maximizedwindow @reset-nodes
Feature:
  In order to make new or updated content quickly available to the public
  Or to urgently hide content again from the public
  As a site administrator
  I can define rules to flush the web front end cache (e.g. Varnish)

  Background:
    # We start by settings parameters that are required by the
    # nexteuropa_varnish modules.
    Given "my-website" is "correctly" configured as the purge application tag
    And these modules are enabled
      | modules            |
      | nexteuropa_varnish |
    And I am logged in as a user with the "administrator" role

  Scenario: View purge rules.
    Given the following cache purge rules:
     | Content Type | Paths to Purge        |
     | page         | \/, \/all\-basic\-pages |
     | page         | \/more\-basic\-pages    |
     | article      | \/all\-articles        |
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge        |
      | Basic page   | \/, \/all\-basic\-pages |
      | Basic page   | \/more\-basic\-pages    |
      | Article      | \/all\-articles        |

  Scenario: Add a purge rule.
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    And I click "Add cache purge rule"
    And I select "Basic page" from "Content Type"
    And I fill "Paths" with the regex:
      """
      /
      /all-basic-pages
      /yet-another-page
      """
    And I press the "Save" button
    Then I should see the error message "Regex is invalid."
    Then I fill "Paths" with the regex:
      """
      \/
      \/all\-basic\-pages
      \/yet\-another\-page
      """
     And I press the "Save" button
     Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge                                |
      | Basic page   | \/, \/all\-basic\-pages, \/yet\-another\-page |

  Scenario: Check scope of the rule.
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    And I click "Add cache purge rule"
    And I select "Basic page" from "Content Type"
    And I fill "Paths" with the regex:
      """
      content\/global\-editorial\-team
      """
    And I press the "Check scope" button
    Then I should see the success message "Here is the 100 first results matching your regex"
  Scenario: Remove a purge rule.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | \/, \/all\-basic\-pages |
      | page         | \/more\-basic\-pages   |
      | article      | \/all\-articles       |
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    And I click "delete" next to the 2nd cache purge rule
    And I press the "Confirm" button
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge          |
      | Basic page   | \/, \/all\-basic\-pages |
      | Article      | \/all\-articles         |

  Scenario: Edit a purge rule.
    Given the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | \/, \/all\-basic\-pages |
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    And I click "edit" next to the 1st cache purge rule
    Then the "Content Type" field should contain "page"
    And the radio button "A specific list of regex" is selected

  @moderated-content
  Scenario: Create a draft.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge        |
      | page         | \/, \/all\-basic\-pages |
      | page         | \/more\-basic\-pages    |
      | article      | \/all\-articles        |
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  @moderated-content
  Scenario: Immediately publish a new page.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge          |
      | page         | \/, \/all\-basic\-pages |
      | page         | \/more\-basic\-pages    |
      | article      | \/all\-articles         |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                 |
      | \/                   |
      | \/all\-basic\-pages  |
      | \/more\-basic\-pages |

  @moderated-content
  Scenario: Moderate a page.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge          |
      | page         | \/, \/all\-basic\-pages |
      | page         | \/more\-basic\-pages    |
      | article      | \/all\-articles         |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Needs Review" from "state"
    And I press the "Apply" button
    Then the web front end cache was not instructed to purge any paths

  @moderated-content 
  Scenario: Publish a page with moderation.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge        |
      | page         | \/, \/all\-basic\-pages |
      | page         | \/more\-basic\-pages    |
      | article      | \/all\-articles        |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                 |
      | \/                   |
      | \/all\-basic\-pages  |
      | \/more\-basic\-pages |
    When Execute all purge rules
    And I click "New draft"
    And I select "Basic HTML" from "Text format"
    And I fill in "Body" with "Page body draft"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  @moderated-content
  Scenario: Withdraw a published page.
    Given the default purge rule is disabled
    And I am viewing a multilingual "page" content:
      | language | title            | body                       |
      | en       | Test purge rules | Page to test unpublication |
    And the following cache purge rules:
      | Content Type | Paths to Purge          |
      | page         | \/, \/all\-basic\-pages |
      | page         | \/more\-basic\-pages    |
      | article      | \/all\-articles         |
    And the web front end cache is ready to receive requests.
    When I click "Unpublish this revision"
    And I press the "Unpublish" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                     |
      | \/                       |
      | \/all\-basic\-pages        |
      | \/more\-basic\-pages       |

  @non-moderated-content
  Scenario: Create draft of a an editorial team.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | \/, \/all\-basic\-pages |
      | page           | \/more\-basic\-pages   |
      | editorial_team | \/all\-articles       |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  @non-moderated-content
  Scenario: Immediately publish a new editorial team.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | \/, \/all-basic-pages |
      | page           | \/more\-basic\-pages   |
      | editorial_team | \/all\-articles       |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path            |
      | \/all\-articles |

  @non-moderated-content
  Scenario: Publish an existing draft of an editorial team.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | \/, \/all\-basic\-pages |
      | page           | \/more\-basic\-pages   |
      | editorial_team | \/all\-articles       |
    And the web front end cache is ready to receive requests.
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
      | \/all\-articles |

  @non-moderated-content
  Scenario: Edit an existing draft of an editorial team.
    Given the default purge rule is disabled
    And the web front end cache is ready to receive requests.
    And I go to "node/add/editorial-team"
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
    Given the default purge rule is disabled
    And the web front end cache is ready to receive requests.
    And I go to "node/add/editorial-team"
    And I fill in "Name" with "NextEuropa Platform Core"
    And I press "Save"
    And the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | page           | \/, \/all\-basic\-pages |
      | page           | \/more\-basic\-pages   |
      | editorial_team | \/all\-articles       |
    When I click "Edit"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path          |
      | \/all\-articles |

  @purge-rule-type-node
  Scenario: Add a purge rule to clear paths of the node the action is performed on.
    Given the default purge rule is disabled
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    And I click "Add cache purge rule"
    And I select "Basic page" from "Content Type"
    And I select the radio button "Paths of the node the action is performed on"
    And I press the "Save" button
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge                         |
      | Basic page   | paths of the node                      |

  @purge-rule-type-node
  Scenario: Edit a purge rule.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         |                     |
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    And I click "edit" next to the 1st cache purge rule
    Then the "Content Type" field should contain "page"
    And the radio button "Paths of the node the action is performed on" is selected

  @moderated-content @purge-rule-type-node
  Scenario: Immediately publish a new page and purge its paths.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         |                |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/page"
    And I fill in "Title" with "frontend-cache-purge-publish-immediately"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                                     |
      | content\/frontend\-cache\-purge\-publish\-immediately_en |
      | node\/[node:last-created-node-id]                        |
      | node\/[node:last-created-node-id]_[a-z]{2}               |
      | content\/frontend\-cache\-purge\-publish\-immediately    |

  @moderated-content @purge-rule-type-node
  Scenario: Purge the paths of a basic page when it is withdrawn.
    Given the default purge rule is disabled
    And the following languages are available:
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
    And the web front end cache is ready to receive requests.
    When I click "Unpublish this revision"
    And I press the "Unpublish" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                              |
      | content\/frontend\-cache\-purge\-withdrawal_en    |
      | content\/frontend\-cache\-purge\-withdrawal_fr    |
      | content\/frontend\-cache\-purge\-withdrawal_nl    |
      | node\/[node:last-created-node-id]                 |
      | node\/[node:last-created-node-id]_[a-z]{2}        |
      | content\/frontend\-cache\-purge\-withdrawal       |

  @moderated-content @purge-rule-type-node
  Scenario: Purge the paths of a basic page when it is published via moderation.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         |                |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/page"
    And I fill in "Title" with "frontend-cache-purge-publication"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                            |
      | content\/frontend\-cache\-purge\-publication_en |
      | node\/[node:last-created-node-id]                                         |
      | node\/[node:last-created-node-id]_[a-z]{2}                                |
      | content\/frontend\-cache\-purge\-publication    | 

    When Execute all purge rules
    And I click "New draft"
    And I select "Basic HTML" from "Text format"
    And I fill in "Body" with "Body: frontend-cache-purge-publication draft"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths

  @moderated-content @purge-rule-type-node
  Scenario: As any alias has revisions, the purge request must be sent directly for a published basic page when
  its URL is changed, whatever its moderation state
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge |
      | page         |                |
    When I go to "node/add/page"
    And I fill in "Title" with "frontend-cache-purge-published-page"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    And the web front end cache is ready to receive requests.
    When I click "New draft"
    And I click "URL path settings"
    And I uncheck the box "Generate automatic URL alias"
    And I fill in "URL alias" with "frontend-cache-purge-published-page-custom-alias"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                                             |
      | content\/frontend\-cache\-purge\-published\-page_en              |
      | content\/frontend\-cache\-purge\-published\-page                 |
      | frontend\-cache\-purge\-published\-page\-custom\-alias_en        |
      | node\/[node:last-created-node-id]                                |
      | node\/[node:last-created-node-id]_[a-z]{2}                       |
      | frontend\-cache\-purge\-published\-page\-custom\-alias           |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Publish an editorial team.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type   | Paths to Purge      |
      | editorial_team |                     |
    And the web front end cache is ready to receive requests.
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-editorial-team-publication"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                                             |
      | content\/frontend\-cache\-purge\-editorial\-team\-publication_en |
      | node\/[node:last-created-node-id]                                |
      | node\/[node:last-created-node-id]_[a-z]{2}                       |
      | content\/frontend\-cache\-purge\-editorial\-team\-publication    |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Publish an existing draft of an editorial team.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    And the web front end cache is ready to receive requests.
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
      | content\/frontend\-cache\-purge\-editorial\-team\-publish\-draft_en       |
      | node\/[node:last-created-node-id]                                                                   |
      | node\/[node:last-created-node-id]_[a-z]{2}                                                          |
      | content\/frontend\-cache\-purge\-editorial\-team\-publish\-draft          |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Change the URL of a published editorial team.
    Given the default purge rule is disabled
    And I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-editorial-team-change-alias"
    And I press "Save"
    And the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    And the web front end cache is ready to receive requests.
    When I click "Edit"
    And I uncheck the box "Generate automatic URL alias"
    And I fill in "frontend-cache-purge-editorial-team-custom-alias" for "URL alias"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                                         |
      | content\/frontend\-cache\-purge\-editorial\-team\-change\-alias_en |
      | content\/frontend\-cache\-purge\-editorial\-team\-change\-alias    |
      | frontend\-cache\-purge\-editorial\-team\-custom\-alias_en          |
      | node\/[node:last-created-node-id]                                  |
      | node\/[node:last-created-node-id]_[a-z]{2}                         |
      | frontend\-cache\-purge\-editorial\-team\-custom\-alias             |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Edit an existing draft of an editorial team.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    And the web front end cache is ready to receive requests.
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
    Given the default purge rule is disabled
    And I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-withdraw-editorial-team"
    And I press "Save"
    And the following cache purge rules:
      | Content Type   | Paths to Purge |
      | editorial_team |                |
    And the web front end cache is ready to receive requests.
    When I click "Edit"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path          |
      | content\/frontend\-cache\-purge\-withdraw\-editorial\-team_en |
      | node\/[node:last-created-node-id]                             |
      | node\/20_[a-z]{2}                                             |
      | content\/frontend\-cache\-purge\-withdraw\-editorial\-team    |

  Scenario: Use basic authentication.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge      |
      | page         | \/more\-basic\-pages|
    And the web front end cache is ready to receive requests.
    And nexteuropa_varnish is configured to authenticate with user "usr" and password "pass"
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then the web front end cache received a request authenticated with user "usr" and password "pass"

  Scenario: Authentication failures are logged.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge       |
      | page         | \/more\-basic\-pages |
    And the web front end cache is ready to receive requests.
    And nexteuropa_varnish is configured to authenticate with user "usr" and password "pass"
    And the web front end cache will refuse the authentication credentials
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then an error is logged with type "nexteuropa_varnish" and a message matching "Clear operation failed for target http://localhost:[0-9]*: 401 Unauthorized"
@tag_test
  Scenario: Paths to purge are logged.
    Given the default purge rule is disabled
    And the following cache purge rules:
      | Content Type | Paths to Purge          |
      | page         | \/more\-basic\-pages, \/    |
      | page         | \/even\-more\-basic\-pages  |
    And the web front end cache is ready to receive requests.
    And nexteuropa_varnish is configured to authenticate with user "usr" and password "pass"
    And the web front end cache will refuse the authentication credentials
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then an informational regex message is logged with type "nexteuropa_varnish" and a message matching "Clearing paths: \/more\-basic\-pages, \/, \/even\-more\-basic\-pages"

  Scenario: No purge are instructed if a part of the configuration has disappeared.
    Given the following cache purge rules:
      | Content Type | Paths to Purge           |
      | page         | \/more\-basic\-pages, \/ |
      | page         |                          |
    And "my-website" is "not correctly" configured as the purge application tag
    When I go to "node/add/page"
    And I fill in "Title" with "frontend-cache-purge-publish-immediately"
    And I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I fill in "Moderation notes" with "Immediately publishing this"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths
    And a critical error message is logged with type "nexteuropa_varnish" and a message matching "No path has been sent for clearing because all module settings are not set."

  # Scenarios for checking the default purge rule functionality

  @moderated-content @purge-rule-type-node
  Scenario: Purge the paths of a basic page when it is withdrawn using the default purge rule.
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
    And the web front end cache is ready to receive requests.
    When I click "Unpublish this revision"
    And I press the "Unpublish" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                           |
      | content\/frontend\-cache\-purge\-withdrawal_en |
      | content\/frontend\-cache\-purge\-withdrawal_fr |
      | content\/frontend\-cache\-purge\-withdrawal_nl |
      | node\/[node:last-created-node-id]               |
      | node\/[node:last-created-node-id]_[a-z]{2}     |
      | content\/frontend\-cache\-purge\-withdrawal    |

  @moderated-content @purge-rule-type-node
  Scenario: Purge the paths of a basic page when it is published via moderation using the default purge rule.
    Given the web front end cache is ready to receive requests.
    When I go to "node/add/page"
    And I fill in "Title" with "frontend-cache-purge-publication"
    And I press "Save"
    And I click "Moderate"
    And I select "Published" from "state"
    And I press the "Apply" button
    Then the web front end cache was instructed to purge the following paths for the application tag "my-website":
      | Path                                            |
      | content\/frontend\-cache\-purge\-publication_en |
      | node\/[node:last-created-node-id]               |
      | node\/[node:last-created-node-id]_[a-z]{2}      |
      | content\/frontend\-cache\-purge\-publication    |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Publish an existing draft of an editorial team using the default purge rule.
    Given the web front end cache is ready to receive requests.
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
      | content\/frontend\-cache\-purge\-editorial\-team\-publish\-draft_en |
      | node\/[node:last-created-node-id]                                   |
      | node\/[node:last-created-node-id]_[a-z]{2}                          |
      | content\/frontend\-cache\-purge\-editorial\-team\-publish\-draft    |

  @non-moderated-content @unilingual-content @purge-rule-type-node
  Scenario: Set the 'nexteuropa_varnish_prevent_purge' variable in the setting file prevents any purge requests to be sent
    and the "Purge caches" button is disabled
    Given I request to change the variable nexteuropa_varnish_prevent_purge to "TRUE"
    When I go to "node/add/editorial-team"
    And I fill in "Name" with "frontend-cache-purge-editorial-team-publish-draft"
    And I click "Publishing options"
    And I uncheck the box "Published"
    And I press "Save"
    And I click "Edit"
    And I click "Publishing options"
    And I check the box "Published"
    And I press "Save"
    Then the web front end cache was not instructed to purge any paths
    When I go to "admin/config/system/nexteuropa-varnish/general"
    Then the "Purge caches" button is disabled
    And I should see the warning message "The purge mechanism is temporary disabled. Purge rules are still manageable but they will not be executed until it is enabled again."
    When I go to "/admin/config/system/nexteuropa-varnish/purge_rules"
    Then I should see the warning message "The purge mechanism is temporary disabled. Purge rules are still manageable but they will not be executed until it is enabled again."
    When I click "Add cache purge rule"
    And I select "Basic page" from "Content Type"
    And I fill "Paths" with the regex:
      """
      \/
      \/all\-basic\-pages
      \/yet\-another\-page
      """
    And I press the "Save" button
    Then I see an overview with the following cache purge rules:
      | Content Type | Paths to Purge                         |
      | Basic page   | \/, \/all\-basic\-pages, \/yet\-another\-page |
    And I should see the warning message "The purge mechanism is temporary disabled. Purge rules are still manageable but they will not be executed until it is enabled again."

  # Scenario testing the "Full Varnish caches" feature

  Scenario: As administrator, I want to flush Varnish through the purge admin interface
    When I go to "admin/config/system/nexteuropa-varnish/general"
    And I press "Purge caches"
    Then I should see "Are you sure you want to purge Varnish cache ?"
    And I should see "The action you are about to perform has a deep impact on the site's performance!"
    When I press "Continue"
    Then the web front end cache was instructed to purge completely its index for the application tag "my-website"
    And I should see the success message "The Varnish caches have been fully flushed."

  # Scenario testing the "Full all Drupal and Varnish caches" feature

  Scenario: As administrator, I want to flush Drupal and Varnish through the purge admin interface
    When I go to "admin/config/system/nexteuropa-varnish/general"
    And I check "Clear drupal cache as well"
    And I press "Purge caches"
    Then I should see "Are you sure you want to purge Varnish and Drupal cache ?"
    And I should see "The action you are about to perform has a deep impact on the site's performance!"
    When I press "Continue"
    Then the web front end cache was instructed to purge completely its index for the application tag "my-website"
    And I should see the success message "The Drupal and Varnish caches have been fully flushed."

