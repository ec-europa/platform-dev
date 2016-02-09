@api
Feature: Multilingual features
  In order to easily understand the content of the European Commission
  As a citizen of the European Union
  I want to be able to read content in my native language


  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |

  Scenario: Content can be translated in available languages
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
      | fr       | Ce titre est en Français     |
      | de       | Dieser Titel ist auf Deutsch |
    Then I should see the heading "This title is in English"
    And I click "English" in the "header_top" region
    Then I should be on the language selector page
    And I click "Français"
    Then I should see the heading "Ce titre est en Français"
    And I click "Français" in the "header_top" region
    Then I should be on the language selector page
    When I click "Deutsch"
    And I should see the heading "Dieser Titel ist auf Deutsch"
    And I click "Deutsch"
    Then I should be on the language selector page
    And I click "English"
    Then I should see the heading "This title is in English"

  Scenario: Custom URL suffix language negotiation is applied by default on new content.
    Given I am logged in as a user with the 'administrator' role
    And I am viewing a multilingual "page" content:
      | language | title            |
      | en       | Title in English |
      | fr       | Title in French  |
      | de       | Title in German  |
    Then I should be on "content/title-english_en"
    And I click "English" in the "header_top" region
    Then I should be on the language selector page
    And I click "Français"
    Then I should be on "content/title-english_fr"
    And I click "Français" in the "header_top" region
    Then I should be on the language selector page
    And I click "Deutsch"
    Then I should be on "content/title-english_de"

  Scenario: Enable multiple languages
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/language"
    Then I should see "English"
    And I should see "French"
    And I should see "German"

  @cleanEnvironment
  Scenario: Enable language suffix and check the base path
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/language/configure"
    And I check the box "edit-language-enabled-nexteuropa-multilingual-url-suffix"
    And I uncheck the box "edit-language-enabled-locale-url"
    And I press the "Save settings" button
    Then I should see the success message "Language negotiation configuration saved."
    When I go to "admin/config/regional/language/edit/en"
    And I fill in "edit-prefix" with "en-prefix"
    And I press the "Save language" button
    And I go to "admin/config/system/site-information"
    And I fill in "edit-site-frontpage" with "admin/fake-url"
    And I select "01000" from "edit-classification"
    And I press the "Save configuration" button
    Then I should see the success message "The configuration options have been saved."
    And the cache has been cleared
    And I should not see "admin/fake-url" in the ".form-item-site-frontpage span.field-prefix" element
    And I should not see "en-prefix" in the ".form-item-site-frontpage span.field-prefix" element
    When I go to "admin/config/regional/language/edit/en"
    And I fill in "edit-prefix" with "en"
    And I press the "Save language" button

  Scenario: Path aliases are not deleted when translating content via translation management
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-de"
    And I press the "Request translation" button
    And I select "Translator A" from "Translator"
    And I press the "Submit to translator" button
    Then I should see the following success messages:
      | success messages                        |
      | The translation job has been submitted. |
    And I click "Translation"
    Then I should see "This title is in English"
    And I click "manage" in the "This title is in English" row
    And I click "view" in the "In progress" row
    And I fill in "Translation" with "Dieser Titel ist auf Deutsch"
    And I press the "Save" button
    And I click "reviewed" in the "The translation of This title is in English to German is finished and can now be reviewed." row
    And I press the "Save as completed" button
    Then I should see "The translation for This title is in English has been accepted."
    And I click "This title is in English"
    And I should be on "content/title-english_en"
    And I should see the heading "This title is in English"
    And I visit "content/title-english_de"
    And I should see the heading "Dieser Titel ist auf Deutsch"

  Scenario: Fields and field groups label can be translated
	Given I am logged in as a user with the 'administrator' role
	And I am viewing a multilingual "page" content:
	  | language | title            |
	  | en       | Title in English |
	  | fr       | Titre en Français  |

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
	# Edit content
	When I go to "content/title-english_en"
	And I click "New draft"
	And I select the radio button "Red" with the id "edit-field-selectcolor-en-red"
	And I select "published" from "edit-workbench-moderation-state-new"
	And I press the "Save" button
	Then I should see the success message "Basic page Title in English has been updated."
	# Field group translation: groupcolor
	When I go to "content/title-english_fr"
	And I go to "admin/config/regional/translate/translate"
	And I fill in "edit-string" with "My Group Color"
	And I press the "Filter" button
	And I click "edit"
	And I fill in "edit-translations-fr" with "Mon Groupe Couleur"
	And I press the "Save translation" button
	Then I should see the success message "The string has been saved."
	# Now we can check behavior of Field  label
	# Test English language
	When I go to "content/title-english_en"
	Then I should see "Title in English" in the "#page-title" element
	And I should see "My Group Color" in the "fieldset.group-groupcolor span.fieldset-legend" element
	And I should see "Select a Color" in the "div.field-name-field-selectcolor div.field-label" element
	And I should see "Red" in the "div.field-name-field-selectcolor div.field-items div.field-item" element
	# Test French language
	When I go to "content/title-english_fr"
	Then I should see "Titre en Français" in the "#page-title" element
	And I should see "Mon Groupe Couleur" in the "fieldset.group-groupcolor span.fieldset-legend" element
	And I should see "Selectionner une Couleur" in the "div.field-name-field-selectcolor div.field-label" element
	And I should see "Rouge" in the "div.field-name-field-selectcolor div.field-items div.field-item" element
	# Test Deutsch language
	When I go to "content/title-english_de"
	Then I should see "Title in English" in the "#page-title" element
	And I should see "My Group Color" in the "fieldset.group-groupcolor span.fieldset-legend" element
	And I should see "Select a Color" in the "div.field-name-field-selectcolor div.field-label" element
	And I should see "Red" in the "div.field-name-field-selectcolor div.field-items div.field-item" element
	# Test 2nd language
	When I go to "content/title-english_en?2nd-language=fr"
	Then I should see "Title in English" in the "#page-title" element
	And I should see "My Group Color" in the "fieldset.group-groupcolor span.fieldset-legend" element
	And I should see "Select a Color" in the "div.field-name-field-selectcolor div.field-label" element
	And I should see "Red" in the "div.field-name-field-selectcolor div.field-items div.field-item" element
	# Test 2nd language
	When I go to "content/title-english_de?2nd-language=fr"
	Then I should see "Titre en Français" in the "#page-title" element
	And I should see "Mon Groupe Couleur" in the "fieldset.group-groupcolor span.fieldset-legend" element
	And I should see "Selectionner une Couleur" in the "div.field-name-field-selectcolor div.field-label" element
	And I should see "Rouge" in the "div.field-name-field-selectcolor div.field-items div.field-item" element
	# Finally, delete the added fields
	When I go to "admin/structure/types/manage/page/fields/field_selectcolor/delete"
	And I press the "Delete" button
	Then I should see the success message "The field Select a Color has been deleted from the Basic page content type."
	When I go to "admin/structure/types/manage/page/groups/group_groupcolor/delete/default"
	And I press the "Delete" button
	Then I should see the success message "The group My Group Color has been deleted from the Basic page content type."