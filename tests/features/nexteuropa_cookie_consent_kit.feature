@api
Feature: NextEuropa cookie content kit
  In order to accept/reject cookies
  As a website visitor
  I should have cck script embedded into the page correctly.

  Background:
    Given these modules are enabled
      | modules                         |
      | nexteuropa_cookie_consent_kit   |
    And the cookie consent kit feature has been configured correctly

  Scenario: CCK script embedded into the page correctly
    Given I am on the homepage
    Then I should have one cookie consent popup on the page

  Scenario: Admin can change the parameters of CCK
    Given I change the variable "nexteuropa_cookie_consent_kit_policy_url" to "https://ec.europa.eu/info/cookies_en"
    And I change the variable "nexteuropa_cookie_consent_kit_appendix" to "Extra text"
    And I am on the homepage
    Then the response should contain "{\"utility\":\"cck\",\"url\":\"https:\/\/ec.europa.eu\/info\/cookies_en\",\"appendix\":\"Extra text\"}"
