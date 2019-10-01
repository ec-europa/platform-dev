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
    And the cache has been cleared

  Scenario: As anonymous I should see the nexteuropa tags (Creator, IPG Classification, Reference)
    Given I am on the homepage
    And I am an anonymous user
    Then the response should contain the meta tag with the "creator" name the "property" type and the "COMM/DG/UNIT" content
    And the response should contain the meta tag with the "classification" name the "property" type and the "03000" content
    And the response should contain the meta tag with the "reference" name the "property" type and the "European Commission" content
    And the response should contain the meta tag with the "og:image" name the "property" type and the "/tests/files/logo.png" content
