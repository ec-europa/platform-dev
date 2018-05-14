@api @javascript @theme_wip
Feature: news standard and news core
  In order to publish news
  As different types of users
  I want to be able to propose news

  Background:
    Given I use device with "1920" px and "1080" px resolution
    And the module is enabled
      | modules       |
      | news_core     |
      | news_standard |

    And I am viewing a "news" content:
      | title                          | News test 1 |
      | author                         | admin              |
      | body                           | news test 1 body   |
      | field_news_publication_date    | 1510226280         |
      | group_content_access           | 1                  |
      | status                         | 1                  |
      | workbench_moderation_state     | published          |
      | workbench_moderation_state_new | published          |

  Scenario: as user, I can see news menu link and click on it to see the published news
    Given I am on the homepage
    Then  I should see "News"
    When  I click "News"
    And   I wait
    Then  I should see the heading "News"
    And   I should see "News test 1"
    When  I click "News test 1"
    Then  I should see "news test 1 body"


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
    Examples:
      | role          | title                   |
      | administrator | Test news administrator |
      | contributor   | Test news contributor   |
      | editor        | Test news editor        |

  Scenario: as user, I can see featured news on the homepage
    Given I am not logged in
    Given I am viewing an "news" content:
      | title              | News test      |
      | body               | news test body |
      | status             | 1              |
      | moderation state   | published      |
      | revision state     | published      |
    When  I go to homepage
    Then  I should see "News test"
    And   I click "News test"
    Then  I should see "News test body"
