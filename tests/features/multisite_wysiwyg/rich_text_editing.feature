@api
Feature: Testing the rich text options available with the toolbar present on WYSIWYG fields like "Body".
  I want to be able to format my content with rich text options supplied by the displayed toolbar

  Background:
    Given I am logged in as a user with the 'editor' role

  @javascript
  Scenario: I create a content that contains a link with the following tag attributes: id, class and hreflang
    # Necessary for PhantomJS to set a wider screen resolution.
    Given I use device with "1920" px and "1080" px resolution
    When I go to "node/add/page"
    And I fill in the content's title with "Page title"
    And I click the "Link (Ctrl+K)" button in the "Body" WYSIWYG editor
    And I wait 2 seconds
    Then I should see the "CKEditor" modal dialog from the "Body" WYSIWYG editor with "Link" title
    When I fill in "URL" with "europa.eu/european-union/index_ga"
    And I click the "Advanced" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    And I fill in "Id" with "id-behat-987456"
    And I fill in "Stylesheet Classes" with "css-behat-test"
    And I fill in "Language code (hreflang)" with "ga"
    And I click the "OK" link in the "CKEditor" modal dialog from the "Body" WYSIWYG editor
    And I press "Save"
    Then the page should contain the element with following id "id-behat-987456" and given attributes:
      | Attribute | Value                                     |
      | class     | css-behat-test                            |
      | href      | http://europa.eu/european-union/index_ga  |
      | hreflang  | ga                                        |
