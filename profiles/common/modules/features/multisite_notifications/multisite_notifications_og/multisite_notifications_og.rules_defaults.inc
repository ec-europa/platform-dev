<?php

/**
 * @file
 * multisite_notifications_og.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function multisite_notifications_og_default_rules_configuration() {
  $items = array();
  $items['rules_multisite_og_community_refused'] = entity_import('rules_config', '{ "rules_multisite_og_community_refused" : {
      "LABEL" : "multisite OG community refused",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "draft" } },
        { "contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } },
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "community" : "community" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "node:author:mail" ],
            "subject" : "Community refused",
            "message" : "Dear [node:author:name],\\r\\n\\r\\nYour community [node:title] has been refused.\\r\\n\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_multisite_og_community_request'] = entity_import('rules_config', '{ "rules_multisite_og_community_request" : {
      "LABEL" : "multisite OG community request",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } },
        { "contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "draft" } },
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "community" : "community" } }
          }
        }
      ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "3" : "3" } },
            "subject" : "Creation of community request",
            "message" : "Dear [recipient_user:name],\\r\\n\\r\\n[node:author] requests a community creation [node:title] located at [node:url]\\r\\n\\r\\nGo to administration at [site:url]\\/en\\/admin\\/workbench"
          }
        }
      ]
    }
  }');
  $items['rules_multisite_og_member_blocked'] = entity_import('rules_config', '{ "rules_multisite_og_member_blocked" : {
      "LABEL" : "multisite OG member blocked",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "multisite notifications" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_blocked" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership has been blocked for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYour membership has been blocked for \\u0027[group:title]\\u0027 located at [group:url]",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] blocked for [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] blocked for [group:title] in [group:url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_multisite_og_member_remove'] = entity_import('rules_config', '{ "rules_multisite_og_member_remove" : {
      "LABEL" : "multisite OG member remove",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "multisite notifications" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_delete" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Group \\u0027[group:title]\\u0027 removal\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYou have been removed from \\u0027[group:title]\\u0027",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] removed from [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] removed from [group:title] in [group:url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_multisite_og_membership_approved'] = entity_import('rules_config', '{ "rules_multisite_og_membership_approved" : {
      "LABEL" : "multisite OG membership approved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "multisite notifications" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_approved" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request was approved for \\u0027[group:title]\\u0027",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \\u0027[group:title]\\u0027 located at [group:url]",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] joined [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] joined [group:title] in [group:url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_og_member_subscribe_active_'] = entity_import('rules_config', '{ "rules_og_member_subscribe_active_" : {
      "LABEL" : "multisite OG member subscribe (Active)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "multisite notifications" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request was approved for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \\u0027[group:title]\\u0027 located at [group:url]"
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] joined [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] joined [group:title] in [group:url]"
          }
        }
      ]
    }
  }');
  $items['rules_og_member_subscribe_pending_'] = entity_import('rules_config', '{ "rules_og_member_subscribe_pending_" : {
      "LABEL" : "multisite OG member subscribe (Pending)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "multisite notifications" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request for \\u0027[group:title]\\u0027",
            "message" : "[account:name],\\r\\n\\r\\nYour membership to group \\u0027[group:title]\\u0027 located at [group:url] is pending approval."
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] membership request [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] requests membership for group \\u0027[group:title]\\u0027 in [group:url].\\r\\n\\r\\n[og_membership:og-membership-request]"
          }
        }
      ]
    }
  }');
  return $items;
}
