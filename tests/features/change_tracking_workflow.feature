@api
Feature: Change tracking features
  In order to ease communications between editors while they manage website
  content, I want to use the tracking feature available with WYSIWYG fields.
  Tracked changes must be cleared before content is published or sent for
  translation; otherwise the content publishing is blocked.

  Background:
    Given the module is enabled
      | modules                   |
      | nexteuropa_trackedchanges |
      | bean_admin_ui             |
      | context_ui                |
      | field_ui                  |
      | ds_ui                     |
      | video_ui                  |
      | migrate_ui                |
      | og_ui                     |
      | print_ui                  |
      | rules_admin               |
      | subscriptions_blog_ui     |
      | subscriptions_ui          |
      | tmgmt_ui                  |
      | tmgmt_node_ui             |
      | tmgmt_entity_ui           |
      | views_ui                  |
    And I am logged in as a user with the 'administrator' role

  Scenario: Text formats should be available
    When I go to "admin/config/content/formats"
    Then I should see "Full HTML + Change tracking"

  @javascript
  Scenario: Checking WYSIWYG enabling and disabling change tracking on given WYSIWYG profile
    When I go to "admin/config/content/wysiwyg/tracked_changes/setup"
    And I click "enable tracked changes buttons" in the "Full HTML" row
    Then I should see "Enabled" in the "Full HTML" row
    And I should see the message "Change tracking enabled on full_html WYSIWYG profile"
    When I click "disable tracked changes buttons" in the "Full HTML" row
    And I wait for the end of the batch job
    Then I should see "Disabled" in the "Full HTML" row
    And I should see the message "Change tracking disabled on full_html WYSIWYG profile"

  Scenario Outline: "Basic page" case: If WYSIWYG workflow settings are correctly
  configured, The change of the content state to "validated" or "published" must
  be blocked if CKEditor Lite tracked changes exist in WYSIWYG fields
    When I go to "admin/config/content/wysiwyg/tracked_changes/workbench"
    And I check the box "Validated"
    And I check the box "Published"
    And I press "Save configuration"
    Then I should see the success message "The configuration options have been saved."
    When I go to "node/add/page"
    And I fill in the content's title with "Page title"
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
    When I go to "node/add/article"
    And I fill in "edit-title" with "Article title"
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

  @wip
  #See nept-2440
  Scenario Outline: Change tracking are visible while seeing the content page
    When I go to "admin/config/content/wysiwyg/tracked_changes/workbench"
    And I check the box "Validated"
    And I check the box "Published"
    And I press "Save configuration"
    When I am viewing an "page" content:
      | title            | Lorem ipsum dolor sit amet                                      |
      | body             | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
      | moderation state | draft                                                           |
    And I click "Edit draft"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"
    And I should see the following warning messages:
      | warning messages | 
      | <strong>The change tracking is activated on some fields of this "Basic page" content</strong>.<br /> <small>Please accept or reject tracked changes before setting the content state to validated or published.</small> |
    And I should see highlighted elements

    Examples:
      | html                                                                                                                                                                                                                                                                                                                                                                                                                                                              | expected                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
      | <p><span class=\"ice-del ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1470931683200\" data-time=\"1470931683200\" data-userid=\"1\" data-username=\"admin\">consectetur </span></p>                                                                                                                                                                                                                                                    | <p><span class=\"ice-del ckeditor-lite-del-inv ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1470931683200\" data-time=\"1470931683200\" data-userid=\"1\" data-username=\"admin\">consectetur </span></p>                                                                                                                                                                                                                                                                  |
      | <p><a href=\"http://www.europa.eu\"><span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"3\" data-last-change-time=\"1470931716682\" data-time=\"1470931698028\" data-userid=\"1\" data-username=\"admin\">Link example</span></a><span class=\"ice-ins ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1471619239866\" data-time=\"1471619234543\" data-userid=\"1\" data-username=\"admin\"> additional content</span></p> | <p><a href=\"http://www.europa.eu\"><span class=\"ice-ins ckeditor-lite-ins ice-cts-1\" data-changedata=\"\" data-cid=\"3\" data-last-change-time=\"1470931716682\" data-time=\"1470931698028\" data-userid=\"1\" data-username=\"admin\">Link example</span></a><span class=\"ice-ins ckeditor-lite-ins ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1471619239866\" data-time=\"1471619234543\" data-userid=\"1\" data-username=\"admin\"> additional content</span></p> |

  Scenario Outline: If no changing tracks exist, I do not see any messages or HTML tags related to the change tracking
    Given I go to "admin/config/content/wysiwyg/tracked_changes/workbench"
    And I check the box "Validated"
    And I check the box "Published"
    And I press "Save configuration"
    When I am viewing an "page" content:
      | title            | Lorem ipsum dolor sit amet                                      |
      | body             | <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p> |
      | moderation state | draft                                                           |
    When I click "Edit draft"
    And I fill in "Body" with "<html>"
    And I press "Save"
    Then the response should contain "<expected>"
    And I should not see the following warning messages:
      | warning messages | 
      | <strong>The change tracking is activated on some fields of this "Basic page" content</strong>.<br /> <small>Please accept or reject tracked changes before setting the content state to validated or published.</small> |
    And I should not see highlighted elements

    Examples:
      | html                                                                                                       | expected                                                                                                   |
      | <p>No ice-ins or ice-del tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p> | <p>No ice-ins or ice-del tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p> |
      | <p>No tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                    | <p>No tracking change <a href=\"http://www.europa.eu/newsroom\">The latest news</a></p>                    |

  @theme_wip
  # It is in wip for the europa theme because it implies a step referring a
  # region. This must be evaluate deeper before being able to know how to deal with.
  Scenario Outline: The change of the content state to "validated" or "published" must be blocked if
  CKEditor Lite tracked changes exist in WYSIWYG fields of a translation
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
    When I go to "admin/config/content/wysiwyg/tracked_changes/workbench"
    And I check the box "Validated"
    And I check the box "Published"
    And I press "Save configuration"
    Then I should see the success message "The configuration options have been saved."
    When I am viewing a multilingual "page" content:
      | language | title              | body                 |
      | en       | Title in English   | <p>Page body</p>     |
      | fr       | Titre en Français  | <p>Corps de page</p> |
    And I click "English" in the "header_top" region
    And I click "Français"
    And I click "New draft"
    And I click "French"
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
        | field_ne_body:value  | "<p>The following inline image should be displayed.</p> [[{""fid"":""1"",""view_mode"":""default"",""fields"":{""format"":""default"",""field_file_image_alt_text[und][0][value]"":"" ""},""type"":""media"",""attributes"":{""class"":""media-element file-default""}}]]" |
        | field_ne_body:format | full_html_track |
      Then I should not see "[[{"
      And I should not see "}]]"
      But the response should contain "sites/default/files/default_images/user_default.png"

  @javascript
   Scenario: As content administrator, I should view all entities having tracked changes in their current revision in the
     "Content tracked changes" page
     Given the following contents using "Full HTML + Change tracking" for WYSIWYG fields:
       | language | title                                                 | Body                                                                                                                                                                                                  | moderation state | type          |
       | und      | Article without tracked changes                       | No tracked change                                                                                                                                                                                     | validated        | article       |
       | und      | Article with tracked changes                          | There are <span class="ice-del ice-cts-1" data-changedata="" data-cid="2" data-last-change-time="1470931683200" data-time="1470931683200" data-userid="1" data-username="admin">tracked change</span> | draft            | article       |
       | en       | Page without tracked changes                          | No tracked change                                                                                                                                                                                     | validated        | page          |
       | en       | Page with tracked changes                             | There are <span class="ice-del ice-cts-1" data-changedata="" data-cid="2" data-last-change-time="1470931683200" data-time="1470931683200" data-userid="1" data-username="admin">tracked change</span> | draft            | page          |
       | en       | Page with tracked changes and a published version     | No tracked change when published                                                                                                                                                                      | published        | page          |
     When I go to "content/page-tracked-changes-and-published-version_en"
     And I click "New draft"
     And I select "Basic HTML" from "Text format"
     And I fill in "Body" with "<span class=\"ice-del ice-cts-1\" data-changedata=\"\" data-cid=\"2\" data-last-change-time=\"1470931683200\" data-time=\"1470931683200\" data-userid=\"1\" data-username=\"admin\">There are tracked change now.</span>"
     And I press "Save"
     Then I should see the success message "Page with tracked changes and a published version has been updated."
     When I go to "admin/config/content/wysiwyg/tracked_changes/table_status"
     And I press "Force scanning"
    And I wait for the end of the batch job
     Then I should see the success message "The tracked changes table is rebuilt."
     When I go to "admin/content/tracked_changes"
     Then I should see "und" in the "Article with tracked changes" row
     And I should see "en" in the "Page with tracked changes" row
     And I should see "en" in the "Page with tracked changes and a published version" row
     And I should not see "Article without tracked changes"
     And I should not see "Page without tracked changes"


  @javascript
  Scenario: As administrator, I cannot disable Tracking change buttons from a WYSIWYG profile if tracked changes are detected
    on fields that use this profile
    Given the tracking change is activate for "Full HTML" WYSIWYG profile
    And the following contents using "Full HTML" for WYSIWYG fields:
      | language | title                                                 | Body                                                                                                                                                                                                  | moderation state | type          |
      | und      | Article without tracked changes                       | No tracked change                                                                                                                                                                                     | validated        | article       |
      | und      | Article with tracked changes                          | There are <span class="ice-del ice-cts-1" data-changedata="" data-cid="2" data-last-change-time="1470931683200" data-time="1470931683200" data-userid="1" data-username="admin">tracked change</span> | draft            | article       |
      | en       | Page without tracked changes                          | No tracked change                                                                                                                                                                                     | validated        | page          |
      | en       | Page with tracked changes                             | There are <span class="ice-del ice-cts-1" data-changedata="" data-cid="2" data-last-change-time="1470931683200" data-time="1470931683200" data-userid="1" data-username="admin">tracked change</span> | draft            | page          |
    When I go to "admin/config/content/wysiwyg/tracked_changes/setup"
    And I click "disable tracked changes buttons" in the "Full HTML" row
    And I wait for the end of the batch job
    Then I should see this following error message:
    """
    The deactivation of the change tracking feature for the full_html profile stopped because tracked changes have been detected.
    Please accept or reject them before proceeding to the deactivation; the list of entities with tracked changes is available here.
    """
    And I should see "Enabled" in the "Full HTML" row

