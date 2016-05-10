@api @i18n
Feature: Second favorite language tests
  In order to be accessible to European citizens,
  Users should be able to switch content to their favorite language.

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
      | it        |
      | bg        |

  Scenario Outline: Check the role of the second favorite language on the language fallback
    Given I am viewing a multilingual "page" content:
      | language | title                    |
      | en       | This title is in English |
      | fr       | Ce titre est en Français |
      | it       | Questo titolo èn inglese |
    When I go to "<url><favorite>"
    Then I should see the heading "<title>"

    Examples:
    | url                      | favorite         | title                    |
    | content/title-english_en |                  | This title is in English |
    | content/title-english_bg |                  | This title is in English |
    | content/title-english_bg | ?2nd-language=it | Questo titolo èn inglese |
    | content/title-english_bg | ?2nd-language=de | This title is in English |
