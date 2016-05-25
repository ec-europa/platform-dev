<?php
/**
 * @file
 * Example of configuration directives to leverage the Flexible Purge module.
 */

// Tell Drupal to include the definition of the FlexiblePurgeCache class.
$conf['cache_backends'][] = 'path/to/flexible_purge/flexible_purge.cache.inc';

if (!(isset($prevent_frontend_invalidation) && $prevent_frontend_invalidation)) {
  // Use Flexible Purge to handle cache_page clear operations.
  $conf['cache_class_cache_page'] = 'FlexiblePurgeCache';
}

// Keep caching pages  into database -- unless your setup  was tweaked enough to
// make  Varnish able  to  check  Drupal sessions,  Drupal  remains better  than
// Varnish to determine whether a request is anonymous.
// Default is FALSE.
$conf['fp_keep_caching_for_cache_page'] = 'DrupalDatabaseCache';

// Do not prevent Flexible Purge from doing its work.
// Default is FALSE.
$conf['fp_skip_clear_for_cache_page'] = FALSE;

// Let Varnish know which application is emitting the PURGE request.
$conf['fp_tag_for_cache_page'] = 'our_beloved_mission_critical_app';

// Get  rid of  protocol, domain  and port  in received  cids before  generating
// regexps.
// Default is TRUE.
$conf['fp_fix_cids_for_cache_page'] = TRUE;

// Also get rid of the Drupal base path before generating regexps; this way, the
// resulting regexps are based on pure Drupal paths and do not embed any part of
// the Drupal base URL.
// Default is FALSE.
$conf['fp_strip_base_path_for_cache_page'] = TRUE;

// Array of  HTTP targets. For  instance, it can  be your Varnish  servers, with
// PURGE-dedicated TCP ports.
// Default is array('127.0.0.1:1234').
$conf['fp_http_targets_for_cache_page'] = array(
  'foo.fqdn.example.com:1234',
  'bar.fqdn.example.com:1234',
);

// The  minimum cache  lifetime, i.e.  the minimum  amount of  time that  should
// elapse between two effective clear operations.
// It is severely enforced by Flexible Purge:  not a single HTTP request will be
// emitted if the  minimum cache lifetime does not allow  it. This behaviour can
// be refined by implementing fp_refine_min_cache_lifetime_for_cache_bin().
// Default is 0.
$conf['fp_min_cache_lifetime_for_cache_page'] = 120;

// HTTP  request  template. Use  the  @{token}  syntax  to include  tokens  from
// FlexiblePurgeCache::prepareValues().
// Default can be found in FlexiblePurgeCache::defaultRequestSkeleton().
$conf['fp_http_request_for_cache_page'] = array(
  'method' => 'PURGE',
  'path' => '/invalidate',
  'headers' => array(
    'X-Invalidate-Tag' => '@{tag}',
    'X-Invalidate-Host' => '@{host}',
    'X-Invalidate-Base-Path' => '@{base_path}',
    'X-Invalidate-Type' => '@{clear_type}',
    'X-Invalidate-Regexp' => '@{path_regexp}',
  ),
);

// Disable the "Force frontend cache invalidation" button added by the module in
// admin/config/development/performance.
// Default is FALSE.
$conf['fp_disable_big_red_button'] = FALSE;

// Enable debug. This variable is used only in the sample functions below.
// Default is FALSE.
$conf['fp_debug'] = TRUE;

/* All functions below are purely optional and can be commented out.
The code provided  below simply  outputs  debug lines  when clearing  caches
through Drush.
 */

/**
 * Configuration function executed when retrieving minimum cache lifetime.
 *
 * Alter/refine  the   configured  minimum  cache  lifetime   (provided  through
 * $min_cache_lifetime) for the clear operation involving $cid and $wildcard.
 * Must return the final minimum cache lifetime.
 */
function fp_refine_min_cache_lifetime_for_cache_page($cid, $wildcard, $min_cache_lifetime) {
  if (function_exists('drush_main') && variable_get('fp_debug', FALSE)) {
    drush_print('==================================================');
    drush_print('  Treating clear operation for:');
    drush_print('    $cid: ' . var_export($cid, TRUE));
    drush_print('    $wildcard: ' . var_export($wildcard, TRUE));
    drush_print('  Minimum cache lifetime: ' . $min_cache_lifetime);
  }

  // Do not refine the configured minimum cache lifetime.
  return $min_cache_lifetime;
}

/**
 * Configuration function executed for each HTTP target.
 *
 * Alter  the HTTP  request template  ($request) intended  for the  given target
 * server ($target) for the clear operation involving $cid and $wildcard.
 * The purpose  of this  function is  to process  targets differently  and/or to
 * complete the template with dynamically computed values.
 * Must return the final request template.
 */
function fp_alter_request_for_cache_page($cid, $wildcard, $target, $request) {
  if (function_exists('drush_main') && variable_get('fp_debug', FALSE)) {
    drush_print('  Initial request for ' . $target . ': ' . var_export($request, TRUE));
  }

  // Do not actually alter the request.
  return $request;
}

/**
 * Configuration function executed before curl_exec().
 *
 * Alter  the cURL  handle ($curl_res)  which is  about to  send a  HTTP request
 * ($request)  to the  given target  server  ($target) for  the clear  operation
 * involving $cid and $wildcard.
 * The purpose of this function is  to configure absolutely anything required to
 * send the HTTP request as expected.
 * See  the  PHP  documentation  for   curl_setopt()  for  an  overview  of  the
 * possibilites.
 * Must return FALSE  to abort the request or anything  else to effectively send
 * it.
 */
function fp_alter_curl_for_cache_page($cid, $wildcard, $target, $request, &$curl_res) {
  if (function_exists('drush_main') && variable_get('fp_debug', FALSE)) {
    drush_print('Setting CURLOPT_VERBOSE.');
    @curl_setopt($curl_res, CURLOPT_VERBOSE, TRUE);
    @curl_setopt($curl_res, CURLOPT_STDERR, fopen('php://stdout', 'w'));
    drush_print('Outgoing and incoming HTTP headers:');
  }

  // Send that request.
  return TRUE;
}

/**
 * Configuration function executed after curl_exec().
 *
 * Execute  code after  curl_exec() was  called on  $curl_res in  order to  send
 * $request to $target for the clear operation involving $cid and $wildcard.
 * Whatever curl_exec() returned is made available through $exec.
 * Must return FALSE to prevent execution  of the default error handling code or
 * anything else to let Flexible Purge handle cURL errors.
 */
function fp_curl_exec_for_cache_page($cid, $wildcard, $target, $request, &$curl_res, $exec) {
  if (function_exists('drush_main') && variable_get('fp_debug', FALSE)) {
    drush_print('Response body: ' . var_export($exec, TRUE));
  }

  // Proceed with default error handling.
  return TRUE;
}
