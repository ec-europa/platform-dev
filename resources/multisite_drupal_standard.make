api = 2
core = 7.x

; ===========
; Drupal core
; ===========

includes[] = "drupal-core.make"


; ===================
; Contributed modules
; ===================

projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.0-rc5"

projects[advagg][subdir] = "contrib"
projects[advagg][version] = "2.16"

projects[advanced_help][subdir] = "contrib"
projects[advanced_help][version] = "1.3"

projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.8"
; Issue #2178283 : Apache Solr doesn't invalidate its caches when inserting a new node type.
; https://drupal.org/node/2178283
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-2890
projects[apachesolr][patch][] = https://www.drupal.org/files/issues/apachesolr-invalidate-caches-new-node-type-2178283.patch
; Issue #1649158 : Date Facets (without a time) can show in Multiple Months.
; https://drupal.org/node/1649158
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4335
projects[apachesolr][patch][] = https://www.drupal.org/files/apachesolr-multiple-dates-hack-1649158-15.patch
; Issue #2446419 : Incorrect display of some main menu items and browser tab titles on some pages.
; https://www.drupal.org/node/2446419
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-6765
projects[apachesolr][patch][] = https://www.drupal.org/files/issues/apachesolr_search-overwritten_menu_items-2446419.patch
; Issue #2657666 : Notice: Undefined property: stdClass::$status_message
; https://www.drupal.org/node/2657666
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-7651
projects[apachesolr][patch][] = https://www.drupal.org/files/issues/apachesolr-undefined-property-2657666-4-D7.patch
;https://www.drupal.org/node/2333447#comment-10826660
projects[apachesolr][patch][] = https://www.drupal.org/files/issues/apachesolr-missing-tabs-2333447-10-D7.patch
; Issue NEXTEUROPA-11356 - setting up default timeout value for drupal_http_request function (500 errors investigation).
projects[apachesolr][patch][] = patches/apachesolr-changing_drupal_http_request_timeout_value.patch
; Delay removing entities from the index.
; https://www.drupal.org/node/2764637
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11582
projects[apachesolr][patch][] = https://www.drupal.org/files/issues/apachesolr-delay-entity-removal-2764637-1.patch

projects[apachesolr_attachments][subdir] = "contrib"
projects[apachesolr_attachments][version] = "1.4"
; Issue #2581925 : Empty parent_entity_id in apachesolr_index_entities_file table.
; https://www.drupal.org/node/2581925
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4224
projects[apachesolr_attachments][patch][] = https://www.drupal.org/files/issues/apachesolr_attachments-empty_parent_entity_id-2581925-0.patch
; Issue #1854088 : PDOException: SQLSTATE[40001]: Serialization failure: 1213 Deadlock found.
; https://www.drupal.org/node/1854088
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-3744
projects[apachesolr_attachments][patch][] = https://www.drupal.org/files/issues/apachesolr_attachments-cleanup_efficiency_and_deadlock_chance_reduction-1854088-16.patch

projects[apachesolr_multilingual][subdir] = "contrib"
projects[apachesolr_multilingual][version] = "1.3"

projects[apachesolr_multisitesearch][subdir] = "contrib"
projects[apachesolr_multisitesearch][version] = "1.1"

projects[autosave][subdir] = "contrib"
projects[autosave][version] = "2.2"

projects[bean][subdir] = "contrib"
projects[bean][version] = 1.9

projects[better_exposed_filters][subdir] = "contrib"
projects[better_exposed_filters][version] = "3.4"

projects[better_formats][subdir] = "contrib"
projects[better_formats][version] = "1.0-beta1"
projects[better_formats][patch][] = https://www.drupal.org/files/issues/better_format-strict-warning-1717470-11.patch

projects[bootstrap_gallery][subdir] = "contrib"
projects[bootstrap_gallery][version] = "3.1"

projects[bounce][subdir] = "contrib"
projects[bounce][version] = "1.7"

projects[captcha][subdir] = "contrib"
projects[captcha][version] = "1.3"

projects[chosen][subdir] = "contrib"
projects[chosen][version] = 2.0-beta4

projects[chr][subdir] = "contrib"
projects[chr][version] = "1.7"
; Issue #2512054 : Call to legacy function curl_http_request. Please use chr_curl_http_request instead.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5588
; https://www.drupal.org/node/2512054
projects[chr][patch][] = https://www.drupal.org/files/issues/chr-deprecated_call-2512054-2.patch
; Issue #2142949 : Receiving error message - Notice: Undefined offset: 1 in chr_curl_http_request().
; https://www.drupal.org/node/2142949
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-1944
projects[chr][patch][] = https://www.drupal.org/files/issues/chr-undefined-index-1-due-response-without-payload.patch
; Issue #2355631 : rewrite header host without port number.
; https://www.drupal.org/node/2355631
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-6231
projects[chr][patch][] = https://www.drupal.org/files/issues/chr-1.6-patch-rewrite-header-host-without-standard-port-number_0.patch

projects[ckeditor_link][subdir] = "contrib"
projects[ckeditor_link][version] = "2.3"

projects[ckeditor_lite][subdir] = contrib
projects[ckeditor_lite][version] = 1.0-rc3

projects[coffee][subdir] = "contrib"
projects[coffee][version] = 2.3

projects[collapse_text][subdir] = "contrib"
projects[collapse_text][version] = "2.4"
; https://www.drupal.org/node/2487115
projects[collapse_text][patch][] = http://cgit.drupalcode.org/collapse_text/patch/?id=85656e4960d22fc145d5c3e3a79b81eaeb4cbde5

projects[colorbox][subdir] = "contrib"
projects[colorbox][version] = "2.10"

