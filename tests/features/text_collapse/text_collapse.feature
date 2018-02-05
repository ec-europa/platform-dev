@api @javascript @theme_wip
# When trying to launch the test with ec_europa theme the following notice is given: Notice: Undefined index: #form_id in atomium_preprocess_form() (line 24 of /srv/httpd/sites/b24st_resp/profiles/multisite_drupal_standard/themes/atomium/atomium/templates/form/form.component.inc).
Feature: Text collapse
  In order to create collapse items in content
  As a registered user
  I want to be able to add collapsible text in wysiwyg

  Background:
    Given I am logged in as a user with the 'administrator' role
    And the module is enabled
      | modules       |
      | collapse_text |
      | text_collapse |

  Scenario: text collapse without rich text
    Given I am logged in as a user with the "administrator" role
    When  I go to "/node/add/page"
    And   I fill in "Title" with "Text collapse behat test"
    And   I click "Disable rich-text"
    And   I fill in "edit-field-ne-body-en-0-value" with "[collapsed title=Here my collapsible item] Hidden text [/collapsed]"
    And   I press "Save"
    Then  I should see the text "Here my collapsible item"
    And   I should not see the text "Hidden text"
    When  I click "Here my collapsible item"
    And   I wait 2 seconds
    Then  I should see the text "Hidden text"
    When  I click "Here my collapsible item"
    And   I wait 2 seconds
    Then  I should not see the text "Hidden text"
    But   I should see the text "Here my collapsible item"

  Scenario: text collapse with rich text
    Given I am logged in as a user with the "administrator" role
    When  I go to "/node/add/page"
    And   I fill in "Title" with "Text collapse behat test"
    Given I fill in the rich text editor "Body" with "[collapsed title=Here my collapsible item] Hidden text [/collapsed]"
    And   I press "Save"
    Then  I should see the text "Here my collapsible item"
    And   I should not see the text "Hidden text"
    When  I click "Here my collapsible item"
    And   I wait 2 seconds
    Then  I should see the text "Hidden text"
    When  I click "Here my collapsible item"
    And   I wait 2 seconds
    Then  I should not see the text "Hidden text"
    But   I should see the text "Here my collapsible item"
