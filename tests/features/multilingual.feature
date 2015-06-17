Feature: Multilingual features
  In order to easily understand the content of the European Commission
  As a citizen of the European Union
  I want to be able to read content in my native language

  @api
  Scenario: Enable multiple languages
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    And I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/language"
    Then I should see "English"
    And I should see "French"
    And I should see "German"
