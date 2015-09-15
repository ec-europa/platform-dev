Feature: Feature set
  In order to activate feature to the website
  As an administrator
  I want to be able to enable and disable a feature module by using feature set page.
  
@api @javascript
Scenario: Administrator user can enable and disable features
  Given I am logged in as a user with the 'administrator' role
  When I visit "admin/structure/feature-set"
  And I check the box "featureset-text_collapse"
  And I press the "Validate" button
  And I wait for the batch job to finish
  Then I should see the success message "Text Collapse feature is now active on your site."
  And I should not see the text "Links feature is now disabled on your site."
  When I check the box "featureset-text_collapse"
  Then I should see the success message "Text Collapse feature is now disabled on your site."
  When I visit "admin/reports/dblog"
  Then I should not see the text "Notice: Undefined variable: check_node in feature_set"