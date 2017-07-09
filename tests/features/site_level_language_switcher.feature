@api
Feature: Site level language switcher tests
  In order to read a content in different languages
  As an anonymous user
  I want to be able have access to the translations of a content by using the site level language switcher

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
      | it        |
    And these modules are enabled
      |splash_screen|

  Scenario: Anonymous user can see the site level language selector
    Given I am viewing a multilingual "page" content:
      | language | title                      |
      | en       | This title is in English   |
      | fr       | Ce titre est en Français   |
      | it       | Questo titolo è in inglese |
    Then I should see an "nept_element:site-language-switcher" element

  Scenario Outline: Check site level language switcher behaviour
    Given I am viewing a multilingual "page" content:
      | language | title                      |
      | en       | This title is in English   |
      | fr       | Ce titre est en Français   |
      | it       | Questo titolo è in inglese |
    When I go to "<url><favorite>"
    And I click "English" in the "header_top"
    And I click "<language>"
    Then I should be on "<target><target_favorite>"
    And I should see the heading "<title>"

    Examples:
    | url                      | favorite         | language | target                   | target_favorite  | title                      |
    | content/title-english_en |                  | Français | content/title-english_fr |                  | Ce titre est en Français   |
    | content/title-english_en | ?2nd-language=fr | Italiano | content/title-english_it | ?2nd-language=fr | Questo titolo è in inglese |
    | content/title-english_en | ?2nd-language=fr | Français | content/title-english_fr |                  | Ce titre est en Français   |
