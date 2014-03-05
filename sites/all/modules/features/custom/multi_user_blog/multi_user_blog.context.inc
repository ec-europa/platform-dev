<?php
/**
 * @file
 * multi_user_blog.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function multi_user_blog_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'blog_posts';
  $context->description = 'A context to add active trail class to blog posts';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog_post' => 'blog_post',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'blog',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to blog posts');
  t('Menu items');
  $export['blog_posts'] = $context;

  return $export;
}
