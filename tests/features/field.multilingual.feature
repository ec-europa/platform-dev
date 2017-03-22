@api @communitites
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
	And I am viewing a multilingual "page" content:
      | language | title             |field_selectcolor|
      | en       | Title in English  | Red             |
      | fr       | Titre en Français | Red             |

  Scenario: Administrator can create and translate field and field group labels
	Given I am logged in as a user with the 'administrator' role
	# Add and translate field and field Group
	# Field creation: selectcolor
	When I go to "admin/structure/types/manage/page/fields"
	And I fill in "edit-fields-add-new-field-label" with "Select a Color"
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
	And I fill in "edit-strings-fieldfield-selectcolorallowed-valuesred" with "Rouge"
	And I fill in "edit-strings-fieldfield-selectcolorallowed-valuesblue" with "Bleu"
	And I press the "Save translation" button
	Then I should see the success message "3 translations were saved successfully."
	# Field group creation: groupcolor
	When I go to "admin/structure/types/manage/page/display"
	And I fill in "edit-fields-add-new-group-label" with "My Group Color"
	And I fill in "edit-fields-add-new-group-group-name" with "groupcolor"
	And I select "_add_new_group" from "edit-fields-field-selectcolor-parent"
	And I press the "Save" button
	Then I should see the success message "Your settings have been saved."
	Then I should see the success message "New group My Group Color successfully created."
	# Field group translation: groupcolor
	When I go to "content/title-english_en"
	And I click "New draft"
	And I select the radio button "Red" with the id "edit-field-selectcolor-en-red"
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

	@api
	Scenario Outline: Check translation of field and field group labels
	# fix missing translation (deleted because languages are deleted at the end of scenario)
	Given I run drush "sqlq" '"INSERT INTO locales_target SELECT lid , 0x4d6f6e2047726f75706520436f756c657572, \\"fr\\",  0, 0, 0 FROM locales_source WHERE source = \\"My Group Color\\""'
	Given I am an anonymous user
	When I go to "<url>"
	Then I should see "<title>" in the "#page-title" element
	And I should see "<grouplabel>" in the "fieldset.group-groupcolor span.fieldset-legend" element
	And I should see "<fieldlabel>" in the "div.field-name-field-selectcolor div.field-label" element
	And I should see "<fieldvalue>" in the "div.field-name-field-selectcolor div.field-items div.field-item" element

	Examples:
      | url                                       | title             | grouplabel         | fieldlabel               | fieldvalue |
      | content/title-english_en                  | Title in English  | My Group Color     | Select a Color           | Red        |
      | content/title-english_fr                  | Titre en Français | Mon Groupe Couleur | Selectionner une Couleur | Rouge      |
      | content/title-english_de                  | Title in English  | My Group Color     | Select a Color           | Red        |
      | content/title-english_en?2nd-language=fr  | Title in English  | My Group Color     | Select a Color           | Red        |
      | content/title-english_de?2nd-language=fr  | Titre en Français | Mon Groupe Couleur | Selectionner une Couleur | Rouge      |

	Scenario: Administrator can delete field group labels
	# Finally, delete the added fields
	Given I am logged in as a user with the 'administrator' role
	When I go to "admin/structure/types/manage/page/fields/field_selectcolor/delete"
	And I press the "Delete" button
	Then I should see the success message "The field Select a Color has been deleted from the Basic page content type."
	When I go to "admin/structure/types/manage/page/groups/group_groupcolor/delete/default"
	And I press the "Delete" button
	Then I should see the success message "The group My Group Color has been deleted from the Basic page content type."
