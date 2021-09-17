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
projects[admin_menu][version] = "3.0-rc6"
projects[admin_menu][patch][]  = patches/admin_menu_above_globan-nept-2667.patch

projects[administration_language_negotiation][subdir] = "contrib"
projects[administration_language_negotiation][version] = "1.4"

projects[advagg][subdir] = "contrib"
projects[advagg][version] = "2.33"
; NEPT-2790: Scan code for @codingStandardsIgnoreFile and fix
; https://www.drupal.org/project/advagg/issues/3116299
projects[advagg][patch][] = https://www.drupal.org/files/issues/2020-02-27/php7_compatibility-3116299-2.patch
; https://github.com/ec-europa/platform-dev/pull/2869
projects[advagg][patch][] = https://www.drupal.org/files/issues/2019-06-02/advagg_replace_continue_with_break-3058949-2.patch

projects[advanced_help][subdir] = "contrib"
projects[advanced_help][version] = "1.5"

projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.12"
; Issue #1649158 : Date Facets (without a time) can show in Multiple Months.
; https://drupal.org/node/1649158
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4335
projects[apachesolr][patch][] = https://www.drupal.org/files/apachesolr-multiple-dates-hack-1649158-15.patch
; Issue #2657666 : Notice: Undefined property: stdClass::$status_message
; https://www.drupal.org/node/2657666
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-7651
projects[apachesolr][patch][] = https://www.drupal.org/files/issues/apachesolr-undefined-property-2657666-4-D7.patch
; Delay removing entities from the index.
; https://www.drupal.org/node/2764637
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11582
projects[apachesolr][patch][] = https://www.drupal.org/files/issues/2020-01-28/apachesolr-delay-entity-removal-2764637-4.patch

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
; Issue #2017705 : Performance! Add missed indexes to apachesolr_index_entities_file table
; https://www.drupal.org/node/2017705
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2776
projects[apachesolr_attachments][patch][] = https://www.drupal.org/files/issues/module_slows_down-2017705-7.patch
; Issue #2677866 : Cannot install on mysql >= 5.6
; https://www.drupal.org/node/2677866
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-326
projects[apachesolr_attachments][patch][] = https://www.drupal.org/files/issues/mysql-56-compatibility-2677866-12.patch

projects[apachesolr_multilingual][subdir] = "contrib"
projects[apachesolr_multilingual][version] = "1.3"
; Issue #2998996: [ PHP 7.2 Compatibility ] - Function each() is deprecated since PHP 7.2; Use a foreach loop instead
; https://www.drupal.org/project/apachesolr_multilingual/issues/2998996
projects[apachesolr_multilingual][patch][] = https://www.drupal.org/files/issues/2019-06-26/apachesolr_multilingual-each_deprecated-2998996-9-D7.patch

projects[apachesolr_multisitesearch][subdir] = "contrib"
projects[apachesolr_multisitesearch][version] = "1.2"

projects[autologout][subdir] = "contrib"
projects[autologout][version] = "4.5"
; Issue #2739114 : Change warning message to be more user friendly
; https://www.drupal.org/node/2739114
projects[autologout][patch][] = https://www.drupal.org/files/issues/change-warning-message-2739114-15.patch

projects[autosave][subdir] = "contrib"
projects[autosave][version] = "2.2"

projects[bean][subdir] = "contrib"
projects[bean][version] = 1.13

projects[better_exposed_filters][subdir] = "contrib"
projects[better_exposed_filters][version] = "3.6"

projects[better_formats][subdir] = "contrib"
projects[better_formats][version] = "1.0-beta2"
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-157
; Apply patch to fix xss injection
projects[better_formats][patch][] = https://www.drupal.org/files/issues/better_formats-2896131-6-missing-check_plain-when-showing-filter-name.patch

projects[bootstrap_gallery][subdir] = "contrib"
projects[bootstrap_gallery][version] = "3.1"

projects[bounce][subdir] = "contrib"
projects[bounce][version] = "1.7"

projects[cdn][subdir] = "contrib"
projects[cdn][version] = "2.9"

projects[chosen][subdir] = "contrib"
projects[chosen][version] = "2.1"

projects[chr][subdir] = "contrib"
projects[chr][version] = "1.9"
; Issue #2355631: rewrite header host without port number.
; https://www.drupal.org/node/2355631
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-6231
projects[chr][patch][] = https://www.drupal.org/files/issues/chr-1.6-patch-rewrite-header-host-without-standard-port-number_0.patch
; Issue #2825701: allow PURGE requests.
; https://www.drupal.org/node/2825701
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-81
projects[chr][patch][] = https://www.drupal.org/files/issues/chr-purge-2825701-2.patch
; https://www.drupal.org/project/chr/issues/3028043
projects[chr][patch][] = https://www.drupal.org/files/issues/2019-03-04/chr_status_message-3028043-2.patch

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
projects[context][version] = "3.10"
projects[context][patch][] = https://www.drupal.org/files/issues/massively-increase-pe-reroll-873936-67.patch

projects[context_entity_field][subdir] = "contrib"
projects[context_entity_field][version] = "1.1"
; Make condition work for entity references.
; Patch implemented in DEV version.
; https://www.drupal.org/node/1847038
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5056
projects[context_entity_field][patch][] = https://www.drupal.org/files/add-entity-references.patch

projects[context_og][subdir] = "contrib"
projects[context_og][version] = "2.1"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.15"
; PHP 7 compatibility.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2662
; https://www.drupal.org/project/ctools/issues/3006202
; https://www.drupal.org/project/ctools/issues/3079343
projects[ctools][patch][] = https://www.drupal.org/files/issues/2019-04-03/ctools-func_get_args-3006202-13.patch
projects[ctools][patch][] = https://www.drupal.org/files/issues/2019-09-05/ctools-php7-3079343-3.patch

