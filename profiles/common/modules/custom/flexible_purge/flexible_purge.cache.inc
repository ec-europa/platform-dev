<?php
/**
 * @file
 * Include file for FlexiblePurge, to be used in settings.php.
 */

/**
 * FlexiblePurgeCache emits HTTP requests when its clear() method is called.
 *
 * Note: this module provides no configuration U.I. Its behaviour can be
 * defined by setting a few Drupal variable, typically via the $conf array in
 * settings.php.
 * It is also possible to further refine this behaviour by defining some
 * functions in settings.php.
 * All variable and function names start with fp_ and end with _for_cache_bin,
 * where cache_bin must be replaced with the bin name you use (typically
 * 'cache_page').
 *
 * It supports proxying: this allows using this class without losing the
 * features of its precedecessor. A typical use case consists of using this
 * class to invalidate a web accelerator frontend while still filling the
 * cache_page MySQL table to improve response times in case the web accelerator
 * still forwards a lot of requests.
 * To do so, simply set the fp_keep_caching_for_cache_page variable to the name
 * of any class implementing DrupalCacheInterface, such as DrupalDatabaseCache,
 * Redis_Cache or MemCacheDrupal.
 */
class FlexiblePurgeCache implements DrupalCacheInterface {
  protected $bin;
  protected $actualCacheObject;

  /**
   * Construct a FlexiblePurgeCache object.
   *
   * If fp_keep_caching_for_cache_bin states a class name, instantiate an
   * instance of it and enable proxying.
   *
   * @param string $bin
   *   Cache bin name, for example 'cache_page'.
   */
  public function __construct($bin) {
    $this->bin = $bin;
    // This class has the ability to act as a proxy for another class.
    $this->actualCacheObject = NULL;
    $class = variable_get('fp_keep_caching_for_' . $bin, FALSE);
    if ($class) {
      // Initialize a $class instance that will take care of actually caching.
      // content in any kind of backend storage.
      try {
        $this->actualCacheObject = new $class($bin);
      }
      catch (Exception $e) {
        watchdog(
          'Flexible Purge',
          'Failed to initialize actual cache object: !exception',
          array('!exception' => print_r($e, TRUE)),
          WATCHDOG_ERROR
        );
      }
    }
  }

  /**
   * Proxy a method call.
   *
   * If proxying is enabled, proxy the call to $method along with its
   * $arguments to the adequate object.
   *
   * @param string $method
   *    Method - function name.
   * @param mixed $default_return
   *    Default return.
   * @param array $arguments
   *    Arguments array.
   *
   * @return mixed $default_return if proxying is disabled, or whatever the called
   *    $default_return if proxying is disabled, or whatever the called
   *    method returned.
   */
  protected function proxy($method, $default_return = NULL, $arguments = array()) {
    if (!is_null($this->actualCacheObject)) {
      return call_user_func_array(array($this->actualCacheObject, $method), $arguments);
    }
    return $default_return;
  }

  /**
   * If required, proxy the get operation. Otherwise do nothing.
   *
   * @param string $cid
   *    The cache ID of the data to retrieve.
   *
   * @return mixed
   *    The cache or FALSE on failure.
   */
  public function get($cid) {
    return $this->proxy(__FUNCTION__, FALSE, func_get_args());
  }

  /**
   * If required, proxy the getMultiple operation. Otherwise do nothing.
   *
   * @param array $cids
   *    Array with cache IDs.
   *
   * @return mixed
   *    The cache or empty array on failure.
   */
  public function getMultiple(&$cids) {
    return $this->proxy(__FUNCTION__, array(), func_get_args());
  }

  /**
   * If required, proxy the set operation. Otherwise do nothing.
   *
   * @param string $cid
   *    The cache ID.
   * @param array $data
   *    Data array.
   * @param int $expire
   *    Cache expiration settings.
   *
   * @return mixed
   *    The cache or NULL.
   */
  public function set($cid, $data, $expire = CACHE_PERMANENT) {
    return $this->proxy(__FUNCTION__, NULL, func_get_args());
  }

  /**
   * If required, proxy the isEmpty operation. Otherwise do nothing.
   */
  public function isEmpty() {
    return $this->proxy(__FUNCTION__, FALSE, func_get_args());
  }

