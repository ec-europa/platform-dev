@api @poetry @CleanTmgmtJobs
Feature: Fast track language selection

  Background:
    Given these modules are enabled
      | modules                     |
      | ne_dgt_rules                |
      | ne_tmgmt_dgt_ftt_translator |
    And the following languages are available:
      | languages |
      | en        |
      | fr        |
      | es        |
      | de        |
    And the following Poetry settings:
    """
      address: http://localhost:28080/wsdl
      method: requestService
    """
    And I update the "dgt_ftt" translator settings with the following values:
    """
      settings:
        dgt_counter: '40012'
        dgt_code: WEB
        callback_username: poetry
        callback_password: pass
        dgt_ftt_username: user
        dgt_ftt_password: pass
        dgt_ftt_workflow_code: STS
      organization:
        responsible: DIGIT
        author: IE/CE/DIGIT
        requester: IE/CE/DIGIT/A/3
      contacts:
        author: john_smith
        secretary: john_smith
        contact: john_smith
        responsible: john_smith
      feedback_contacts:
        email_to: john.smith@example.com
        email_cc: john.smith@example.com
    """
    And I request to change the variable "ne_dgt_rules_translator" to "dgt_ftt"
    And Poetry will return the following "response.status" message response:
    """
    identifier:
      code: WEB
      year: 2017
      number: 40029
      version: 0
      part: 0
      product: TRA
    status:
      -
        type: request
        code: '0'
        date: 06/10/2017
        time: 02:41:53
        message: OK
    """
    And "page" content:
      | language | title     |
      | en       | Test page |

  Scenario: All languages are selected by default.
    Given I have the following rule:
    """
    {
      "rules_dgt_ftt_translations" : {
        "LABEL" : "DGT FTT Translations",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "draft",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "validated"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_translation_request" : {
              "USING" : {
                "node" : [ "node" ],
                "target_languages" : { "value" : [] }
              },
              "PROVIDE" : {
                "tmgmt_job" : { "tmgmt_job" : "Translation Job" },
                "dgt_service_response" : { "dgt_service_response" : "DGT Service response" },
                "dgt_service_response_status" : { "dgt_service_response_status" : "DGT Service Response - Response status" },
                "dgt_service_demand_status" : { "dgt_service_demand_status" : "DGT Service Response - Demand status" }
              }
            }
          },
          { "drupal_message" : { "message" : [ "dgt-service-response-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-demand-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-response:raw-xml" ] } }
        ]
      }
    }
    """
    And I am logged in as a user with the "administrator" role
    And I visit the "page" content with title "Test page"
    Then I should see "Revision state: Draft"
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see "Revision state: Validated"
    When I go to "admin/tmgmt"
    Then I should see "German" in the "td" element with the "class" attribute set to "views-field views-field-target-language"
    And I should see "French" in the "td" element with the "class" attribute set to "views-field views-field-target-language"
    And I should see "Spanish" in the "td" element with the "class" attribute set to "views-field views-field-target-language"

  Scenario: Selecting a language only sends a request for that language.
    Given I have the following rule:
    """
    {
      "rules_dgt_ftt_translations" : {
        "LABEL" : "DGT FTT Translations",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "draft",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "validated"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_translation_request" : {
              "USING" : {
                "node" : [ "node" ],
                "target_languages" : { "value" : { "fr" : "fr" } }
              },
              "PROVIDE" : {
                "tmgmt_job" : { "tmgmt_job" : "Translation Job" },
                "dgt_service_response" : { "dgt_service_response" : "DGT Service response" },
                "dgt_service_response_status" : { "dgt_service_response_status" : "DGT Service Response - Response status" },
                "dgt_service_demand_status" : { "dgt_service_demand_status" : "DGT Service Response - Demand status" }
              }
            }
          },
          { "drupal_message" : { "message" : [ "dgt-service-response-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-demand-status:message" ] } },
          { "drupal_message" : { "message" : [ "dgt-service-response:raw-xml" ] } }
        ]
      }
    }
    """
    And I am logged in as a user with the "administrator" role
    And I visit the "page" content with title "Test page"
    Then I should see "Revision state: Draft"
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see "Revision state: Validated"
    When I go to "admin/tmgmt"
    Then I should see "French" in the "td" element with the "class" attribute set to "views-field views-field-target-language"
    And I should not see "German" in the "td" element with the "class" attribute set to "views-field views-field-target-language"
    And I should not see "Spanish" in the "td" element with the "class" attribute set to "views-field views-field-target-language"