projects[customerror][subdir] = "contrib"
projects[customerror][version] = "1.4"

projects[date][subdir] = "contrib"
projects[date][version] = "2.11-beta3"
; Issue #2305049: Wrong timezone handling in migrate process.
; https://www.drupal.org/node/2305049
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-3324
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-4710
projects[date][patch][] = https://www.drupal.org/files/issues/2019-06-30/2305049-12_1.patch

projects[date_ical][subdir] = "contrib"
projects[date_ical][version] = "3.9"
; Issue #2909036 : Clone is a reserved keyword since PHP5.
; https://www.drupal.org/node/2909036
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-266
projects[date_ical][patch][2909036] = https://www.drupal.org/files/issues/clone_is_reserved_keyword-2909036-1.patch

projects[diff][subdir] = "contrib"
projects[diff][version] = 3.4

projects[ds][subdir] = "contrib"
projects[ds][version] = "2.16"

projects[easy_breadcrumb][subdir] = "contrib"
projects[easy_breadcrumb][version] = "2.17"
projects[easy_breadcrumb][patch][] = https://www.drupal.org/files/issues/2020-12-18/easy_breadcrumb_query_array.patch

projects[email][subdir] = "contrib"
projects[email][version] = "1.3"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.9"
; Invalid argument supplied for foreach() in entity_metadata_convert_schema()
; https://www.drupal.org/node/2564119
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1025
projects[entity][patch][] = https://www.drupal.org/files/issues/Use-array-in-foreach-statement-2564119-1.patch

projects[entity_translation][subdir] = "contrib"
projects[entity_translation][version] = "1.1"
; Issue #1707156 : Workbench Moderation integration
; https://www.drupal.org/node/1707156
projects[entity_translation][patch][] = https://www.drupal.org/files/issues/2018-07-25/workbench_moderation-1707156-83.patch

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = 1.5
; Issue #10558568 : Broken updates due to Classes living in .module files
; https://www.drupal.org/node/2441965#comment-10558568
projects[entitycache][patch][] = https://www.drupal.org/files/issues/entitycache_fix_upgrade_path-2441965-62.patch
; Issue #2981629 : create_function is deprecated in PHP 7.2
; https://www.drupal.org/project/entitycache/issues/2981629
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2635
projects[entitycache][patch][] = https://www.drupal.org/files/issues/2018-07-05/entitycache_php_7-2981629-0.patch

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.5"
; Allow handlers to modify $items before calling entity_view()
; https://www.drupal.org/node/2651982
projects[entityreference][patch][] = https://www.drupal.org/files/issues/feature--entityreference-alter-items.patch

projects[entityreference_prepopulate][subdir] = "contrib"
projects[entityreference_prepopulate][version] = "1.7"
; Allow friendly field identifiers in URL.
; https://www.drupal.org/project/entityreference_prepopulate/issues/1809776
projects[entityreference_prepopulate][patch][] = https://www.drupal.org/files/issues/entityreference_prepopulate-1809776-5-test-only.patch

projects[eu_cookie_compliance][subdir] = "contrib"
projects[eu_cookie_compliance][version] = "1.28"

projects[extlink][subdir] = "contrib"
projects[extlink][version] = "1.18"

projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.5"
; facetapi_map_assoc() does not check if index exists.
; Note: This patch is to be remoaved with the future version 7.x-1.6.
; Indeed, the patch has already been pushed with the #2373023 d.o. issue.
; https://www.drupal.org/project/facetapi/issues/2768779
; and https://www.drupal.org/node/2373023
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2042
projects[facetapi][patch][] = https://www.drupal.org/files/issues/facetapi-2768779-facetapi_map_assoc-undefined-index.patch
; and https://www.drupal.org/node/3055360
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2631
projects[facetapi][patch][] = https://www.drupal.org/files/issues/2019-08-23/facetapi-func_get_args-3055360-7_d7.patch

projects[fast_404][subdir] = "contrib"
projects[fast_404][version] = "1.5"

projects[features][subdir] = "contrib"
projects[features][version] = "2.11"
; Issue #1437264: features_var_export is converting custom class objects to arrays if don't have export method
; https://www.drupal.org/node/1437264
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4759
projects[features][patch][] = https://www.drupal.org/files/issues/features-var-export-object-1437264-12_0.patch

projects[feature_set][subdir] = "contrib"
projects[feature_set][version] = "1.3"
; NEPT-930 - Feature set page should use admin theme - adding new markup, css and js to the patch
projects[feature_set][patch][] = patches/feature_set-add_categories_management-nexteuropa_4459-nept_930.patch
projects[feature_set][patch][] = patches/feature_set-check_disable_enable-nexteuropa_4459.patch
projects[feature_set][patch][] = patches/feature_set-misc-nexteuropa_4459.patch
; Issue #2831766: Feature set does not invoke hook_requirements().
; https://www.drupal.org/node/2831766
projects[feature_set][patch][] = https://www.drupal.org/files/issues/feature_set_invoke_hook_requirements-2831766-6.patch

projects[feeds][subdir] = "contrib"
projects[feeds][version] = "2.0-beta5"
projects[feeds][patch][] = https://www.drupal.org/files/issues/feeds_delete_if_empty_source-2333667-8.patch
projects[feeds][patch][] = patches/phpcs_ignore_safe_mode.patch

; "Feeds: Entity Translation" is a dependency for nexteuropa_newsroom module.
; So far, the module does not have any official release.
; The following declaration is based on the one recommended by the
; nexteuropa_newsroom team to sub-sites; including the patch
; "feeds_et_link_support-2078069-3.patch".
projects[feeds_et][subdir] = "contrib"
projects[feeds_et][download][type] = git
projects[feeds_et][download][revision] = bf0d6d00b1a80a630d4266b04c254f2335177346
projects[feeds_et][download][branch] = 7.x-1.x
; Add support for link fields, patch required for the nexteuropa_newsroom module;
; see module README file.
; https://www.drupal.org/node/2078069
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2018
projects[feeds_et][patch][] = https://www.drupal.org/files/issues/feeds_et_link_support-2078069-3.patch