  /**
   * Emit HTTP requests describing the clear operation.
   *
   * Emit HTTP requests describing the clear operation hinted by \a $cid and
   * \a $wildcard. Then, if required, proxy that same operation.
   *
   * @param string $cid
   *   Cache id to clear -- accept absolute URLs, URL paths or Drupal paths.
   * @param bool $wildcard
   *   Whether $cid is to be interpreted as a wildcard expression.
   *
   * @return mixed
   *    The cache or FALSE.
   */
  public function clear($cid = NULL, $wildcard = FALSE) {
    $return = $this->proxy(__FUNCTION__, FALSE, func_get_args());
    // Should we do anything at all?
    if (!variable_get('fp_skip_clear_for_' . $this->bin, FALSE)) {
      $this->emitRequestsThrottled($cid, $wildcard);
    }
    return $return;
  }

  /**
   * Check minimum cache lifetime before emitting HTTP requests.
   *
   * Check the minimum cache lifetime settings and, if permitted, emit HTTP
   * requests describing a clear operation.
   *
   * @param string $cid
   *   The cache ID.
   * @param bool $wildcard
   *   Whether $cid is to be interpreted as a wildcard expression.
   */
  public function emitRequestsThrottled($cid, $wildcard) {
    $now = time();
    $min_cache_lifetime = $this->minimumCacheLifetime($cid, $wildcard);
    if ($min_cache_lifetime > 0) {
      // There is a minimum cache lifetime to be enforced.
      $latest_clear = $this->latestEffectiveClear();
      if (is_null($latest_clear)) {
        // No known timestamp for the latest clear? Go on and set it.
        $this->emitRequests($cid, $wildcard, $now);
      }
      else {
        // We now know when the latest clear was actually triggered.
        if (($latest_clear + $min_cache_lifetime) < $now) {
          // We are beyond the minimum cache lifetime, we can proceed with the
          // actual invalidation and update the latest clear timestamp.
          $this->emitRequests($cid, $wildcard, $now);
        }
      }
    }
    else {
      // There is no minimum cache lifetime to be enforced.
      $this->emitRequests($cid, $wildcard);
    }
  }

  /**
   * Emit HTTP requests describing the clear operation hinted by arguments.
   *
   * Requests are emitted to the targets (hostname:port) listed in the
   * fp_http_targets_for_cache_bin variable.
   * The skeleton returned by the defaultRequest() method is used to compose
   * outgoing HTTP requests. It is possible to tailor this skeleton by defining
   * and implementing the fp_alter_request_for_cache_bin() function in
   * settings.php.
   *
   * Outgoing HTTP requests are emitted using Curl in a very simple way. It is
   * possible to customize what Curl will do by defining and implementing the
   * fp_alter_curl_for_cache_bin() function in settings.php.
   *
   * @param string $cid
   *   Cache id to clear -- accept absolute URLs, URL paths or Drupal
   *   paths.
   * @param bool $wildcard
   *   Whether $cid is to be interpreted as a wildcard expression.
   * @param mixed $store_timestamp
   *   Whether to store the date of the latest effective clear
   *   operation. This date can later be used to comply with the minimum cache
   *   lifetime.
   */
  public function emitRequests($cid, $wildcard, $store_timestamp = FALSE) {
    if (!$this->checkCurl()) {
      return;
    }
    // Get the default request skeleton for this clear operation.
    $default_request = $this->defaultRequest($cid, $wildcard);

    // Loop on known targets.
    $http_targets = variable_get('fp_http_targets_for_' . $this->bin, array('127.0.0.1:1234'));
    foreach ($http_targets as $target) {
      // Copy the default request to ensure it does not get passed by reference.
      $request = $default_request;

      // First chance to customize the request.
      $alter_function = 'fp_alter_request_for_' . $this->bin;
      if (function_exists($alter_function)) {
        $request = $alter_function($cid, $wildcard, $target, $request);
      }

      // Skip this target if the request was replaced by a non-array value.
      if (!is_array($request)) {
        continue;
      }

      // Actually start playing with Curl.
      $send_request = TRUE;
      $curl_res = @curl_init();
      @curl_setopt($curl_res, CURLOPT_CUSTOMREQUEST, $request['method']);
      @curl_setopt($curl_res, CURLOPT_URL, sprintf('http://%s%s', $target, $request['path']));
      @curl_setopt($curl_res, CURLOPT_HTTPHEADER, $this->formatHttpHeaders($request['headers']));
      @curl_setopt($curl_res, CURLOPT_FOLLOWLOCATION, FALSE);
      @curl_setopt($curl_res, CURLOPT_RETURNTRANSFER, TRUE);

      // Second chance to customize the request.
      $alter_function = 'fp_alter_curl_for_' . $this->bin;
      if (function_exists($alter_function)) {
        // There are too many possibilities with HTTP and too many Curl options
        // for our code to ever be perfect; therefore, it is way simpler to let
        // configuration alter our curl resource.
        $send_request = $alter_function($cid, $wildcard, $target, $request, $curl_res);
      }
      // Configuration may even abort requests.
      if ($send_request === FALSE) {
        continue;
      }

      // Send the HTTP request.
      $handle_errors = TRUE;
      $exec = @curl_exec($curl_res);
      // Allow configuration to handle errors or simply act after the response
      // was received (e.g., debug the response).
      $error_function = 'fp_curl_exec_for_' . $this->bin;

      if (function_exists($error_function)) {
        $handle_errors = $error_function($cid, $wildcard, $target, $request, $curl_res, $exec);
      }

      // Default error handling, unless instructed to skip it.
      if ($handle_errors !== FALSE) {
        if ($exec === FALSE || curl_errno($curl_res)) {
          watchdog(
            'Flexible Purge',
            'Clear operation failed for target :target: :curl_error',
            array(':target' => $target, ':curl_error' => curl_error($curl_res))
          );
        }
      }
    }
    if ($store_timestamp !== FALSE) {
      $this->setLatestEffectiveClear($store_timestamp);
    }
  }

