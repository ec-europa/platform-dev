@api
Feature: Field Multilingual features
  In order to easily understand the content of the European Commission
  As a citizen of the European Union
  I want to be able to read field label in my native language


  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |

  Scenario: Administrator can translate field and field group labels. Once it is done,
  users see field and field group labels translated in interface language or in the source language
  if translations are not done
    Given I am logged in as a user with the 'administrator' role
    # Add and translate field and field Group
    And a field with the following settings is added to the "page" type:
      | Label           | Select a Color  |
      | Name            | select_color    |
      | Type            | list_text       |
      | Cardinality     | 1               |
      | Widget          | options_buttons |
      | Allowed values  | Red::Blue       |
      | Translatable    | TRUE            |
    And a field group with the following settings is added to the "page" type view:
      | Label             | My Group Color     |
      | Group name        | group_select_color |
      | Children          | select_color       |
      | Extra CSS classes | group-group-color  |
      | Weight            | 10                 |
    And I am viewing a multilingual "page" content:
      | language | title             | field_select_color |
      | en       | Title in English  | Red                |
      | fr       | Titre en Français | Red                |
    # Field translation: selectcolor
    When I go to "admin/structure/types/manage/page/fields/field_select_color/translate/fr"
    And I fill in "edit-strings-fieldfield-select-colorpagelabel" with "Selectionner une Couleur"
    And I fill in "edit-strings-fieldfield-select-colorallowed-valuesred" with "Rouge"
    And I fill in "edit-strings-fieldfield-select-colorallowed-valuesblue" with "Bleu"
    And I press the "Save translation" button
    Then I should see the success message "3 translations were saved successfully."
    # Field group translation: groupcolor.
    When I go to "content/title-english_en"
    And I click "New draft"
    And I select the radio button "Red" with the id "edit-field-select-color-en-red"
    And I select "published" from "edit-workbench-moderation-state-new"
    And I press the "Save" button
    Then I should see the success message "Basic page Title in English has been updated."
    When I go to "content/title-english_fr"
    And I go to "admin/config/regional/translate/translate"
    And I fill in "edit-string" with "My Group Color"
    And I press the "Filter" button
    And I click "edit"
    And I fill in "edit-translations-fr" with "Mon Groupe Couleur"
    And I press the "Save translations" button
    Then I should see the success message "The string has been saved."
    # Check that anonymous user sees labels in the expected language.

     # Checking given translations for different variants
    Given I am an anonymous user
    When I go to "content/title-english_en"
    Then I should see "Title in English" in the "nept_element:page-title" element
    And I should see "My Group Color" in the "nept_element:field-group:color-selection-legend" element
    And I should see "Select a Color" in the "nept_element:field:color-selection-label" element
    And I should see "Red" in the "nept_element:field:color-selection-value" element

    When I go to "content/title-english_de"
    Then I should see "Title in English" in the "nept_element:page-title" element
    And I should see "My Group Color" in the "nept_element:field-group:color-selection-legend" element
    And I should see "Select a Color" in the "nept_element:field:color-selection-label" element
    And I should see "Red" in the "nept_element:field:color-selection-value" element

    When I go to "content/title-english_en?2nd-language=fr"
    Then I should see "Title in English" in the "nept_element:page-title" element
    And I should see "My Group Color" in the "nept_element:field-group:color-selection-legend" element
    And I should see "Select a Color" in the "nept_element:field:color-selection-label" element
    And I should see "Red" in the "nept_element:field:color-selection-value" element

    When I go to "content/title-english_fr"
    Then I should see "Titre en Français" in the "nept_element:page-title" element
    And I should see "Mon Groupe Couleur" in the "nept_element:field-group:color-selection-legend" element
    And I should see "Selectionner une Couleur" in the "nept_element:field:color-selection-label" element
    And I should see "Rouge" in the "nept_element:field:color-selection-value" element

    When I go to "content/title-english_de?2nd-language=fr"
    Then I should see "Titre en Français" in the "nept_element:page-title" element
    And I should see "Mon Groupe Couleur" in the "nept_element:field-group:color-selection-legend" element
    And I should see "Selectionner une Couleur" in the "nept_element:field:color-selection-label" element
    And I should see "Rouge" in the "nept_element:field:color-selection-value" element