projects[colors][subdir] = "contrib"
projects[colors][version] = "1.0-rc1"

projects[context][subdir] = "contrib"
projects[context][version] = "3.6"
projects[context][patch][] = patches/context-slow_menu_items-873936-20.patch

projects[context_entity_field][subdir] = "contrib"
projects[context_entity_field][version] = "1.1"
; Make condition work for entity references.
; Patch implemented in DEV version.
; https://www.drupal.org/node/1847038
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5056
projects[context_entity_field][patch][] = https://www.drupal.org/files/add-entity-references.patch

projects[context_og][subdir] = "contrib"
projects[context_og][version] = "2.1" 

projects[css_injector][subdir] = "contrib"
projects[css_injector][version] = "1.10"
; Allow file upload with css injector
; https://www.drupal.org/node/2506775
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-6580
projects[css_injector][patch][] = https://www.drupal.org/files/issues/add_upload_files_v4.patch
; Unnecessary DB query and cache_set when rules are empty
; https://www.drupal.org/node/2759319
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-12128
projects[css_injector][patch][] = https://www.drupal.org/files/issues/css_injector_load_rule_cache_empty-2759319-4.patch

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.9"

projects[customerror][subdir] = "contrib"
projects[customerror][version] = "1.4"

projects[date][subdir] = "contrib"
projects[date][version] = "2.9"
; Issue #2305049: Wrong timezone handling in migrate process.
; https://www.drupal.org/node/2305049
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-3324
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-4710
projects[date][patch][] = https://www.drupal.org/files/issues/2305049-12.patch

projects[date_ical][subdir] = "contrib"
projects[date_ical][version] = "3.9"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[ds][subdir] = "contrib"
projects[ds][version] = "2.11"

projects[easy_breadcrumb][subdir] = "contrib"
projects[easy_breadcrumb][version] = "2.12"
; Issue #2290941 : Breadcrumb shows escaped HTML tags on core admin pages
; https://www.drupal.org/node/2290941
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6753
projects[easy_breadcrumb][patch][] = https://www.drupal.org/files/issues/check-plain-vs-filter-xss_0_1.patch

projects[email][subdir] = "contrib"
projects[email][version] = "1.3"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.6"

projects[entity_translation][download][branch] = 7.x-1.x
projects[entity_translation][download][revision] = 221e302
projects[entity_translation][download][type] = git
projects[entity_translation][subdir] = "contrib"
projects[entity_translation][patch][] = patches/entity_translation-001-et-forward_revisions-1707156-23.patch

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = 1.2

projects[entityreference][download][branch] = 7.x-1.x
projects[entityreference][download][revision] = b5009cd1406f72a4
projects[entityreference][download][type] = git
projects[entityreference][subdir] = "contrib"
; Issue #2401811: Rendered entity is not language aware
; https://www.drupal.org/node/1674792
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6056
projects[entityreference][patch][] = https://www.drupal.org/files/issues/entityreference-rendered-entity-is-not-language-aware-1674792-85.patch
; Allow handlers to modify $items before calling entity_view()
; https://www.drupal.org/node/2651982
projects[entityreference][patch][] = https://www.drupal.org/files/issues/feature--entityreference-alter-items.patch

projects[entityreference_prepopulate][subdir] = "contrib"
projects[entityreference_prepopulate][version] = "1.5"
projects[entityreference_prepopulate][patch][] = patches/entityreference_prepopulate-ajax-prepopulation-1958800-1.5.patch

projects[eu_cookie_compliance][subdir] = "contrib"
projects[eu_cookie_compliance][version] = "1.14"

projects[extlink][subdir] = "contrib"
projects[extlink][version] = "1.18"

projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.5"

projects[fast_404][subdir] = "contrib"
projects[fast_404][version] = "1.5"

projects[fblikebutton][subdir] = "contrib"
projects[fblikebutton][version] = "2.3"

projects[features][subdir] = "contrib"
projects[features][version] = "2.9"
; Issue #1437264: features_var_export is converting custom class objects to arrays if don't have export method
; https://www.drupal.org/node/1437264
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4759
projects[features][patch][] = https://www.drupal.org/files/issues/features-var-export-object-1437264-12_0.patch

projects[feature_set][subdir] = "contrib"
projects[feature_set][version] = "1.3"
projects[feature_set][patch][] = patches/feature_set-add_categories_management-nexteuropa_4459.patch
projects[feature_set][patch][] = patches/feature_set-check_disable_enable-nexteuropa_4459.patch
projects[feature_set][patch][] = patches/feature_set-misc-nexteuropa_4459.patch

projects[feeds][subdir] = "contrib"
projects[feeds][version] = "2.0-beta1"
; Issue #2828605: feeds_system_info_alter() can triggers "The following module has moved within the file system".
; https://www.drupal.org/node/2828605
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-567
projects[feeds][patch][] = https://www.drupal.org/files/issues/feeds-moved-module-2828605-7.patch

projects[feeds_tamper][subdir] = "contrib"
projects[feeds_tamper][version] = "1.1"

projects[feeds_xpathparser][subdir] = "contrib"
projects[feeds_xpathparser][version] = "1.1"

projects[field_collection][subdir] = "contrib"
projects[field_collection][version] = "1.0-beta10"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.5"
; https://www.drupal.org/node/2604284
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6603
projects[field_group][patch][] = https://www.drupal.org/files/issues/field_group_label_translation_patch.patch

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-beta2"
; Fix error when switching from Public to Private destination
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-8239
; https://www.drupal.org/node/2537982
projects[file_entity][patch][] = https://www.drupal.org/files/issues/2537982-fix-changing-file-scheme.patch

