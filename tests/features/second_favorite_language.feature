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
  @javascript
  Scenario Outline: Check the role of the second favorite language on the language fallback
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/config/regional/translate/translate"
    And I fill in "String contains" with "Body"
    And I click "edit" in the "field_ne_body:page:label" row
    And I fill in "French" with "Corps du texte"
    And I fill in "Italian" with "Corpo del testo"
    And I press "Save translations"
    Then I should see the following success messages:
      | success messages           |
      | The string has been saved. |

    When I create the following multilingual "page" content:
      | language | title                       | field_ne_body              |
      | en       | This title is in English    | English body               |
      | fr       | Ce titre est en Français    | Corps de texte français    |
      | it       | Questo titolo è in italiano | Corpo di testo in italiano |

    Then I go to "<url><favorite>"
    And I click "<language>" in the "content_top"
    Then I should be on "<target><target_favorite>"
    And I should see the heading "<title>"
    And I should see "<field_ne_body>"

    Examples:
      | url                      | favorite         | language | target                   | target_favorite  | title                       | field_ne_body              |
      | content/title-english_de |                  | Français | content/title-english_de | ?2nd-language=fr | Ce titre est en Français    | Corps de texte français    |
      | content/title-english_bg | ?2nd-language=fr | Italiano | content/title-english_bg | ?2nd-language=it | Questo titolo è in italiano | Corpo di testo in italiano |
      | content/title-english_de | ?2nd-language=it | Français | content/title-english_de | ?2nd-language=fr | Ce titre est en Français    | Corps de texte français    |


