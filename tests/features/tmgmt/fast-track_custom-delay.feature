@api @poetry
Feature: Fast track

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
      number: 40012
      version: 0
      part: 0
      product: REV
    status:
      -
        type: request
        code: '0'
        date: 06/10/2017
        time: 02:41:53
        message: OK
    """

  Scenario: Request using custom date field.
    Given I create a new "datestamp" field named "delay_date" on "page"
    When I am logged in as a user with the "administrator" role
    And I have the following rule:
    """
    {
      "rules_dgt_ftt_review" : {
        "LABEL" : "DGT FTT Review",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "draft",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "needs_review"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_review_request" : {
              "USING" : { "node" : [ "node" ] ,
                "delay" : "2017-12-01 15:00:00"
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
    And I have the following rule:
    """
    {
      "rules_dgt_ftt_translations_delay" : {
        "LABEL" : "DGT FTT Translations",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "REQUIRES" : [ "ne_dgt_rules", "rules", "workbench_moderation" ],
        "ON" : { "workbench_moderation_after_moderation_transition" : [] },
        "IF" : [
          { "comparison_of_moderation_states_after_transition" : {
              "previous_state_source" : [ "previous-state" ],
              "previous_state_value" : "needs_review",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "validated"
            }
          },
          { "entity_has_field" : { "entity" : [ "node" ], "field" : "delay_date" } }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_translation_request" : {
              "USING" : {
                "node" : [ "node" ],
                "delay" : [ "node:delay-date" ],
                "target_languages" : { "value" : [] },
                "dgt_ftt_workflow_code" : "STS"
              },
              "PROVIDE" : {
                "tmgmt_job" : { "tmgmt_job" : "Translation Job" },
                "dgt_service_response" : { "dgt_service_response" : "DGT Service response" },
                "dgt_service_response_status" : { "dgt_service_response_status" : "DGT Service Response - Response status" },
                "dgt_service_demand_status" : { "dgt_service_demand_status" : "DGT Service Response - Demand status" }
              }
            }
          }
        ]
      }
    }
    """
    And I go to "node/add/page"
    And I fill in "Title" with "Test page"
    And I fill in "edit-delay-date-und-0-value-day" with "14"
    And I fill in "edit-delay-date-und-0-value-month" with "11"
    And I fill in "edit-delay-date-und-0-value-year" with "2018"
    And I fill in "edit-delay-date-und-0-value-hour" with "12"
    And I fill in "edit-delay-date-und-0-value-minute" with "00"
    And I press "Save"
    Then I should see "Revision state: Draft"
    When I select "Needs Review" from "state"
    And I press "Apply"
    Then I should see "Revision state: Needs Review"
    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see "Revision state: Validated"
    And Poetry service received request should contain the following text:
      | <titre>Test page</titre>                                      |
      | <organisationResponsable>DIGIT</organisationResponsable>      |
      | <organisationAuteur>IE/CE/DIGIT</organisationAuteur>          |
      | <serviceDemandeur>IE/CE/DIGIT/A/3</serviceDemandeur>          |
      | <applicationReference>FPFIS</applicationReference>            |
      | <delai>14/11/2018</delai>                                     |
      | <attributionsDelai>14/11/2018</attributionsDelai>             |
