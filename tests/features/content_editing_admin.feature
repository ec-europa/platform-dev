@api @ec_europa_theme
Feature: Content editing as administrator
  In order to manage the content on the website
  As an administrator
  I want to be able to create, edit and delete content

  Background:
    Given I am logged in as a user with the 'administrator' role
  @javascript
  Scenario Outline: Test allowed HTML
    # The Wysiwyg does not return the HTML exactly as entered. It will insert
    # whitespace and some additional tags. Hence the expected HTML differs from
    # the entered HTML.
    When I go to "node/add/page"
    And I click "Disable rich-text"
    And I fill in the content's title with "The right way is the right way"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the "<selector>" element should contain "<expected>"

    Examples:
      | html                                                                                         | selector                        | expected                                                                                     |
      | <p style=\"text-align:right\">The right way</p>                                              | .ecl-field__body .ecl-editor    | <p style=\"text-align:right\">The right way</p>                                              |
      | <p><span style=\"font-family:courier\"><span style=\"font-size:18px\"><strong>Fancy</strong> | .ecl-field__body .ecl-editor    | <p><span style=\"font-family:courier\"><span style=\"font-size:18px\"><strong>Fancy</strong> |
      | <p><span style=\"color:#800000\"><em><u>Yay!</u></em></span></p>                             | .ecl-field__body .ecl-editor    | <p><span style=\"color:#800000\"><em><u>Yay!</u></em></span></p>                             |
      | <pre>Preformatted text</pre>                                                                 | .ecl-field__body .ecl-editor    | <pre>Preformatted text</pre>                                                                 |
      | <blockquote>A quote</blockquote>                                                             | .ecl-field__body .ecl-editor    | <blockquote><p>A quote</p></blockquote>                                                      |
      | <ul><li>A bullet!</li></ul>                                                                  | .ecl-field__body .ecl-editor ul | <li>A bullet!</li>                                                                           |
      | <ol><li>A number?</li></ol>                                                                  | .ecl-field__body .ecl-editor ol | <li>A number?</li>                                                                           |
      | <p><a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                         | .ecl-field__body .ecl-editor    | <p><a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                         |
      | <h2 style=\"font-style:italic\">Styled heading</h2>                                          | .ecl-field__body .ecl-editor    | <h2 style=\"font-style:italic\">Styled heading</h2>                                          |
      | <div class=\"css_class-name\">Applied css class</div>                                        | .ecl-field__body .ecl-editor    | <div class=\"css_class-name\">Applied css class</div>                                        |
      | <div id=\"my-id_123\">A container with a custom HTML ID.</div>                               | .ecl-field__body .ecl-editor    | <div id=\"my-id_123\">A container with a custom HTML ID.</div>                               |
      | <dl><dt>List Title</dt><dd>List item</dd></dl>                                               | .ecl-field__body .ecl-editor    | <dt>List Title</dt>                                                                          |
      | <div id=\"2validid\">A container with an valid HTML ID</div>                                 | .ecl-field__body .ecl-editor    | 2validid                                                                                     |

  @javascript
  Scenario Outline: Test disallowed HTML
    When I go to "node/add/page"
    And I click "Disable rich-text"
    And I fill in the content's title with "<title>"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should not contain "<unexpected>"

    Examples:
      | title                                                                 | html                                                                  | unexpected                                                              |
      | <script>alert('xss');</script>                                        | <script>alert('xss');</script>                                        | <script>alert('xss');</script>                                          |
      | <a href='javascript:alert('xss');'>xss</a>                            | <a href=\"javascript:alert('xss');\">xss</a>                          | <a href=\"javascript:alert('xss');\">xss</a>                            |
      | <p style='background-image: url(javascript:alert('xss'))'>xss</p>    | <p style=\"background-image: url(javascript:alert('xss'))\">xss</p>    | <p style=\"background-image: url(javascript:alert('xss'))\">xss</p>     |
      | This is not the right way                                             | <div class=\"2classname\">Applied invalid css class</div>             | classname                                                               |
      | This is not the right way                                             | <div class=\"classname?&*\">Applied invalid css class</div>           | classname                                                               |
 
  Scenario Outline: Check admin UI always shows english
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | it        |
    Then I go to "admin/config/regional/translate/translate"
    And I fill in "String contains" with "Body"
    And I press "Filter"
    And I click "edit" in the "field_ne_body:page:label" row
    And I fill in "French" with "Corps du texte"
    And I fill in "Italian" with "Corpo del testo"
    And I press "Save translations"
    Then I should see the success message "The string has been saved."
    Given I create the following multilingual "page" content:
      | language      | title                       | field_ne_body     |
      | en            | This title is in English    | English body      |
      | fr            | Ce titre est en Français    | Corps en français |
      | it            | Questo titolo è in italiano | Corpo in italiano |
    And I go to "<url>"
    And I click "New draft"
    And I click "<language_name>"
    And I select "Basic HTML" from "Text format"
    Then I should see "Body"
    And I should see "<field_ne_body>"
    And I should not see "<body_label>"

    Examples:
      | url                      | language_name  | field_ne_body        | body_label      |
      | content/title-english_fr | French         | Corps en français    | Corps du texte  |
      | content/title-english_it | Italian        | Corpo in italiano    | Corpo del testo |