projects[feeds_tamper][subdir] = "contrib"
projects[feeds_tamper][version] = "1.2"

projects[feeds_xpathparser][subdir] = "contrib"
projects[feeds_xpathparser][version] = "1.1"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.6"
; https://www.drupal.org/node/2604284
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6603
projects[field_group][patch][] = https://www.drupal.org/files/issues/field_group_label_translation_patch.patch
; After update from 1.5 to 1.6 empty field groups (because of field permissions)
; are now being displayed as empty groups
; https://www.drupal.org/node/2926605
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2016
projects[field_group][patch][] = https://www.drupal.org/files/issues/field_group-remove-array_parents-2494385-11.patch
; https://www.drupal.org/node/3016503
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2633
projects[field_group][patch][] = https://www.drupal.org/files/issues/2018-11-28/field_group-func_get_args-3016503-2.patch

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.27"

projects[filefield_sources][subdir] = "contrib"
projects[filefield_sources][version] = "1.11"

projects[filefield_sources_plupload][subdir] = "contrib"
projects[filefield_sources_plupload][version] = "1.1"
; Fix Field description persistance
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7572
; https://www.drupal.org/node/2705523
projects[filefield_sources_plupload][patch][] = https://www.drupal.org/files/issues/filefield_sources_plupload-metadata_persistance-2705523.patch
; Fix ajax file updload
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1844
; https://www.drupal.org/project/filefield_sources_plupload/issues/2466505
projects[filefield_sources_plupload][patch][] = https://www.drupal.org/files/issues/filefield-sources-plupload-ajax-wrapper-2466505-1.patch

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.9"
; NEPT-2845 Fix missing Primary Key issues.
projects[flag][patch][] = https://www.drupal.org/files/issues/2020-11-04/flag-add_missing_primary_key-2834419-6_1.patch

projects[flexslider][subdir] = "contrib"
projects[flexslider][version] = "2.0-rc2"
; Issue #2219435: remove pause button if there is only one slide.
projects[flexslider][patch][] = https://www.drupal.org/files/issues/pause_1_slide-flexslider-2219435-1.patch

projects[flexslider_views_slideshow][download][revision] = "0b1f8e7e24c168d1820ccded63c319327d57a97e"
projects[flexslider_views_slideshow][download][type] = "git"
projects[flexslider_views_slideshow][download][url] = http://git.drupal.org/project/flexslider_views_slideshow.git
projects[flexslider_views_slideshow][subdir] = "contrib"

projects[freepager][download][revision] = "c11c40f6e3e54ff728515589600a0d8e26d831f1"
projects[freepager][download][type] = "git"
projects[freepager][download][url] = http://git.drupal.org/project/freepager.git
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
; Issue #3063000: PHP7 compatibility.
; https://www.drupal.org/project/fullcalendar/issues/3063000
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2661
projects[fullcalendar][patch][] = https://www.drupal.org/files/issues/2019-06-20/php7.2-upgrade-707484-1.patch


projects[geofield][subdir] = "contrib"
projects[geofield][version] = "2.3"
projects[geofield][patch][] = https://www.drupal.org/files/issues/geofield-feeds_import_not_saving-2534822-17.patch

projects[geophp][download][branch] = 7.x-1.x
projects[geophp][download][revision] = 2777c5e
projects[geophp][download][type] = git
projects[geophp][subdir] = "contrib"

projects[honeypot][subdir] = "contrib"
projects[honeypot][version] = "1.26"
; NEPT-2845 Fix missing primary key issues.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2845
projects[honeypot][patch][] = https://www.drupal.org/files/issues/2020-07-07/honeypot-add_primary_key-2943526-13-D7.patch

projects[i18n][subdir] = "contrib"
projects[i18n][version] = "1.27"
; Language field display should default to hidden.
; https://www.drupal.org/node/1350638
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-3996
; Also requires a patch for Drupal core issue https://www.drupal.org/node/1256368,
; you can find it in drupal-core.make.
projects[i18n][patch][] = https://www.drupal.org/files/i18n-hide_language_by_default-1350638-5.patch

projects[i18nviews][subdir] = "contrib"
projects[i18nviews][version] = "3.0-alpha1"

projects[inline_entity_form][subdir] = "contrib"
projects[inline_entity_form][version] = "1.8"

projects[job_scheduler][subdir] = "contrib"
projects[job_scheduler][version] = "2.0-alpha3"

projects[jplayer][subdir] = "contrib"
projects[jplayer][version] = "2.0"
; https://www.drupal.org/project/jplayer/issues/2977834
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1657
projects[jplayer][patch][] = https://www.drupal.org/files/issues/2018-06-06/2977834-2.patch

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.7"
; Issue #2621436: Allow permissions to granted roles.
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7825
projects[jquery_update][patch][] = https://www.drupal.org/files/issues/jquery_update_permissions-2621436-2_0.patch

projects[l10n_update][subdir] = "contrib"
projects[l10n_update][version] = "2.2"
; Issue #2922809: When trying to update i have "Recoverable fatal error: Argument 2 passed to format_string".
; The fix is made of 2 patches.
; https://www.drupal.org/node/2922809
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-272
projects[l10n_update][patch][] = https://www.drupal.org/files/issues/l10n_update-missing-log-vars-2922809-10.patch

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.5"

projects[link][subdir] = "contrib"
projects[link][version] = "1.7"

projects[linkchecker][subdir] = "contrib"
projects[linkchecker][version] = "1.4"
projects[linkchecker][patch][] = https://www.drupal.org/files/issues/bean-integration-2127731-0.patch
projects[linkchecker][patch][] = https://www.drupal.org/files/issues/linkchecker-max_redirects-2593465-1-D7_0.patch

