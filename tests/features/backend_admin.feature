Feature: Warn administrators if features are overridden
  In order to know that work needs to be done on my website
  As an administrator
  I need to be notified if my features are overridden

@api
Scenario: Warning is shown when feature is overridden
      Given the module is enabled
      |modules|
      |multisite_drupal_toolbox_test|
  And I am logged in as an administrator
  When I am on "admin"
  Then I should not see the warning message containing "Some of this website's features are overridden"
  And I should not see the warning message containing "Multisite drupal toolbox test"
  When I run drush "vset" "multisite_drupal_toolbox_foobar 'bar'"
  And I am on "admin"
  Then I should see the warning message containing "Some of this website's features are overridden"
  And I should see the warning message containing "Multisite drupal toolbox test"
