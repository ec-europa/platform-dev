@api
Feature: NextEuropa Metatags feature
  In order to manage metatags (some of the metatags are mandatory)
  As an administrator
  I want to be able to configure metatags for the whole site, for a given content type and for a given content

  Background:
    Given these modules are enabled
      | modules             |
      | nexteuropa_metatags |
    And I change the variable "nexteuropa_classification" to "03000"
    And I change the variable "nexteuropa_og_image" to "/tests/files/logo.png"

  Scenario: As anonymous I should see the nexteuropa tags (Creator, IPG Classification, Reference)
    Given I am on the homepage
    And I am an anonymous user
    Then the response should contain the meta tag with the "creator" name the "property" type and the "COMM/DG/UNIT" content
    And the response should contain the meta tag with the "classification" name the "property" type and the "03000" content
    And the response should contain the meta tag with the "reference" name the "property" type and the "European Commission" content
    And the response should contain the meta tag with the "og:image" name the "property" type and the "/tests/files/logo.png" content

  Scenario: As an administrator I want to be able to set metatags for a given content
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/config/search/metatags/config/node"
    And I should see "<meta_tags>"

    Examples:
      | meta_tags       |
      | BASIC TAGS      |
      | Page title      |
      | Description     |
      | Keywords        |
      | ADVANCED TAGS   |
      | OPEN GRAPH      |

  Scenario: As an administrator I want to be able to set metatags for a given content
    Given I am logged in as a user with the "administrator" role
    When I go to "node/add/page"
    Then I should see the text "Meta tags"
    When I click "Meta tags"
    And I should see "<meta_tags>"

    Examples:
      | meta_tags       |
      | Basic tags      |
      | Page title      |
      | Description     |
      | Keywords        |
      | Advanced tags   |
      | Open Graph      |