projects[mail_edit][subdir] = "contrib"
projects[mail_edit][version] = "1.1"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = "2.34"

projects[maxlength][subdir] = "contrib"
projects[maxlength][version] = "3.3"

projects[media][subdir] = contrib
projects[media][version] = 2.26
; Embedded documents in the WYSIWYG can be very hard to delete.
; https://www.drupal.org/node/2028231
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-771
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1015
; Media markup navigation causes duplicated links
projects[media][patch][] = https://www.drupal.org/files/issues/media-delete-embedded-document-2028231-11.patch
; NEPT-2718 Error thrown when maxlength module is enabled
projects[media][patch][] = patches/media-nept-2718-maxlength-title-error.patch
; NEPT-2845 Fix missing primary key issues.
projects[media][patch][] = https://www.drupal.org/files/issues/2020-08-03/add_primary_key_for-2865131-8.patch

projects[media_avportal][subdir] = "contrib"
projects[media_avportal][version] = "1.5"

projects[media_dailymotion][subdir] = "contrib"
projects[media_dailymotion][version] = "1.1"
; Issue #2560403: Provide Short URL for media dailymotion.
; https://www.drupal.org/node/2560403
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7082
projects[media_dailymotion][patch][] = https://www.drupal.org/files/issues/media_dailymotion-mini-url-2560403-7-7.x.patch
projects[media_dailymotion][patch][] = patches/media_dailymotion-handle_protocol-4103.patch

projects[media_flickr][subdir] = "contrib"
projects[media_flickr][version] = "2.0-alpha5"

projects[media_node][subdir] = "contrib"
projects[media_node][version] = "1.0-rc2"
projects[media_node][patch][] = patches/media_node-incorrect_permission_check-4273.patch

projects[media_vimeo][subdir] = "contrib"
projects[media_vimeo][version] = "2.1"

projects[media_youtube][subdir] = "contrib"
projects[media_youtube][version] = "3.10"
projects[media_youtube][patch][] = https://www.drupal.org/files/issues/2018-06-28/nocookie-default.patch
projects[media_youtube][patch][] = https://www.drupal.org/files/issues/2021-01-07/media_youtube-1572550-117.patch

projects[media_colorbox][subdir] = "contrib"
projects[media_colorbox][version] = "1.0-rc4"

projects[menu_attributes][subdir] = "contrib"
projects[menu_attributes][version] = "1.0"
projects[menu_attributes][patch][] = patches/menu_attributes-add_icon_for_menu_item-2327.patch
projects[menu_attributes][patch][] = patches/menu_attributes-option_to_disable_css_class-2988.patch
projects[menu_attributes][patch][] = patches/menu_attributes-option_to_hide_children-6757.patch

projects[menu_block][subdir] = "contrib"
projects[menu_block][version] = "2.7"
projects[menu_block][patch][] = patches/menu_block-jqueryUI_issue-5211.patch

projects[menu_token][download][branch] = 7.x-1.x
projects[menu_token][download][revision] = 27ab9f244d7813803cfa662d05ffc1747d758956
projects[menu_token][download][type] = git
projects[menu_token][subdir] = "contrib"
projects[menu_token][patch][] = https://www.drupal.org/files/issues/2838033_1.patch

projects[message][subdir] = "contrib"
projects[message][version] = "1.12"
; Fix for an error when the purge limit fall below 0 during the cron execution.
; https://www.drupal.org/node/2030101
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1704
projects[message][patch][2030101] = https://www.drupal.org/files/issues/fix-cron-purge-messages-error-2030101-2.patch
; Fix Message type receive new internal ID on feature revert.
; https://www.drupal.org/project/message/issues/2719823
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1744
projects[message][patch][2719823] = https://www.drupal.org/files/issues/message-preserve-local-ids-on-revert-2719823-2.patch
; Fix Cloning fails when changing the form with ajax.
; https://www.drupal.org/project/message/issues/2872964
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1744
projects[message][patch][2872964] = https://www.drupal.org/files/issues/2872964-message-cloneajax-2.patch


projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.27"
; https://www.drupal.org/node/3113325
projects[metatag][patch][] = https://www.drupal.org/files/issues/2020-02-21/metatag-n3113325-6.patch

projects[migrate][subdir] = contrib
projects[migrate][download][branch] = 7.x-1.x
projects[migrate][download][revision] = ac8a749e580c16b6963088fb1901aebb052e1008

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.1"
; Issue #3052121: INI directive 'safe_mode' is deprecated since PHP 5.3 and removed since PHP 5.4
; https://www.drupal.org/project/mimemail/issues/3052121
projects[mimemail][patch][] = https://www.drupal.org/files/issues/2019-05-02/remove-deprecated-function-3052121-2.patch
; Issue #2947006: Remove usage of deprecated create_function() calls for PHP 7.2+ future proofing
; https://www.drupal.org/project/mimemail/issues/2947006
projects[mimemail][patch][] = https://www.drupal.org/files/issues/2018-05-28/mimemail-support_php_72-2947006-4.patch

; This is a dependency of media_bulk_upload that platform provides
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2498
projects[multiform][subdir] = "contrib"
projects[multiform][version] = "1.6"

projects[nagios][download][branch] = 7.x-1.x
projects[nagios][download][revision] = 7da732e2d4943ec5368243f4cd2e33eb02769f23
projects[nagios][download][type] = git
projects[nagios][subdir] = "contrib"
; NEPT-451 Add possibility to report on individual variables
; https://www.drupal.org/node/2854854
projects[nagios][patch][] = https://www.drupal.org/files/issues/nagios-id-support-2854854-5.patch

