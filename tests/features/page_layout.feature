@api
Feature: Page Layout
  In order to respect standard templates
  As a citizen of the European Union
  I want to be able to see components in the right regions

  Scenario Outline: Anonymous user can see the links in header and footer
    Given I am not logged in
    When I am on the homepage
    Then I should see "<text>" in the "<element>" element

    # Test all links in header and footer
    Examples:
      | text                     | element                  |
      | Legal notice             | .region-header-top       |
      | Cookies                  | .region-header-top       |
      | Contact on Europa        | .region-header-top       |
      | Search on Europa         | .region-header-top       |
      | Last update              | .region-footer           |
      | Top                      | .region-footer           |
      | Legal notice             | .region-footer           |
      | Cookies                  | .region-footer           |
      | Contact on Europa        | .region-footer           |
      | Search on Europa         | .region-footer           |

  Scenario Outline: Anonymous user can see the page title
    Given I am not logged in
    When I am on "<page>"
    Then I should see "<text>" in the "html head title" element

  # Test the page head title in different pages
    Examples:
      | page       | text                                        |
      | /          | Welcome to NextEuropa - European Commission |
      | user       | User account - European Commission          |

  @javascript @maximizedwindow
  Scenario: Logged user can see the content in the column right and left
    Given I am logged in as a user with the 'administrator' role
    When I visit "admin/structure/types/add"
    And I fill in "name" with "Content type test"
    And I press the "Save and add fields" button
    Then I should see the success message "The content type Content type test has been added."
    When I fill in "fields[_add_new_field][label]" with "field 1"
    And I select "Long text" from "fields[_add_new_field][type]"
    And I select "Text area (multiple rows)" from "fields[_add_new_field][widget_type]"
    And I press the "Save" button
    And I press the "Save field settings" button
    Then I should see the success message "Updated field field 1 field settings."
    When I press the "Save settings" button
    Then I should see the success message "Saved field 1 configuration."
    When I fill in "fields[_add_new_field][label]" with "field 2"
    And I select "Long text" from "fields[_add_new_field][type]"
    And I select "Text area (multiple rows)" from "fields[_add_new_field][widget_type]"
    And I press the "Save" button
    And I press the "Save field settings" button
    Then I should see the success message "Updated field field 2 field settings."
    When I press the "Save settings" button
    Then I should see the success message "Saved field 2 configuration."
    When I visit "admin/structure/types/manage/content-type-test/display"
    And I select "Two column" from "additional_settings[layout]"
    And I wait for AJAX to finish
    And I press the "Save" button
    Then I should see the success message "Your settings have been saved."
    When I select "Left" from "edit-fields-field-field-1-region"
    And I wait for AJAX to finish
    And I select "Right" from "edit-fields-field-field-2-region"
    And I wait for AJAX to finish
    And I press the "Save" button
    Then I should see the success message "Your settings have been saved."
    When I visit "node/add/content-type-test"
    And I fill in "Title" with "Example to compare two divs"
    And I fill in "field 1" with "text 1"
    And I fill in "field 2" with "text 2"
    And I press the "Save" button
    Then I should see the success message "Content type test Example to compare two divs has been created."
    And I check if "field-name-field-field-1" and "field-name-field-field-2" have the same position from top
    When I am not logged in
    And I visit "content/example-compare-two-divs"
    Then I check if "field-name-field-field-1" and "field-name-field-field-2" have the same position from top