projects[filefield_sources][subdir] = "contrib"
projects[filefield_sources][version] = "1.10"
; Update custom version of file_save_upload() to match Drupal 7.56
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1185
; https://www.drupal.org/node/2888308
projects[filefield_sources][patch][] = https://www.drupal.org/files/issues/filefield-sources-2888308-2.patch

projects[filefield_sources_plupload][subdir] = "contrib"
projects[filefield_sources_plupload][version] = "1.1"
; Fix Field description persistance
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7572
; https://www.drupal.org/node/2705523
projects[filefield_sources_plupload][patch][] = https://www.drupal.org/files/issues/filefield_sources_plupload-metadata_persistance-2705523.patch

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.7"

projects[flexible_purge][download][revision] = "d7cfc7d98dbffb3d9439da25c3398a46056e4086"
projects[flexible_purge][download][type] = "git"
projects[flexible_purge][download][url] = "http://git.drupal.org/project/flexible_purge.git"
projects[flexible_purge][subdir] = "contrib"


projects[flexslider][subdir] = "contrib"
projects[flexslider][version] = "2.0-rc1"

projects[flexslider_views_slideshow][download][revision] = "0b1f8e7e24c168d1820ccded63c319327d57a97e"
projects[flexslider_views_slideshow][download][type] = "git"
projects[flexslider_views_slideshow][download][url] = "http://git.drupal.org/project/flexslider_views_slideshow.git"
projects[flexslider_views_slideshow][subdir] = "contrib"

projects[fpa][subdir] = "contrib"
projects[fpa][version] = "2.6"

projects[freepager][download][revision] = "c11c40f6e3e54ff728515589600a0d8e26d831f1"
projects[freepager][download][type] = "git"
projects[freepager][download][url] = "http://git.drupal.org/project/freepager.git"
projects[freepager][subdir] = "contrib"

projects[fullcalendar][subdir] = "contrib"
projects[fullcalendar][version] = "2.0"
; Issue #2185449: Using AJAX results in errors when scrolling through months
; https://www.drupal.org/node/2185449
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4393
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6674
projects[fullcalendar][patch][] = https://www.drupal.org/files/issues/ajax_date_format-2185449-17.patch
; Issue #1803770: Uncaught TypeError: Cannot read property 'views_dom_id:***' of undefined.
; https://www.drupal.org/node/1803770
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4112
projects[fullcalendar][patch][] = https://www.drupal.org/files/issues/uncaught_typeerror-1803770-10.patch
; Issue #2325549: AJAX doesn't work in jQuery 1.9+
; https://www.drupal.org/node/2325549
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7373
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7237
projects[fullcalendar][patch][] = https://www.drupal.org/files/issues/2325549-jquery19_ajax.patch

projects[geofield][subdir] = "contrib"
projects[geofield][version] = "2.3"
projects[geofield][patch][] = https://www.drupal.org/files/issues/geofield-feeds_import_not_saving-2534822-17.patch

projects[geophp][download][branch] = 7.x-1.x
projects[geophp][download][revision] = 2777c5e
projects[geophp][download][type] = git
projects[geophp][subdir] = "contrib"

projects[hidden_captcha][subdir] = "contrib"
projects[hidden_captcha][version] = "1.0"

projects[i18n][subdir] = "contrib"
projects[i18n][version] = "1.13"
; Language field display should default to hidden.
; https://www.drupal.org/node/1350638
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-3996
; Also requires a patch for Drupal core issue https://www.drupal.org/node/1256368,
; you can find it in drupal-core.make.
projects[i18n][patch][] = https://www.drupal.org/files/i18n-hide_language_by_default-1350638-5.patch
projects[i18n][patch][] = https://www.drupal.org/files/issues/i18n-2092883-5-term%20field-not%20displayed.patch

projects[i18nviews][download][revision] = "dae921bd53cd321f5f0addaa06402018b0abbfb6"
projects[i18nviews][download][type] = "git"
projects[i18nviews][download][url] = "http://git.drupal.org/project/i18nviews.git"
projects[i18nviews][subdir] = "contrib"

projects[inline_entity_form][subdir] = "contrib"
projects[inline_entity_form][version] = "1.6"

projects[integration][download][revision] = "2b29abc8a34f051fbb82c47deeb02e4456faf995"
projects[integration][download][type] = "git"
projects[integration][download][url] = "http://git.drupal.org/project/integration.git"
projects[integration][subdir] = "contrib"

projects[integration_couchdb][download][revision] = "dcadb1ea483cbdaa7f476f7e0e8530873f484616"
projects[integration_couchdb][download][type] = "git"
projects[integration_couchdb][download][url] = "http://git.drupal.org/project/integration_couchdb.git"
projects[integration_couchdb][subdir] = "contrib"

projects[job_scheduler][subdir] = "contrib"
projects[job_scheduler][version] = "2.0-alpha3"

projects[jplayer][subdir] = "contrib"
projects[jplayer][version] = "2.0-beta1"

projects[jqmulti][subdir] = "contrib"
projects[jqmulti][version] = "1.0"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.7"
; Issue #2621436: Allow permissions to granted roles.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7825
projects[jquery_update][patch][] = https://www.drupal.org/files/issues/jquery_update_permissions-2621436-2_0.patch

projects[js_injector][subdir] = "contrib"
projects[js_injector][version] = "2.1"
; Issue #1820210: After packing a JS Injector Rule into a feature, Notice: Undefined property: stdClass::$crid in js_injector_init() .
; https://www.drupal.org/node/1820210
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-8855
projects[js_injector][patch][] = https://www.drupal.org/files/issues/change-js_filename-1820210-2.patch
projects[js_injector][patch][] = patches/js_injector-delete-space-in-the-name-of-js-file.patch

