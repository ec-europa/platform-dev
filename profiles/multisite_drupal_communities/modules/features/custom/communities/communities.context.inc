<?php
/**
 * @file
 * communities.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function communities_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'communities';
  $context->description = 'context for communities';
  $context->tag = 'communities';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'community' => 'community',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'path' => array(
      'values' => array(
        'node/*/group' => 'node/*/group',
        'node/*/moderation' => 'node/*/moderation',
        'group/node/*' => 'group/node/*',
      ),
    ),
  );
  /* to be uncommented after next update 07/01/13 */
  /*$context->reactions = array(
    'block' => array(
      'blocks' => array(
        'multisite_og_button-og-contextual-links' => array(
          'module' => 'multisite_og_button',
          'delta' => 'og-contextual-links',
          'region' => 'sidebar_left',
          'weight' => '-10',
        ),
        'views-community_content-block_content' => array(
          'module' => 'views',
          'delta' => 'community_content-block_content',
          'region' => 'sidebar_left',
          'weight' => '-9',
        ),
        'menu-menu-communities-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-communities-menu',
          'region' => 'sidebar_left',
          'weight' => '-8',
        ),
        'views-communities_members-block_1' => array(
          'module' => 'views',
          'delta' => 'communities_members-block_1',
          'region' => 'sidebar_left',
          'weight' => '-7',
        ),
      ),
    ),
  );*/
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'multisite_og_button-og-contextual-links' => array(
          'module' => 'multisite_og_button',
          'delta' => 'og-contextual-links',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'views-community_content-block_content' => array(
          'module' => 'views',
          'delta' => 'community_content-block_content',
          'region' => 'sidebar_first',
          'weight' => '-9',
        ),
        'menu-menu-communities-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-communities-menu',
          'region' => 'sidebar_first',
          'weight' => '-8',
        ),
        'views-communities_members-block_1' => array(
          'module' => 'views',
          'delta' => 'communities_members-block_1',
          'region' => 'sidebar_first',
          'weight' => '-7',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('communities');
  t('context for communities');
  $export['communities'] = $context;

  return $export;
}
