@api @communitites
Feature: Text formats configuration
  In order to input text in the website
  As a user
  I need specific text formats to be available and correctly configured

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: Text formats should be available
    When I go to "admin/config/content/formats"
    Then I should see "Full HTML"
    And I should see "Filtered HTML"
    And I should see "Basic HTML"
    And I should see "Plain text"

  Scenario Outline: Text formats should have correct permission
    When I go to "admin/config/content/formats/<format>"
    Then the "administrator" checkbox should <administrator>
    And the "contributor" checkbox should <contributor>
    And the "editor" checkbox should <editor>
    And the "authenticated user" checkbox should <authenticated_user>
    And the "anonymous user" checkbox should <anonymous user>

    Examples:
      | format        | administrator | contributor   | editor      | authenticated_user  | anonymous user  |
      | full_html     | be checked    | be checked    | be checked  | not be checked      | not be checked  |
      | filtered_html | be checked    | be checked    | be checked  | be checked          | be checked      |
      | basic_html    | be checked    | be checked    | be checked  | be checked          | be checked      |
