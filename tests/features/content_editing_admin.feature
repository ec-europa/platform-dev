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

  @api
  Scenario Outline: Change tracking are visible while seeing the content page
    When I am viewing an "page" content:
      | title            | Lorem ipsum dolor sit amet                                      |
      | body             | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
      | moderation state | draft                                                           |
    When I click "Edit draft"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"
    And I should see the following warning messages:
      | warning messages | <strong>The change tracking is activated on some fields of this page</strong>.<br /> <small>Please validate tracked changes before publishing it or sending it for translation.</small> |
    And I should see an "div.ICE-Tracking" element
    
    Examples:
      | html                                                                                                                                                                                                                                                | expected                                                                                                                                                                                                                                                              |
      | <p><span class=\"ice-del ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1470931683200\" data-time=\"1470931683200\" data-userid=\"1\" data-username=\"admin\">consectetur </span></p>                                      | <p><span class=\"ice-del ckeditor-lite-del-inv ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1470931683200\" data-time=\"1470931683200\" data-userid=\"1\" data-username=\"admin\">consectetur </span></p>                                  |
      | <p><a href=\"http://www.europa.eu\"><span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"3\" data-last-change-time=\"1470931716682\" data-time=\"1470931698028\" data-userid=\"1\" data-username=\"admin\">Link example</span></a></p> | <p><a href=\"http://www.europa.eu\"><span class=\"ice-ins ckeditor-lite-ins ice-cts-1\" data-changedata=\"\" data-cid=\"3\" data-last-change-time=\"1470931716682\" data-time=\"1470931698028\" data-userid=\"1\" data-username=\"admin\">Link example</span></a></p> |

  @api
  Scenario Outline: If no changing tracks exist, I do not see any messages or HTML tags related to the change tracking
    When I am viewing an "page" content:
      | title            | Lorem ipsum dolor sit amet                                      |
      | body             | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
      | moderation state | draft                                                           |
    When I click "Edit draft"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"
    And I should not see the following warning messages:
      | warning messages | <strong>The change tracking is activated on some fields of this page</strong>.<br /> <small>Please validate tracked changes before publishing it or sending it for translation.</small> |
    And I should not see an "div.ICE-Tracking" element

    Examples:
      | html                                                                                                       | expected                                                                                                   |
      | <p>No ice-ins or ice-del tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p> | <p>No ice-ins or ice-del tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p> |
      | <p>No tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                    | <p>No tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                    |

  @api @javascript @wip
  Scenario: Upload an image with format and alt text
    When I go to "node/add/page"
    And I select "Full HTML + Change tracking" from "Text format"
    And I fill in "Title" with "Title with tracking "
    And I click the "Add media" button in the "edit-field-ne-body-und-0-value" WYSIWYG editor
    And I switch to the frame "mediaBrowser"
    And I attach the file "/profiles/multisite_drupal_standard/themes/ec_resp/logo.png" to "files[upload]"
    And I press "Next"
    Then I should see "Destination"
    When I select the radio button "Public local files served by the webserver."
    And I press "Next"
    Then I should see a "#edit-submit" element
    And I press "Save"
    And I switch to the frame "mediaStyleSelector"
    And I should see "Choose the type of display you would like for this file"
    And I click the fake "Submit" button
    And I switch out of all frames
    # Save the whole node.
    And I press "edit-submit"
    # See the image in the node
    Then I should see the "img" element in the "content" region