  /**
   * Check whether Curl functions are available.
   *
   * @param bool $emit_watchdog
   *    TRUE/FALSE.
   *
   * @return bool
   *    TRUE/FALSE.
   */
  public function checkCurl($emit_watchdog = TRUE) {
    // Ensure curl is available.
    $ok = function_exists('curl_init');
    if (!$ok && $emit_watchdog) {
      watchdog(
        'Flexible Purge',
        'curl_init() does not appear to exist; no request will be sent',
        array(),
        WATCHDOG_ERROR
      );
    }

    return $ok;
  }

  /**
   * Provide the current HTTP Host.
   *
   * @return string
   *   The HTTP Host extracted from Drupal's base URL or, in case of error,
   *   $_SERVER['HTTP_HOST'].
   */
  public function getHostFromBaseUrl() {
    $parts = parse_url($GLOBALS['base_url']);
    if ($parts === FALSE) {
      // Theoretically sanitized during bootstrap.
      return $_SERVER['HTTP_HOST'];
    }
    else {
      return $parts['host'];
    }
  }

  /**
   * Provide values considered useful to describe the clear operation.
   *
   * @param string $cid
   *    The cache ID.
   * @param bool $wildcard
   *    Whether $cid is to be interpreted as a wildcard expression.
   *
   * @return array
   *    Array with values.
   */
  public function prepareValues($cid, $wildcard) {
    $values = array();
    $values['cid'] = is_array($cid) ? implode('|', $cid) : $cid;
    $values['wildcard'] = $wildcard ? 'True' : 'False';
    $values['tag'] = variable_get('fp_tag_for_' . $this->bin);
    $values['host'] = $this->getHostFromBaseUrl();
    $values['base_path'] = rtrim($GLOBALS['base_path'], '/');
    $values['base_url'] = $GLOBALS['base_url'];
    $values += $this->analyzeClearRequest($cid, $wildcard);

    return $values;
  }

  /**
   * Analyze the clear operation hinted by \a $cid and \a $wildcard.
   *
   * @param string $cid
   *    The cache ID.
   * @param bool $wildcard
   *    Whether $cid is to be interpreted as a wildcard expression.
   *
   * @return array An array with two keys:
   *    An array with two keys:
   *    - clear_type describes the kind of invalidation:
   *    - 'full' means everything related to the site is to be cleared;
   *    - 'wildcard' means the original cid was interpreted as a wildcard;
   *    - 'regexp-multiple' means multiple cids were provided
   *    - 'regexp-simple' means a single cid was provided
   *    - path_regexp is a suggestion of regular expression to achieve the
   *    required invalidation. Empty if clear_type is 'full'.
   */
  public function analyzeClearRequest($cid, $wildcard) {
    if (empty($cid) || ($wildcard === TRUE && $cid === '*')) {
      $analysis = array('clear_type' => 'full', 'path_regexp' => '');
    }
    else {
      $analysis = array(
        'clear_type' => 'regexp-' . (is_array($cid) ? 'multiple' : 'single'),
        'path_regexp' => $this->generateRegexp($cid, $wildcard),
      );
    }

    return $analysis;
  }

