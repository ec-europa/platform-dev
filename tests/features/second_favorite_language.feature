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

  Scenario Outline: Check consistency of second favorite language fallback
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/config/regional/translate/translate"
    And I fill in "String contains" with "Body"
    And I press "Filter"
    And I click "edit" in the "field_ne_body:page:label" row
    And I fill in "French" with "Corps du texte"
    And I fill in "Italian" with "Corpo del testo"
    And I press "Save translations"
    Then I should see the following success messages:
      | success messages           |
      | The string has been saved. |
    When I go to "admin/structure/types/manage/page/display_en"
    And I select "above" from "edit-fields-field-ne-body-label"
    And I press "Save"
    Then I should see the following success messages:
      | success messages               |
      | Your settings have been saved. |
    When I create the following multilingual "page" content:
      | language | title                       | field_ne_body              |
      | en       | This title is in English    | English body               |
      | fr       | Ce titre est en Français    | Corps de texte français    |
      | it       | Questo titolo è in italiano | Corpo di testo in italiano |
    And I go to "<url><favorite>"
    And I click "<language>" in the "content_top"
    Then I should be on "<target><target_favorite>"
    And I should see the heading "<title>"
    And I should see "<field_ne_body>"
    And I should see "<body_label>"

    Examples:
      | url                      | favorite         | language | target                   | target_favorite  | title                       | field_ne_body              | body_label      |
      | content/title-english_de |                  | Français | content/title-english_de | ?2nd-language=fr | Ce titre est en Français    | Corps de texte français    | Corps du texte  |
      | content/title-english_bg | ?2nd-language=fr | Italiano | content/title-english_bg | ?2nd-language=it | Questo titolo è in italiano | Corpo di testo in italiano | Corpo del testo |
      | content/title-english_de | ?2nd-language=it | Français | content/title-english_de | ?2nd-language=fr | Ce titre est en Français    | Corps de texte français    | Corps du texte  |


