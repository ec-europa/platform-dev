@api @javascript
Feature: NextEuropa cookie content kit
  In order to accept/reject cookies
  As a website visitor
  I should see the cookie content banner.

  Scenario: Display NextEuropa cookie content kit banner
    Given the module is enabled
      | modules                       |
      | nexteuropa_cookie_consent_kit |
    And I change the variable "nexteuropa_cookie_consent_kit_display_cookie_banner" to "1"
    And I change the variable "nexteuropa_cookie_consent_kit_policy_url" to "https://ec.europa.eu/info/cookies_en"
    When I am logged in as a user with the "anonymous user" role
    And I am on the homepage
    And I wait for AJAX to finish
    Then I should see the text "This site uses cookies to offer you a better browsing experience"
