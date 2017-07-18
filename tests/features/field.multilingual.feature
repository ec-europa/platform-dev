@javascript @maximizedwindow @api
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
    And I create the following multilingual "page" content:
      | language | title             |
      | en       | Title in English  |
      | fr       | Titre en Français |

  @theme_wip
  # It is in wip because of the steps:
  # - And I should see "My Group Color" in the "nept_element:field-group:color-selection-legend" element
  # - And I should see "Select a Color" in the "nept_element:field:color-selection-label" element
  # - And I should see "Red" in the "nept_element:field:color-selection-value" element
  # The reason is the field component is not implemented yet.
  # It will be done with the ticket NEPT-1066
  Scenario: Administrator can create and translate field and field group labels.
    Given I am logged in as a user with the 'administrator' role
  # Add and translate field and field Group
  # Field creation: selectcolor
    When I go to "admin/structure/types/manage/page/fields"
    And I fill in "edit-fields-add-new-field-label" with "Select a Color"
    And I click "Edit" in the "New field" row
    And I fill in "edit-fields-add-new-field-field-name" with "selectcolor"
    And I select "list_text" from "edit-fields-add-new-field-type"
    And I select "options_buttons" from "edit-fields-add-new-field-widget-type"
    And I press the "Save" button
    And I fill in "edit-field-settings-allowed-values" with:
	  """
	  Red
	  Blue
	  """
    And I press the "Save field settings" button
    And I check the box "edit-field-translatable"
    And I press the "Save settings" button
    Then I should see the success message "Saved Select a Color configuration."
  # Field translation: selectcolor
    When I go to "admin/structure/types/manage/page/fields/field_selectcolor/translate/fr"
    And I fill in "edit-strings-fieldfield-selectcolorpagelabel" with "Selectionner une Couleur"
    And I click "Field settings"
    And I fill in "edit-strings-fieldfield-selectcolorallowed-valuesred" with "Rouge"
    And I fill in "edit-strings-fieldfield-selectcolorallowed-valuesblue" with "Bleu"
    And I press the "Save translation" button
    Then I should see the success message "3 translations were saved successfully."
  # Field group creation: groupcolor
    When I go to "admin/structure/types/manage/page/display"
    And I fill in "edit-fields-add-new-group-label" with "My Group Color"
    And I fill in "edit-fields-add-new-group-group-name" with "groupcolor"
    And I press the "Save" button
    Then I should see the success message "New group My Group Color successfully created."
    And I should see the success message "Your settings have been saved."
    When I put the field "field_selectcolor" inside the field group "group_groupcolor" of an entity "node" type of "page" using the view mode "default"
    And I click "Manage fields"
    And I press the "Clone" button
    And I put the field "field_selectcolor" inside the field group "group_groupcolor" of an entity "node" type of "page" using the view mode "form"
    And I go to "admin/structure/types/manage/page/fields"
    And I press the "Save" button
  # Displaying once the field group 'groupcolor' label and translating it
    When I go to "node/add/page_en"
    And I go to "admin/config/regional/translate/translate"
    And I fill in "edit-string" with "My Group Color"
    And I press the "Filter" button
    And I click "edit"
    And I fill in "edit-translations-fr" with "Mon Groupe Couleur"
    And I press the "Save translations" button
    Then I should see the success message "The string has been saved."

  # Check that anonymous user sees labels in the expected language.
  # Updating the main node
    When I go to "content/title-english_en"
    And I click "New draft"
    And I select the radio button "Red" with the id "edit-field-selectcolor-en-red"
    And I click "Publish"
    And I select "published" from "edit-workbench-moderation-state-new"
    And I press the "Save" button
    Then I should see the success message "Basic page Title in English has been updated."

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

    # Deleting the added fields
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/structure/types/manage/page/fields/field_selectcolor/delete"
    And I press the "Delete" button
    Then I should see the success message "The field Select a Color has been deleted from the Basic page content type."
    When I go to "admin/structure/types/manage/page/groups/group_groupcolor/delete/default"
    And I press the "Delete" button
    Then I should see the success message "The group My Group Color has been deleted from the Basic page content type."
