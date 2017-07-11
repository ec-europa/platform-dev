@api
Feature: Ecas Authentication
  In order to use the ECAS authenticating system
  As an administrator
  I want to set-up ECAS in a site

Scenario: Administrators can set up ECAS
  Given I am logged in as a user with the "administrator" role
  When I go to "admin/config/ecas/settings"
  And I fill in "ECAS Assurance Level for this application" with "TOP"
  And I press "Save configuration"
  Then I should see the success message "The configuration options have been saved."

Scenario: Administrators can add the last update block in a region
  Given I am logged in as a user with the "administrator" role
  When I visit "admin/structure/block"
  Then I should see the text "EU Login"

@theme_wip
# It is in wip for the europa theme because it implies a step referring a
# region. This must be evaluate deeper before being able to know how to deal with.
Scenario: Logged in users can logout with the EU Login block
  Given I am logged in as a user with the "administrator" role
  And that the block "ecas" from module "ecas" is assigned to the region "sidebar_right"
  When I am on the homepage
  Then I should see the link "Logout" in the "sidebar_right" region

@theme_wip
# It is in wip for the europa theme because it implies a step referring a
# region. This must be evaluate deeper before being able to know how to deal with.
Scenario: Anonymous users can login with the EU Login block
  Given I am an anonymous user
  And that the block "ecas" from module "ecas" is assigned to the region "sidebar_right"
  When I am on the homepage
  Then I should see the link "Login" in the "sidebar_right" region

@wip
Scenario: Anonymous users can login with ECAS
  Given I am an anonymous user
  And I go to "ecas"
  Then I should be on the ecas page

@Ecas
Scenario: ECAS users can't edit their information
  Given I am logged in as an Ecas user with the "authenticated" role
  When I click "My account"
  And I click "Edit"
  Then the "First name" form element should be disabled