  /**
   * Generate regular expressions for non-full invalidations.
   *
   * Generate a regular expression which matches what must be invalidated by
   * the clear operation hinted by \a $cid and \a $wildcard.
   * If the fp_fix_cids_for_cache_bin variable is set to TRUE (this is the
   * defaults), \a $cid will be adjusted.
   *
   * @param string $cid
   *    The cache ID.
   * @param bool $wildcard
   *    Whether $cid is to be interpreted as a wildcard expression.
   *
   * @see fixCids()
   *
   * @return string
   *    Regular expression string.
   */
  public function generateRegexp($cid, $wildcard) {
    if (is_null($cid)) {
      return '';
    }
    // Start by normalizing received arguments to an array of CIDs pointing to
    // booleans stating whether or not each CID is to be treated as a wildcard.
    $norm_cid = array();
    if (is_array($cid)) {
      foreach ($cid as $id => $url) {
        // If $wildcard is an array, we assume $wildcard and $cid have the same
        // length and the same keys. This is particularly suited to parameters
        // passed by hook_expire_cache().
        // Otherwise, we simply use $wildcard as a boolean value for all cids.
        $norm_cid[$url] = is_array($wildcard) ? $wildcard[$id] : (bool) $wildcard;
      }
    }
    else {
      $norm_cid[$cid] = (bool) $wildcard;
    }

    // The cache_page bin uses absolute URLs as cid -- convert them back to
    // Drupal paths. fixCids may also be used to strip the base path.
    if (variable_get('fp_fix_cids_for_' . $this->bin, TRUE)) {
      $cid = $this->fixCids($norm_cid);
    }

    if (!count($cid)) {
      return '';
    }
    else {
      $regexp_parts = array();

      foreach ($cid as $c => $is_wildcard) {
        $c = preg_quote($c);
        $regexp_parts[] = $is_wildcard ? $c : $c . '$';
      }

      $regexp = sprintf('^(%s)', implode('|', $regexp_parts));
    }

    return $regexp;
  }

  /**
   * Fix the provided cid or list of cids.
   *
   * @param array $cid
   *    A normalized array of cids, as generated by generateRegexp().
   *
   * @return array
   *    A fixed copy of \a $cid, ensuring no cid contain a protocol scheme
   *    or a host.
   *    If the fp_strip_base_path_for_cache_bin variable is set to TRUE, the
   *    Drupal's base path is trimmed so the resulting cids become Drupal paths.
   */
  protected function fixCids($cid) {
    // Optionally, one can strip the base path when fixing cids.
    $strip_base_path = variable_get('fp_strip_base_path_for_' . $this->bin, FALSE);
    $strip_regexp = sprintf('#^%s/*#', rtrim($GLOBALS['base_path'], '/'));

    $fixed_cid = array();
    foreach ($cid as $url => $is_wildcard) {
      // parse_url has the benefit of correctly handling URLs such as "/foo"
      // or "foo/bar".
      $path = parse_url($url, PHP_URL_PATH);
      if ($path !== FALSE && !is_null($path)) {
        if ($strip_base_path) {
          $path = preg_replace($strip_regexp, '', $path);
        }
        if (drupal_strlen($path)) {
          // Keep the non-empty path, but ensure we do not override a wildcard
          // status with a non-wildcard one (the opposite is considered ok).
          if (array_key_exists($path, $fixed_cid)) {
            $fixed_cid[$path] = $fixed_cid[$path] | $is_wildcard;
          }
          else {
            $fixed_cid[$path] = $is_wildcard;
          }
        }
      }
    }

    return $fixed_cid;
  }

