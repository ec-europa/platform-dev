@api
Feature: Content editing
  In order to manage the content on the website
  As an editor
  I want to be able to create, edit and delete content

  Background:
    Given I am logged in as a user with the 'administrator' role

  @api
  Scenario Outline: Test allowed HTML
    # The Wysiwyg does not return the HTML exactly as entered. It will insert
    # whitespace and some additional tags. Hence the expected HTML differs from
    # the entered HTML.
    When I go to "node/add/page"
    And I fill in "Title" with "The right way is the right way"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"

    Examples:
      | html                                                                                         | expected                                                                                     |
      | <p style=\"text-align:right\">The right way</p>                                              | <p style=\"text-align:right\">The right way</p>                                              |
      | <p><span style=\"font-family:courier\"><span style=\"font-size:18px\"><strong>Fancy</strong> | <p><span style=\"font-family:courier\"><span style=\"font-size:18px\"><strong>Fancy</strong> |
      | <p><span style=\"color:#800000\"><em><u>Yay!</u></em></span></p>                             | <p><span style=\"color:#800000\"><em><u>Yay!</u></em></span></p>                             |
      | <pre>Preformatted text</pre>                                                                 | <pre>Preformatted text</pre>                                                                 |
      | <blockquote>A quote</blockquote>                                                             | <blockquote><p>A quote</p></blockquote>                                                      |
      | <ul><li>A bullet!</li></ul>                                                                  | <ul><li>A bullet!</li>                                                                       |
      | <ol><li>A number?</li></ol>                                                                  | <ol><li>A number?</li>                                                                       |
      | <p><a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                         | <p><a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                         |
      | <h2 style=\"font-style:italic\">Styled heading</h2>                                          | <h2 style=\"font-style:italic\">Styled heading</h2>                                          |
      | <div class=\"css_class-name\">Applied css class</div>                                        | <div class=\"css_class-name\">Applied css class</div>                                        |
      | <div id=\"my-id_123\">A container with a custom HTML ID.</div>                               | <div id=\"my-id_123\">A container with a custom HTML ID.</div>                               |

  @api
  Scenario Outline: Test disallowed HTML
    When I go to "node/add/page"
    And I fill in "Title" with "This is not the right way"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should not contain "<expected>"

  Examples:
    | html                                                                | expected                      |
    | <script>alert('xss')</script>                                       | <script>alert('xss')</script> |
    | <a href=\"javascript:alert('xss')\">xss</a>                         | javascript:alert              |
    | <p style=\"background-image: url(javascript:alert('xss'))\">xss</p> | javascript:alert              |
    | <div class=\"2classname\">Applied invalid css class</div>           | classname                     |
    | <div class=\"classname?&*\">Applied invalid css class</div>         | classname                     |
    | <div id=\"2invalidid\">A container with an invalid HTML ID</div>    | invalidid                     |
    | <div id=\"invalidid.\">A container with an invalid HTML ID</div>    | invalidid                     |

  @api
  Scenario Outline: The change of the content state to "validated" or "published" must be blocked if
  CKEditor Lite tracked changes exist in WYSIWYG fields
    Given I am logged in as a user with the 'administrator' role
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I fill in "Body" with "Page body"
    And I press "Save"
    Then I should see "View draft"
    When I click "Edit draft"
    And I select "Full HTML + Change tracking" from "field_ne_body[en][0][format]"
    And I fill in "Body" with "<blocked>"
    And I select "Validated" from "Moderation state"
    And I press "Save"
    Then I should see the error message "The field contains tracked changes that may not be saved."
    And I should see the error message "Current content includes unprocessed changes in the English version. In order to save progress, please accept or reject them, or change the content state."
    When I select "Validated" from "Moderation state"
    And I press "Save"
    Then I should see the error message "The field contains tracked changes that may not be saved."
    And I should see the error message "Current content includes unprocessed changes in the English version. In order to save progress, please accept or reject them, or change the content state."
    When I select "Needs Review" from "Moderation state"
    And I press "Save"
    Then I should see the success message "Basic page Page title has been updated."
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see the error message "Current content includes unprocessed changes in the English version. In order to save progress, please accept or reject them, or change the content state."

    Examples:
  | blocked                                                                                                                                                                                                                        |
  | <p>Page body<span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1471619239866\" data-time=\"1471619234543\" data-userid=\"1\" data-username=\"admin\"> additional content</span></p> |



