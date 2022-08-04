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
projects[admin_menu][patch][]  = patches/admin_menu-above_globan_nept_2667.patch

projects[administration_language_negotiation][subdir] = "contrib"
projects[administration_language_negotiation][version] = "1.4"

projects[advagg][subdir] = "contrib"
projects[advagg][version] = "2.35"

projects[advanced_help][subdir] = "contrib"
projects[advanced_help][version] = "1.6"

projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.12"
; Issue #1649158 : Date Facets (without a time) can show in Multiple Months.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-4335
projects[apachesolr][patch][1649158] = https://www.drupal.org/files/apachesolr-multiple-dates-hack-1649158-15.patch
; Issue #2657666 : Notice: Undefined property: stdClass::$status_message
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-7651
projects[apachesolr][patch][2657666] = https://www.drupal.org/files/issues/apachesolr-undefined-property-2657666-4-D7.patch
; Delay removing entities from the index.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11582
projects[apachesolr][patch][2764637] = https://www.drupal.org/files/issues/2020-01-28/apachesolr-delay-entity-removal-2764637-4.patch

projects[apachesolr_attachments][subdir] = "contrib"
projects[apachesolr_attachments][version] = "1.4"
; Issue #2581925 : Empty parent_entity_id in apachesolr_index_entities_file table.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-4224
projects[apachesolr_attachments][patch][2581925] = https://www.drupal.org/files/issues/apachesolr_attachments-empty_parent_entity_id-2581925-0.patch
; Issue #1854088 : PDOException: SQLSTATE[40001]: Serialization failure: 1213 Deadlock found.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-3744
projects[apachesolr_attachments][patch][1854088] = https://www.drupal.org/files/issues/apachesolr_attachments-cleanup_efficiency_and_deadlock_chance_reduction-1854088-16.patch
; Issue #2017705 : Performance! Add missed indexes to apachesolr_index_entities_file table
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2776
projects[apachesolr_attachments][patch][2017705] = https://www.drupal.org/files/issues/module_slows_down-2017705-7.patch
; Issue #2677866 : Cannot install on mysql >= 5.6
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-326
projects[apachesolr_attachments][patch][2677866] = https://www.drupal.org/files/issues/mysql-56-compatibility-2677866-12.patch

projects[apachesolr_multilingual][subdir] = "contrib"
projects[apachesolr_multilingual][version] = "1.3"
; Issue #2998996: [ PHP 7.2 Compatibility ] - Function each() is deprecated since PHP 7.2; Use a foreach loop instead
projects[apachesolr_multilingual][patch][2998996] = https://www.drupal.org/files/issues/2019-06-26/apachesolr_multilingual-each_deprecated-2998996-9-D7.patch

projects[apachesolr_multisitesearch][subdir] = "contrib"
projects[apachesolr_multisitesearch][version] = "1.2"

projects[autologout][subdir] = "contrib"
projects[autologout][version] = "4.6"

projects[autosave][subdir] = "contrib"
projects[autosave][version] = "2.2"

projects[bean][subdir] = "contrib"
projects[bean][version] = 1.13

projects[better_exposed_filters][subdir] = "contrib"
projects[better_exposed_filters][version] = "3.6"

projects[better_formats][subdir] = "contrib"
projects[better_formats][version] = "1.0-beta2"
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-157
; Apply patch to fix xss injection
projects[better_formats][patch][2896131] = https://www.drupal.org/files/issues/better_formats-2896131-6-missing-check_plain-when-showing-filter-name.patch

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
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-6231
projects[chr][patch][2355631] = https://www.drupal.org/files/issues/chr-1.6-patch-rewrite-header-host-without-standard-port-number_0.patch
; Issue #2825701: allow PURGE requests.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-81
projects[chr][patch][2825701] = https://www.drupal.org/files/issues/chr-purge-2825701-2.patch
projects[chr][patch][3028043] = https://www.drupal.org/files/issues/2019-03-04/chr_status_message-3028043-2.patch

projects[ckeditor_link][subdir] = "contrib"
projects[ckeditor_link][version] = "2.3"

projects[ckeditor_lite][subdir] = contrib
projects[ckeditor_lite][version] = 1.0-rc3

projects[coffee][subdir] = "contrib"
projects[coffee][version] = 2.3

projects[collapse_text][subdir] = "contrib"
projects[collapse_text][version] = "2.4"
projects[collapse_text][patch][2487115] = http://cgit.drupalcode.org/collapse_text/patch/?id=85656e4960d22fc145d5c3e3a79b81eaeb4cbde5

projects[colorbox][subdir] = "contrib"
projects[colorbox][version] = "2.16"

projects[colors][subdir] = "contrib"
projects[colors][version] = "1.0-rc1"

projects[context][subdir] = "contrib"
projects[context][version] = "3.10"
projects[context][patch][873936] = https://www.drupal.org/files/issues/massively-increase-pe-reroll-873936-67.patch

