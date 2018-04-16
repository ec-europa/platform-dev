Feature: Updater
  In order to update the configuration of site during a deployment
  As deployer, I want to execute updater scripts run though one drush command

  Scenario: I enable the Drupal maintenance mode and disable through
    2 updater scripts run at different times.
    # Execution of updater-smoke-test-for-feature-1.php to enable maintenance
    # mode.
    Given I run drush "update-website --path=tests/files/updater_drush"
    And I go to the homepage
    Then the response should contain "Site under maintenance"
    # Execution of updater-smoke-test-for-feature-2.php to disable maintenance
    # mode.
    When I run drush "update-website --path=tests/files/updater_drupal_api"
    And I go to the homepage
    Then the response should not contain "Site under maintenance"