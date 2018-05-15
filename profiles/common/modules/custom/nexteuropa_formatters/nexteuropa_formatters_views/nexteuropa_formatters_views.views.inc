<?php

/**
 * @file
 * Custom Views plugins implementation.
 */

/**
 * Implements hook_views_plugins().
 */
function nexteuropa_formatters_views_views_plugins() {
  return array(
    'row' => array(
      'nexteuropa_formatters_views_card_rows' => array(
        'title' => t('Europa card'),
        'help' => t('Choose fields to display in the Europa card component.'),
        'handler' => 'nexteuropa_formatters_views_card_rows',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'nexteuropa_formatters_views_blockquote_rows' => array(
        'title' => t('Europa blockquote'),
        'help' => t('Choose fields to display in the Europa blockquote component.'),
        'handler' => 'nexteuropa_formatters_views_blockquote_rows',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'nexteuropa_formatters_views_expandable_rows' => array(
        'title' => t('Europa expandable'),
        'help' => t('Choose fields to display in the Europa expandable component.'),
        'handler' => 'nexteuropa_formatters_views_expandable_rows',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'nexteuropa_formatters_views_timelines_rows' => array(
        'title' => t('Europa timelines'),
        'help' => t('Choose fields to display in the Europa timelines component.'),
        'handler' => 'nexteuropa_formatters_views_timelines_rows',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'nexteuropa_formatters_views_banner_rows' => array(
        'title' => t('Europa banner'),
        'help' => t('Choose fields to display in the Europa banner component.'),
        'handler' => 'nexteuropa_formatters_views_banner_rows',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'style' => array(
      'ec_europa_link_blocks' => array(
        'title' => t('EC Europa Link blocks'),
        'help' => t('Displays link using the EC Europa link blocks component.'),
        'handler' => 'nexteuropa_link_blocks_style',
        'theme' => 'link_blocks',
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
