@api @javascript
Feature: news standard and news core
  In order to publish news
  As different types of users
  I want to be able to propose news

  Background:
    Given I use device with "1080" px and "1920" px resolution
    And the module is enabled
      | modules       |
      | news_core     |
      | news_standard |
      # | news_og       |

  Scenario: news menu link
    Given I am on the homepage
    Then  I should see "News"
    When  I click "News"
    Then  I should see the heading "News"


  Scenario Outline: as a user with permissions I can propose news for publication
    Given I am logged in as a user with the '<role>' role
    When  I go to "node/add/news"
    And   I fill in "edit-title" with "<title>"
    And   I fill in the rich text editor "Body" with "body for the Test News behat"
    Then  I should not see "Publication date"
    And   I click "Dates"
    And   I should see "Publication date"
    And   I fill in "edit-field-news-publication-date-und-0-value-datepicker-popup-0" with "06/11/2017"
    And   I fill in "edit-field-news-publication-date-und-0-value-timeEntry-popup-1" with "12:00"
    And   I press "Save"
    Then  I should see the text "News <title> has been created"
  #    ---> and an email should be sent
    Examples:
      | role          | title                   |
      | administrator | Test news administrator |
      | contributor   | Test news contributor   |
      | editor        | Test news editor        |

  # Scenario: as member I can see private news according to my membership
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

  Scenario: as user, I can see featured new on the homepage
    Given I am not logged in
    Given I am viewing an "news" content:
      | title              | News test      |
      | body               | news test body |
      | status             | 1              |
      | moderation state   | published      |
      | revision state     | published      |
    When I go to homepage
    And  I click "News test"
    Then I should see "News test body"

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

  # Scenario: as a user with permission, I can flag news within my community as "highlighted" so that they appear at community's homepage
  #   When I go to "my communities"
  #   And  I click "All news"
  #   And  I click "One of the news from the list"
  #   And  I click "highlight this news"
  #   And I click "Community link taken from the breadcrumb or from the clikable community logo"
  #   Then I should see "a block containing highlighted contents"


  # Scenario: as Community manager, I can manage News within my community thanks to my workbench
  #   When  I click "My workbench"
  #   Then  I should see "a block dedicated to news showing most recent news to approve"
  #   When  I click "approve link taken from one of the news"
  #   And   I click "Confirm"
  #   Then  I should see the text "The approved news doesn't appear in the block"
  #   When  I click "All news"
  #   Then  I should see the text "Page shows a list of all news created in the community. For each news, following links exist depending on news's status : approve, deny, edit, remove, highlight, feature"
