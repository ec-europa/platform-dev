@api @communities @javascript @maximizedwindow
Feature: news communities and news core
  In order to publish news
  As different types of users
  I want to be able to propose news

  Background:
    Given the module is enabled
      | modules       |
      | news_core     |
      | news_og       |
    And I am viewing a "community" content:
      | title                          | Public community 1  |
      | workbench_moderation_state     | published           |
      | workbench_moderation_state_new | published           |
    And I am viewing a "news" content:
      | title                          | News test 1 public |
      | author                         | admin              |
      | body                           | news test 1 body   |
      | field_news_publication_date    | 1510226280         |
      | group_content_access           | 1                  |
      | og_group_ref                   | Public community 1 |
      | status                         | 1                  |
      | workbench_moderation_state     | published          |
      | workbench_moderation_state_new | published          |
    And I am viewing a "news" content:
      | title                          | News test 2 public highlighted |
      | author                         | admin              |
      | body                           | news test 2 body   |
      | field_news_publication_date    | 1510226280         |
      | og_group_ref                   | Public community 1 |
      | group_content_access           | 1                  |
      | field_highlighted              | highlight          |
      | workbench_moderation_state     | published          |
      | workbench_moderation_state_new | published          |
      | status                         | 1                  |
    And I am viewing a "news" content:
      | title                          | News test 3 private higlighted|
      | author                         | admin                         |
      | body                           | news test 2 body              |
      | field_news_publication_date    | 1510226280                    |
      | og_group_ref                   | Public community 1            |
      | group_content_access           | 2                             |
      | field_highlighted              | highlight                     |
      | workbench_moderation_state     | published                     |
      | workbench_moderation_state_new | published                     |
      | status                         | 1                             |

  @theme_wip
  Scenario: as User, I can go to the public news section thanks to the "News" item in the main menu
    Given I am not logged in
    When I am on "/"
    Then I should see the link "Communities"
    And I should see the link "News"
    When I click "News"
    Then I should be on "/news_public"
    And I should see the text "News"

  @theme_wip
  Scenario: as Member I can propose news for publication to the community manager
    Given I am logged in as a user with the 'administrator' role
    And I have the "administrator member" role in the "Public community 1" group
    And I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 1 public"
    And I click "New draft"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I am logged in as a user with the 'contributor' role
    And I have the "member" role in the "Public community 1" group
    When I go to "communities_directory/my"
    Then I should see "Public community 1"
    When I click "Public community 1"
    And I click "Create content"
    And I click on the element with xpath "//*[@id='block-multisite-og-button-og-contextual-links']/div/ul/li[2]/a"
    And I fill in "edit-title" with "Test news behat"
    And I fill in the rich text editor "Body" with "Body for test news behat"
    And I click "Community"
    And I check "highlight"
    And I select "Public - accessible to all site users" from "Group content visibility"
    And I click "Revision information"
    And I select "Needs Review" from "Moderation state"
    And I press "Save"
    And I should see the text "News Test news behat has been created"
    And I should see the text "Latest content"
    But I should not see the link "Test news behat"

  @theme_wip
  Scenario: as Community manager I can create a news and publish it
    Given I am logged in as a user with the 'administrator' role
    And I have the "member" role in the "Public community 1" group
    When I go to "communities_directory/my"
    Then I should see "Public community 1"
    When I click "Public community 1"
    And I click "Create content"
    And I click on the element with xpath "//*[@id='block-multisite-og-button-og-contextual-links']/div/ul/li[2]/a"
    And I fill in "edit-title" with "Test news behat"
    And I fill in the rich text editor "Body" with "Body for test news behat"
    And I click on the element with xpath "//*[@id='news-node-form']/div/div[1]/ul/li[4]/a/strong"
    And I check "highlight"
    And I select "Public - accessible to all site users" from "Group content visibility"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the text "News Test news behat has been created"
    And I should see the text "Latest content"
    And I should see the link "Test news behat"

  @theme_wip
  Scenario: as member I can see private news according to my membership
    Given I am logged in as a user with the 'administrator' role
    And I have the "administrator member" role in the "Public community 1" group
    And I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 1 public"
    And I click "New draft"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 2 public highlighted"
    And I click "New draft"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 3 private higlighted"
    And I click "New draft"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I am logged in as a user with the 'contributor' role and I have the following fields:
      | username | contributor2          |
      | name     | contributor2          |
      | mail     | contributor2@test.com |
      | pass     | contributor           |
    And I have the "administrator member" role in the "Public community 1" group
    When I go to "communities_directory/my"
    And I click "Public community 1"
    Then I should see "Members list" in the "sidebar_left" region
    And I should see the link "contributor2" in the "sidebar_left" region
    And I should see the text "Highlighted news" in the "content_top" region
    And I should see the link "News test 2 public highlighted" in the "content_top" region
    And I should see the link "News test 3 private higlighted" in the "content_top" region
    But I should not see the link "News test 1 public" in the "content_top" region
    And I should see "Latest Content"
    And I should see the link "News test 3 private higlighted" in the "sidebar_left" region
    And I should see the link "News test 2 public highlighted" in the "sidebar_left" region
    And I should see the link "News test 1 public" in the "sidebar_left" region
    When I click "News test 2 public highlighted"
    Then I should see the heading "News test 2 public highlighted"

  @theme_wip
  Scenario: as user, I can see public news on the homepage
    Given I am logged in as a user with the 'administrator' role
    And I have the "administrator member" role in the "Public community 1" group
    And I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 2 public highlighted"
    And I click "New draft"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 3 private higlighted"
    And I click "New draft"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 1 public"
    And I click "New draft"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I am not logged in
    When I go to homepage
    Then I should see "News test 1 public"
    And I should see "News test 2 public highlighted"
    But I should not see "News test 3 private higlighted"
    When I click "News test 2 public highlighted"
    Then I should see the heading "News test 2 public highlighted"

  @theme_wip
  Scenario: as Community manager, I can flag news within my community as "Top news" so that they appear at site's homepage
    Given I am logged in as a user with the 'administrator' role
    And I have the "administrator member" role in the "Public community 1" group
    When I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 1 public"
    And I click "New draft"
    And I follow "Publishing options"
    And I check "Promoted to front page"
    And I check "Sticky at top of lists"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I go to homepage
    Then I should see the link "News test 1 public"
    And I should see the link "Read more"
    And I should see the link "about News test 1 public"

  @theme_wip
  Scenario: as Community manager, I can flag news within my community as "highlighted" so that they appear at community's homepage
    Given I am logged in as a user with the 'administrator' role
    And I have the "administrator member" role in the "Public community 1" group
    When I go to "/community/public-community-1"
    And I click "News" in the "sidebar_left" region
    And I click "News test 1 public"
    And I click "New draft"
    And I click on the element with xpath "//*[@id='news-node-form']/div/div[1]/ul/li[4]/a/strong"
    And I check "highlight"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    And I go to "communities_directory/my"
    And I click "Public community 1"
    Then I should see the link "News test 1 public" in the "content_top" region
