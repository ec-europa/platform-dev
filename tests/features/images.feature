@api
Feature: Images
  In order to make my website more attractive
  As a contributor
  I can attach images to content

  @theme_wip
  # It is in WIP because the image display is not integrated in europa yet.
  # see NEPT-1243
  Scenario: Add a caption to an Article image
    Given I am logged in as a user with the "administrator" role
    When I go to "node/add/article"
    And I fill in "Title" with "Article with image and caption"
    And I attach the file "/tests/files/logo.png" to "edit-field-image-und-0-upload"
    And I press "Save"
    Then the response should contain "has been created."
    When I go to "/admin/content/file"
    And I click "logo.png"
    And I click "Edit"
    And I fill in "File name" with "Image name"
    And I fill in "Caption" with "Image caption"
    And I press "Save"
    Then the response should contain "has been updated."
    When I go to "/admin/content"
    And the cache has been cleared
    And I click "Article with image and caption"
    Then I should see "Image caption"
