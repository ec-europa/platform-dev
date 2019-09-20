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
        'community/*' => 'community/*',
      ),
    ),
    'views' => array(
      'values' => array(
        'articles_list' => 'articles_list',
        'calendar:month' => 'calendar:month',
        'communities_directory' => 'communities_directory',
        'e_library:page' => 'e_library:page',
        'links:page' => 'links:page',
        'news:page' => 'news:page',
        'surveys_list:page_1' => 'surveys_list:page_1',
        'wiki_list:page_1' => 'wiki_list:page_1',
        'wiki_list:page_2' => 'wiki_list:page_2',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-communities-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-communities-menu',
          'region' => 'sidebar_left',
          'weight' => '-20',
        ),
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

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'communities_menu_item';
  $context->description = 'A context to add active trail class to content posts into community';
  $context->tag = 'Menu items';
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
        'community/*/article/*' => 'community/*/article/*',
      ),
    ),
    'views' => array(
      'values' => array(
        'articles_list:page' => 'articles_list:page',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'communities_directory',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to content posts into community');
  t('Menu items');
  $export['communities_menu_item'] = $context;

  return $export;
}
