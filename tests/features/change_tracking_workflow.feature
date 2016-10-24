@api @wip @failOnTravis
Feature: Change tracking features
  In order to ease communications between editors while they manage website
  content, a tracking feature is available with WYSIWYG fields.
  I want to use it while I edit content, and I want to see tracked
  changes while I view content draft.
  Tracked changes must be cleared before content is published or sent for
  translation; otherwise the content publishing is blocked

  Background:
    Given I am logged in as a user with the 'administrator' role
    When I go to "admin/config/content/multisite_wysiwyg/workbench"
    And I check the box "edit-nexteuropa-editorial-tracking-wbm-states-validated"
    And I check the box "edit-nexteuropa-editorial-tracking-wbm-states-published"
    And I press "Save configuration"
    Then I should see the success message "The configuration options have been saved."

  Scenario Outline: "Basic page" case: If WYSIWYG workflow settings are correctly
  configured, The change of the content state to "validated" or "published" must
  be blocked if CKEditor Lite tracked changes exist in WYSIWYG fields
    Given I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I fill in "Body" with "Page body"
    And I press "Save"
    Then I should see "View draft"
    When I click "Edit draft"
    And I select "Full HTML + Change tracking" from "Text format"
    And I fill in "Body" with "<blocked>"
    And I select "Validated" from "Moderation state"
    And I press "Save"
    Then I should see the error message "Body contains tracked changes information."
    And I should see the error message "Tracked changes detected in the English version. Please reject or accept changes before setting the state to Validated or Published."
    When I select "Validated" from "Moderation state"
    And I press "Save"
    Then I should see the error message "Body contains tracked changes information."
    And I should see the error message "Tracked changes detected in the English version. Please reject or accept changes before setting the state to Validated or Published."
    When I select "Needs Review" from "Moderation state"
    And I press "Save"
    Then I should see the success message "Basic page Page title has been updated."
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see the error message "Tracked changes detected in the English version. Please reject or accept changes before setting the state to Validated or Published."

    Examples:
      | blocked                                                                                                                                                                                                                        |
      | <p>Page body<span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1471619239866\" data-time=\"1471619234543\" data-userid=\"1\" data-username=\"admin\"> additional content</span></p> |

  Scenario Outline: "Article with neutral language" case: The change of the
  content state to "validated" or "published" must be blocked if CKEditor
  Lite tracked changes exist in WYSIWYG fields
    Given I go to "node/add/article"
    And I fill in "Title" with "Article title"
    And I fill in "Body" with "Article body"
    And I press "Save"
    Then I should see "View draft"
    When I click "Edit draft"
    And I select "Full HTML + Change tracking" from "Text format"
    And I fill in "Body" with "<blocked>"
    And I select "Validated" from "Moderation state"
    And I press "Save"
    Then I should see the error message "Body contains tracked changes information."
    And I should see the error message "Tracked changes detected in this revision. Please reject or accept changes before setting the state to Validated or Published."
    When I select "Validated" from "Moderation state"
    And I press "Save"
    Then I should see the error message "Body contains tracked changes information."
    And I should see the error message "Tracked changes detected in this revision. Please reject or accept changes before setting the state to Validated or Published."
    When I select "Needs Review" from "Moderation state"
    And I press "Save"
    Then I should see the success message "Article Article title has been updated."
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see the error message "Tracked changes detected in this revision. Please reject or accept changes before setting the state to Validated or Published."

    Examples:
      | blocked                                                                                                                                                                                                                        |
      | <p>Article body<span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1471619239866\" data-time=\"1471619234543\" data-userid=\"1\" data-username=\"admin\"> additional content</span></p> |

  Scenario Outline: Change tracking are visible while seeing the content page
    Given I am viewing an "page" content:
      | title            | Lorem ipsum dolor sit amet                                      |
      | body             | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
      | moderation state | draft                                                           |
    And I click "Edit draft"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"
    And I should see the following warning messages:
      | warning messages | <strong>The change tracking is activated on some fields of this "Basic page" content</strong>.<br /> <small>Please accept or reject tracked changes before setting the content state to validated or published.</small> |
    And I should see highlighted elements

    Examples:
      | html                                                                                                                                                                                                                                                | expected                                                                                                                                                                                                                                                              |
      | <p><span class=\"ice-del ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1470931683200\" data-time=\"1470931683200\" data-userid=\"1\" data-username=\"admin\">consectetur </span></p>                                      | <p><span class=\"ice-del ckeditor-lite-del-inv ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1470931683200\" data-time=\"1470931683200\" data-userid=\"1\" data-username=\"admin\">consectetur </span></p>                                  |
      | <p><a href=\"http://www.europa.eu\"><span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"3\" data-last-change-time=\"1470931716682\" data-time=\"1470931698028\" data-userid=\"1\" data-username=\"admin\">Link example</span></a></p> | <p><a href=\"http://www.europa.eu\"><span class=\"ice-ins ckeditor-lite-ins ice-cts-1\" data-changedata=\"\" data-cid=\"3\" data-last-change-time=\"1470931716682\" data-time=\"1470931698028\" data-userid=\"1\" data-username=\"admin\">Link example</span></a></p> |

  Scenario Outline: If no changing tracks exist, I do not see any messages or HTML tags related to the change tracking
   Given I am viewing an "page" content:
      | title            | Lorem ipsum dolor sit amet                                      |
      | body             | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
      | moderation state | draft                                                           |
    When I click "Edit draft"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"
    And I should not see the following warning messages:
      | warning messages | <strong>The change tracking is activated on some fields of this "Basic page" content</strong>.<br /> <small>Please accept or reject tracked changes before setting the content state to validated or published.</small> |
    And I should not see highlighted elements

    Examples:
      | html                                                                                                       | expected                                                                                                   |
      | <p>No ice-ins or ice-del tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p> | <p>No ice-ins or ice-del tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p> |
      | <p>No tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                    | <p>No tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                    |

  Scenario Outline: The change of the content state to "validated" or "published" must be blocked if
  CKEditor Lite tracked changes exist in WYSIWYG fields of a translation
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    When I am viewing a multilingual "page" content:
      | language | title              | body                 |
      | en       | Title in English   | <p>Page body</p>     |
      | fr       | Titre en Français  | <p>Corps de page</p> |
    And I click "English" in the "header_top" region
    And I click "Français"
    And I click "New draft"
    And I select "Full HTML + Change tracking" from "field_ne_body[fr][0][format]"
    And I fill in "Body" with "<blocked>"
    And I press "Save"
    Then I should see the success message "Basic page Titre en Français has been updated."
    When I click "Français" in the "header_top" region
    And I click "English"
    When I select "Published" from "state"
    And I press "Apply"
    Then I should see the error message "Tracked changes detected in the French version. Please reject or accept changes before setting the state to Validated or Published."
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see the error message "Tracked changes detected in the French version. Please reject or accept changes before setting the state to Validated or Published."
    When I select "Needs Review" from "state"
    And I press "Apply"
    Then I should not see the error message "Tracked changes detected in the French version. Please reject or accept changes before setting the state to Validated or Published."

    Examples:
      | blocked                                                                                                                                                                                                                                  |
      | <p>Corps de page<span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1471619239866\" data-time=\"1471619234543\" data-userid=\"1\" data-username=\"admin\"> avec contenu additionnel</span></p> |

    Scenario: Make sure that inline images are correctly shown when tracking change is enabled.
      Given I am viewing an "page" content:
        | title                | Checking inline images work |
        | field_ne_body:value  | <p>The following inline image should be displayed.</p> [[{"fid":"1","view_mode":"default","fields":{"format":"default","field_file_image_alt_text[und][0][value]":"","field_file_image_title_text[und][0][value]":"","field_caption[und][0][value]":""},"type":"media","attributes":{"class":"media-element file-default"}}]] |
        | field_ne_body:format | full_html_track |
      Then I should not see "[[{"
      And I should not see "}]]"
      But the response should contain "sites/default/files/default_images/user_default.png"