projects[l10n_update][subdir] = "contrib"
projects[l10n_update][version] = "2.0"
; Allow to override the http client code, to support proxying secure
; http connections with the chr module.
; https://www.drupal.org/node/750000
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11765
projects[l10n_update][patch][] = https://www.drupal.org/files/issues/l10n_update-allow-alternate-http-client-750000-15.patch

projects[language_cookie][subdir] = "contrib"
projects[language_cookie][version] = "1.9"

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.2"

projects[link][subdir] = "contrib"
projects[link][version] = "1.4"

projects[linkchecker][subdir] = "contrib"
projects[linkchecker][version] = "1.2"
projects[linkchecker][patch][] = https://www.drupal.org/files/issues/bean-integration-2127731-0.patch
projects[linkchecker][patch][] = https://www.drupal.org/files/issues/linkchecker-max_redirects-2593465-1-D7_0.patch

projects[mail_edit][subdir] = "contrib"
projects[mail_edit][version] = "1.1"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = "2.34"

projects[maxlength][subdir] = "contrib"
projects[maxlength][version] = "3.2-beta2"

projects[media][subdir] = contrib
projects[media][version] = 2.0-beta1
; Issue #2062721: Add a white list of file fields that can be overwritten when the file is added in the wysiwyg
; https://www.drupal.org/node/2062721
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-2607
projects[media][patch][] = https://www.drupal.org/files/issues/media-wysiwyg-override-white-list-2062721-86.patch
; Issue #2401811: With Media WYSIWYG enabled - "Contextual links" are shown for anonymous users.
; https://www.drupal.org/node/2401811
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-3650
projects[media][patch][] = http://www.drupal.org/files/issues/file_entity-remove-contextual-links-2401811-11.patch
; Issue #2028231: Embedded documents in the WYSIWYG can be very hard to delete
; https://www.drupal.org/node/2028231
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-771
; Media markup navigation causes duplicated links
projects[media][patch][] = https://www.drupal.org/files/issues/media-delete-embedded-document-2028231-11.patch
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1026
projects[media][patch][] = patches/media-inputs_whitelist-1026.patch


projects[media_crop][subdir] = "contrib"
projects[media_crop][version] = "1.4"

projects[media_dailymotion][subdir] = "contrib"
projects[media_dailymotion][version] = "1.1"
; Issue #2560403: Provide Short URL for media dailymotion.
; https://www.drupal.org/node/2560403
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7082
projects[media_dailymotion][patch][] = https://www.drupal.org/files/issues/media_dailymotion-mini-url-2560403-7-7.x.patch
projects[media_dailymotion][patch][] = patches/media_dailymotion-handle_protocol-4103.patch

projects[media_flickr][subdir] = "contrib"
projects[media_flickr][version] = "1.0-alpha4"
projects[media_flickr][patch][] = patches/media_flickr-Media_v2_removed_XML_APIs-2089665-1.patch
projects[media_flickr][patch][] = patches/media_flickr-fix_photoset_url_issue-2183.patch
projects[media_flickr][patch][] = patches/media_flickr-missing_thumbnail-2494.patch
projects[media_flickr][patch][] = patches/media_flickr-undefined_index-2183.patch
; Support for newer Flickr album urls.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-12401
; https://www.drupal.org/node/2602558
projects[media_flickr][patch][] = https://www.drupal.org/files/issues/import_albums_error-7.x-1.x-2602558-5.patch

projects[media_node][subdir] = "contrib"
projects[media_node][version] = "1.0-rc2"
projects[media_node][patch][] = patches/media_node-incorrect_permission_check-4273.patch

projects[media_vimeo][subdir] = "contrib"
projects[media_vimeo][version] = "2.1"

projects[media_youtube][subdir] = "contrib"
projects[media_youtube][version] = "3.0"

projects[media_colorbox][subdir] = "contrib"
projects[media_colorbox][version] = "1.0-rc4"

projects[menu_attributes][subdir] = "contrib"
projects[menu_attributes][version] = "1.0-rc3"
projects[menu_attributes][patch][] = patches/menu_attributes-add_icon_for_menu_item-2327.patch
projects[menu_attributes][patch][] = patches/menu_attributes-option_to_disable_css_class-2988.patch
projects[menu_attributes][patch][] = patches/menu_attributes-option_to_hide_children-6757.patch

projects[menu_block][subdir] = "contrib"
projects[menu_block][version] = "2.7"
projects[menu_block][patch][] = patches/menu_block-jqueryUI_issue-5211.patch

projects[menu_token][subdir] = "contrib"
projects[menu_token][version] = "1.0-beta5"
projects[menu_token][patch][] = patches/menu_token-link_uuid_menu_items_can_not_be_edited-2005556-2.patch

projects[message][subdir] = "contrib"
projects[message][version] = "1.10"

projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.7"

; A recent version of the Migrate module is pinned that contains a fix for
; https://www.drupal.org/node/2504517
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-4710
; Todo: revert back to the stable version when Migrate 7.x-2.9 is released.
projects[migrate][download][branch] = 7.x-2.x
projects[migrate][download][revision] = 046c6ad
projects[migrate][download][type] = git
projects[migrate][subdir] = contrib

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.0-beta4"

projects[nexteuropa_newsroom][download][branch] = 7.x-1.x
projects[nexteuropa_newsroom][download][type] = git
projects[nexteuropa_newsroom][subdir] = "custom"
projects[nexteuropa_newsroom][download][tag] = v3.2
projects[nexteuropa_newsroom][download][url] = https://github.com/ec-europa/nexteuropa-newsroom-reference.git

projects[node_export][subdir] = "contrib"
projects[node_export][version] = "3.0"

