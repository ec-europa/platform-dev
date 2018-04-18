<?php

/**
 * @file
 * Helper function for installing the communities feature.
 */

/**
 * Enable the og-context negociation 'multisite_communities'.
 */
function communities_enable_og_context_negociation() {
  $og_negociations = variable_get('og_context_negotiation_group_context', array('url' => -5, 'node' => -4));
  // Ensure nexteuropa_community og context negotiation is not enabled.
  if (!isset($og_negociations["multisite_communities"]) && !isset($og_negociations["nexteuropa_communities"])) {
    $og_negociations["multisite_communities"] = array();
    variable_set('og_context_negotiation_group_context', $og_negociations);
  }
}
