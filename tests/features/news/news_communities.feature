@api @javascript
Feature: news standard and news core
  In order to publish news
  As different types of users
  I want to be able to propose news

  Background:
    Given I use device with "1080" px and "1920" px resolution
    Given the module is enabled
      | modules       |
      | news_core     |
      | news_og       |
      # | news_standard |

    And I am viewing a "community" content:
      | title                          | Public community 1  |
      | workbench_moderation_state     | published           |
      | workbench_moderation_state_new | published           |


  Scenario: news menu link
    Given I am on "/"
    Then  I should see the link "Communities"
    Then  I should see the link "News"
    When  I click "News"
    When  I go to "/news_public"
    Then  I should see the text "News"


  Scenario: as Member I can propose news for publication to the community manager
    Given I am logged in as a user with the 'contributor' role and I have the following fields:
      | username | contributor          |
      | name     | contributor          |
      | password | pass                 |
      | mail     | contributor@test.com |
    And   I have the "member" role in the "Public community 1" group
    When  I go to "communities_directory/my"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Create content"
    # And   I click "News" in the "sidebar_left" region
    And   I click on the element with xpath "//*[@id='block-multisite-og-button-og-contextual-links']/div/ul/li[2]/a"
    # Then  I should see the text "New content: Your draft will be placed in moderation"
    And   I fill in "edit-title" with "Test news behat"
    And   I fill in the rich text editor "Body" with "Body for test news behat"
    And   I wait
    And   I click "Community"
    And   I check "highlight"
    And   I select "Public - accessible to all site users" from "Group content visibility"
    # I set the state to published
    # And   I click on the element with xpath "//*[ws-node-form']/div/div[1]/ul/li[9]/a"
    # And   I follow "Publishing options"
    And   I click "Revision information"
    # And   I select "Published" from "Moderation state"
    And   print last response
    And   I select "Needs Review" from "Moderation state"
    And   I press "Save"
    And   I should see the text "News Test news behat has been created"
    And   print last response
    And   I should not see the text "Latest content"
    And   I should not see the link "Test news behat"

  Scenario: as Community manager I can create a news and publicate it
    Given I am logged in as a user with the 'administrator' role and I have the following fields:
      | username | administrator          |
      | name     | administrator          |
      | password | pass                   |
      | mail     | administrator@test.com |
    And   I have the "member" role in the "Public community 1" group
    When  I go to "communities_directory/my"
    Then  I should see "Public community 1"
    And   I click "Public community 1"
    And   I click "Create content"
    # And   I click "News" in the "sidebar_left" region
    And   I click on the element with xpath "//*[@id='block-multisite-og-button-og-contextual-links']/div/ul/li[2]/a"
    # Then  I should see the text "New content: Your draft will be placed in moderation"
    And   I fill in "edit-title" with "Test news behat"
    And   I fill in the rich text editor "Body" with "Body for test news behat"
    And   I wait
    And   print last response
    And   I click on the element with xpath "//*[@id='news-node-form']/div/div[1]/ul/li[4]/a/strong"
    # And   I click "Community"
    And   I check "highlight"
    And   I select "Public - accessible to all site users" from "Group content visibility"
    # I set the state to published
    # And   I click on the element with xpath "//*[@id='news-node-form']/div/div[1]/ul/li[9]/a"
    And   I follow "Publishing options"
    # And   I click "Revision information"
    And   I select "Published" from "Moderation state"
    # And   I select "Needs review" from "Moderation state"
    And   I press "Save"
    And   I should see the text "News Test news behat has been created"
    And   print last response
    And   I should see the text "Latest content"
    And   I should see the link "Test news behat"

  Scenario: as member I can see private news according to my membership
     Given I am viewing a "news" content:
      | title              | News test      |
      | body               | news test body |
      | status             | 1              |
      | moderation state   | published      |
      | revision state     | published      |
      | community          |
    # Given I am logged in as a user with the 'contributor' role and I have the following fields:
    #   | username | contributor          |
    #   | name     | contributor          |
    #   | mail     | contributor@test.com |
    # And I have the "member" role in the "Public community 1" group
  #   When I go to "my communities"
  #   And I click "One of the communities I'm member of"
  #   Then I should see the text "--- mensaje de que a section shows a restricted list of news created in that community"
  #   When I click "One of the news in the list"
  #   Then I should see "...... cosas de la noticia"

  # Scenario: as user, I can see featured public new on the homepage
  #   When I go to "/home"
  #   And  I click "one of the news in the homepage"
  #   Then I should see ".......... cosas de la noticia"

  # Scenario: as User, I can go to the public news section thanks to the "News" item in the main menu
  #   When I click "News"
  #   Then I should see ..... complete list of featured public news
  #   When I click "one of the news in the list"
  #   Then I should see ".... cosas de la noticia"

  # Scenario: as Community manager, I can flag news within my community as "Top news" so that they appear at site's homepage
  #   When I go to "my communities"
  #   And  I click "All news"
  #   And I click "one of the news"
  #   And I check "It's a top news"
  #   And I check "Home link takeen from the breadcrumb or from the clickable site logo"
  #   Then I should see "--- cosas de la noticia"

  # Scenario: as Community manager, I can flag news within my community as "highlighted" so that they appear at community's homepage
  #   When I go to "my communities"
  #   And  I click "All news"
  #   And  I click "One of the news from the list"
  #   And  I click "highlight this news"
  #   And I click "Community link taken from the breadcrumb or from the clikable community logo"
  #   Then I should see "a block containing highlighted contents"


  # Scenario: as Community manager, I can manage New within my community thanks to my workbench
  #   When  I click "My workbench"
  #   Then  I should see "a block dedicated to news showing most recent news to approve"
  #   When  I click "approve link taken from one of the news"
  #   And   I click "Confirm"
  #   Then  I should see the text "The approved news doesn't appear in the block"
  #   When  I click "All news"
  #   Then  I should see the text "Page shows a list of all news created in the community. For each news, following links exist depending on news's status : approve, deny, edit, remove, highlight, feature"