projects[og][subdir] = "contrib"
projects[og][version] = "2.9"
; VBO and OG
; https://www.drupal.org/node/2561507
projects[og][patch][] = https://www.drupal.org/files/issues/og_vbo_and_og_2561507-6.patch
projects[og][patch][] = patches/og-og_field_access-bypass_field_access-5159.patch

; NEXTEUROPA-11789 Issue in Bean reference to OG
; https://www.drupal.org/node/1880226
projects[og][patch][] = https://www.drupal.org/files/issues/og-use_numeric_id_for_membership_etid-1880226-5.patch

projects[og_linkchecker][download][branch] = 7.x-1.x
projects[og_linkchecker][download][revision] = 7257d0e
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][subdir] = "contrib"
projects[og_linkchecker][patch][] = patches/og_linkchecker-001-og_linkchecker-og-2-x-compatibility-2214661-2.patch

projects[om_maximenu][subdir] = "contrib"
projects[om_maximenu][version] = "1.44"

projects[password_policy][subdir] = "contrib"
projects[password_policy][version] = "2.0-alpha5"
; https://www.drupal.org/node/2489918 - MULTISITE-8185
projects[password_policy][patch][] = https://www.drupal.org/files/issues/password_policy-7.x-2.x-fix_element_alter_error-2489918-4.patch

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.3"
; https://www.drupal.org/node/1267966
; The online patch doesn't work with 1.3 version
projects[pathauto][patch][] = patches/pathauto-admin_patterns-1267966-140.patch
; Generate automatic URL alias
; https://www.drupal.org/node/1847444
projects[pathauto][patch][] = https://www.drupal.org/files/issues/pathauto-patch_for_pathautho1.3.patch

projects[pathauto_persist][subdir] = "contrib"
projects[pathauto_persist][version] = "1.4"

projects[piwik][subdir] = "contrib"
projects[piwik][version] = "2.9"

; Instead of using a stable version of the plupload module, we stick here to a
; more recent git revision in order to solve unexpected failures with a
; plupload JS library patch included in the default Drush make file of the
; module. In the scope of https://www.drupal.org/node/2088143, this default make
; file got reduced to an example make file which is not executed any longer by
; default, so we can download and patch the plupload JS library ourselves (see
; further on in the libraries section of this make file).
projects[plupload][subdir] = "contrib"
projects[plupload][download][branch] = 7.x-1.x
projects[plupload][download][revision] = bba974c6f3224346a1acae4181a700b55129e6e1
projects[plupload][download][type] = git

projects[print][subdir] = "contrib"
projects[print][version] = "2.0"

projects[quicktabs][subdir] = "contrib"
projects[quicktabs][version] = "3.6"
projects[quicktabs][patch][] = patches/quicktabs-ajax-default-tab-none_1741488-10.patch
projects[quicktabs][patch][] = patches/quicktabs-tabs_broken-3880.patch
projects[quicktabs][patch][] = patches/quicktabs-user-interface-2108935-2.patch

projects[rate][subdir] = "contrib"
projects[rate][version] = "1.7"
projects[rate][patch][] = patches/rate-translate_description-1178.patch

projects[realname][subdir] = "contrib"
projects[realname][version] = "1.2"

projects[registration][subdir] = "contrib"
projects[registration][version] = "1.6"

projects[registry_autoload][subdir] = "contrib"
projects[registry_autoload][version] = 1.3

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.9"

projects[scheduler][subdir] = "contrib"
projects[scheduler][version] = 1.3

projects[scheduler_workbench][subdir] = "contrib"
projects[scheduler_workbench][version] = 1.3

projects[select_or_other][subdir] = "contrib"
projects[select_or_other][version] = 2.22

projects[simplenews][subdir] = "contrib"
projects[simplenews][version] = "1.1"
projects[simplenews][patch][] = patches/simplenews-fieldset-weight-4330.patch

projects[simplenews_statistics][subdir] = "contrib"
projects[simplenews_statistics][version] = "1.0-alpha1"
; Syntax error in simplenews_statistics test file
; https://www.drupal.org/node/2607422
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6813
projects[simplenews_statistics][patch][] = https://www.drupal.org/files/issues/simplenews_statistics-syntax_error-2607422-3.patch
; https://www.drupal.org/node/2673290
projects[simplenews_statistics][patch][] = https://www.drupal.org/files/issues/simplenews_statistics-simpletest-warning-message-2673290-3-D7.patch

projects[site_map][subdir] = "contrib"
projects[site_map][version] = "1.3"

projects[smart_trim][subdir] = "contrib"
projects[smart_trim][version] = 1.5

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[subscriptions][subdir] = "contrib"
projects[subscriptions][version] = "1.1"

projects[tagclouds][subdir] = "contrib"
projects[tagclouds][version] = "1.10"

projects[term_reference_tree][subdir] = "contrib"
projects[term_reference_tree][version] = "1.10"
projects[term_reference_tree][patch][] = patches/term_reference_tree-i18n-2000.patch
projects[term_reference_tree][patch][] = patches/term_reference_tree-ie8-2000.patch

projects[title][download][branch] = 7.x-1.x
projects[title][download][revision] = 1f89073
projects[title][download][type] = git
projects[title][subdir] = "contrib"

projects[tmgmt][download][branch] = 7.x-1.x
projects[tmgmt][download][revision] = bd307cb0cdf55a20092f616aeb0c39bd918aef5d
projects[tmgmt][download][type] = git
projects[tmgmt][subdir] = contrib
; @see https://www.drupal.org/node/2489134
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/support_for_link_field-2489134-9.patch
; @see https://www.drupal.org/node/272245
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/tmgmt-test_translator_missing-2722455-2.patch
; #2812863 : Insufficient access check on Views
; https://www.drupal.org/node/2812863
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-60
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/2812863.patch

