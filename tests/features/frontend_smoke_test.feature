@api
Feature: Frontend smoke test
  In order to detect whether the front end has any obvious failures
  As a front end developer
  I want to perform a couple of quick checks on the platform

  # Test whether Bootstrap, our CSS, the logo and the search image are present.
  # Note that these tests are specific to the current 'ec_resp' theme. When a
  # new theme is developed this will need to be adapted.
  Scenario: Check availability of assets
    Given the following files can be downloaded:
      | profiles/multisite_drupal_standard/themes/ec_resp/bootstrap/fonts/glyphicons-halflings-regular.woff2 |
      | profiles/multisite_drupal_standard/themes/ec_resp/css/ec_resp.css                                    |
      | profiles/multisite_drupal_standard/themes/ec_resp/images/search-button.png                           |
      | profiles/multisite_drupal_standard/themes/ec_resp/logo.png                                           |


  Scenario: Check security issue for Drupal Core
    Given the module is enabled
      |modules  |
      |update   |
    Given I am logged in as a user with the "administer software updates,view the administration theme" permissions
    And I am on "admin/modules/update"
    Then the response should not contain "<td><a href=\"https://www.drupal.org/project/drupal\">Drupal core</a> (Security update)</td>"
