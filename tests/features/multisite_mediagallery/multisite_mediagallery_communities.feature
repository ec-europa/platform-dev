@api @javascript @communities @theme_wip
Feature: multisite media gallery og
  In order to add, edit and remove content to the media gallery
  As different types of users
  I want to be able to add media content through the mediagallery feature in Next Europa communities

  Background:
    Given I use device with "1920" px and "1080" px resolution
    Given the module is enabled
      | modules                          |
      | multisite_mediagallery_core      |
      | multisite_mediagallery_community |
      | multisite_block_carousel         |
    Given I am viewing a "community" content:
      | title                          | Public community 1  |
      | workbench_moderation_state     | published           |
      | workbench_moderation_state_new | published           |
    Given users:
      | username      | name          | password | mail                   | roles         | og_roles_permissions |
      | administrator | administrator | pass     | administrator@test.com | administrator | administrator member |
      | contributor   | contributor   | pass     | contributor@test.com   | contributor   | member               |
      | editor        | editor        | pass     | editor@test.com        | editor        | administrator member |
    Given I am logged in as "administrator"
    And   I have the "administrator member" role in the "Public community 1" group
    Given I am viewing a "gallerymedia" content:
      | title                           | Media gallery 1      |
      | author                          | editor               |
      | body                            | Media gallery 1 body |
      | group_content_access            | 1                    |
      | status                          | 1                    |
      | workbench_moderation_state      | published            |
      | workbench_moderation_state_new  | published            |
      | og_group_ref                    | Public community 1   |
    Given I am viewing a "gallerymedia" content:
      | title                           | Media gallery 2      |
      | author                          | contributor          |
      | body                            | Media gallery 2 body |
      | status                          | 1                    |
      | group_content_access            | 1                    |
      | workbench_moderation_state      | published            |
      | workbench_moderation_state_new  | published            |
      | og_group_ref                    | Public community 1   |
    When  I go to "/community/public-community-1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I wait
    And   I click "Media gallery 1"
    And   I click "New draft"
    And   I follow "Publishing options"
    And   I select "Published" from "Moderation state"
    And   I press "Save"
    When  I go to "/community/public-community-1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I wait
    And   I click "Media gallery 2"
    And   I click "New draft"
    And   I click "Browse"
    Then  the media browser opens
    And   I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And   I press "Next"
    And   I wait
    And   I press "Next"
    And   I wait
    And   I fill in "Name" with "My picture 2"
    And   I press "Save"
    Then  the media browser closes
    And   I follow "Publishing options"
    And   I select "Published" from "Moderation state"
    And   I press "Save"

  Scenario: as user I can browse the media gallery
    Given I am not logged in
    When  I go to "communities_directory"
    And   I click "Public community 1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I should see "Media gallery 2"
    When  I click "Media gallery 2"
    Then  I should see the heading "Media gallery 2"
    And   I should see "My picture 2"

  Scenario: as administrator member I can post media content with photo
    Given I am logged in as "editor"
    And   I have the "administrator member" role in the "Public community 1" group
    When  I go to "communities_directory/my/"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Create content"
    And   I click on the element with xpath "//*[@id='block-multisite-og-button-og-contextual-links']/div/ul/li[2]/a"
    And   I fill in "Title" with "My gallery"
    And   I fill in the rich text editor "Body" with "body for the Test News behat"
    And   I click "Browse"
    Then  the media browser opens
    And   I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And   I press "Next"
    And   I wait
    And   I press "Next"
    And   I wait
    And   I fill in "Name" with "My picture"
    And   I press "Save"
    Then  the media browser closes
    When  I follow "Revision information"
    And   I select "Needs Review" from "Moderation state"
    And   I press "Save"
    Then  I should see the text "Media Gallery My gallery has been created."

  Scenario Outline: as administrator member or member I can edit my own media gallery content
    Given I am logged in as "<user>"
    And   I have the "<community role>" role in the "Public community 1" group
    When  I go to "communities_directory/my/"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 1"
    When  I click "<content>"
    And   I click "New draft"
    And   I click "Browse"
    Then  the media browser opens
    And   I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And   I press "Next"
    And   I wait
    And   I press "Next"
    And   I wait
    And   I fill in "Name" with "My picture"
    And   I press "Save"
    Then  the media browser closes
    When  I follow "<publishing options>"
    And   I select "<state>" from "Moderation state"
    And   I press "Save"
    Then  I should see the text "Media Gallery <content> has been updated."
    Examples:
      | user          | content         | publishing options   | state        | community role       |
      | editor        | Media gallery 1 | Revision information | Needs Review | administrator member |
      | contributor   | Media gallery 2 | Revision information | Needs Review | member               |

  Scenario Outline: as administrator member I can edit other people's media gallery content
    Given I am logged in as "<user>"
    And   I have the "administrator member" role in the "Public community 1" group
    When  I go to "communities_directory/my/"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I should see "Media gallery 2"
    When  I click "Media gallery 2"
    And   I click "New draft"
    And   I click "Browse"
    Then  the media browser opens
    And   I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And   I press "Next"
    And   I wait
    And   I press "Next"
    And   I wait
    And   I fill in "Name" with "My picture"
    And   I press "Save"
    Then  the media browser closes
    When  I follow "<publishing options>"
    And   I select "<state>" from "Moderation state"
    And   I press "Save"
    Then  I should see the text "Media Gallery Media gallery 2 has been updated."
    Examples:
      | user          | publishing options   | state        |
      | editor        | Revision information | Needs Review |

  Scenario Outline: as administrator member or member I can delete my own media gallery content
    Given I am logged in as "<user>"
    And   I have the "<community role>" role in the "Public community 1" group
    When  I go to "communities_directory/my/"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 1"
    When  I click "<content>"
    And   I click "New draft"
    And   I press "Delete"
    And   I press "Delete"
    Then  I should see "Media Gallery <content> has been deleted."
    Examples:
      | user          | content         | publishing options   | state        | community role       |
      | editor        | Media gallery 1 | Revision information | Needs Review | administrator member |
      | contributor   | Media gallery 2 | Revision information | Needs Review | member               |

  Scenario Outline: as administrator member I can delete other people's media gallery content
    Given I am logged in as "<user>"
    And   I have the "administrator member" role in the "Public community 1" group
    When  I go to "communities_directory/my/"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 1"
    When  I click "Media gallery 2"
    And   I click "New draft"
    And   I press "Delete"
    And   I press "Delete"
    Then  I should see "Media Gallery Media gallery 2 has been deleted."
    Examples:
      | user          | publishing options   | state        |
      | editor        | Revision information | Needs Review |

  Scenario: as member I cannot edit nor delete other people's media gallery content
    Given I am logged in as "contributor"
    And   I have the "member" role in the "Public community 1" group
    When  I go to "communities_directory/my/"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Media Gallery" in the "sidebar_left" region
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 1"
    When  I click "Media gallery 1"
    Then  I should not see "New draft"


  @wip
  # The following scenario doesn't work due to some php errors that appear when loading a video file
  Scenario: as Administrator member I can post media content with video
    Given I am logged in as "administrator"
    And   I have the "administrator member" role in the "Public community 1" group
    When  I go to "communities_directory/my/"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Create content"
    And   I click on the element with xpath "//*[@id='block-multisite-og-button-og-contextual-links']/div/ul/li[2]/a"
    And   I fill in "Title" with "My gallery video"
    And   I fill in the rich text editor "Body" with "body for the Test News behat"
    And   I click "Browse"
    And   I attach the file "/tests/files/SampleVideo.mp4" to "edit-field-video-upload-und-0-upload"
    When  I follow "Publishing options"
    And   I select "Published" from "Moderation state"
    And   I press "Save"
    Then  I should see the text "Media Gallery My gallery video has been created."
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "My gallery video"
    When  I click "My gallery"
    Then  I should see "SampleVideo.mp4"