projects[context_entity_field][subdir] = "contrib"
projects[context_entity_field][version] = "1.1"
; Make condition work for entity references.
; Patch implemented in DEV version.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-5056
projects[context_entity_field][patch][1847038] = https://www.drupal.org/files/add-entity-references.patch

projects[context_og][subdir] = "contrib"
projects[context_og][version] = "2.1"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.19"

projects[customerror][subdir] = "contrib"
projects[customerror][version] = "1.4"

projects[date][subdir] = "contrib"
projects[date][version] = "2.12"

projects[date_ical][subdir] = "contrib"
projects[date_ical][version] = "3.10"

projects[diff][subdir] = "contrib"
projects[diff][version] = 3.4

projects[ds][subdir] = "contrib"
projects[ds][version] = "2.16"

projects[easy_breadcrumb][subdir] = "contrib"
projects[easy_breadcrumb][version] = "2.17"
projects[easy_breadcrumb][patch][3080576] = https://www.drupal.org/files/issues/2020-12-18/easy_breadcrumb_query_array.patch
projects[easy_breadcrumb][patch][1649220] = https://www.drupal.org/files/issues/2021-05-19/easy_breadcrumb-init_fatal_issue.patch

projects[email][subdir] = "contrib"
projects[email][version] = "1.3"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.10"
; Invalid argument supplied for foreach() in entity_metadata_convert_schema()
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1025
projects[entity][patch][2564119] = https://www.drupal.org/files/issues/Use-array-in-foreach-statement-2564119-1.patch

projects[entity_translation][subdir] = "contrib"
projects[entity_translation][version] = "1.1"
; Issue #1707156 : Workbench Moderation integration
projects[entity_translation][patch][1707156] = https://www.drupal.org/files/issues/2018-07-25/workbench_moderation-1707156-83.patch

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = 1.5
; Issue #10558568 : Broken updates due to Classes living in .module files
projects[entitycache][patch][2441965] = https://www.drupal.org/files/issues/entitycache_fix_upgrade_path-2441965-62.patch
; Issue #2981629 : create_function is deprecated in PHP 7.2
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2635
projects[entitycache][patch][2981629] = https://www.drupal.org/files/issues/2018-07-05/entitycache_php_7-2981629-0.patch

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.5"
; Allow handlers to modify $items before calling entity_view()
projects[entityreference][patch][2651982] = https://www.drupal.org/files/issues/feature--entityreference-alter-items.patch

projects[entityreference_prepopulate][subdir] = "contrib"
projects[entityreference_prepopulate][download][type] = git
projects[entityreference_prepopulate][download][revision] = 5d65d841
projects[entityreference_prepopulate][download][branch] = 7.x-1.x

projects[eu_cookie_compliance][subdir] = "contrib"
projects[eu_cookie_compliance][version] = "1.28"

projects[extlink][subdir] = "contrib"
projects[extlink][version] = "1.18"

projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.5"
; facetapi_map_assoc() does not check if index exists.
; Note: This patch is to be remoaved with the future version 7.x-1.6.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2042
projects[facetapi][patch][2373023] = https://www.drupal.org/files/issues/facetapi-2768779-facetapi_map_assoc-undefined-index.patch
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2631
projects[facetapi][patch][3055360] = https://www.drupal.org/files/issues/2019-08-23/facetapi-func_get_args-3055360-7_d7.patch

projects[fast_404][subdir] = "contrib"
projects[fast_404][version] = "1.5"

projects[features][subdir] = "contrib"
projects[features][version] = "2.13"

projects[feature_set][subdir] = "contrib"
projects[feature_set][version] = "1.3"
; NEPT-930 - Feature set page should use admin theme - adding new markup, css and js to the patch
projects[feature_set][patch][] = patches/feature_set-add_categories_management-nexteuropa_4459-nept_930.patch
projects[feature_set][patch][] = patches/feature_set-check_disable_enable-nexteuropa_4459.patch
projects[feature_set][patch][] = patches/feature_set-misc-nexteuropa_4459.patch
; Issue #2831766: Feature set does not invoke hook_requirements().
projects[feature_set][patch][2831766] = https://www.drupal.org/files/issues/feature_set_invoke_hook_requirements-2831766-6.patch

projects[feeds][subdir] = "contrib"
projects[feeds][version] = "2.0-beta5"
projects[feeds][patch][2333667] = https://www.drupal.org/files/issues/feeds_delete_if_empty_source-2333667-8.patch
projects[feeds][patch][] = patches/feeds-phpcs_ignore_safe_mode.patch

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
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2018
projects[feeds_et][patch][2078069] = https://www.drupal.org/files/issues/feeds_et_link_support-2078069-3.patch

projects[feeds_tamper][subdir] = "contrib"
projects[feeds_tamper][version] = "1.2"

