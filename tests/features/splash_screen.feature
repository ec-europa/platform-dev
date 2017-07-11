@api
Feature: Splash Screen features
  In order navigate on the site in my language of preference
  As a citizen of the European Union
  I want to be able to choose my language at my first site connection

  Background:
    Given these modules are enabled
      | modules       |
      | splash_screen |
    And these following languages are available:
      | languages |
      | en        |
      | de        |
      | fr        |
      | bg        |

  Scenario: Users can access to splash screen pages
    Given I am an anonymous user
    When I go to "/"
    Then I should see an "nept_element:block:splash-page-language-selection" element
    And I should see the link "English"
    And I should see the link "Deutsch"
    And I should see the link "Français"
    And I should see the link "Български"

  # Regression test for a bug that broke the Portuguese (pt-pt) link.
  # See https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-5585
  Scenario: Test language with a custom prefix
    Given I am logged in as a user with the 'administrator' role
    And the "pt-pt" language is available
    When I go to "admin/config/regional/language/edit/pt-pt"
    And I fill in "edit-prefix" with "pt"
    And I press the "Save language" button
    When I go to "/"
    Then I should see the link "Português"
    When I click "Português"
    Then the url should match "(.*)_pt"

  Scenario: Administrators can blacklisted languages for the splash screen page
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/regional/splash_screen_settings"
    And I fill in "edit-splash-screen-blacklist" with "fr bg"
    And I press the "Save" button
    Then I should see the success message "The configuration options have been saved."
    When I go to "/"
    Then I should see an "nept_element:block:splash-page-language-selection" element
    And I should see the link "English"
    And I should see the link "Deutsch"
    And I should not see "Български"
    And I should not see "Français"

  Scenario: Being able to change the splash screen title
    Given I am logged in as a user with the 'administrator' role
    When I go to "/"
    Then I should see "NextEuropa" in the "nept_element:title-metatag" element
    When I go to "admin/config/regional/splash_screen_settings"
    And I fill in "edit-splash-screen-title-value" with "Splash screen testing title"
    And I press the "Save" button
    Then I should see the success message "The configuration options have been saved."
    When I go to "/"
    Then I should see "Splash screen testing title" in the "nept_element:title-metatag" element
    # Also test as an anonymous user
    Given I am not logged in
    And I go to "/"
    Then I should see "Splash screen testing title" in the "nept_element:title-metatag" element
