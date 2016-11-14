@api
Feature: Content editing as administrator
  In order to manage the content on the website
  As an administrator
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