projects[feeds_xpathparser][subdir] = "contrib"
projects[feeds_xpathparser][version] = "1.1"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.6"
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6603
projects[field_group][patch][2604284] = https://www.drupal.org/files/issues/field_group_label_translation_patch.patch
; After update from 1.5 to 1.6 empty field groups (because of field permissions)
; are now being displayed as empty groups
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2016
projects[field_group][patch][2494385] = https://www.drupal.org/files/issues/field_group-remove-array_parents-2494385-11.patch
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2633
projects[field_group][patch][3016503] = https://www.drupal.org/files/issues/2018-11-28/field_group-func_get_args-3016503-2.patch

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.35"

projects[filefield_sources][subdir] = "contrib"
projects[filefield_sources][version] = "1.11"

projects[filefield_sources_plupload][subdir] = "contrib"
projects[filefield_sources_plupload][version] = "1.1"
; Fix Field description persistance
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-7572
projects[filefield_sources_plupload][patch][2705523] = https://www.drupal.org/files/issues/filefield_sources_plupload-metadata_persistance-2705523.patch
; Fix ajax file updload
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1844
projects[filefield_sources_plupload][patch][2466505] = https://www.drupal.org/files/issues/filefield-sources-plupload-ajax-wrapper-2466505-1.patch

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.9"
; NEPT-2845 Fix missing Primary Key issues.
projects[flag][patch][2834419] = https://www.drupal.org/files/issues/2020-11-04/flag-add_missing_primary_key-2834419-6_1.patch
; https://www.drupal.org/node/2333593
; https://www.drupal.org/node/3255257
; Merge both patches locally
projects[flag][patch][] = patches/flag-offset_null_flag_rules_action_info-3255257-2333593.patch


