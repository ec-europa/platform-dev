@api @javascript
Feature: multisite media gallery
  In order to add content to the media gallery
  As different types of users
  I want to be able to add media content through the mediagallery feature

  Background:
    Given I use device with "1920" px and "1080" px resolution
    Given the module is enabled
      | modules                         |
      | multisite_mediagallery_core     |
      | multisite_mediagallery_standard |
      | multisite_block_carousel        |
    Given users:
      | username      | name          | password | mail                   | roles         |
      | administrator | administrator | pass     | administrator@test.com | administrator |
      | contributor   | contributor   | pass     | contributor@test.com   | contributor   |
      | editor        | editor        | pass     | editor@test.com        | editor        |
    Given I am viewing a "gallerymedia" content:
      | title                           | Media gallery 1      |
      | author                          | administrator        |
      | body                            | Media gallery 1 body |
      | status                          | 1                    |
      | workbench_moderation_state_new  | published            |
    Given I am viewing a "gallerymedia" content:
      | title                           | Media gallery 2      |
      | author                          | contributor          |
      | body                            | Media gallery 2 body |
      | status                          | 1                    |
      | workbench_moderation_state_new  | published            |
    Given I am viewing a "gallerymedia" content:
      | title                           | Media gallery 3      |
      | author                          | editor               |
      | body                            | Media gallery 3 body |
      | status                          | 1                    |
      | workbench_moderation_state_new  | published            |

  Scenario: as user I can browse the media gallery
    Given I am not logged in
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "Media gallery 1"
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 3"
    When  I click "Media gallery 2"
    Then  I should see the heading "Media gallery 2"

  # Scenario: as user I can see the carousel in the homepage
  #   Given I am not logged in
  #   When  I go to the homepage
  #   # Then  I should see ""
  #   Then  the page should contain the element with following id "media-gallery-carousel" and given attributes:
  #     | Attribute | Value           |
  #     | class     | carousel slide  |

  Scenario: as administrator I can post media content with photo and I can see it in the carousel in the homepage
    Given I am logged in as a user with the "administrator" role
    When  I go to "/node/add/gallerymedia_en"
    And   I fill in "Title" with "My gallery"
    And   I fill in the rich text editor "Body" with "body for the Test News behat"
    And   I click "Browse"
    Then  the media browser opens
    And   I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And   I press "Next"
    And   I wait
    And   I press "Next"
    And   I wait
    And   I fill in "File name" with "My picture"
    And   I press "Save"
    Then  the media browser closes
    When  I follow "Publishing options"
    And   I select "Published" from "Moderation state"
    And   I press "Save"
    Then  I should see the text "Media Gallery My gallery has been created."
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "My gallery"
    When  I click "My gallery"
    Then  I should see "My picture"
    When  I go to the homepage
    Then  the page should contain the element with following id "media-gallery-carousel" and given attributes:
      | Attribute | Value           |
      | class     | carousel slide  |

  Scenario Outline: as administrator, editor or contributor I can edit my own media gallery content
    Given I am logged in as "<user>"
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "Media gallery 1"
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 3"
    When  I click "<content>"
    And   I click "New draft"
    And   I click "Browse"
    Then  the media browser opens
    And   I attach the file "/tests/files/logo.png" to "edit-upload-upload"
    And   I press "Next"
    And   I wait
    And   I press "Next"
    And   I wait
    And   I fill in "File name" with "My picture"
    And   I press "Save"
    Then  the media browser closes
    When  I follow "<publishing options>"
    And   I select "<state>" from "Moderation state"
    And   I press "Save"
    Then  I should see the text "Media Gallery <content> has been updated."
    Examples:
      | user          | content         | publishing options   | state        |
      | administrator | Media gallery 1 | Publishing options   | published    |
      | editor        | Media gallery 3 | Revision information | Needs Review |
      | contributor   | Media gallery 2 | Revision information | Needs Review |

  Scenario Outline: as administrator or editor I can edit other people's media gallery content
    Given I am logged in as "<user>"
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "Media gallery 1"
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
    And   I fill in "File name" with "My picture"
    And   I press "Save"
    Then  the media browser closes
    When  I follow "<publishing options>"
    And   I select "<state>" from "Moderation state"
    And   I press "Save"
    Then  I should see the text "Media Gallery Media gallery 2 has been updated."
    Examples:
      | user          | publishing options   | state        |
      | administrator | Publishing options   | published    |
      | editor        | Revision information | Needs Review |

  Scenario Outline: as administrator, editor or contributor I can delete my own media gallery content
    Given I am logged in as "<user>"
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "Media gallery 1"
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 3"
    When  I click "<content>"
    And   I click "New draft"
    And   I press "Delete"
    And   I press "Delete"
    Then  I should see "Media Gallery <content> has been deleted."
    Examples:
      | user          | content         | publishing options   | state        |
      | administrator | Media gallery 1 | Publishing options   | published    |
      | editor        | Media gallery 3 | Revision information | Needs Review |
      | contributor   | Media gallery 2 | Revision information | Needs Review |

  Scenario Outline: as administrator or editor I can delete other people's media gallery content
    Given I am logged in as "<user>"
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "Media gallery 1"
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 3"
    When  I click "Media gallery 2"
    And   I click "New draft"
    And   I press "Delete"
    And   I press "Delete"
    Then  I should see "Media Gallery Media gallery 2 has been deleted."
    Examples:
      | user          | publishing options   | state        |
      | administrator | Publishing options   | published    |
      | editor        | Revision information | Needs Review |

  Scenario: as contributor I cannot edit nor delete other people's media gallery content
    Given I am logged in as "contributor"
    When  I go to the homepage
    And   I click "Galleries"
    Then  I should see "Media gallery 1"
    And   I should see "Media gallery 2"
    And   I should see "Media gallery 3"
    When  I click "Media gallery 3"
    Then  I should not see "New draft"



  # The following scenario doesn't work due to some php errors that appear when loading a video file
  # Scenario: as Administrator I can post media content with video
  #   Given I am logged in as a user with the "administrator" role
  #   When  I go to "/node/add/gallerymedia_en"
  #   And   I fill in "Title" with "My gallery video"
  #   And   I fill in the rich text editor "Body" with "body for the Test News behat"
  #   And   I click "Browse"
  #   And   I attach the file "/tests/files/SampleVideo.mp4" to "edit-field-video-upload-und-0-upload"
  #   When  I follow "Publishing options"
  #   And   I select "Published" from "Moderation state"
  #   And   I press "Save"
  #   Then  I should see the text "Media Gallery My gallery video has been created."
  #   When  I go to the homepage
  #   And   I click "Galleries"
  #   Then  I should see "My gallery video"
  #   When  I click "My gallery"
  #   Then  I should see "SampleVideo.mp4"