projects[nexteuropa_newsroom][download][type] = git
projects[nexteuropa_newsroom][download][url] = https://github.com/ec-europa/nexteuropa-newsroom-reference.git
projects[nexteuropa_newsroom][download][tag] = v3.5.17
projects[nexteuropa_newsroom][subdir] = custom

projects[og][subdir] = "contrib"
projects[og][version] = "2.10"
; VBO and OG
; https://www.drupal.org/node/2561507
projects[og][patch][] = https://www.drupal.org/files/issues/og_vbo_and_og_2561507-6.patch
projects[og][patch][] = patches/og-og_field_access-bypass_field_access-5159.patch
; NEXTEUROPA-11789 Issue in Bean reference to OG
; https://www.drupal.org/node/1880226
projects[og][patch][] = https://www.drupal.org/files/issues/og-use_numeric_id_for_membership_etid-1880226-5.patch
; NEPT-2493 entity issue
projects[og][patch][] = https://git.drupalcode.org/project/og/commit/a2231ab851ca82865a0070dbd58dfd5fcb2fdd66.diff

projects[og_linkchecker][subdir] = "contrib"
projects[og_linkchecker][version] = "2.0-rc1"

projects[om_maximenu][subdir] = "contrib"
projects[om_maximenu][version] = "1.44"
;NEPT-1631: Creating a mega menu gives warnings
;https://www.drupal.org/node/1824704
projects[om_maximenu][patch][1824704] = https://www.drupal.org/files/issues/fix_illegal_string_offset-1824704-8.patch

projects[password_policy][subdir] = "contrib"
projects[password_policy][version] = "2.0-alpha8"
;NEPT-2749: password_policy_user_load() assumes field is_generated exists
;https://www.drupal.org/node/2978953
projects[password_policy][patch][] = https://www.drupal.org/files/issues/2019-11-22/password_policy-check_existence_of_is_generated-2978953-7.patch

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
projects[plupload][patch][] = https://www.drupal.org/files/issues/2018-05-22/files_not_uploaded_in_subdir-2974466.patch

projects[print][subdir] = "contrib"
projects[print][version] = "2.2"
; Allow alternate location of ttfont directories
; https://www.drupal.org/project/print/issues/3036143
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2253
projects[print][patch][] = https://www.drupal.org/files/issues/2019-03-06/location_ttfont_directories-3036143-4.patch
; https://www.drupal.org/node/3006747
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2639
projects[print][patch][] = https://www.drupal.org/files/issues/2018-10-15/print-support-72.patch

projects[quicktabs][subdir] = "contrib"
projects[quicktabs][version] = "3.8"
projects[quicktabs][patch][] = patches/quicktabs-MULTISITE-3880.patch
projects[quicktabs][patch][2222805] = https://www.drupal.org/files/issues/quicktabs-log_empty-2222805-14.patch

projects[rate][subdir] = "contrib"
projects[rate][version] = "1.7"
; Description should be translatable
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-1178
projects[rate][patch][] = patches/rate-translate_description-1178.patch
; Undefined property: stdClass::$timezone in rate_expiration module
; https://www.drupal.org/project/rate/issues/1421016
projects[rate][patch][] = https://www.drupal.org/files/issues/rate-is_null_fix-1421016-9.patch

projects[realname][subdir] = "contrib"
projects[realname][version] = "1.4"
projects[realname][patch][] = https://www.drupal.org/files/issues/2021-01-20/realname-recursive_bug-1369824-7.x-1.4.patch

projects[redirect][subdir] = "contrib"
projects[redirect][download][branch] = 7.x-1.x
projects[redirect][download][revision] = 7f9531d08c4a3ffb18685fa894d3034299a572c0
; Prevent new redirects from being deleted on cron runs.
; https://www.drupal.org/node/1396446
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1945
projects[redirect][patch][1396446] = https://www.drupal.org/files/issues/2019-07-29/redirect_purge_from_created_1396446-67.patch
projects[redirect][patch][] = patches/redirect_nept_2502.patch

projects[registration][subdir] = "contrib"
projects[registration][version] = "1.7"

projects[registry_autoload][subdir] = "contrib"
projects[registry_autoload][version] = 1.3
; class_implements(): Class Drupal\integration\Backend\Entity\
; BackendEntityController does not exist and could not be loaded entity.module:1480
; https://www.drupal.org/node/2870868
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1950
projects[registry_autoload][patch][2870868] = https://www.drupal.org/files/issues/autoload_bootstrap_dependency_issues-2870868-2.patch

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.12"
projects[rules][version] = "2.12"
; https://www.drupal.org/node/3028444
projects[rules][patch][] = https://www.drupal.org/files/issues/2019-01-25/3028444-6-markup-and-test.patch
; https://www.drupal.org/node/826986
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2160
projects[rules][patch][] = https://www.drupal.org/files/issues/2020-03-19/file_events-826986-42.patch

; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2615
; We use the dev version of the module to be able to run the module simpletest.
projects[scheduler][subdir] = "contrib"
projects[scheduler][download][type] = "git"
projects[scheduler][download][url] = "https://git.drupalcode.org/project/scheduler.git"
projects[scheduler][download][revision] = "89707ba3affa72beea0b428230e61f4c5a0c1283"

; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2615
; We use the dev version of the module to be able to run the module simpletest.
projects[scheduler_workbench][subdir] = "contrib"
projects[scheduler_workbench][download][type] = "git"
projects[scheduler_workbench][download][url] = "https://git.drupalcode.org/project/scheduler_workbench.git"
projects[scheduler_workbench][download][revision] = "46e8db33e54a0d873ff60956d4d2f90d27c4735d"

