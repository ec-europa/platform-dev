@api @poetry @i18n
Feature: TMGMT Poetry features
  In order request a new translation for the Portuguese language
  As a Translation manager user
  I want to be able to create a translation request for the Portuguese language (from Portugal)

  Background:
    Given the module is enabled
      |modules                |
      |tmgmt_poetry_mock      |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | en        |
      | pt-pt     |
      | fr        |
      | de        |
      | it        |

  Scenario: Checking the counter init request.
    Given I am logged in as a user with the 'administrator' role
    When I go to "node/add/page"
    And I fill in "Title" with "Page title"
    And I fill in "Body" with "Page body content"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-fr"
    And I press "Request translation"
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has the codeDemandeur "ABCD"
    And the translation request has the sequence "NEXT_EUROPA_COUNTER"

  @javascript
  Scenario: Create a request translation for French and Portuguese
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "Portuguese" row
    And I press the "Request translation" button
    And I wait
    Then I should see "Contact usernames"
    And I should see "Organization"

  Scenario: I can access an overview of recent translation jobs.
    Given local translator "Translator A" is available
    Given I am logged in as a user with the "administrator" role
    Given I create the following multilingual "page" content:
      | language | title              | field_ne_body     |
      | en       | Title in English 1 | Body in English 1 |
      | de       | Title in German 1  | Body in German 1  |
    And I create the following multilingual "page" content:
      | language | title              | field_ne_body     |
      | en       | Title in English 2 | Body in English 2 |
      | it       | Title in Italian 2 | Body in Italian 2 |
      | de       | Title in German 2  | Body in German 2  |
    And I create the following job for "page" with title "Title in English 1"
      | source language | en                                      |
      | target language | fr                                      |
      | translator      | Translator A                            |
      | title_field     | Title in French 1                       |
      | reference       | MAIN_4_POETRY_WEB/2016/63904/0/0/TRA    |
    And I create the following job for "page" with title "Title in English 1"
      | source language | en                                      |
      | target language | it                                      |
      | translator      | Translator A                            |
      | title_field     | Title in Italian 1                      |
      | reference       | SUB_4_POETRY_WEB/2016/63904/0/0/TRA     |
    And I create the following job for "page" with title "Title in English 2"
      | source language | en                                      |
      | target language | fr                                      |
      | translator      | Translator A                            |
      | title_field     | Title in French 2                       |
      | reference       | SUB_4_POETRY_WEB/2016/63904/0/0/TRA     |
    And I am on "admin/tmgmt/recent-changes"
    Then I should see "The translation of Title in English 1 to French is finished and can now be reviewed." in the "Title in English 1 English French" row
    And I should see "WEB/2016/63904/0/0/TRA" in the "Title in English 1 English French" row
    And I should see "The translation of Title in English 1 to Italian is finished and can now be reviewed." in the "Title in English 1 English Italian" row
    And I should see "WEB/2016/63904/0/0/TRA" in the "Title in English 1 English Italian" row
    And I should see "The translation of Title in English 2 to French is finished and can now be reviewed." in the "Title in English 2 English French" row
    And I should see "WEB/2016/63904/0/0/TRA" in the "Title in English 1 English French" row
    And I should not see "_POETRY_"
    Given the translation job with label "Title in English 1" and target language "fr" is accepted
    And I am on "admin/tmgmt/recent-changes"
    Then I should see "The translation for Title in English 1 has been accepted."
    And I should see "The translation of Title in English 1 to French is finished and can now be reviewed."

  @javascript
  Scenario: Request main job before other translations + request a new translation.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Page for main and sub jobs"
    And I fill in "Body" with "Here is the content of the page for main and sub jobs."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I check the box "settings[languages][it]"
    And I press "Submit to translator"
    Then I should not see an "#edit-languages-fr.form-radio" element
    But I should see an "#edit-languages-fr.form-checkbox" element
    And I should see "In progress" in the "French" row
    And I should see "In progress" in the "Italian" row
    And I store node ID of translation request page
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->it" row
    And I click "Needs review" in the "Italian" row
    And I press "Save as completed"
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see "None" in the "Italian" row

  Scenario: A request for translation that is not submitted won't generate a job item.
    Given I am logged in as a user with the "administrator" role
    Given I am viewing a multilingual "page" content:
      | language | title                     |
      | en       | English  Title NoJobItem  |
    And I click "Translate" in the "primary_tabs" region
    And I select the radio button "" with the id "edit-languages-pt-pt"
    And I press the "Request translation" button
    And I move backward one page
    Then I should not see the link "In progress"

  @javascript
  Scenario: Test not sending one job and moving to another job.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I fill in "Title" with "Original version"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    Then I go to "node/add/page"
    And I fill in "Title" with "A second original version"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I press "Submit to translator"
    Then I should not see an "#edit-languages-fr.form-radio" element
    But I should see an "#edit-languages-fr.form-checkbox" element
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see an "#edit-languages-fr.form-checkbox" element
    But I should not see "Please end up the active translation process before creating a new request."

  @javascript
  Scenario: Request main job before other translations.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I fill in "Title" with "Page for main and subjobs"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I select "TMGMT Poetry Test translator" from "Translator"
    And I wait for AJAX to finish
    And I check the box "settings[languages][it]"
    And I press "Submit to translator"
    But I should see "Please end up the active translation process before creating a new request."
    And I should see "In progress" in the "French" row
    And I should see "In progress" in the "Italian" row
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->it" row
    And I click "Needs review" in the "Italian" row
    And I press "Save as completed"
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see "None" in the "Italian" row

  @javascript
  Scenario: Test rejection of a translation.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Original version"
    And I fill in "Body" with "Here is the content of the page for original version."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I store job ID of translation request page
    And I press "Submit to translator"
    But I should see "Please end up the active translation process before creating a new request."
    And I should see "In progress" in the "French" row
    Then I go to "admin/poetry_mock/dashboard"
    And I click "Reject translation" in the "en->fr" row
    Then I should see "None" in the "French" row
    And I go to stored job Id translation request page
    Then I should see "Aborted" in the "French" row

  @javascript
  Scenario: Test creation of translation jobs for vocabularies using TMGMT.
    Given I am logged in as a user with the "administrator" role
    And I go to "admin/tmgmt/sources/i18n_string_taxonomy_vocabulary"
    And I should see "classification (taxonomy:vocabulary:1)"
    And I check the box on the "classification (taxonomy:vocabulary:1)" row
    And I press "Request translation"
    Then I should see the success message "One job needs to be checked out."
    And I check the box "settings[languages][it]"
    And I wait for AJAX to finish
    And I press "Submit to translator"
    Then I should see the success message containing "Job has been successfully submitted for translation. Project ID is:"

  @javascript
  Scenario Outline: Request translation of a basic page into French.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Body" with <body>
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    Then I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has version 0
    And the translation request document is valid XHTML

    Examples:
      | title                | body                                                                                 |
      | Simple text          | 'Some simple text.'                                                                  |
      | Paragraph            | '<p>A paragraph</p>'                                                                 |
      | Abbreviation         | '<p>Drupal is mainly written in <abbr title="PHP: Hypertext Preprocessor">PHP</abr>' |
      | Unclosed break       | '<p>This paragraph contains <br> a not properly closed line break.</p>'              |
      | Ampersand &, < and > | 'Title contains characters with a special meaning in HTML.'                          |
      | Entities in body     | 'Some text with &amp;, &lt; and &gt;. And do not forget &acute;!'                    |
      | Unclosed hr          | 'Let us add a thematic <hr> break.'                                                  |

  @javascript
  Scenario Outline: Request translation of a page with HTML5 into French.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "<title>"
    And I fill in "Body" with "<body>"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    When I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has version 0
    When I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see "None" in the "French" row

    Examples:
      | title                | body                                                                                                       |
      | HTML5 Section        | <section><h1>WWW</h1><p>The World Wide Web is ...</p></section>                                            |
      | HTML5 Audio          | <audio controls=''><source src='horse.ogg' type='audio/ogg' />...</audio>                                  |
      | HTML5 Video          | <video controls='' height='240' width='320'><source src='movie.mp4' type='video/mp4' />...</video>         |
      | HTML5 Figure         | <figure><figcaption>...</figcaption></figure>                                                              |

  @javascript
  Scenario Outline: Request translation for multiple languages.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Body" with <body>
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    When I click "Translate" in the "primary_tabs" region
    Then I store node ID of translation request page
    Given I am logged in as a user with the 'contributor' role
    And I have the 'contributor' role in the 'Global editorial team' group
    And I go to stored node Id translation request page
    And I check the box on the "French" row
    And I check the box on the "Italian" row
    And I check the box on the "Portuguese" row
    And I press "Request translation"
    And I wait
    Then I should see "Change translator"
    And the "edit-settings-languages-fr" field should contain "fr"
    And the "edit-settings-languages-it" field should contain "it"
    And the "edit-settings-languages-pt-pt" field should contain "pt-pt"
    And I press "Submit to translator"
    Then I should see "In progress" in the "French" row
    And I should see "In progress" in the "Italian" row
    And I should see "In progress" in the "Portuguese" row

    Examples:
      | title      | body                  |
      | Page title | '<p>Body content</p>' |

  Scenario: Poetry replaces all tokens present in the node.
    Given I am logged in as a user with the "administrator" role
    Given I create the following multilingual "page" content:
      | language | title             | field_ne_body                                                                                      |
      | en       | Two tokens please | <p>[node:1:link]{Title in English 1 as Link}.</p><p>[node:2:link]{Title in English 2 as Link}.</p> |
    And I create the following job for "page" with title "Two tokens please"
      | source language | en                                   |
      | target language | fr                                   |
      | translator      | TMGMT Poetry Test translator         |
      | title_field     | Title in French 1                    |
      | reference       | MAIN_1_POETRY_WEB/2016/63904/0/0/TRA |
    And I visit the "page" content with title "Two tokens please"
    And I click "Translate" in the "primary_tabs" region
    And I click "Needs review" in the "content" region
    Then I should see the text '<tmgmt_poetry_ignore value="[node:1:link]{Title in English 1 as Link}"/>'
    And I should see the text '<tmgmt_poetry_ignore value="[node:2:link]{Title in English 2 as Link}"/>'

  @javascript
  Scenario: Fill in metadata when requesting a translation.
    Given I am logged in as a user with the 'administrator' role
    And I go to "node/add/page"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Body" with "Metadata test"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    When I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I fill in "Label" with "Testing translation metadata including special chars like &"
    And I click "Contact usernames"
    And inside fieldset "Contact usernames" I fill in "Author" with "Janssen & Janssen auteur"
    And inside fieldset "Contact usernames" I fill in "Secretaire" with "Janssen & Janssen secretary"
    And inside fieldset "Contact usernames" I fill in "Contact" with "Janssen & Janssen contact"
    And inside fieldset "Contact usernames" I fill in "Responsible" with "Janssen & Janssen responsible"
    And I click "Organization"
    And inside fieldset "Organization" I fill in "Responsable" with "& DG/directorate/unit who is responsible"
    And inside fieldset "Organization" I fill in "Author" with "& DG/directorate/unit from which the document comes"
    And inside fieldset "Organization" I fill in "Requester" with "& DG/directorate/unit of the person submitting the request"
    And I fill in "Remark" with "Further remarks & comments"
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has titre "NE-CMS: Testing translation metadata including special chars like &"
    And the translation request has the following contacts:
      | type        | nickname                      |
      | auteur      | Janssen & Janssen auteur      |
      | secretaire  | Janssen & Janssen secretary   |
      | contact     | Janssen & Janssen contact     |
      | responsable | Janssen & Janssen responsible |
    And the translation request has organisationResponsable "& DG/directorate/unit who is responsible"
    And the translation request has organisationAuteur "& DG/directorate/unit from which the document comes"
    And the translation request has serviceDemandeur "& DG/directorate/unit of the person submitting the request"
    And the translation request has remarque "Further remarks & comments"

    Scenario: Inspect the 'Last change' data of a translation request
      Given I am logged in as a user with the 'administrator' role
      And I am viewing a multilingual "page" content:
        | language | title            | body                    |
        | en       | Title            | Last change column test |
      When I click "Translate" in the "primary_tabs" region
      Then I should see "Last change"
      When I check the box on the "French" row
      And I press "Request translation"
      And I press "Submit to translator"
      Then I see the date of the last change in the "French" row
