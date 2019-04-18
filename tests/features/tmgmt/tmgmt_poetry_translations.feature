@api @poetry_mock @i18n
Feature: TMGMT Poetry features
  In order request new translations for nodes/taxonomies with Poetry service.
  As an Administrator
  I want to be able to create/manage translation requests.

  Background:
    Given the module is enabled
      |modules                |
      |tmgmt_poetry_mock      |
    And tmgmt_poetry is configured to use tmgmt_poetry_mock
    And the following languages are available:
      | languages |
      | pt-pt     |
      | fr        |
      | de        |
      | it        |

  @javascript @theme_wip @maximizedwindow
  Scenario: Test creation of translation jobs for vocabularies and terms using TMGMT.
    Given I am logged in as a user with the "administrator" role
    And the vocabulary "Vocabulary Test" is created
    And the term "Term Test" in the vocabulary "Vocabulary Test" exists
    When I go to "admin/structure/taxonomy/vocabulary_test/edit"
    And I select the radio button "Localize. Terms are common for all languages, but their name and description may be localized."
    And I press "Save and translate"
    Then I should see the success message "Updated vocabulary Vocabulary Test."

    When I check the box on the "Italian" row
    And I press "Request translation"
    Then I should see the success message "One job needs to be checked out."

    When I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the success message containing "Job has been successfully submitted for translation. Project ID is:"

    When I click "List"
    And I click "Term Test"
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    Then I should see the success message "One job needs to be checked out."

    When I fill in "Date" with a relative date of "+10" days
    And I press "Submit to translator"
    Then I should see the success message containing "Job has been successfully submitted for translation. Project ID is:"

    When I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->it" row
    Then I should see the success message "Translation was received. Check the translation page."

    When I click "Check the translation page"
    And I click "review" in the "Italian" row
    And I press "Save as completed"
    Then I should see "translated" in the "Italian" row

    When I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    Then I should see the success message "Translation was received. Check the translation page."

    When I click "Check the translation page"
    And I click "review" in the "French" row
    And I press "Save as completed"
    Then I should see "translated" in the "French" row

  @javascript @theme_wip
  Scenario: Test creation of translation jobs for vocabularies using TMGMT.
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/tmgmt/sources/i18n_string_taxonomy_vocabulary"
    Then I should see "classification (taxonomy:vocabulary:1)"

    When I check the box on the "classification (taxonomy:vocabulary:1)" row
    And I press "Request translation"
    Then I should see the success message "One job needs to be checked out."

    When I check the box "settings[languages][it]"
    And I wait for AJAX to finish
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the success message containing "Job has been successfully submitted for translation. Project ID is:"

  @javascript @theme_wip
  Scenario Outline: Request translation of a basic page into French.
    Given I am logged in as a user with the "administrator" role
    When I go to "node/add/page"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Body" with <body>
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has version to 0
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

  @javascript @theme_wip
  Scenario Outline: Request translation of a page with HTML5 or IFRAME video into French.
    Given I am logged in as a user with the "administrator" role
    When I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "<title>"
    And I fill in "Body" with "<body>"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has version to 0

    When I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Check the translation page"
    And I click "Needs review" in the "French" row
    And I press "Save as completed"
    Then I should see "None" in the "French" row

    Examples:
      | title                | body                                                                                                                                                                                                                              |
      | HTML5 Section        | <section><h1>WWW</h1><p>The World Wide Web is ...</p></section>                                                                                                                                                                   |
      | HTML5 Audio          | <audio controls=''><source src='horse.ogg' type='audio/ogg' />...</audio>                                                                                                                                                         |
      | HTML5 Video          | <video controls='' height='240' width='320'><source src='movie.mp4' type='video/mp4' />...</video>                                                                                                                                |
      | YouTube Video        | <iframe class=\"media-youtube-player\" width=\"640\" height=\"390\" title=\"Los Muppets - Mahna Mahna\" src=\"//www.youtube.com/embed/9ezRFBnWBKg\" frameborder=\"0\" allowfullscreen>Video of Los Muppets - Mahna Mahna</iframe> |
      | Vimeo Video          | <iframe class=\"media-vimeo-player\" width=\"640\" height=\"390\" title=\"EARTH\" src=\"//player.vimeo.com/video/32001208\" frameborder=\"0\" allowfullscreen>Video of EARTH</iframe>                                                         |
      | Dailymotion Video    | <iframe frameborder=\"0\" width=\"640\" height=\"390\" src=\"//www.dailymotion.com/embed/video/x4e66jg\"></iframe>                                                                                                                        |
      | AV Portal Video      | <iframe width=\"640\" height=\"390\" frameborder=\"0\" allowfullscreen=\"\" mozallowfullscreen=\"\" webkitallowfullscreen=\"\" id=\"videoplayer15672\" scrolling=\"no\" src=\"//av.tib.eu/player/15672\"></iframe>                                  |
      | HTML5 Figure         | <figure><figcaption>...</figcaption></figure>                                                                                                                                                                                     |
      | HTML5 Figure         | <source src='horse.ogg' type='audio/ogg'>                                                                                                                                                                                         |

  @javascript @theme_wip
  Scenario Outline: Request translation for multiple languages.
    Given I am logged in as a user with the "administrator" role
    When I go to "node/add/page"
    And I fill in "Title" with "<title>"
    And I fill in the rich text editor "Body" with <body>
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I store node ID of translation request page
    And I am logged in as a user with the 'contributor' role
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

    When I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see "In progress" in the "French" row
    And I should see "In progress" in the "Italian" row
    And I should see "In progress" in the "Portuguese" row

    Examples:
      | title      | body                  |
      | Page title | '<p>Body content</p>' |

  Scenario: Poetry replaces all tokens present in the node.
    Given I am logged in as a user with the "administrator" role
    When I create the following multilingual "page" content:
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

  @javascript @theme_wip
  Scenario: Fill in metadata when requesting a translation.
    Given I am logged in as a user with the "administrator" role
    And I go to "node/add/page"
    And I fill in "Title" with "Title"
    And I fill in the rich text editor "Body" with "Metadata test"
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I wait
    And I fill in "Label" with "Testing translation metadata including special chars like &"
    And inside fieldset "Contact usernames" I fill in "Author" with "AUTEUR"
    And inside fieldset "Contact usernames" I fill in "Secretaire" with "SECRETARY"
    And inside fieldset "Contact usernames" I fill in "Contact" with "CONTACT"
    And inside fieldset "Contact usernames" I fill in "Responsible" with "RESPONSIBLE"
    And inside fieldset "Organization" I fill in "Responsable" with "& DG/directorate/unit who is responsible"
    And inside fieldset "Organization" I fill in "Author" with "& DG/directorate/unit from which the document comes"
    And inside fieldset "Organization" I fill in "Requester" with "& DG/directorate/unit of the person submitting the request"
    And I fill in "Remark" with "Further remarks & comments"
    And I fill in "Date" with a relative date of "+20" days
    And I wait
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then the poetry translation service received the translation request
    And the translation request has titre "NE-CMS: my-website - Testing translation metadata including special chars like &"
    And the translation request has the following contacts:
      | type        | nickname    |
      | auteur      | auteur      |
      | secretaire  | secretary   |
      | contact     | contact     |
      | responsable | responsible |
    And the translation request has organisationResponsable "& DG/directorate/unit who is responsible"
    And the translation request has organisationAuteur "& DG/directorate/unit from which the document comes"
    And the translation request has serviceDemandeur "& DG/directorate/unit of the person submitting the request"
    And the translation request has remarque "Further remarks & comments"

  @javascript @maximizedwindow @theme_wip
  Scenario: Adding new languages to the ongoing translation request
    Given I am logged in as a user with the 'editor' role
    And I have the 'contributor' role in the 'Global editorial team' group
    When I am viewing a multilingual "page" content:
      | language | title            | body                    |
      | en       | Title            | Last change column test |
    And I click "Translate" in the "primary_tabs" region
    Then I should not see "Request addition of new languages"

    When I check the box on the "French" row
    And I check the box on the "Portuguese" row
    And I press "Request translation"
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    And I store the job reference of the translation request page
    Then I should not see "Request addition of new languages"
    And I should see "None" in the "German" row
    And I should see "None" in the "Italian" row

    When I am logged in as a user with the 'administrator' role
    And I go to "admin/poetry_mock/dashboard"
    And I click "Send 'ONG' status" in the "en->fr" row
    And I click "Send 'ONG' status" in the "en->pt-pt" row
    Then I should see the success message "The status request was sent. Check the translation page."

    When I click "Check the translation page"
    Then I should see "Request addition of new languages"

    When I click "Request addition of new languages"
    Then I wait 3 seconds
    And I fill in "Date" with a relative date of "+21" days
    And I press "Add languages"
    Then I should see the error message "You have to select at least one language to add it to the ongoing translation request."

    When I click "Request addition of new languages"
    And inside fieldset "Request addition of new languages" I check the box on the "German" row
    And inside fieldset "Request addition of new languages" I check the box on the "Italian" row
    And I press "Add languages"
    Then the poetry translation service received the additional language translation request
    And the additional language translation request contains the following languages:
      | Language   |
      | German     |
      | Italian    |
    And the relative delay date of the request is "+21" days
    And I should see "In progress" in the "German" row
    And I should see "In progress" in the "Italian" row
    And I should not see "Request addition of new languages"
    And I should see the success message "The following languages were added to the ongoing translation request: German, Italian"

  @javascript
  Scenario: Validate max field length when TMGMT Auto accept is enabled.
    Given I am logged in as a user with the "administrator" role
    When I go to "admin/config/regional/tmgmt_translator/manage/tmgmt_poetry_test_translator"
    And I check the box "Auto accept finished translations"
    And I fill in "Counter" with "NEXT_EUROPA_COUNTER"
    And I fill in "Requester code" with "WEB"
    And I fill in "Callback User" with "drupal_callback_user"
    And I fill in "Callback Password" with "drupal_callback_password"
    And I fill in "Poetry User" with "poetry_user"
    And I fill in "Poetry Password" with "poetry_password"
    And I fill in "Website identifier" with "my-website"
    And I fill in "Responsable" with "DIGIT"
    And I fill in "DG Author" with "IE/CE/DIGIT"
    And I fill in "Requester" with "IE/CE/DIGIT/A/3"
    And I fill in "Author" with "limaari"
    And I fill in "Secretaire" with "limaari"
    And I fill in "Contact" with "limaari"
    And I fill in "Responsible" with "limaari"
    And I fill in "Email to" with "limaari@sapo.pt"
    And I fill in "Email CC" with "limaari@sapo.pt"
    And I press the "Save translator" button
    Then I should see the success message "The configuration options have been saved."

    When I am logged in as a user with the "administrator" role
    And I go to "node/add/page"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Here is an English title to validate the field while sending to translation with auto accept enabled. This title is exactly 255 characters long, this way we test the translation is fine, since the response from mock will add exactly four characters fields"
    And I fill in "Body" with "The title max length is 255 characters, if this limit is exceeded an error will be thrown before trying to save the data in database, due to the validation on the needsReview process which check the translation data against field limit."
    And I press "Save"
    And I select "Published" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I check the box on the "French" row
    And I press "Request translation"
    And I fill in "Date" with a relative date of "+20" days
    And I press "Submit to translator"
    Then I should see the success message containing "Job has been successfully submitted for translation. Project ID is:"

    When I go to "admin/poetry_mock/dashboard"
    And I click "Translate" in the "en->fr" row
    And I click "Check the translation page"
    Then I should see "Needs review" in the "French" row
