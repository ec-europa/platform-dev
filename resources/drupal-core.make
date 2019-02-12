api = 2
core = 7.x

projects[drupal][type] = "core"
projects[drupal][version] = "7.63"

; AJAX callbacks not properly working with the language url suffix.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4268
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11656
; https://www.drupal.org/node/565808
projects[drupal][patch][] = patches/ajax-js_url_suffix.patch

; node_access filters out accessible nodes when node is left joined.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-2689
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11805
; https://www.drupal.org/node/1349080
projects[drupal][patch][] = patches/node-node_access_views_relationship-1349080.patch

; Make sure that _locale_parse_js_file() never runs a file_get_contents() on a remote file.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-12269
; https://www.drupal.org/node/2762865
; https://www.drupal.org/node/2385069
projects[drupal][patch][] = https://www.drupal.org/files/issues/2385069-19-drupal7-do-not-test.patch

; Move local configuration directives out of the Git repository.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-3154
; Improve logout functionality by updating cookie settings
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-440
projects[drupal][patch][] = patches/default-settings-updates.patch

; Allow management of visibility for pseudo-fields.
; https://www.drupal.org/node/1256368
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-3996
; Also requires a patch for i18n issue https://www.drupal.org/node/1350638,
; you can find it in multisite_drupal_standard.make.
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-n1256368-91.patch

; Allow DRUPAL_MAXIMUM_TEMP_FILE_AGE to be overridden.
; Please read carefully: https://www.drupal.org/node/1399846?page=1#comment-11718181
; The hook_update_N() has been removed from the patch, it needs to be added somewhere else to be consistent.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5641
projects[drupal][patch][] = https://www.drupal.org/files/issues/cleanup-files-1399846-315.patch

; Make sure drupal_add_js marks files as external when no type is specified and is_external is true:
; https://www.drupal.org/node/2697611
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-9874
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal_add_js_sanitize_external-2697611-4.patch

; Document $attributes, $title_attributes, and $content_attributes template variables
; https://www.drupal.org/node/569362
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-64
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-doc-theme-attributes-d7-569362-53.patch

; Fix empty label on validation error message for multiple required textfield.
; https://www.drupal.org/node/980144#comment-11695545
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-224
projects[drupal][patch][] = https://www.drupal.org/files/issues/980144-98_0.patch

; Reverting to revisions prior to addition of field translations is broken.
; https://www.drupal.org/node/1992010
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-495
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-revision-revert-messes-up-field-translation-1992010-31_D7.patch

; Prevents the change of e-mail addresses of connected users when they are on the contact form
; http://drupal.org/node/601776
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-548
projects[drupal][patch][] = https://www.drupal.org/files/601776-contact-core-134.patch

; URL alias load is inconsistent if there are more then one alias
; https://www.drupal.org/project/drupal/issues/1160764
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1993
projects[drupal][patch][] = https://www.drupal.org/files/issues/1160764-34-path_load_order.patch

; Image alternative text loses text preceding colon upon leaving plain-text editor or upon saving node
; https://www.drupal.org/project/drupal/issues/2859006
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2001
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-no_protocol_filter-2105841-111-D7.patch

; Set the session's cookie lifetime to 0 so that cookies are deleted when the browser is closed.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-900
projects[drupal][patch][] = patches/set-session-cookie-lifetime-0.patch

; Filter "Convert URLs into links" doesn't support multilingual web addresses.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1995
; See https://www.drupal.org/project/drupal/issues/1657886.
projects[drupal][patch][] = https://www.drupal.org/files/issues/2018-09-28/filter-urlfilter-i18n-1657886-41.patch
