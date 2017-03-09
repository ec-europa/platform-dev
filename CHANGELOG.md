# NextEuropa Platform change log

## Version 2.3.0

### Improvements
  * NEPT-4 - Upgrade - chr module to version 7.x-1.8 (2015-Dec-04)
  * NEPT-36 - Performance - Remove css and js injectors from the platform codebase
  * NEPT-61 - DGT connector - Add website identifier in the title of the job sent via poetry
  * NEPT-62 - DGT connector - Make job deadline field mandatory & do not suggest any date
  * NEPT-69 - DGT connector - Add behat scenario to test allowing to resend a rejected job with an increment in version
  * NEPT-71 - DGT connector - Add COUNTER scenarios into behat tests
  * NEPT-93 - Performance/Varnish - Log into watchdog when web frontend caches are cleared
  * NEPT-98 - DGT connector - Allow to add more languages to an ongoing translation request
  * NEPT-112 - Contextual links are not rendered correctly in beans when listed via Views d.o/node/2084823
  * NEPT-124 - Upgrade - SA-CONTRIB-2016-050 - Flag
  * NEPT-130 - Upgrade - Display suite to 7.x-2.14 (2016-Apr-26)
  * NEPT-145 - Tracked changes - Icons shoud always be active when tracked changes exist. (code fix & add test)
  * NEPT-161 - Upgrade - menu_token to beta7 d.o/node/2838033
  * NEPT-163 - EU Login - Replace ECAS labels with new labels to align to EU login
  * NEPT-165 - Ensure PHP 7 compatibility of core platform specific code
  * NEPT-173 - Performance - Do not enable the apachesolr_multisitesearch module by default
  * NEPT-174 - Performance - Make apachesolr optional
  * NEPT-183 - Upgrade - Platform to Drupal 7.51
  * NEPT-206 - Permission 'use media wysiwyg' forced in multisite_wysiwyg feature. Move it from hard to soft config
  * NEPT-220 - Remove module multisite_review from the codebase
  * NEPT-228 - Remove possibility to add "Editorial team member" user role using the bulk update
  * NEPT-257 - Add cce_basic_config readme
  * NEPT-258 - Remove profiles/multisite_drupal_standard/inject_data.php
  * NEPT-287 - Upgrade - UUID module to beta2
  * NEPT-297 - Upgrade - Security risk: 13/25 Upgrade bootstrap to latest version
  * NEPT-357 - Upgrade - i18n_views to version 7.x-3.0-alpha1 + Patches if necessary
  * NEPT-424 - Include the path "/tests" in the CodeSniffer configuration file
  * NEPT-525 - Remove apachesolr, css_injector, js_injector and contact from communities profile
  * NEPT-553 - Nexteuropa_newsroom upgraded

### New features (For more details on each feature, see the README.md file at the root of the feature's folder)
  * NEPT-79 - Performance/Varnish - An administrator can enable the web frontend cache control feature through Feature set
  * NEPT-80 - Performance/Varnish - Automatically clear the web frontend cache of particular content when an action is performed on it
  * NEPT-81 - Performance/Varnish - Eliminate automatic full web frontend cache purges
  * NEPT-182 - DGT connector - As a CEM user I can enable a feature for DGT connector through feature set
  * NEPT-202 - Tracked changes - Create a feature for the functionality provided in ckeditor_lite
  * NEPT-403 - Contact module should be optional, create a feature that can be enabled/disabled
  * NEPT-444 - Add CDN module to the Core stack

### Bug fixes
  * NEPT-41 - Users are no longer gaining Editorial Team Member role. Fix issue & add a regression test
  * NEPT-64 - Theme - ec-resp is missing tag $attributes in template block.tpl.php d.o/node/569362
  * NEPT-102 - DGT connector - A page that was already requested for translation can be modified & requested again, even if not all previous translations were received.
  * NEPT-107 - Multilingual - Views & entity translation issue when estonian language is active
  * NEPT-121 - Simplenews - issue with entity cache : Multiple transmissions of newsletter possible. d.o/node/2801239
  * NEPT-123 - Multilingual - Error on tokens for multilingual content
  * NEPT-141 - Tracked Changes - Full HTML + Change tracking doesn't have the right filters enabled
  * NEPT-156 - Theme - ec_resp_link can generate links with an empty class attribute
  * NEPT-185 - Patch chr module to avoid corruption of files during migration. d.o/node/2816399
  * NEPT-211 - Do not generate token for types that are not defined
  * NEPT-212 - Fix issue on parent uri token for taxonomy terms
  * NEPT-221 - WYSIWYG - Description lists (dt) are not correctly rendered because they are not whitelisted in security_allowed_tags
  * NEPT-224 - Fix empty field label for required multiple textfield d.o/node/980144
  * NEPT-255 - multisite_drupal_core - Missing user_default.png and empty_gallery.png files at install
  * NEPT-291 - Nexteuropa_editorial - Addition of ckeditor_lite css file breaks display suite layout
  * NEPT-325 - mpdf version 7.0 was deleted from github
  * NEPT-412 - Security - XSS issue in node form on title fields
  * NEPT-552 - Fix trait not found in nexteuropa_multilingual.behat.inc

## Previous versions
Please refer to archived Delivery notes in the FPFIS wiki regarding previous versions.