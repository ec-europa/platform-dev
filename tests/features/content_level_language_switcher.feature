@api @communitites
Feature: Content level language switcher tests
  In order to read a content in different languages
  As an anonymous user
  I want to be able have access to the translations of a content

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
      | it        |
    And I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/language"
    And I fill in "edit-weight-en" with "-10"
    And I fill in "edit-weight-fr" with "-9"
    And I fill in "edit-weight-de" with "-8"
    And I fill in "edit-weight-it" with "-7"
    And I press the "Save configuration" button
    Then I should see "Configuration saved."

  Scenario: Check the visibility of the content level language switcher
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
      | fr       | Ce titre est en Français     |
      | de       | Dieser Titel ist auf Deutsch |
    When I go to "content/title-english_en"
    Then I should not see an ".block-language-selector-page" element
    When I go to "content/title-english_fr"
    Then I should not see an ".block-language-selector-page" element
    When I go to "content/title-english_de"
    Then I should not see an ".block-language-selector-page" element
    When I go to "content/title-english_it"
    Then I should see an ".block-language-selector-page" element

  Scenario Outline: Anonymous user can see the available translations of a content
    Given I am viewing a multilingual "page" content:
      | language | title                       |
      | en       | This title is in English    |
      | fr       | Ce titre est en Français    |
      | it       | Questo titolo è in Francese |
    When I go to "<url>"
    Then the language options on the page content language switcher should be "<active_language>" non clickable followed by "<language_order>" links

    Examples:
    | url                                      | active_language | language_order    |
    | content/title-english_de                 | english         | français,italiano |
    | content/title-english_de?2nd-language=fr | français        | english,italiano  |