projects[token][subdir] = "contrib"
projects[token][version] = "1.6"
projects[token][patch][] = patches/token-1058912-88-limit-token-depth.patch

projects[token_filter][subdir] = "contrib"
projects[token_filter][version] = 1.1

projects[translation_overview][subdir] = "contrib"
projects[translation_overview][version] = "2.0-beta1"
; https://www.drupal.org/node/2673314
projects[translation_overview][patch][] = https://www.drupal.org/files/issues/translation_overview-simpletest-warning-message-2673314-2-D7.patch

projects[translation_table][subdir] = "contrib"
projects[translation_table][version] = "1.0-beta1"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.2"

projects[tweetbutton][subdir] = "contrib"
projects[tweetbutton][version] = "2.0-beta1"

projects[user_dashboard][subdir] = "contrib"
projects[user_dashboard][version] = "1.4"

projects[user_field_privacy][subdir] = "contrib"
projects[user_field_privacy][version] = "1.2"

projects[username_enumeration_prevention][subdir] = "contrib"
projects[username_enumeration_prevention][version] = "1.2"

projects[uuid][subdir] = "contrib"
projects[uuid][version] = "1.0-beta1"

projects[variable][subdir] = "contrib"
projects[variable][version] = "2.5"

projects[video][subdir] = "contrib"
projects[video][version] = "2.11"
projects[video][patch][] = patches/video-revert_issue-1891012-0.patch
projects[video][patch][] = patches/video-security-883.patch

projects[views][subdir] = "contrib"
projects[views][version] = 3.15

; Error when configuring exposed group filter: "The value is required if title for this item is defined."
; https://www.drupal.org/node/1818176
projects[views][patch][] = https://www.drupal.org/files/views-1818176-11.patch
; Fatal error: Unsupported operand types in [path to drupal]/sites/all/modules/views/includes/handlers.inc on line 1032
; https://www.drupal.org/node/1752062
projects[views][patch][] = https://www.drupal.org/files/includes_handlers.inc_.git_.patch
; Default argument not skipped in breadcrumbs
; https://www.drupal.org/node/1201160
projects[views][patch][] = https://www.drupal.org/files/issues/views-contextual_filter_exception_breadcrumbs-1201160-17.patch

projects[views_ajax_history][subdir] = "contrib"
projects[views_ajax_history][version] = "1.0"

projects[views_bootstrap][subdir] = "contrib"
projects[views_bootstrap][version] = "3.1"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.3"

projects[views_data_export][subdir] = "contrib"
projects[views_data_export][version] = "3.0-beta9"

projects[views_datasource][version] = "1.0-alpha2"
projects[views_datasource][subdir] = "contrib"

projects[views_geojson][subdir] = "contrib"
projects[views_geojson][version] = "1.0-beta3"

projects[views_litepager][subdir] = "contrib"
projects[views_litepager][version] = "3.0"

projects[views_slideshow][subdir] = "contrib"
projects[views_slideshow][version] = "3.1"

projects[views_slideshow_slider][subdir] = "contrib"
projects[views_slideshow_slider][version] = "3.0"

projects[votingapi][subdir] = "contrib"
projects[votingapi][version] = "2.12"

projects[webform][subdir] = "contrib"
projects[webform][version] = "4.12"
projects[webform][patch][] = patches/webform-use_ecas_link-1235.patch

projects[webform_rules][subdir] = "contrib"
projects[webform_rules][version] = "1.6"

projects[workbench][subdir] = "contrib"
projects[workbench][version] = "1.2"

projects[workbench_access][subdir] = "contrib"
projects[workbench_access][version] = "1.4"

projects[workbench_email][subdir] = "contrib"
projects[workbench_email][version] = "3.6"
; Issue #2501321: Add email subject and message to Features.
; https://www.drupal.org/node/2501321
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7225
projects[workbench_email][patch][] = https://www.drupal.org/files/issues/workbench_email-add_email_subject_message_to_feature-2501321-1.patch
; Issue only reproducible on NextEuropa platform
; https://www.drupal.org/node/2590385
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7225
projects[workbench_email][patch][] = patches/workbench_email-revert_feature_error-1.patch

projects[workbench_moderation][subdir] = "contrib"
projects[workbench_moderation][version] = "1.4"
projects[workbench_moderation][patch][] = patches/workbench_moderation-001-wm-field_translations-2285931-1.patch
projects[workbench_moderation][patch][] = patches/workbench_moderation-005-workbench_moderation.rules-5054.patch
projects[workbench_moderation][patch][] = https://www.drupal.org/files/issues/support_for_migrate-1445824-35.patch
; Issue #2360091 View published tab is visible when a published node has a draft.
; https://www.drupal.org/node/2360091
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-10670
projects[workbench_moderation][patch][] = https://www.drupal.org/files/issues/workbench_moderation-7.x-dev_update_tab_count.patch
; Node revision history optimization on large websites.
; https://www.drupal.org/node/1408838
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-12122
projects[workbench_moderation][patch][] = https://www.drupal.org/files/issues/workbench_moderation-optimize_node_revision_history-1408838-67.patch
; Node revision in shutdown function causes error in behat tests
; https://www.drupal.org/node/2645622
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-13039
projects[workbench_moderation][patch][] = https://www.drupal.org/files/issues/node-deleted-before-shutdown-function-2645622-4.patch
; Doesn't handle file attachments
; We need to merge the changes in the drupal.org ticket with the previous patch because they change the same line
; https://www.drupal.org/node/1084436
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-592
projects[workbench_moderation][patch][] = patches/workbench_moderation-002-1084436-2645622-merge.patch
; Allow cron to run workbench_moderation_set_state_action
; https://www.drupal.org/node/2476489 (patch #12)
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-968
projects[workbench_moderation][patch][] = https://www.drupal.org/files/issues/force_transition-2476489-12.patch

