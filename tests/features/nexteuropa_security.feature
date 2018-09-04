@api
Feature: Nexteuropa Security
  In order to ensure the settings of honeypot are correctly set
  As a site administrator
  I want to be able to check that the module is installed by default and the settings of honeypot are right

   Scenario: Honeypot is enforced in all forms
    Given I am logged in as a user with the 'administrator' role
    When  I go to "admin/config/content/honeypot_en"
    Then  the "edit-honeypot-protect-all-forms" checkbox should be checked