api = 2
core = 7.x

projects[drupal][type] = "core"
projects[drupal][version] = "7.50"
projects[drupal][download][type] = get
projects[drupal][download][url] = https://ftp.drupal.org/files/projects/drupal-7.50.tar.gz

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
projects[drupal][patch][] = patches/default-settings-php-include-local-settings-3154.patch

; Allow management of visibility for pseudo-fields.
; https://www.drupal.org/node/1256368
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-3996
; Also requires a patch for i18n issue https://www.drupal.org/node/1350638,
; you can find it in multisite_drupal_standard.make.
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-n1256368-91.patch

; Allow DRUPAL_MAXIMUM_TEMP_FILE_AGE to be overridden.
; https://www.drupal.org/node/1399846
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5641
projects[drupal][patch][] = https://www.drupal.org/files/issues/cleanup-files-1399846-291.patch

; A validation error occurs for anonymous users when $form['#token'] == FALSE.
; https://www.drupal.org/node/1617918
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4863
projects[drupal][patch][] = https://www.drupal.org/files/issues/1617918-33-d7-do-not-test.patch

; Make sure drupal_add_js marks files as external when no type is specified and is_external is true:
; https://www.drupal.org/node/2697611
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-9874
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal_add_js_sanitize_external-2697611-4.patch

; Document $attributes, $title_attributes, and $content_attributes template variables
; https://www.drupal.org/node/569362
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-64
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-doc-theme-attributes-d7-569362-53.patch

; Compatibility with PHP 7
; Patch from drupal.org slightly adjusted to exclude the change in rdf_test.info
; because this doesn't apply cleanly on a stable release.
; https://www.drupal.org/node/2656548
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11467
projects[drupal][patch][] = patches/drupal-2656548-26-php7.patch