projects[workbench_og][subdir] = "contrib"
projects[workbench_og][version] = "2.0-beta1"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.2"
projects[wysiwyg][patch][] = patches/wysiwyg-ckeditor4-bug-version-1799.patch
projects[wysiwyg][patch][] = patches/wysiwyg-ckeditor_ie_fix-1914904-5.patch
projects[wysiwyg][patch][] = patches/wysiwyg-local_css_file_paths-1793704-14.patch
projects[wysiwyg][patch][] = patches/wysiwyg-js-url-9874.patch
; Features export doesn't work correctly
; https://www.drupal.org/node/2414575
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1
projects[wysiwyg][patch][] = https://www.drupal.org/files/issues/wysiwyg-feature_export_object_to_array-2414575-10-7.patch

projects[xml_field][subdir] = "contrib"
projects[xml_field][version] = "2.2"

projects[xmlsitemap][subdir] = "contrib"
projects[xmlsitemap][version] = "2.3"
; Using rel="alternate" rather than multiple sitemaps by language context
; https://www.drupal.org/node/1670086
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11505
projects[xmlsitemap][patch][] = https://www.drupal.org/files/issues/xmlsitemap-using_rel_alternate-1670086-50.patch
projects[xmlsitemap][patch][] = patches/xmlsitemap-using_rel_alternate-nexteuropa_multilingual_url_suffix.patch


; =========
; Libraries
; =========

; chosen 1.4.2
libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/1.4.2/chosen_v1.4.2.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries

; colorbox 1.6.3
libraries[colorbox][download][type] = get
libraries[colorbox][download][url] = https://github.com/jackmoore/colorbox/archive/1.6.3.zip
libraries[colorbox][directory_name] = colorbox
libraries[colorbox][destination] = libraries

; ckeditor 4.4.8
libraries[ckeditor][download][type]= "file"
libraries[ckeditor][download][request_type]= "get"
libraries[ckeditor][download][file_type] = "zip"
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.4.8/ckeditor_4.4.8_full.zip
libraries[ckeditor][download][sha1] = "ed246ac87cad3c4cfa1f723fcfbe4a6e3a5c6992"
libraries[ckeditor][directory_name] = "ckeditor"

; ckeditor_lite library. Buttons are added in nexteuropa_core_install().
libraries[ckeditor_lite][download][type]= "file"
libraries[ckeditor_lite][download][request_type]= "get"
libraries[ckeditor_lite][download][file_type] = "zip"
libraries[ckeditor_lite][download][url] = http://download.ckeditor.com/lite/releases/lite_1.1.30.zip
libraries[ckeditor_lite][subdir] = ckeditor/plugins
libraries[ckeditor_lite][directory_name] = "lite"

; ckeditor_moono specific skin : moonocolor
libraries[ckeditor_moono][download][type]= "file"
libraries[ckeditor_moono][download][request_type]= "get"
libraries[ckeditor_moono][download][file_type] = "zip"
libraries[ckeditor_moono][download][url] = http://download.ckeditor.com/moonocolor/releases/moonocolor_4.5.1.zip
libraries[ckeditor_moono][destination] = "../common/modules/features/multisite_wysiwyg/ckeditor/skins"
libraries[ckeditor_moono][directory_name] = "moonocolor"

; cycle 3.0.2 (commit d6557ca)
libraries[cycle][download][type] = "git"
libraries[cycle][destination] = "libraries"
libraries[cycle][download][url] = https://github.com/malsup/cycle.git
libraries[cycle][download][tag] = "3.0.3"

; fancybox 2.1.5
libraries[fancybox][download][type]= "file"
libraries[fancybox][download][request_type]= "get"
libraries[fancybox][download][file_type] = "zip"
libraries[fancybox][download][url] = https://github.com/fancyapps/fancyBox/zipball/v2.1.5
libraries[fancybox][destination] = "../common/libraries"

; flexslider 2.5.0
libraries[flexslider][download][type]= "file"
libraries[flexslider][download][url] = https://github.com/woothemes/FlexSlider/archive/version/2.5.0.zip
libraries[flexslider][download][request_type]= "get"
libraries[flexslider][download][file_type] = "zip"
libraries[flexslider][destination] = "../common/libraries"

; fullcalendar 1.6.7
libraries[fullcalendar][download][url] = https://github.com/fullcalendar/fullcalendar/archive/v1.6.7.zip
libraries[fullcalendar][download][type]= "file"
libraries[fullcalendar][download][request_type]= "get"
libraries[fullcalendar][download][file_type] = "zip"
libraries[fullcalendar][destination] = "../common/libraries"

; fullcalendar 1.5.4 fork (used for the events_resources module)
libraries[fullcalendar_resources][download][url] = http://ikelin.github.io/fullcalendar/fullcalendar-1.5.4.zip
libraries[fullcalendar_resources][download][type]= "file"
libraries[fullcalendar_resources][download][request_type]= "get"
libraries[fullcalendar_resources][download][file_type] = "zip"
libraries[fullcalendar_resources][destination] = "../common/libraries"

; history.js v1.8b2
libraries[history][download][type] = "git"
libraries[history][download][url] = https://github.com/browserstate/history.js/
libraries[history][directory_name] = "history.js"
libraries[history][destination] = "libraries"
libraries[history][download][tag] = "1.8.0b2"

