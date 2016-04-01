@api
Feature: Webtools Language Coverage (LACO) service can check the language coverage of site pages
  In order to have a clear view of the language coverage
  As an external LACO client
  I can check the language coverage of site pages

  Scenario: Ordinary site pages have the same coverage as the enabled languages on the site.
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    Then I should get a "200" for "en" language coverage on the "user" path
    And I should get a "200" for "fr" language coverage on the "user" path
    And I should get a "404" for "de" language coverage on the "user" path
    And I should get a "404" for "pl" language coverage on the "user" path

  @run
  Scenario: Content language coverage depends on its actual translations.
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
    And I am viewing a multilingual "page" content:
      | language | title             |
      | en       | Title in English  |
      | fr       | Titre en Français |
    Then I should get a "200" for "en" language coverage on the "content/title-english" path
    And I should get a "200" for "fr" language coverage on the "content/title-english" path
    And I should get a "200" for "en" language coverage on the "content/title-english_en" path
    And I should get a "200" for "fr" language coverage on the "content/title-english_fr" path
    And I should get a "200" for "en" language coverage on the "content/title-english?text=abc" path
    And I should get a "200" for "en" language coverage on the "content/title-english_en?text=abc" path
    And I should get a "200" for "fr" language coverage on the "content/title-english_fr?text=abc" path
    And I should get a "404" for "pl" language coverage on the "content/title-english" path
    And I should get a "404" for "de" language coverage on the "content/title-english" path
    And I should get a "404" for "de" language coverage on the "content/title-english?text=abc" path
    And I should get a "404" for "de" language coverage on the "content/title-english_en?text=abc" path
    And I should get a "404" for "de" language coverage on the "content/title-english_fr?text=abc" path

# What happen when a page actually does not exists?
#    And I should get a "404" for "en" language coverage on the "content/title-english-not-existing" path