; Allow to schedule the publish date of a revision
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1999
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2504
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2615
; https://www.drupal.org/project/scheduler_workbench/issues/2048999
projects[scheduler_workbench][patch][] = https://www.drupal.org/files/issues/2020-01-30/scheduler_workbench-revision_publish-2048999-69.patch
; NEPT-2787: Remove already published nodes from scheduler list
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2787
; We need a local patch for d.o/3118719 as the above already modidifies the files
projects[scheduler_workbench][patch][] = patches/persistent_nodes-3118719-7.patch

projects[select_or_other][subdir] = "contrib"
projects[select_or_other][version] = 2.24

projects[simplenews][subdir] = "contrib"
projects[simplenews][version] = "1.1"
projects[simplenews][patch][] = patches/simplenews-fieldset-weight-4330.patch
; #2801239: Issue with Entity cache
; https://www.drupal.org/node/2801239
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-121
projects[simplenews][patch][] = https://www.drupal.org/files/issues/entitycache_issue-2801239-3.patch
; Add hook_drush_sql_sync_sanitize
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2100
; https://www.drupal.org/project/simplenews/issues/3017665#comment-12879291
projects[simplenews][patch][] = https://www.drupal.org/files/issues/2019-02-11/Add_hook_drush_sql_sync_sanitize-3017665-7.patch
; Issue 3051338: Support PHP 7.2
; https://www.drupal.org/project/simplenews/issues/3051338
projects[simplenews][patch][] = https://www.drupal.org/files/issues/2019-04-28/remove-deprecated-each.patch

projects[simplenews_statistics][subdir] = "contrib"
projects[simplenews_statistics][version] = "1.0-alpha1"
; Syntax error in simplenews_statistics test file
; https://www.drupal.org/node/2607422
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6813
projects[simplenews_statistics][patch][] = https://www.drupal.org/files/issues/simplenews_statistics-syntax_error-2607422-3.patch
; https://www.drupal.org/node/2673290
projects[simplenews_statistics][patch][] = https://www.drupal.org/files/issues/simplenews_statistics-simpletest-warning-message-2673290-3-D7.patch
; https://www.drupal.org/node/2351763
projects[simplenews_statistics][patch][] = https://www.drupal.org/files/issues/simplenews_statistics.module_0.patch

projects[site_map][subdir] = "contrib"
projects[site_map][version] = "1.3"

projects[smart_trim][subdir] = "contrib"
projects[smart_trim][version] = 1.5

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[subscriptions][subdir] = "contrib"
projects[subscriptions][version] = "1.1"

projects[tagclouds][subdir] = "contrib"
projects[tagclouds][version] = "1.12"

projects[term_reference_tree][subdir] = "contrib"
projects[term_reference_tree][version] = "1.11"
; i18n compatibility
; https://www.drupal.org/node/1514794
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-2000
projects[term_reference_tree][patch][1514794] = https://www.drupal.org/files/i18n_compatibility_rerolled-1514794-27.patch
; Slider layout broken in IE lt i8
; https://www.drupal.org/project/term_reference_tree/issues/1277268
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-2000
projects[term_reference_tree][patch][] = https://www.drupal.org/files/issues/slider_layout_broken_in_ie8-1277268-25.patch
; PHP Fatal Error Call to undefined method i18n_object_wrapper::
; strings_update().
; It fixes a bug reproducible on sub-sites like BRP but not on fresh install
; of the platform.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1987
; https://www.drupal.org/node/2082573
projects[i18n][patch][] = https://www.drupal.org/files/issues/2018-06-24/i18n-fatal-error-undefined-strings_update-2082573-54.patch

projects[title][download][branch] = 7.x-1.x
projects[title][download][revision] = 8119fa2
projects[title][download][type] = git
projects[title][subdir] = "contrib"

projects[tmgmt][subdir] = contrib
projects[tmgmt][version] = 1.0-rc3
; @see https://www.drupal.org/node/2489134
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/support_for_link_field-2489134-9.patch
; @see https://www.drupal.org/node/2722455
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/tmgmt-test_translator_missing-2722455-2.patch
; #2812863 : Insufficient access check on Views
; https://www.drupal.org/node/2812863
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-60
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/2812863.patch
; #2362321 : Check source length limits
; https://www.drupal.org/node/2362321
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1802
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2029
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/2019-02-04/check_source_length-d7-2362321-42.patch
; #2955245 : i18nviews strings are not shown on sources view
; https://www.drupal.org/node/2955245
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1878
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/2018-04-17/2955245-5.patch
; https://www.drupal.org/node/3021843
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2178
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/2020-02-26/translation_not_taking_into_account_the_source_data_update-3021843-23.patch
; https://www.drupal.org/project/tmgmt/issues/3050356
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2590
projects[tmgmt][patch][] = https://www.drupal.org/files/issues/2019-04-24/count_error_php_7_2-3050356-2.patch

projects[token][subdir] = "contrib"
projects[token][version] = "1.7"
; #1058912: Prevent recursive tokens
; https://www.drupal.org/node/1058912
projects[token][patch][] = https://www.drupal.org/files/token-1058912-88-limit-token-depth.patch

projects[token_filter][subdir] = "contrib"
projects[token_filter][version] = 1.1

projects[translation_overview][subdir] = "contrib"
projects[translation_overview][version] = "2.0-beta2"

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
projects[username_enumeration_prevention][version] = "1.3"

projects[uuid][subdir] = "contrib"
projects[uuid][version] = "1.3"
; https://www.drupal.org/project/uuid/issues/3058011
projects[uuid][patch][] = https://git.drupalcode.org/project/uuid/commit/311a2d668f990f7547c2125cebf69b55d2349f77.diff
; https://www.drupal.org/node/3061669
projects[uuid][patch][] = https://www.drupal.org/files/issues/2019-09-27/uuid-fix_missing_services_test_class-3061669-17.patch

projects[variable][subdir] = "contrib"
projects[variable][version] = "2.5"

