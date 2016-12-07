@api @javascript @maximizedwindow
Feature: Change tracking features
  We check that a user can enable the "NextEuropa Tracked Changes" set, but he can disable it
  only if no tracked changes are detected in the current values of WYSIWYG fields

  Background:
    Given I am logged in as a user with the 'administrator' role

  Scenario: As administrator, I can disable the "NextEuropa Tracked Changes" feature if tracked changes are not detected
  on fields that use this profile
    Given the module is enabled
      | modules                   |
      | nexteuropa_trackedchanges |
    When I go to "admin/structure/feature-set"
    And I click "Editorial Management"
    And I click the ".form-item-featureset-nexteuropa-trackedchanges" element
    And I press "Validate"
    And I wait for the batch job to finish
    Then I should see the success message "NextEuropa Tracked Changes feature is now inactive on your site."
    When I go to "admin/config/content/wysiwyg/tracked_changes/table_status"
    And the response should not contain "Tracked changes logs status"

  Scenario: As administrator, I could not disable the "NextEuropa Tracked Changes" feature if tracked changes are detected
  on fields that use this profile
    Given the module is enabled
      | modules                   |
      | nexteuropa_trackedchanges |
    And the following contents using "Full HTML + Change tracking" for WYSIWYG fields:
      | language | title                                                 | Body                                                                                                                                                                                                  | moderation state | type          |
      | und      | Article without tracked changes                       | No tracked change                                                                                                                                                                                     | validated        | article       |
      | und      | Article with tracked changes                          | There are <span class="ice-del ice-cts-1" data-changedata="" data-cid="2" data-last-change-time="1470931683200" data-time="1470931683200" data-userid="1" data-username="admin">tracked change</span> | draft            | article       |
      | en       | Page without tracked changes                          | No tracked change                                                                                                                                                                                     | validated        | page          |
      | en       | Page with tracked changes                             | There are <span class="ice-del ice-cts-1" data-changedata="" data-cid="2" data-last-change-time="1470931683200" data-time="1470931683200" data-userid="1" data-username="admin">tracked change</span> | draft            | page          |
    When I go to "admin/structure/feature-set"
    And I click "Editorial Management"
    And I click the ".form-item-featureset-nexteuropa-trackedchanges" element
    And I press "Validate"
    And I wait for the batch job to finish
    Then I should see this following error message:
    """
    The deactivation stopped because tracked changes have been detected in contents.
    Please accept or reject them before proceeding to the deactivation; the list of entities with tracked changes is available here.
    """
    When I go to "admin/config/content/wysiwyg/tracked_changes/table_status"
    And the response should contain "Tracked changes logs status"

  Scenario: As administrator, I can enable the "NextEuropa Tracked Changes" feature
    When I go to "admin/structure/feature-set"
    And I click "Editorial Management"
    And I click the ".form-item-featureset-nexteuropa-trackedchanges" element
    And I press "Validate"
    And I wait for the batch job to finish
    Then I should see the success message "NextEuropa Tracked Changes feature is now active on your site."
    When I go to "admin/config/content/wysiwyg/tracked_changes/table_status"
    And the response should contain "Tracked changes logs status"