projects[flexslider][subdir] = "contrib"
projects[flexslider][version] = "2.0-rc2"
; Issue #2219435: remove pause button if there is only one slide.
projects[flexslider][patch][2219435] = https://www.drupal.org/files/issues/pause_1_slide-flexslider-2219435-1.patch

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
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-4393
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6674
projects[fullcalendar][patch][2185449] = https://www.drupal.org/files/issues/ajax_date_format-2185449-17.patch
; Issue #1803770: Uncaught TypeError: Cannot read property 'views_dom_id:***' of undefined.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-4112
projects[fullcalendar][patch][1803770 = https://www.drupal.org/files/issues/uncaught_typeerror-1803770-10.patch
; Issue #2325549: AJAX doesn't work in jQuery 1.9+
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-7373
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-7237
projects[fullcalendar][patch][2325549] = https://www.drupal.org/files/issues/2325549-jquery19_ajax.patch
; Issue #3063000: PHP7 compatibility.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2661
projects[fullcalendar][patch][3063000] = https://www.drupal.org/files/issues/2019-06-20/php7.2-upgrade-707484-1.patch


projects[geofield][subdir] = "contrib"
projects[geofield][version] = "2.3"
projects[geofield][patch][2534822] = https://www.drupal.org/files/issues/geofield-feeds_import_not_saving-2534822-17.patch

projects[geophp][download][branch] = 7.x-1.x
projects[geophp][download][revision] = 2777c5e
projects[geophp][download][type] = git
projects[geophp][subdir] = "contrib"

projects[honeypot][subdir] = "contrib"
projects[honeypot][version] = "1.26"
; NEPT-2845 Fix missing primary key issues.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2845
projects[honeypot][patch][2943526] = https://www.drupal.org/files/issues/2020-07-07/honeypot-add_primary_key-2943526-13-D7.patch

projects[i18n][subdir] = "contrib"
projects[i18n][version] = "1.31"
; Language field display should default to hidden.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-3996
; Also requires a patch for Drupal core issue https://www.drupal.org/node/1256368,
; you can find it in drupal-core.make.
projects[i18n][patch][1350638] = https://www.drupal.org/files/i18n-hide_language_by_default-1350638-5.patch

projects[i18nviews][subdir] = "contrib"
projects[i18nviews][version] = "3.0-alpha1"

projects[inline_entity_form][subdir] = "contrib"
projects[inline_entity_form][version] = "1.8"

projects[job_scheduler][subdir] = "contrib"
projects[job_scheduler][version] = "2.0-alpha3"

projects[jplayer][subdir] = "contrib"
projects[jplayer][version] = "2.0"
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1657
projects[jplayer][patch][2977834] = https://www.drupal.org/files/issues/2018-06-06/2977834-2.patch

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.7"
; Issue #2621436: Allow permissions to granted roles.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-7825
projects[jquery_update][patch][2621436] = https://www.drupal.org/files/issues/jquery_update_permissions-2621436-2_0.patch

projects[l10n_update][subdir] = "contrib"
projects[l10n_update][version] = "2.2"
; Issue #2922809: When trying to update i have "Recoverable fatal error: Argument 2 passed to format_string".
; The fix is made of 2 patches.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-272
projects[l10n_update][patch][2922809] = https://www.drupal.org/files/issues/l10n_update-missing-log-vars-2922809-10.patch

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.5"

projects[link][subdir] = "contrib"
projects[link][version] = "1.9"

projects[linkchecker][subdir] = "contrib"
projects[linkchecker][version] = "1.4"
projects[linkchecker][patch][2127731] = https://www.drupal.org/files/issues/bean-integration-2127731-0.patch
projects[linkchecker][patch][2593465] = https://www.drupal.org/files/issues/linkchecker-max_redirects-2593465-1-D7_0.patch

projects[mail_edit][subdir] = "contrib"
projects[mail_edit][version] = "1.1"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = "2.34"

projects[maxlength][subdir] = "contrib"
projects[maxlength][version] = "3.3"

projects[media][subdir] = contrib
projects[media][version] = 2.27
; Embedded documents in the WYSIWYG can be very hard to delete.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-771
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1015
; Media markup navigation causes duplicated links
projects[media][patch][2028231] = https://www.drupal.org/files/issues/media-delete-embedded-document-2028231-11.patch
; NEPT-2718 Error thrown when maxlength module is enabled
projects[media][patch][] = patches/media-nept_2718_maxlength_title_error.patch
; NEPT-2845 Fix missing primary key issues.
projects[media][patch][2865131] = https://www.drupal.org/files/issues/2020-08-03/add_primary_key_for-2865131-8.patch

projects[media_avportal][subdir] = "contrib"
projects[media_avportal][version] = "1.5"

projects[media_dailymotion][subdir] = "contrib"
projects[media_dailymotion][version] = "1.1"
; Issue #2560403: Provide Short URL for media dailymotion.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-7082
projects[media_dailymotion][patch][2560403] = https://www.drupal.org/files/issues/media_dailymotion-mini-url-2560403-7-7.x.patch
projects[media_dailymotion][patch][] = patches/media_dailymotion-handle_protocol_4103.patch

projects[media_flickr][subdir] = "contrib"
projects[media_flickr][version] = "2.0-alpha5"

projects[media_node][subdir] = "contrib"
projects[media_node][version] = "1.0-rc2"
projects[media_node][patch][] = patches/media_node-incorrect_permission_check-4273.patch

projects[media_vimeo][subdir] = "contrib"
projects[media_vimeo][version] = "2.1"

projects[media_youtube][subdir] = "contrib"
projects[media_youtube][version] = "3.10"
projects[media_youtube][patch][2982442] = https://www.drupal.org/files/issues/2018-06-28/nocookie-default.patch
projects[media_youtube][patch][1572550] = https://www.drupal.org/files/issues/2021-01-07/media_youtube-1572550-117.patch

projects[media_colorbox][subdir] = "contrib"
projects[media_colorbox][version] = "1.0-rc4"
projects[media_colorbox][patch][3155898] = https://www.drupal.org/files/issues/2020-06-30/php-7_4-3155898-1.patch

projects[menu_attributes][subdir] = "contrib"
projects[menu_attributes][version] = "1.1"
projects[menu_attributes][patch][] = patches/menu_attributes-add_icon_for_menu_item-2327.patch
projects[menu_attributes][patch][] = patches/menu_attributes-option_to_disable_css_class-2988.patch
projects[menu_attributes][patch][] = patches/menu_attributes-option_to_hide_children-6757.patch

projects[menu_block][subdir] = "contrib"
projects[menu_block][version] = "2.9"

projects[menu_token][download][branch] = 7.x-1.x
projects[menu_token][download][revision] = 27ab9f244d7813803cfa662d05ffc1747d758956
projects[menu_token][download][type] = git
projects[menu_token][subdir] = "contrib"
projects[menu_token][patch][2838033] = https://www.drupal.org/files/issues/2838033_1.patch

projects[message][subdir] = "contrib"
projects[message][version] = "1.12"
; Fix for an error when the purge limit fall below 0 during the cron execution.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1704
projects[message][patch][2030101] = https://www.drupal.org/files/issues/fix-cron-purge-messages-error-2030101-2.patch
; Fix Message type receive new internal ID on feature revert.
; https://www.drupal.org/project/message/issues/2719823
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1744
projects[message][patch][2719823] = https://www.drupal.org/files/issues/message-preserve-local-ids-on-revert-2719823-2.patch
; Fix Cloning fails when changing the form with ajax.
; https://www.drupal.org/project/message/issues/2872964
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1744
projects[message][patch][2872964] = https://www.drupal.org/files/issues/2872964-message-cloneajax-2.patch

projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.28"
; Prevents metatag_translate_metatags from returning error 500.
; https://www.drupal.org/project/metatag/issues/3224758
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2987
projects[metatag][patch][3224758] = https://www.drupal.org/files/issues/2021-07-21/metatag-n3224758-2.patch

projects[migrate][subdir] = contrib
projects[migrate][download][branch] = 7.x-1.x
projects[migrate][download][revision] = ac8a749e580c16b6963088fb1901aebb052e1008

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.1"
; Issue #3052121: INI directive 'safe_mode' is deprecated since PHP 5.3 and removed since PHP 5.4
projects[mimemail][patch][3052121] = https://www.drupal.org/files/issues/2019-05-02/remove-deprecated-function-3052121-2.patch
; Issue #2947006: Remove usage of deprecated create_function() calls for PHP 7.2+ future proofing
projects[mimemail][patch][2947006] = https://www.drupal.org/files/issues/2018-05-28/mimemail-support_php_72-2947006-4.patch

; This is a dependency of media_bulk_upload that platform provides
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2498
projects[multiform][subdir] = "contrib"
projects[multiform][version] = "1.6"

projects[nagios][download][branch] = 7.x-1.x
projects[nagios][download][revision] = 7da732e2d4943ec5368243f4cd2e33eb02769f23
projects[nagios][download][type] = git
projects[nagios][subdir] = "contrib"
; NEPT-451 Add possibility to report on individual variables
projects[nagios][patch][2854854] = https://www.drupal.org/files/issues/nagios-id-support-2854854-5.patch

projects[nexteuropa_newsroom][download][type] = git
projects[nexteuropa_newsroom][download][url] = https://github.com/ec-europa/nexteuropa-newsroom-reference.git
projects[nexteuropa_newsroom][download][tag] = v3.5.17
projects[nexteuropa_newsroom][subdir] = custom

projects[og][subdir] = "contrib"
projects[og][download][type] = git
projects[og][download][branch] 7.x-2.x
projects[og][download][revision] = 31b62e66
; VBO and OG
projects[og][patch][2561507] = https://www.drupal.org/files/issues/og_vbo_and_og_2561507-6.patch
projects[og][patch][] = patches/og-og_field_access-bypass_field_access-5159.patch
; NEXTEUROPA-11789 Issue in Bean reference to OG
projects[og][patch][1880226] = https://www.drupal.org/files/issues/og-use_numeric_id_for_membership_etid-1880226-5.patch

projects[og_linkchecker][subdir] = "contrib"
projects[og_linkchecker][version] = "2.0-rc1"

projects[om_maximenu][subdir] = "contrib"
projects[om_maximenu][version] = "1.44"
;NEPT-1631: Creating a mega menu gives warnings
projects[om_maximenu][patch][1824704] = https://www.drupal.org/files/issues/fix_illegal_string_offset-1824704-8.patch

projects[password_policy][subdir] = "contrib"
projects[password_policy][version] = "2.0-alpha8"
;NEPT-2749: password_policy_user_load() assumes field is_generated exists
projects[password_policy][patch][2978953] = https://www.drupal.org/files/issues/2019-11-22/password_policy-check_existence_of_is_generated-2978953-7.patch

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.3"
; The online patch doesn't work with 1.3 version
projects[pathauto][patch][] = patches/pathauto-admin_patterns-1267966-140.patch
; Generate automatic URL alias
projects[pathauto][patch][1847444] = https://www.drupal.org/files/issues/pathauto-patch_for_pathautho1.3.patch

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
projects[plupload][patch][2974466] = https://www.drupal.org/files/issues/2018-05-22/files_not_uploaded_in_subdir-2974466.patch

projects[print][subdir] = "contrib"
projects[print][version] = "2.2"
; Allow alternate location of ttfont directories
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2253
projects[print][patch][3036143] = https://www.drupal.org/files/issues/2019-03-06/location_ttfont_directories-3036143-4.patch
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2639
projects[print][patch][3006747] = https://www.drupal.org/files/issues/2018-10-15/print-support-72.patch

projects[quicktabs][subdir] = "contrib"
projects[quicktabs][version] = "3.8"
projects[quicktabs][patch][] = patches/quicktabs-MULTISITE-3880.patch
projects[quicktabs][patch][2222805] = https://www.drupal.org/files/issues/quicktabs-log_empty-2222805-14.patch

projects[rate][subdir] = "contrib"
projects[rate][version] = "1.8"
; Description should be translatable
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-1178
projects[rate][patch][] = patches/rate-translate_description-1178.patch
; Undefined property: stdClass::$timezone in rate_expiration module
projects[rate][patch][1421016] = https://www.drupal.org/files/issues/rate-is_null_fix-1421016-9.patch
projects[rate][patch][3099838] = https://www.drupal.org/files/issues/2021-02-03/3099838-8.rate_.PHP-74-compatibility-.patch

projects[realname][subdir] = "contrib"
projects[realname][version] = "1.4"
projects[realname][patch][1369824] = https://www.drupal.org/files/issues/2021-01-20/realname-recursive_bug-1369824-7.x-1.4.patch
projects[realname][patch][2225889] = https://www.drupal.org/files/issues/2019-05-07/2225889-realname-correct-menu-10.patch
; Fix array offset warning on null.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2992
projects[realname][patch][3263690] = https://www.drupal.org/files/issues/2022-03-17/realname_autocomplete_array_offset_warning-3263690-2.patch

projects[redirect][subdir] = "contrib"
projects[redirect][download][branch] = 7.x-1.x
projects[redirect][download][revision] = 7f9531d08c4a3ffb18685fa894d3034299a572c0
; Prevent new redirects from being deleted on cron runs.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1945
projects[redirect][patch][1396446] = https://www.drupal.org/files/issues/2019-07-29/redirect_purge_from_created_1396446-67.patch
projects[redirect][patch][] = patches/redirect-nept_2502.patch

projects[registration][subdir] = "contrib"
projects[registration][version] = "1.7"
projects[registration][patch][3255020] = https://www.drupal.org/files/issues/2021-12-17/no-desc-for-default-formatter-3255020-2.patch

projects[registry_autoload][subdir] = "contrib"
projects[registry_autoload][version] = 1.3
; class_implements(): Class Drupal\integration\Backend\Entity\
; BackendEntityController does not exist and could not be loaded entity.module:1480
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1950
projects[registry_autoload][patch][2870868] = https://www.drupal.org/files/issues/autoload_bootstrap_dependency_issues-2870868-2.patch

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.13"
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2160
projects[rules][patch][826986] = https://www.drupal.org/files/issues/2020-03-19/file_events-826986-42.patch

; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2615
; We use the dev version of the module to be able to run the module simpletest.
projects[scheduler][subdir] = "contrib"
projects[scheduler][download][type] = "git"
projects[scheduler][download][url] = "https://git.drupalcode.org/project/scheduler.git"
projects[scheduler][download][revision] = "89707ba3affa72beea0b428230e61f4c5a0c1283"

; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2615
; We use the dev version of the module to be able to run the module simpletest.
projects[scheduler_workbench][subdir] = "contrib"
projects[scheduler_workbench][download][type] = "git"
projects[scheduler_workbench][download][url] = "https://git.drupalcode.org/project/scheduler_workbench.git"
projects[scheduler_workbench][download][revision] = "46e8db33e54a0d873ff60956d4d2f90d27c4735d"

; Allow to schedule the publish date of a revision
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1999
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2504
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2615
projects[scheduler_workbench][patch][2048999] = https://www.drupal.org/files/issues/2020-01-30/scheduler_workbench-revision_publish-2048999-69.patch
; NEPT-2787: Remove already published nodes from scheduler list
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2787
; We need a local patch for d.o/3118719 as the above already modidifies the files
projects[scheduler_workbench][patch][] = patches/scheduler_workbench-persistent_nodes_3118719_7.patch

projects[select_or_other][subdir] = "contrib"
projects[select_or_other][version] = 2.24

projects[simplenews][subdir] = "contrib"
projects[simplenews][version] = "1.1"
projects[simplenews][patch][] = patches/simplenews-fieldset_weight_4330.patch
; #2801239: Issue with Entity cache
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-121
projects[simplenews][patch][2801239] = https://www.drupal.org/files/issues/entitycache_issue-2801239-3.patch
; Add hook_drush_sql_sync_sanitize
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2100
projects[simplenews][patch][3017665] = https://www.drupal.org/files/issues/2019-02-11/Add_hook_drush_sql_sync_sanitize-3017665-7.patch
; Issue 3051338: Support PHP 7.2
projects[simplenews][patch][3051338] = https://www.drupal.org/files/issues/2019-04-28/remove-deprecated-each.patch

projects[simplenews_statistics][subdir] = "contrib"
projects[simplenews_statistics][version] = "1.0-alpha1"
; Syntax error in simplenews_statistics test file
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-6813
projects[simplenews_statistics][patch][2607422] = https://www.drupal.org/files/issues/simplenews_statistics-syntax_error-2607422-3.patch
projects[simplenews_statistics][patch][2673290] = https://www.drupal.org/files/issues/simplenews_statistics-simpletest-warning-message-2673290-3-D7.patch
projects[simplenews_statistics][patch][2351763] = https://www.drupal.org/files/issues/simplenews_statistics.module_0.patch

projects[site_map][subdir] = "contrib"
projects[site_map][version] = "1.3"

projects[smart_trim][subdir] = "contrib"
projects[smart_trim][version] = 1.6

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[subscriptions][subdir] = "contrib"
projects[subscriptions][version] = "1.1"

projects[tagclouds][subdir] = "contrib"
projects[tagclouds][version] = "1.12"

projects[term_reference_tree][subdir] = "contrib"
projects[term_reference_tree][version] = "1.11"
; i18n compatibility
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-2000
projects[term_reference_tree][patch][1514794] = https://www.drupal.org/files/i18n_compatibility_rerolled-1514794-27.patch
; Slider layout broken in IE lt i8
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-2000
projects[term_reference_tree][patch][1277268] = https://www.drupal.org/files/issues/slider_layout_broken_in_ie8-1277268-25.patch
; PHP Fatal Error Call to undefined method i18n_object_wrapper::
; strings_update().
; It fixes a bug reproducible on sub-sites like BRP but not on fresh install
; of the platform.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1987
projects[i18n][patch][2082573] = https://www.drupal.org/files/issues/2018-06-24/i18n-fatal-error-undefined-strings_update-2082573-54.patch

projects[title][subdir] = "contrib"
projects[title][version] = 1.0-beta4
projects[title][patch][3079443] = https://www.drupal.org/files/issues/2022-02-22/title-undefined_function_current_path.patch

projects[tmgmt][subdir] = contrib
projects[tmgmt][version] = 1.0-rc3
projects[tmgmt][patch][2489134] = https://www.drupal.org/files/issues/support_for_link_field-2489134-9.patch
projects[tmgmt][patch][2722455] = https://www.drupal.org/files/issues/tmgmt-test_translator_missing-2722455-2.patch
; #2812863 : Insufficient access check on Views
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-60
projects[tmgmt][patch][2812863] = https://www.drupal.org/files/issues/2812863.patch
; #2362321 : Check source length limits
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1802
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2029
projects[tmgmt][patch][2362321] = https://www.drupal.org/files/issues/2019-02-04/check_source_length-d7-2362321-42.patch
; #2955245 : i18nviews strings are not shown on sources view
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1878
projects[tmgmt][patch][2955245] = https://www.drupal.org/files/issues/2018-04-17/2955245-5.patch
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2178
projects[tmgmt][patch][3021843] = https://www.drupal.org/files/issues/2020-02-26/translation_not_taking_into_account_the_source_data_update-3021843-23.patch
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2590
projects[tmgmt][patch][3050356] = https://www.drupal.org/files/issues/2019-04-24/count_error_php_7_2-3050356-2.patch

projects[token][subdir] = "contrib"
projects[token][version] = "1.8"
; #1058912: Prevent recursive tokens
projects[token][patch][1058912] = https://www.drupal.org/files/token-1058912-88-limit-token-depth.patch

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
projects[uuid][patch][3058011] = https://git.drupalcode.org/project/uuid/commit/311a2d668f990f7547c2125cebf69b55d2349f77.diff
projects[uuid][patch][3061669] = https://www.drupal.org/files/issues/2019-09-27/uuid-fix_missing_services_test_class-3061669-17.patch

projects[variable][subdir] = "contrib"
projects[variable][version] = "2.5"

projects[video][subdir] = "contrib"
projects[video][version] = "2.14"
projects[video][patch][] = patches/video-revert_issue_1891012_0.patch
;NEPT-2629 PHP7 compatibility
projects[video][patch][] = patches/video-toolkit_2629.patch
projects[video][patch][3039351] = https://www.drupal.org/files/issues/2019-08-06/video-php7.2-3039351-3-7.x.patch
;MULTISITE-883 security
projects[video][patch][] = patches/video-security_883.patch
;NEPT-2690 PHP7.3 compatibility
projects[video][patch][3042169] = https://www.drupal.org/files/issues/2019-08-20/continue_in_switch-3042169-2.patch

projects[views][subdir] = "contrib"
projects[views][version] = 3.25
; Default argument not skipped in breadcrumbs
projects[views][patch][1201160] = https://www.drupal.org/files/issues/views-contextual_filter_exception_breadcrumbs-1201160-17.patch
; Issue #1809958: Issues with AJAX for exposed filters
; https://citnet.tech.ec.europa.eu/CITneupat/jira/browse/NEPT-2261
projects[views][patch][1809958] = https://www.drupal.org/files/issues/2019-07-09/issues-ajax-exposed-filters-blocks-1809958-74.patch

projects[views_ajax_history][subdir] = "contrib"
projects[views_ajax_history][version] = "1.0"

projects[views_bootstrap][subdir] = "contrib"
projects[views_bootstrap][version] = "3.5"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.6"

projects[views_data_export][subdir] = "contrib"
projects[views_data_export][version] = "3.2"
; PHP 7 compatibility Issue
projects[views_data_export][patch][3005288] = https://www.drupal.org/files/issues/2018-10-09/views_data_export-phpcs_warning-php_tag.patch
; NEPT-2845 Fix missing primary key issues.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2845
projects[views_data_export][patch][2715565] = https://www.drupal.org/files/issues/2020-08-03/views_data_export_object_cache_add_primary_-2715565-6.patch

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
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2354
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
; Issue #2590385: Add email subject and message to Features.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/MULTISITE-7225
projects[workbench_email][patch][2590385] = https://www.drupal.org/files/issues/2018-07-13/workbench_email-feature_revert_lock-3.patch
; Issue #2985968: Notice: Undefined index: config_container in workbench_email_form_submit().
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1996
projects[workbench_email][patch][2985968] = https://www.drupal.org/files/issues/2018-07-16/php_notice_undefined_index-config_container-1.patch

projects[drafty][subdir] = "contrib"
projects[drafty][version] = "1.0-rc1"
; Issue #2487013: Make Drafty work with the Title module patch.
projects[drafty][patch][2487013] = https://www.drupal.org/files/issues/title-module-fix-2487013-13.patch

projects[workbench_moderation][subdir] = "contrib"
projects[workbench_moderation][version] = "3.0"
; Issue #2360091 View published tab is visible when a published node has a draft.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-10670
projects[workbench_moderation][patch][2360091] = https://www.drupal.org/files/issues/workbench_moderation-7.x-dev_update_tab_count.patch
; Issue #2825391 Fix current state for transition rules
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1722
projects[workbench_moderation][patch][2825391] = https://www.drupal.org/files/issues/2018-05-14/workbench_moderation_fix_rules_current_state-2825391-46.patch
; Issue #3246269 Fix published node fields not updated.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2981
projects[workbench_moderation][patch][3246269] = https://www.drupal.org/files/issues/2022-03-01/original_node_as_current_published-3246269-2.patch

; Workbench_og does not have a stable version that allows applying the 2
; patches needed to fix the issues NEPT-296 AND NEPT-1866.
; To unblock the situation, the module maintainer has accepted to include
; the patch for NEPT-296 through the commit used below.
; Except the fix, this commit does not add anything to the module version
; previously used by the platform (7.x-2.0-beta1).
; NEPT-296 covers:
; Content not accessible after being published - node_access not updated
; Issue https://www.drupal.org/node/2835937
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-296
projects[workbench_og][subdir] = "contrib"
projects[workbench_og][type] = module
projects[workbench_og][download][type] = git
projects[workbench_og][download][revision] = 511caed35326ec7f328e794dc4be21eb33c5ae86
projects[workbench_og][download][branch] = 7.x-2.x
; Check access for users to view content that was created by them and don't
; belong to an organic group.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-1866
projects[workbench_og][patch][2006134] = https://www.drupal.org/files/issues/2018-06-29/workbench_og-my_drafts_missing-2006134-6.patch
; Check access for unpublished content not included on a group.
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2242
projects[workbench_og][patch][] = patches/workbench_og-grants.patch

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.9"
; CKEditor height does not reflect the rows attribute
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2185
projects[wysiwyg][patch][2410565] = https://www.drupal.org/files/issues/2022-01-06/wysiwyg-heights.2410565.9.patch
; Error highlight missing on wysiwyg
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-2199
projects[wysiwyg][patch][2685519] = https://www.drupal.org/files/issues/wysiwyg-highlighting-required-field-error-2685519-2.patch
; Notice: Trying to access array offset on value of type bool
projects[wysiwyg][patch][3256637] = https://www.drupal.org/files/issues/2022-01-06/wysiwyg-markitup.3256637.4.patch
; PHP 7.3 compliance.
projects[wysiwyg][patch][3261512] = https://www.drupal.org/files/issues/2022-02-01/wysiwyg-php7-compatibility-3261512_1.patch


projects[xml_field][subdir] = "contrib"
projects[xml_field][version] = "2.3"

projects[xmlsitemap][subdir] = "contrib"
projects[xmlsitemap][version] = "2.6"
; Using rel="alternate" rather than multiple sitemaps by language context
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-11505
; https://citnet.tech.ec.europa.eu/CITnet/jira/browse/NEPT-2083
projects[xmlsitemap][patch][1670086] = https://www.drupal.org/files/issues/2018-10-17/xmlsitemap-multilingual_rel_alternate-1670086-99.patch


; =========
; Libraries
; =========

; chosen 1.8.2
libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.8.2/chosen_v1.8.2.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries

; colorbox 1.6.4
libraries[colorbox][download][type] = get
libraries[colorbox][download][url] = https://github.com/jackmoore/colorbox/archive/1.6.4.zip
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

; iCalcreator 2.22
libraries[iCalcreator][download][url] = https://github.com/iCalcreator/iCalcreator/archive/3687fe06deab48e889eae8afd1d31d201eb2b8a0.zip
libraries[iCalcreator][download][type] = "file"
libraries[iCalcreator][download][request_type]= "get"
libraries[iCalcreator][download][file_type] = "zip"
libraries[iCalcreator][download][destination] = "../common/libraries"

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
projects[ec_europa][download][tag] = 0.0.27

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
