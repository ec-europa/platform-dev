@api
Feature: WebTools LACO feature
  In order to insert WebTools LAnguage COverage (LACO) icons in the page content of a website
  As an administrator
  I want to be able to enable the service in Drupal

  Background:
    Given these modules are enabled
      | modules             |
      | nexteuropa_laco     |
      | nexteuropa_metatags |
    And the LACO icon feature has been configured correctly

  Scenario: Check if the LACO script is correctly embedded into pages viewed by authenticated users
    Given I am logged in as a user with the 'administrator' role
    And I am on the homepage
    Then the response should contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content
    When I go to "node/add/page"
    And I fill in the content's title with "Lorem ipsum dolor sit amet"
    And I fill in "Body" with "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
    And I select "Published" from "Moderation state"
    And I press the "Save" button
    Then the response should contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content

  Scenario: Check if the LACO script is correctly embedded into pages viewed by anonymous users
    Given I am an anonymous user
    And I am on the homepage
    Then the response should contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    When I am viewing a "page" content with "published" moderation state:
      | title            | Lorem ipsum dolor sit amet                                      |
      | field_ne_body    | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
    Then the response should contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"
    # The meta tag below must be present in order that the Webtools widget works correctly (see NEPT-1042).
    And the response should contain the meta tag with the "X-UA-Compatible" name and the "IE=edge" content

  Scenario: Check if the LACO script is not embedded into the non existing pages
    Given I go to "falsepage"
    Then the response should not contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"

  Scenario: Check if the LACO script is not embedded into the defined excluded pages
    Given I am logged in as a user with the 'administrator' role
    And I go to "admin/config/regional/nexteuropa_laco"
    Then the response should not contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"
    And I go to "node/add/page"
    Then the response should not contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"
    And I go to "admin"
    Then the response should not contain "{\"service\":\"laco\",\"include\":\"#block-system-main, #sidebar-left, #sidebar-right, .page-content aside\",\"coverage\":{\"document\":\"any\",\"page\":\"any\"},\"language\":\"eu\",\"icon\":\"dot\"}"
