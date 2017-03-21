@api
Feature: Content editing as administrator
  In order to manage the content on the website
  As an administrator
  I want to be able to create, edit and delete content

  Background:
    Given I am logged in as a user with the 'administrator' role
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
      | <dl><dt>List Title</dt><dd>List item</dd></dl>                                               | <dt>List Title</dt>                                                                          |

  Scenario Outline: Test disallowed HTML
    When I go to "node/add/page"
    And I fill in "Title" with "<title>"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should not contain "<unexpected>"

    Examples:
      | title                                                                 | html                                                                  | unexpected                                                              |
      | <script>alert('xss');</script>                                        | <script>alert('xss');</script>                                        | <script>alert('xss');</script>                                          |
      | <a href=\"javascript:alert('xss');\">xss</a>                          | <a href=\"javascript:alert('xss');\">xss</a>                          | <a href=\"javascript:alert('xss');\">xss</a>                            |
      | <p style=\"background-image: url(javascript:alert('xss'))\">xss</p>   | <p style=\"background-image: url(javascript:alert('xss'))\">xss</p>   | <p style=\"background-image: url(javascript:alert('xss'))\">xss</p>     |
      | This is not the right way                                             | <div class=\"2classname\">Applied invalid css class</div>             | classname                                                               |
      | This is not the right way                                             | <div class=\"classname?&*\">Applied invalid css class</div>           | classname                                                               |
      | This is not the right way                                             | <div id=\"2invalidid\">A container with an invalid HTML ID</div>      | invalidid                                                               |
      | This is not the right way                                             | <div id=\"invalidid.\">A container with an invalid HTML ID</div>      | invalidid                                                               |


  Scenario Outline: Check admin UI always shows english
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | it        |
    When I go to "admin/config/regional/translate/translate"
    And I fill in "String contains" with "Body"
    And I press "Filter"
    And I click "edit" in the "field_ne_body:page:label" row
    And I fill in "French" with "Corps du texte"
    And I fill in "Italian" with "Corpo del testo"
    And I press "Save translations"
    Then I should see the success message "The string has been saved."
    Given I create the following multilingual "page" content:
      | language | title                       | field_ne_body              |
      | en       | This title is in English    | English body               |
      | fr       | Ce titre est en Français    | Corps de texte français    |
      | it       | Questo titolo è in italiano | Corpo di testo in italiano |
    And I go to "<url>"
    And I click "New draft"
    Then I should see "Body"
    And I should see "<field_ne_body>"
    And I should not see "<body_label>"

    Examples:
      | url                      | field_ne_body              | body_label      |
      | content/title-english_fr | Corps de texte français    | Corps du texte  |
      | content/title-english_it | Corpo di testo in italiano | Corpo del testo |
