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
      | language | title                      |
      | en       | This title is in English   |
      | fr       | Ce titre est en Français   |
      | it       | Questo titolo è in inglese |
    When I go to "<url><favorite>"
    And I click "<language>" in the "content_top"
    Then I should be on "<target><target_favorite>"
    And I should see the heading "<title>"

    Examples:
    | url                      | favorite         | language | target                   | target_favorite  | title                      |
    | content/title-english_de |                  | Français | content/title-english_de | ?2nd-language=fr | Ce titre est en Français   |
    | content/title-english_bg | ?2nd-language=fr | Italiano | content/title-english_bg | ?2nd-language=it | Questo titolo è in inglese |
    | content/title-english_de | ?2nd-language=it | Français | content/title-english_de | ?2nd-language=fr | Ce titre est en Français   |