projects[video][subdir] = "contrib"
projects[video][version] = "2.14"
projects[video][patch][] = patches/video-revert_issue-1891012-0.patch
;NEPT-2629 PHP7 compatibility
projects[video][patch][] = patches/phpvideotoolkit-2629.patch
projects[video][patch][] = https://www.drupal.org/files/issues/2019-08-06/video-php7.2-3039351-3-7.x.patch
;MULTISITE-883 security
projects[video][patch][] = patches/video-security-883.patch
;NEPT-2690 PHP7.3 compatibility
projects[video][patch][] = https://www.drupal.org/files/issues/2019-08-20/continue_in_switch-3042169-2.patch

projects[views][subdir] = "contrib"
projects[views][version] = 3.23
; Default argument not skipped in breadcrumbs
; https://www.drupal.org/node/1201160
projects[views][patch][] = https://www.drupal.org/files/issues/views-contextual_filter_exception_breadcrumbs-1201160-17.patch
; Issue #3012609: Issues with AJAX for exposed filters
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2261
; https://www.drupal.org/project/views/issues/3012609
; https://www.drupal.org/project/views/issues/1809958
projects[views][patch][] = https://www.drupal.org/files/issues/2019-07-09/issues-ajax-exposed-filters-blocks-1809958-74.patch
; Issue 3076826: func_get_args(), no longer report the original value as passed to a parameter
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2641
; https://www.drupal.org/project/views/issues/3076826
projects[views][patch][] = https://www.drupal.org/files/issues/2019-08-23/views-php7-3076826-2.patch

projects[views_ajax_history][subdir] = "contrib"
projects[views_ajax_history][version] = "1.0"

projects[views_bootstrap][subdir] = "contrib"
projects[views_bootstrap][version] = "3.2"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.5"
; Rules actions 'View and display' only works if Bulk Ops field is in 'master' of a view.
; https://www.drupal.org/node/2856974
projects[views_bulk_operations][patch][] = https://www.drupal.org/files/issues/non_master_views_actions_2856974-2.patch
; Issue #3054586: [php7 compatibility]: func_get_args(), no longer report the original value as passed to a parameter
; https://www.drupal.org/project/views_bulk_operations/issues/3054586
projects[views_bulk_operations][patch][] = https://www.drupal.org/files/issues/2019-05-16/removed_warning_for_php7.2.patch

projects[views_data_export][subdir] = "contrib"
projects[views_data_export][version] = "3.2"
; PHP 7 compatibility Issue
; https://www.drupal.org/project/views_data_export/issues/3005288
projects[views_data_export][patch][] = https://www.drupal.org/files/issues/2018-10-09/views_data_export-phpcs_warning-php_tag.patch
; NEPT-2845 Fix missing primary key issues.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2845
projects[views_data_export][patch][] = https://www.drupal.org/files/issues/2020-08-03/views_data_export_object_cache_add_primary_-2715565-6.patch

projects[views_datasource][version] = "1.0-alpha2"
projects[views_datasource][subdir] = "contrib"

projects[views_geojson][subdir] = "contrib"
projects[views_geojson][version] = "1.0-beta3"

projects[views_litepager][subdir] = "contrib"
projects[views_litepager][version] = "3.0"

projects[views_slideshow][subdir] = "contrib"
projects[views_slideshow][version] = "3.10"

projects[views_slideshow_slider][subdir] = "contrib"
projects[views_slideshow_slider][version] = "3.0"

projects[votingapi][subdir] = "contrib"
projects[votingapi][version] = "2.15"

projects[webform][subdir] = "contrib"
projects[webform][version] = "4.21"
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2354
; Remove link to create new user.
projects[webform][patch][] = patches/webform-use_ecas_link-MULTISITE-1235.patch

projects[webform_rules][subdir] = "contrib"
projects[webform_rules][version] = "1.6"

projects[workbench][subdir] = "contrib"
projects[workbench][version] = "1.2"

projects[workbench_access][subdir] = "contrib"
projects[workbench_access][version] = "1.4"

projects[workbench_email][subdir] = "contrib"
projects[workbench_email][version] = "3.12"
; Issue #2501321: Add email subject and message to Features.
; https://www.drupal.org/node/2590385
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-7225
projects[workbench_email][patch][] = https://www.drupal.org/files/issues/2018-07-13/workbench_email-feature_revert_lock-3.patch
; Issue #2985968: Notice: Undefined index: config_container in workbench_email_form_submit().
; https://www.drupal.org/project/workbench_email/issues/2985968
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1996
projects[workbench_email][patch][] = https://www.drupal.org/files/issues/2018-07-16/php_notice_undefined_index-config_container-1.patch

projects[drafty][subdir] = "contrib"
projects[drafty][version] = "1.0-rc1"
; Issue #2487013: Make Drafty work with the Title module patch.
; https://www.drupal.org/node/2487013
projects[drafty][patch][] = https://www.drupal.org/files/issues/title-module-fix-2487013-13.patch

projects[workbench_moderation][subdir] = "contrib"
projects[workbench_moderation][version] = "3.0"
; Issue #2360091 View published tab is visible when a published node has a draft.
; https://www.drupal.org/node/2360091
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-10670
projects[workbench_moderation][patch][] = https://www.drupal.org/files/issues/workbench_moderation-7.x-dev_update_tab_count.patch
; Issue #2825391 Fix current state for transition rules
; https://www.drupal.org/node/2825391
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1722
projects[workbench_moderation][patch][2825391] = https://www.drupal.org/files/issues/2018-05-14/workbench_moderation_fix_rules_current_state-2825391-46.patch

