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

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'communities';
  $context->description = 'context for communities';
  $context->tag = 'communities';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'article' => 'article',
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
    'views' => array(
      'values' => array(
        'articles_list' => 'articles_list',
        'communities_directory' => 'communities_directory',
      ),
    ),
  );
  $context->reactions = array(
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
        'views-og_pending_membership-block' => array(
          'module' => 'views',
          'delta' => 'og_pending_membership-block',
          'region' => 'sidebar_left',
          'weight' => '-6',
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


  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'communities_homepage';
  $context->description = '';
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
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('communities');
  $export['communities_homepage'] = $context;


  return $export;
}
