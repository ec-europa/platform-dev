@api
Feature: NextEuropa cookie content kit
  In order to accept/reject cookies
  As a website visitor
  I should have cck script embedded into the page correctly.

  Scenario: CCK script embedded into the page correctly
    Given the module is enabled
      | modules                       |
      | nexteuropa_cookie_consent_kit |
    Given the cookie consent kit feature has been configured correctly
    And I am on the homepage
    Then I should have one cookie consent popup on the page