; Workbench_og does not have a stable version that allows applying the 2
; patches needed to fix the issues NEPT-296 AND NEPT-1866.
; To unblock the situation, the module maintainer has accepted to include
; the patch for NEPT-296 through the commit used below.
; Except the fix, this commit does not add anything to the module version
; previously used by the platform (7.x-2.0-beta1).
; NEPT-296 covers:
; Content not accessible after being published - node_access not updated
; Issue https://www.drupal.org/node/2835937
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-296
projects[workbench_og][subdir] = "contrib"
projects[workbench_og][type] = module
projects[workbench_og][download][type] = git
projects[workbench_og][download][revision] = 511caed35326ec7f328e794dc4be21eb33c5ae86
projects[workbench_og][download][branch] = 7.x-2.x
; Check access for users to view content that was created by them and don't
; belong to an organic group.
; Issue https://www.drupal.org/project/workbench_og/issues/2006134
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1866
projects[workbench_og][patch][] = https://www.drupal.org/files/issues/2018-06-29/workbench_og-my_drafts_missing-2006134-6.patch
; Check access for unpublished content not included on a group.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2242
projects[workbench_og][patch][] = patches/workbench_og_grants.patch

; Fix version on a commit, see issue NEPT-2247
projects[wysiwyg][subdir] = "contrib"
;projects[wysiwyg][download][type] = "git"
;projects[wysiwyg][download][url] = "http://git.drupal.org/project/wysiwyg.git"
;projects[wysiwyg][download][revision] = "18832abda6a2a6df93b72a6edb8b980d1e948605"
; CKEditor height does not reflect the rows attribute
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2185
projects[wysiwyg][version] = "2.7"
;projects[wysiwyg][patch][2410565] = https://www.drupal.org/files/issues/wysiwyg-heights.2410565.5.patch
; Error highlight missing on wysiwyg
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2199
;projects[wysiwyg][patch][] = https://www.drupal.org/files/issues/wysiwyg-highlighting-required-field-error-2685519-2.patch

projects[xml_field][subdir] = "contrib"
projects[xml_field][version] = "2.3"

projects[xmlsitemap][subdir] = "contrib"
projects[xmlsitemap][version] = "2.6"
; Using rel="alternate" rather than multiple sitemaps by language context
; https://www.drupal.org/node/1670086
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11505
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2083
projects[xmlsitemap][patch][] = https://www.drupal.org/files/issues/2018-10-17/xmlsitemap-multilingual_rel_alternate-1670086-99.patch


; =========
; Libraries
; =========

; chosen 1.8.2
libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.8.2/chosen_v1.8.2.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries

; colorbox 1.6.3
libraries[colorbox][download][type] = get
libraries[colorbox][download][url] = https://github.com/jackmoore/colorbox/archive/1.6.3.zip
libraries[colorbox][directory_name] = colorbox
libraries[colorbox][destination] = libraries

; ckeditor 4.13.1
libraries[ckeditor][download][type]= "file"
libraries[ckeditor][download][request_type]= "get"
libraries[ckeditor][download][file_type] = "zip"
libraries[ckeditor][download][url] = https://download.cksource.com/CKEditor/CKEditor/CKEditor%204.14.0/ckeditor_4.14.0_full.zip
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
; Adding patch for PHP7 compatibilty on IcalCreator.class.
; https://www.drupal.org/files/issues/iCalcreator-php-7-2707373-6.patch
libraries[iCalcreator][patch][2707373] = https://www.drupal.org/files/issues/iCalcreator-php-7-2707373-6.patch

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

; mpdf
libraries[mpdf][download][type]= "file"
libraries[mpdf][download][request_type]= "get"
libraries[mpdf][download][file_type] = "zip"
libraries[mpdf][download][url] = https://github.com/mpdf/mpdf/archive/v8.0.4.zip
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
libraries[html5shiv][download][type] = "get"
libraries[html5shiv][download][url] = https://raw.githubusercontent.com/aFarkas/html5shiv/a3c7567c5f7055f9b76230bbbc79967d0b9f7003/dist/html5shiv.min.js

; Ec_resp theme: jQuery Mousewheel
libraries[mousewheel][destination] = "themes/ec_resp"
libraries[mousewheel][directory_name] = "scripts"
libraries[mousewheel][download][type] = "get"
libraries[mousewheel][download][url] = https://raw.githubusercontent.com/jquery/jquery-mousewheel/33dc8f1090da2eaadbca8e782965d7fd6c28db42/jquery.mousewheel.min.js

; Ec_resp theme: Respond JS
libraries[respond][destination] = "themes/ec_resp"
libraries[respond][directory_name] = "scripts"
libraries[respond][download][type] = "get"
libraries[respond][download][url] = https://raw.githubusercontent.com/scottjehl/Respond/9d91fd47eb59c11a80d570d4ea0beaa59cfc71bf/dest/respond.min.js

; ======
; Themes
; ======

projects[ec_resp][type] = theme
projects[ec_resp][download][type] = git
projects[ec_resp][download][url] = https://github.com/ec-europa/ec_resp.git
projects[ec_resp][download][tag] = 2.3.10

projects[atomium][type] = theme
projects[atomium][version] = 2.30

projects[ec_europa][type] = theme
projects[ec_europa][download][type] = git
projects[ec_europa][download][url] = https://github.com/ec-europa/ec_europa.git
projects[ec_europa][download][tag] = 0.0.26

; ==============
; Custom modules
; ==============

projects[nexteuropa_poetry][subdir] = "contrib"
projects[nexteuropa_poetry][type] = module
projects[nexteuropa_poetry][download][type] = git
projects[nexteuropa_poetry][download][url] = https://github.com/ec-europa/nexteuropa_poetry.git
projects[nexteuropa_poetry][download][tag] = 0.1.1

projects[nexteuropa_varnish][subdir] = "custom"
projects[nexteuropa_varnish][type] = module
projects[nexteuropa_varnish][download][type] = git
projects[nexteuropa_varnish][download][url] = https://github.com/ec-europa/digit-ne-varnish.git
projects[nexteuropa_varnish][download][tag] = v1.0.11
