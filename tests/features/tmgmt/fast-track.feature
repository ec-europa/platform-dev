@api @poetry
Feature: Fast track

  @wip
  # To trigger this test you have to have an entry regarding the review request.
  # When the steps which are creating that entry would be created we can remove the 'wip' tag.
  Scenario: Fast track workflow.

    Given these modules are enabled
      | modules                     |
      | ne_dgt_rules                |
      | ne_tmgmt_dgt_ftt_translator |

    And the following languages are available:
      | languages |
      | en        |
      | fr        |

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

    # Important: remove poetry_service overrides from your settings.php as it would override the following step.
    And the following Poetry settings:
    """
      address: http://localhost:28080/wsdl
      method: requestService
    """

    And I have the following rule:
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
              "previous_state_value" : "needs_review",
              "new_state_source" : [ "new-state" ],
              "new_state_value" : "validated"
            }
          }
        ],
        "DO" : [
          { "ne_dgt_rules_ftt_node_send_translation_request" : {
              "USING" : { "node" : [ "node" ] },
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
        responsible: John Smith
        author: John Smith
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

    And "page" content:
      | language | title     |
      | en       | Test page |

    And I am logged in as a user with the "administrator" role
    And I visit the "page" content with title "Test page"
    Then I should see "Revision state: Draft"

    When I select "Needs Review" from "state"
    And I press "Apply"
    Then I should see "Revision state: Needs Review"

    When I select "Validated" from "state"
    And I press "Apply"
    Then I should see "Revision state: Validated"

    And Poetry service received request should contain the following text:
      | <titre>Test page</titre>                                      |
      | <organisationResponsable>John Smith</organisationResponsable> |
      | <organisationAuteur>John Smith</organisationAuteur>           |
      | <serviceDemandeur>IE/CE/DIGIT/A/3</serviceDemandeur>          |
      | <applicationReference>FPFIS</applicationReference>            |
