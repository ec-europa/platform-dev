Flexible  Purge  is a  Drupal  module  which  emits customizable  HTTP  requests
whenever a cache_bin  is cleared. It was designed to  invalidate contents cached
by reverse-proxy frontends in a very flexible way.
Basically, Flexible  Purge allows to  dynamically invalidate contents  cached by
Varnish frontends.

It is similar to the Varnish Integration (varnish) module:
* Technically,  it provides a cache-handling  class (named "FlexiblePurgeCache")
implementing the "DrupalCacheInterface".
* It can also be used together with the Cache Expiration (expire) project.

However, unlike Varnish  Integration, Flexible Purge does not  require access to
Varnish's administration socket.
Instead, it sends a single HTTP request  describing what is to be invalidated to
each Varnish frontend.
By default, this HTTP request uses the  PURGE HTTP method, which sounds like the
Purge module.
But  unlike Purge,  Flexible Purge  does  not send  one  request per  URL to  be
invalidated.
Instead, it computes various values, ranging from Drupal's base URL to a regular
expression  matching  the  required  content  invalidation  (yes,  like  Varnish
integration), and send them to Varnish frontends trough custom HTTP headers.
One can then  leverage Varnish's ability to juggle with  HTTP headers to compute
the adequate ban commands.

== Tags and imbricated base URLs ==

Flexible  Purge  was  also  inspired  by   HTTP  Cache  Tag  Auto:  its  default
configuration allows Drupal applications to  send an application-specific tag to
Varnish, which  in turn enables Varnish  to distinguish content cached  for that
specific site without the pitfalls of URLs computations.
This becomes very useful when you map  a first Drupal site to domain.com/foo and
another one to domain.com/foo/bar: you can now invalidate domain.com/foo without
invalidating domain.com/foo/bar.

== Frontend caching does not prevent backend caching ==

FlexiblePurgeCache  supports proxying,  which  means it  can  be placed  between
Drupal and  another cache-handling class, such  as the default one  which stores
cache entries to MySQL.
This typically allows generated pages to be cached in both Varnish and a storage
backend (MySQL, Memcached,  Redis, etc.) to improve performance  in case Varnish
is unable to deliver cached responses for any reason.

== Requesting invalidation does not imply control ==

* Flexible Purge does not tell Varnish  how to proceed with the invalidation; it
  merely reformulates the cache clear operations  it receives into a set of HTTP
  headers that  Varnish can then  leverage on its  own. Whether and  how Varnish
  should react to  Drupal-generated invalidation requests is  driven through VCL
  code.
  An example of such code is provided in flexible_purge.example.inc.vcl.
* Flexible Purge does not even check whether target servers are Varnish servers;
  it can  be used to  inform any other  kind of reverse-proxy,  any intermediate
  layer or any application as long as they have a HTTP listener.

== Targeted at sysadmins ==

Flexible Purge  is targeted at sysadmins,  or more specifically to  this kind of
guys who spend too much of their time hacking into settings.php and *.vcl files:
* Flexible  Purge does  not provide  any administration  U.I. --  everything was
  designed with settings.php files in mind.
* A huge part  of what FlexiblePurgeCache achieves can  be configured, tailored,
  altered and sometimes  even cancelled through standard Drupal  variables and a
  few  (optional) functions  defined in  settings.php. These  functions are  not
  Drupal hooks:  sysadmins do not  need to write their  own module to  alter the
  behaviour of Flexible Purge.
* For instance:
  * one  can  define  a  dynamic  minimum cache  lifetime  by  implementing  the
    fp_min_cache_lifetime_for_cache_page() function in settings.php.
  * The structure of HTTP requests can  be configured: TCP targets, HTTP method,
    request URI, headers (names and values).
  * In  case   this  is   not  enough,   it  remains   possible  to   alter  the
    cURL   handle  right   before  requests   are  sent   by  implementing   the
    fp_alter_curl_for_cache_page() function in settings.php.
  * It is even possible to handle what happens *after* cURL fired a request.
  * see settings.example.inc.php for technical details.
* The  FlexiblePurgeCache  class was  designed  with  'cache_page' in  mind  but
  remains usable for other cache_bins.


== Is there even a Drupal module? ==

Yes, Flexible  Purge also happens  to provide a  regular Drupal module  with the
following features:
* Tell users when exactly the frontend cache was and will be invalidated.
* Let them force that invalidation through a  "big red button" (ok, it is a lie:
  the button is not actually red).
* The big red button may be disabled (e.g., for crawl operations).
* Warn users in case the usual invalidation mechanism is disabled.
* Hook with the Cache Expiration module (if present).
