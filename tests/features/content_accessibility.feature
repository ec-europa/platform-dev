@api
Feature: Content accessibility test
  In order to detect whether the code base and/or the platform configuration disclose
  contents to users that should not access them
  As a front end developer
  I want to perform a couple of quick checks on the platform

  Scenario: Check that unpublished "Basic page" and "Article" content are not
   accessible to anonymous users with the default configuration of the platform
    Given I am an anonymous user
    And I am viewing an "page" content with "draft" moderation state:
      | title            | Lorem ipsum dolor sit amet                                      |
      | field_ne_body    | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
    Then I should get an access denied error
    And I should see the text "You are not authorized to access this page."
    And I should not see the text "Lorem ipsum dolor sit amet"
    When I am viewing an "article" content with "draft" moderation state:
      | title            | EC decides tax advantages for Fiat are illegal                        |
      | body             | Commissioner states tax rulings are not in line with state aid rules. |
    Then I should get an access denied error
    And I should see the text "You are not authorized to access this page."
    And I should not see the text "EC decides tax advantages for Fiat are illegal"

  Scenario: Check that unpublished "Basic page" and "Article" content are
   accessible to "editor" users with the default configuration of the platform
    Given I am logged in as a user with the "editor" role
    And I am viewing an "page" content with "draft" moderation state:
      | title            | Lorem ipsum dolor sit amet                                      |
      | field_ne_body    | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "Lorem ipsum dolor sit amet"
    When I am viewing an "article" content with "draft" moderation state:
      | title            | EC decides tax advantages for Fiat are illegal                        |
      | body             | Commissioner states tax rulings are not in line with state aid rules. |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "EC decides tax advantages for Fiat are illegal"

  Scenario: Check that unpublished "Basic page" and "Article" content are
   accessible to "contributor" users with the default configuration of the platform
    Given I am logged in as a user with the "contributor" role
    And I am viewing an "page" content with "draft" moderation state:
      | title            | Lorem ipsum dolor sit amet                                      |
      | field_ne_body    | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "Lorem ipsum dolor sit amet"
    When I am viewing an "article" content with "draft" moderation state:
      | title            | EC decides tax advantages for Fiat are illegal                        |
      | body             | Commissioner states tax rulings are not in line with state aid rules. |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "EC decides tax advantages for Fiat are illegal"

  Scenario: Check that unpublished "Basic page" and "Article" content are
  accessible to "administrator" users with the default configuration of the platform
    Given I am logged in as a user with the "administrator" role
    And I am viewing an "page" content with "draft" moderation state:
      | title            | Lorem ipsum dolor sit amet                                      |
      | field_ne_body    | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "Lorem ipsum dolor sit amet"
    When I am viewing an "article" content with "draft" moderation state:
      | title            | EC decides tax advantages for Fiat are illegal                        |
      | body             | Commissioner states tax rulings are not in line with state aid rules. |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "EC decides tax advantages for Fiat are illegal"

  Scenario: Check that published "Basic page" and "Article" content are
   accessible to anonymous users with the default configuration of the platform
    Given I am an anonymous user
    And I am viewing an "page" content with "published" moderation state:
      | title            | Lorem ipsum dolor sit amet                                      |
      | field_ne_body    | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "Lorem ipsum dolor sit amet"
    When I am viewing an "article" content with "published" moderation state:
      | title            | EC decides tax advantages for Fiat are illegal                        |
      | body             | Commissioner states tax rulings are not in line with state aid rules. |
    Then I should not get a "403" HTTP response
    And I should not see the text "You are not authorized to access this page."
    And I should see the text "EC decides tax advantages for Fiat are illegal"
