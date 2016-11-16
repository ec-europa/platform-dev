About Varnish
=============
Varnish is a very fast reverse-proxy system which is serving static 
files and anonymous page views based on the previously processed 
requests.

Nexteuropa Varnish
==================
The Nexteuropa Varnish module provides functionality which allows to
send customized HTTP request to the Varnish server based on the
configured 'purge rules'.
Main purpose of those requests is to invalidate the Varnish cache to
reflect recently published content changes.

### Requirements
This feature can be enabled only with the support of the QA/Maintenance
team.
Following variables which are specific to the given environment have to
be configured before enabling the feature:
- 'nexteuropa_varnish_request_user' 
- 'nexteuropa_varnish_request_password'
- 'nexteuropa_varnish_http_targets',
- 'nexteuropa_varnish_tag',
- 'nexteuropa_varnish_request_method'

In order to enable the feature make sure that above varibales are set
then go to the `admin/structure/feature-set` page select 
'Rule-based web frontend cache purging' and click 'Validate' button.

### Custom entity - 'Purge rule'
The Nexteuropa Varnish provides additional custom entity type:
- Purge rule - machine name: `nexteuropa_varnish_cache_purge_rule` 

It allows to create and maintain a set of rules which are responsible
for sending customized HTTP requests to the Varnish server and by
that invalidating the frontend cache.

To add and maintain purge rules go to the following url:
`admin/config/frontend_cache_purge_rules`



