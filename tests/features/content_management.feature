@api @javascript
Feature: Content management
  In order work with site content
  As a site administrator
  I want to be able to access the site's content management section and perform bulk operations.

Scenario: Administrators can publish several content items at once.
  Given "page" content:
    | title       | status |
    | First page  | 0      |
    | Second page | 0      |
    | Third page  | 0      |
  When I am logged in as a user with the "administrator" role
  And I visit "admin/content"
  Then I should have the following options for "operation":
    | Delete item                    |
    | Make content sticky            |
    | Make content unsticky          |
    | Promote content to front page  |
    | Publish content                |
    | Remove content from front page |
    | Save content                   |
    | Unpublish content              |
    | Update node alias              |
  And I select the following rows:
    | row         |
    | First page  |
    | Second page |
    | Third page  |
  And I select "Publish content" from "operation"
  And I press the "Execute" button
  And I press the "Confirm" button
  And I wait for the batch job to finish
  Then I should see "Yes" in the "First page" row
  And I should see "Yes" in the "Second page" row
  And I should see "Yes" in the "Third page" row
