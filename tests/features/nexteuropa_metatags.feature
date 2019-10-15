@api @javascript
Feature: NextEuropa Metatags feature
  In order to manage metatags (some of the metatags are mandatory)
  As an administrator
  I want to be able to configure metatags for the whole site, for a given content type and for a given content

  Scenario: As an administrator I want to be able to set metatags
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/config/search/metatags/config/global"
    And I click the "#edit-metatags-und-nexteuropa .fieldset-title" element
    And I select "03000 - European citizenship, right to vote, ombudsman, protection of privacy" from "IPG Classification"
    And I click the "#edit-metatags-und-open-graph .fieldset-title" element
    And I fill in "edit-metatags-und-ogimage-value" with "/tests/files/logo.png"
    Then I press "Save"
    Then I should see "The meta tag defaults for Global have been saved."
    When I go to "admin/config/search/metatags/config/node"
    And I should see "BASIC TAGS"
    And I should see "Page title"
    And I should see "Description"
    And I should see "Keywords"
    And I should see "ADVANCED TAGS"
    And I should see "OPEN GRAPH"

  Scenario: As an administrator I want to be able to set metatags for a given content
    Given I am logged in as a user with the "administrator" role
    When I go to "node/add/page"
    Then I should see the text "Meta tags"
    When I click "Meta tags"
    Then I should see "BASIC TAGS"
    And I should see "Page title"
    And I should see "Description"
    And I should see "Keywords"
    And I should see "ADVANCED TAGS"
    And I should see "OPEN GRAPH"

  Scenario: As anonymous I should see the nexteuropa tags (Creator, IPG Classification, Reference)
    Given I am on the homepage
    And I am an anonymous user
    Then the response should contain the meta tag with the "creator" name and the "COMM/DG/UNIT" content
    And the response should contain the meta tag with the "classification" name and the "03000" content
    And the response should contain the meta tag with the "reference" name and the "European Commission" content
    And the response should contain the meta tag with the "og:image" name the "property" type and the "/tests/files/logo.png" content