  /**
   * Provide the default skeleton used to generate HTTP requests to be emitted.
   *
   * This skeleton can be customized by setting the
   * fp_http_request_for_cache_bin variable.
   *
   * @return array
   *   An array with the following keys:
   *    - method: the HTTP method (or "verb") -- defaults to 'PURGE'
   *    - path: the URL to contact -- defaults to '/invalidate'
   *    - headers: an array of HTTP headers; defaults to 5 X-Invalidate-*
   *      headers: Tag, Host, Base-Path, Type, Regexp.
   *   Values within that array may contain placeholders, such as \@{tag}, and
   *   are bound to be interpreted and replaced with values from the
   *   prepareValues() method.
   */
  public function defaultRequestSkeleton() {
    // This is the default skeleton used to generate invalidation requests.
    $default_request = array(
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

    return variable_get('fp_http_request_for_' . $this->bin, $default_request);
  }

  /**
   * Helper method to interpret a request skeleton.
   *
   * @param string $item
   *   Value to interpret.
   * @param string $key
   *   Key pointing to \a $item.
   * @param array $values
   *
   *   Array associating known placeholders with their replacement
   *   values.
   */
  protected function interpretSkeleton(&$item, $key, $values) {
    foreach ($values as $token => $value) {
      $item = str_replace('@{' . $token . '}', $value, $item);
    }
  }

  /**
   * Provide the interpreted skeleton for the HTTP requests to be emitted.
   *
   * This is achieved by:
   *   - analyzing the clear operation hinted by \a $cid and \a $wildcard; this
   *     analysis results in a set of properties, such as an application tag, a
   *     clear type, a regular expression, etc;
   *   - getting the default skeleton for HTTP requests;
   *   - recursively interpreting this skeleton using the set of properties.
   *
   * @param string $cid
   *    The cache ID.
   * @param bool $wildcard
   *    Whether $cid is to be interpreted as a wildcard expression.
   *
   * @see prepareValues()
   * @see defaultRequestSkeleton()
   * @see interpretSkeleton()
   *
   * @return array
   *    interpreted skeleton for the HTTP requests.
   */
  public function defaultRequest($cid, $wildcard) {
    $values = $this->prepareValues($cid, $wildcard);
    $skeleton = $this->defaultRequestSkeleton();
    array_walk_recursive($skeleton, array($this, 'interpretSkeleton'), $values);

    return $skeleton;
  }

  /**
   * Transform headers from the skeleton into Curl-acceptable headers.
   *
   * @param array $request_headers
   *    Array with REQUEST headers.
   *
   * @return array
   *    Curl-acceptable headers array.
   */
  protected function formatHttpHeaders($request_headers) {
    $headers = array();
    foreach ($request_headers as $header => $value) {
      if (drupal_strlen(trim($value))) {
        $headers[] = sprintf('%s: %s', $header, trim($value));
      }
    }

    return $headers;
  }

  /**
   * Return the date of the latest effective clear operation.
   */
  public function latestEffectiveClear() {
    return variable_get('fp_latest_clear_for_' . $this->bin, NULL);
  }

  /**
   * Set the date of the latest effective clear operation.
   *
   * @param int $timestamp
   *    Timestamp of the latest effective clear operation.
   */
  public function setLatestEffectiveClear($timestamp) {
    variable_set('fp_latest_clear_for_' . $this->bin, $timestamp);
  }

  /**
   * Return the minimum cache lifetime.
   *
   * The minimum cache lifetime can be customized by setting the
   * fp_min_cache_lifetime_for_cache_bin variable.
   * If a single value is not flexible enough, it remains possible to tailor it
   * to the required clear operation by defining and implementing the
   * fp_refine_min_cache_lifetime_for_cache_bin() function in settings.php.
   *
   * @param string $cid
   *    The cache ID.
   * @param bool $wildcard
   *    Whether $cid is to be interpreted as a wildcard expression.
   *
   * @return mixed
   *    The minimum cache lifetime.
   */
  public function minimumCacheLifetime($cid, $wildcard) {
    $min_cache_lifetime = variable_get('fp_min_cache_lifetime_for_' . $this->bin, 0);
    if ($min_cache_lifetime > 0) {
      // There is a minimum cache lifetime to be enforced.
      // But... is this really worth enforcing it for this particular clear
      // request? Or perhaps we should apply a lower cache lifetime? This is
      // very hard to tell in a generic way, so let the configuration decide.
      $refine_function = 'fp_refine_min_cache_lifetime_for_' . $this->bin;

      if (function_exists($refine_function)) {
        $min_cache_lifetime = $refine_function($cid, $wildcard, $min_cache_lifetime);
      }
    }

    return $min_cache_lifetime;
  }

  /**
   * Return the "keep caching" cache object, if any.
   *
   * @return mixed
   *   An instance of the class stated by fp_keep_caching_for_cache_bin, or
   *   NULL.
   */
  public function keepCachingObject() {
    $class = variable_get('fp_keep_caching_for_' . $this->bin, FALSE);
    if ($class) {
      return $this->actualCacheObject;
    }

    return NULL;
  }

}