; iCalcreator 2.20.2
libraries[iCalcreator][download][url] = https://github.com/iCalcreator/iCalcreator/archive/e3dbec2cb3bb91a8bde989e467567ae8831a4026.zip
libraries[iCalcreator][download][type] = "file"
libraries[iCalcreator][download][request_type]= "get"
libraries[iCalcreator][download][file_type] = "zip"
libraries[iCalcreator][download][destination] = "../common/libraries"

; imgAreaSelect 0.9.10
libraries[jquery.imgareaselect][download][url] = http://odyniec.net/projects/imgareaselect/jquery.imgareaselect-0.9.10.zip
libraries[jquery.imgareaselect][download][type]= "file"
libraries[jquery.imgareaselect][download][request_type]= "get"
libraries[jquery.imgareaselect][download][file_type] = "zip"
libraries[jquery.imgareaselect][destination] = "../common/libraries"

; jplayer 2.9.2
libraries[jplayer][download][url] = https://github.com/happyworm/jPlayer/archive/2.9.2.zip
libraries[jplayer][download][type]= "file"
libraries[jplayer][download][request_type]= "get"
libraries[jplayer][download][file_type] = "zip"
libraries[jplayer][destination] = "../common/libraries"

; jquery 1.11.3
libraries[jquery][download][url] = http://code.jquery.com/jquery-1.11.3.min.js
libraries[jquery][download][type]= "file"
libraries[jquery][download][request_type]= "get"
libraries[jquery][destination] = "../common/libraries"
libraries[jquery][directory_name] = "jquery"

; Leaflet.draw
libraries[Leaflet.draw][destination] = "libraries"
libraries[Leaflet.draw][download][type] = "git"
libraries[Leaflet.draw][download][url] = https://github.com/Leaflet/Leaflet.draw.git
libraries[Leaflet.draw][download][tag] = "v0.3.0"

; modernizr 2.8.3
libraries[modernizr][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.8.3.zip
libraries[modernizr][download][type]= "file"
libraries[modernizr][download][request_type]= "get"
libraries[modernizr][download][file_type] = "zip"
libraries[modernizr][destination] = "../common/libraries"

; mpdf 5.7.4a
libraries[mpdf][download][type]= "file"
libraries[mpdf][download][request_type]= "get"
libraries[mpdf][download][file_type] = "zip"
libraries[mpdf][download][url] = https://github.com/mpdf/mpdf/archive/v5.7.4a.zip
libraries[mpdf][destination] = "libraries"

; Leaflet
libraries[leaflet][destination] = "libraries"
libraries[leaflet][download][type] = "file"
libraries[leaflet][download][url] = http://cdn.leafletjs.com/downloads/leaflet-0.7.5.zip
libraries[leaflet][directory_name] = "leaflet"

; Plupload
libraries[plupload][destination] = "libraries"
libraries[plupload][download][type] = "file"
libraries[plupload][download][request_type]= "get"
libraries[plupload][download][file_type] = "zip"
libraries[plupload][download][url] = https://github.com/moxiecode/plupload/archive/v1.5.8.zip
libraries[plupload][directory_name] = "plupload"
; Remove the examples directory.
; See https://www.drupal.org/node/1903850#comment-11676067.
libraries[plupload][patch][1903850] = "https://www.drupal.org/files/issues/plupload-1_5_8-rm_examples-1903850-29.patch"

; ===========================
; Libraries for Ec_resp Theme
; ===========================

; Ec_resp theme: Bootstrap 3.3.5
libraries[ec_resp_bootstrap][download][type] = get
libraries[ec_resp_bootstrap][download][url] = https://github.com/twbs/bootstrap/releases/download/v3.3.5/bootstrap-3.3.5-dist.zip
libraries[ec_resp_bootstrap][download][file_type] = "zip"
libraries[ec_resp_bootstrap][destination] =  "themes/ec_resp"
libraries[ec_resp_bootstrap][directory_name] = bootstrap

; Ec_resp theme: Bootstrap less
libraries[ec_resp_bootstrap_less][download][type] = "get"
libraries[ec_resp_bootstrap_less][download][url] = https://github.com/twbs/bootstrap/archive/v3.3.5.zip
libraries[ec_resp_bootstrap_less][download][subtree] = "bootstrap-3.3.5/less"
libraries[ec_resp_bootstrap_less][destination] =  "themes/ec_resp/bootstrap"
libraries[ec_resp_bootstrap_less][directory_name] = less

; Ec_resp theme: Html5
libraries[html5shiv][destination] = "themes/ec_resp"
libraries[html5shiv][directory_name] = "scripts"
libraries[html5shiv][download][type] = "git"
libraries[html5shiv][download][url] = https://github.com/aFarkas/html5shiv.git
libraries[html5shiv][download][tag] = "3.7.3"

; Ec_resp theme: jQuery Mousewheel
libraries[mousewheel][destination] = "themes/ec_resp"
libraries[mousewheel][directory_name] = "scripts"
libraries[mousewheel][download][type] = "git"
libraries[mousewheel][download][url] = https://github.com/jquery/jquery-mousewheel.git
libraries[mousewheel][download][tag] = "3.1.13"

; Ec_resp theme: Respond JS
libraries[respond][destination] = "themes/ec_resp"
libraries[respond][directory_name] = "scripts"
libraries[respond][download][type] = "git"
libraries[respond][download][url] = https://github.com/scottjehl/Respond.git
libraries[respond][download][tag] = "1.4.2"

; ======
; Themes
; ======

projects[bootstrap][type] = theme
projects[bootstrap][download][type] = get
projects[bootstrap][download][url] = http://ftp.drupal.org/files/projects/bootstrap-7.x-3.5.zip

projects[europa][type] = theme
projects[europa][download][type] = get
projects[europa][download][url] = https://github.com/ec-europa/platform-theme/releases/download/0.2.0/platform-theme-0.2.0.tar.gz
