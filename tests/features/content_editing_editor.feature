@api
Feature: Content editing as editor
  In order to manage the content on the website
  As an editor
  I want to be able to create and edit articles, and use allowed HTML

  Background:
    Given I am logged in as a user with the 'editor' role

  @api
  Scenario: User can create an article and update it
    When I go to "node/add/article"
    And I fill in "Title" with "Lorem ipsum dolor sit amet"
    And I fill in "Body" with "<p>Consectetur adipiscing elit.</p>"
    And I press "Save"
    Then I should see the heading "Lorem ipsum dolor sit amet"
    And the response should contain "<p>Consectetur adipiscing elit.</p>"
    When I click "Edit draft"
    And I fill in "Body" with "<p>Consectetur elit adipiscing.</p>"
    And I press "Save"
    Then the response should contain "<p>Consectetur elit adipiscing.</p>"

  @api
  Scenario Outline: User can create an article with allowed HTML
    When I go to "node/add/article"
    And I fill in "Title" with "This is the title"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"

    Examples:
      | html                                                                                                | expected                                                                                            |
      | <p>Lorem ipsum dolor sit amet.</p>                                                                  | <p>Lorem ipsum dolor sit amet.</p>                                                                  |
      | <p>Lorem <strong>ipsum</strong> dolor sit <em>amet</em>?</p>                                        | <p>Lorem <strong>ipsum</strong> dolor sit <em>amet</em>?</p>                                        |
      | <p>Lorem <a href=\"/content/ipsum\">ipsum</a> dolor sit amet!</p>                                   | <p>Lorem <a href=\"/content/ipsum\">ipsum</a> dolor sit amet!</p>                                   |
      | <p><cite>Lorem Ipsum</cite> dolor <abbr title=\"Software Integration Test\">SIT</abbr> amet.</p>    | <p><cite>Lorem Ipsum</cite> dolor <abbr title=\"Software Integration Test\">SIT</abbr> amet.</p>    |
      | <blockquote>Lorem ipsum dolor sit amet.</blockquote>                                                | <blockquote><p>Lorem ipsum dolor sit amet.</p></blockquote>                                         |
      | <p>Lorem ipsum <code>dolor(sit);</code> amet.</p>                                                   | <p>Lorem ipsum <code>dolor(sit);</code> amet.</p>                                                   |
      | <ul><li>Lorem ipsum</li><li>Dolor sit amet</li></ul>                                                | <ul><li>Lorem ipsum</li>                                                                            |
      | <ol><li>Lorem ipsum</li><li>Dolor sit amet</li></ol>                                                | <ol><li>Lorem ipsum</li>

  @api
  Scenario: User can create an article but he cannot define its path alias, even during an update.
    The alias is generated automatically.
    When I go to "node/add/article"
    And I fill in "Title" with "Automate article alias"
    And I fill in "Body" with "<p>Consectetur adipiscing elit.</p>"
    Then the response should not contain "<strong>URL path settings</strong>"
    And the response should not contain "<label for=\"edit-path-alias\">URL alias</label>"
    When I press "Save"
    Then I should be on "content/automate-article-alias_en"
    When I click "Edit draft"
    And I fill in "Title" with "2nd Automate article alias"
    Then the response should not contain "<strong>URL path settings</strong>"
    And the response should not contain "<label for=\"edit-path-alias\">URL alias</label>"
    When I press "Save"
    Then I should be on "content/2nd-automate-article-alias_en"
