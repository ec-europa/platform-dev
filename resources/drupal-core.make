api = 2
core = 7.x

projects[drupal][type] = "core"
projects[drupal][version] = "7.97"

; Set the session's cookie lifetime to 0 so that cookies are deleted when the browser is closed.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-900
projects[drupal][patch][] = patches/drupal-set_session_cookie_lifetime_0.patch

; Hide username in RSS feed if content type is set to hide author.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2201
projects[drupal][patch][421586] = https://www.drupal.org/files/issues/2019-08-19/node-post-setting-with-test-421586-31.patch

; AJAX callbacks not properly working with the language url suffix.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4268
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11656
projects[drupal][patch][565808] = patches/drupal-ajax_js_url_suffix.patch

; Document $attributes, $title_attributes, and $content_attributes template variables
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-64
projects[drupal][patch][569362] = https://www.drupal.org/files/issues/drupal-doc-theme-attributes-d7-569362-53.patch

; Prevents the change of e-mail addresses of connected users when they are on the contact form
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-548
projects[drupal][patch][601776] = https://www.drupal.org/files/601776-contact-core-134.patch

; Add missing primary key to taxonomy_index and fix duplicate.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2845
projects[drupal][patch][610076] = https://www.drupal.org/files/issues/2020-06-18/drupal-n610076-86.patch

; Allow management of visibility for pseudo-fields.
; https://www.drupal.org/node/1256368
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-3996
; Also requires a patch for i18n issue https://www.drupal.org/node/1350638,
; you can find it in multisite_drupal_standard.make.
projects[drupal][patch][1256368] = https://www.drupal.org/files/issues/drupal-n1256368-91.patch

; node_access filters out accessible nodes when node is left joined.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-2689
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11805
projects[drupal][patch][1349080] = patches/drupal-node_access_views_relationship-1349080.patch

; Allow DRUPAL_MAXIMUM_TEMP_FILE_AGE to be overridden.
; Please read carefully: https://www.drupal.org/node/1399846?page=1#comment-11718181
; The hook_update_N() has been removed from the patch, it needs to be added somewhere else to be consistent.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5641
projects[drupal][patch][1399846] = https://www.drupal.org/files/issues/cleanup-files-1399846-315.patch

; Add missing primary key to forum.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2845
projects[drupal][patch][1466458] = https://www.drupal.org/files/issues/2020-08-03/forum-duplicate_forum_nodes-1466458-35%20.patch

; Filter "Convert URLs into links" doesn't support multilingual web addresses.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1995
projects[drupal][patch][1657886] = https://www.drupal.org/files/issues/2018-09-28/filter-urlfilter-i18n-1657886-41.patch

; Reverting to revisions prior to addition of field translations is broken.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-495
projects[drupal][patch][1992010] = https://www.drupal.org/files/issues/drupal-revision-revert-messes-up-field-translation-1992010-31_D7.patch

; Locale module: array_unshift() warning.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2438
projects[drupal][patch][2083635] = https://www.drupal.org/files/locale.module-array_unshift-warning-fix.patch

; Fix Date pop up widget breaks exposed views form with Error : Cannot create references to/from string
projects[drupal][patch][2313517] = https://www.drupal.org/files/issues/2021-12-22/cannot_create_references_tofrom_string_offsets_nor_overloaded_objects-2313517-62.patch

; Make sure that _locale_parse_js_file() never runs a file_get_contents() on a remote file.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-12269
projects[drupal][patch][2385069] = https://www.drupal.org/files/issues/2385069-19-drupal7-do-not-test.patch

; Make sure drupal_add_js marks files as external when no type is specified and is_external is true:
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-9874
projects[drupal][patch][2697611] = https://www.drupal.org/files/issues/drupal_add_js_sanitize_external-2697611-4.patch

; Image alternative text loses text preceding colon upon leaving plain-text editor or upon saving node
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2001
projects[drupal][patch][2859006] = https://www.drupal.org/files/issues/2021-04-21/2859006-26.patch
