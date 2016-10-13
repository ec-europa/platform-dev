@api @i18n
Feature: Content translation
  In order to translate my content
  As an administrator
  I want to be able to manage content and translations for fields.

  Scenario: Content page does not show mixed content language
    Given the following languages are available:
      | languages |
      | en        |
      | de        |
    Given I am logged in as a user with the 'administrator' role
    And the "field_ne_body" field is translatable
    When I go to "node/add/page"
    And I fill in "Title" with "English title"
    And I press "Save"
    And I select "Validated" from "state"
    And I press "Apply"
    And I click "Translate" in the "primary_tabs" region
    And I click "add"
    And I select "Basic HTML" from "Text format"
    And I fill in "Title" with "Deutsch title"
    And I fill in "Body" with "Deutsch Body not for English version."
    And I press "Save"
    And I click "English" in the "content" region
    Then I should not see the text "Deutsch Body not for English version."

   @javascript
  Scenario: Make sure that I can add "title_field" fields to a view when the Estonian language is enabled.
      Given the following languages are available:
        | languages |
        | en        |
        | et        |
      And I am logged in as a user with the "administrator" role
      And I import the following view:
        """
          $view = new view();
          $view->name = 'testing_view';
          $view->description = '';
          $view->tag = 'default';
          $view->base_table = 'node';
          $view->human_name = 'Testing view';
          $view->core = 7;
          $view->api_version = '3.0';
          $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

          /* Display: Master */
          $handler = $view->new_display('default', 'Master', 'default');
          $handler->display->display_options['use_more_always'] = FALSE;
          $handler->display->display_options['access']['type'] = 'perm';
          $handler->display->display_options['cache']['type'] = 'none';
          $handler->display->display_options['query']['type'] = 'views_query';
          $handler->display->display_options['exposed_form']['type'] = 'basic';
          $handler->display->display_options['pager']['type'] = 'full';
          $handler->display->display_options['style_plugin'] = 'default';
          $handler->display->display_options['row_plugin'] = 'fields';
        """
      And I visit "admin/structure/views/view/testing_view/edit"
      And I click "views-add-field"
      And I wait for AJAX to finish
      And I check the box "name[field_data_title_field.title_field_et]"
      And I press the "Add and configure fields" button
      And I wait for AJAX to finish
      And I press the "Apply" button
      And I wait for AJAX to finish
      And I press the "Save" button
      Then I should see "The view Testing view has been saved."
      And the response should contain "/admin/structure/views/nojs/config-item/testing_view/default/field/title_field_et_en"

