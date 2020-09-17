@api @javascript
Feature: NextEuropa cookie content kit
  In order to accept/reject cookies
  As a website visitor
  I should see the cookie content banner.

  Scenario: Display NextEuropa cookie content kit banner
    Given the module is enabled
      | modules                       |
      | nexteuropa_cookie_consent_kit |
    Given the cookie consent kit feature has been configured correctly
    And the cache has been cleared
    And I am on the homepage
    Then I should have one cookie consent popup on the page
