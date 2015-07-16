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
projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][patch][] = patches/admin_menu-correctly_display-2360249-74.patch
projects[admin_menu][patch][] = patches/admin_menu-ie6detect-1961178-2.patch
projects[admin_menu][patch][] = patches/admin_menu-undefined_index_name-1997386-3.patch

projects[advagg][subdir] = "contrib"
projects[advagg][version] = "2.7"

projects[advanced_help][subdir] = "contrib"
projects[advanced_help][version] = "1.0"
projects[advanced_help][patch][] = patches/advanced_help-solve_error_message-2202.patch

projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.7"
projects[apachesolr][patch][] = patches/apachesolr-attachment_indexation-481.patch
projects[apachesolr][patch][] = patches/apachesolr-invalidate-caches-new-node-type-2178283.patch
projects[apachesolr][patch][] = patches/apachesolr-multiples_dates-4335.patch
projects[apachesolr][patch][] = patches/apachesolr_search-overwritten_menu_items.patch

projects[apachesolr_attachments][subdir] = "contrib"
projects[apachesolr_attachments][version] = "1.3"
projects[apachesolr_attachments][patch][] = patches/apachesolr_attachments-empty_parent_entity_id.patch
projects[apachesolr_attachments][patch][] = patches/apachesolr_attachments-bypass_deadlocks-1854088-9.patch

projects[apachesolr_multilingual][subdir] = "contrib"
projects[apachesolr_multilingual][version] = "1.2"

projects[apachesolr_multisitesearch][subdir] = "contrib"
projects[apachesolr_multisitesearch][version] = "1.1"

projects[autosave][subdir] = "contrib"
projects[autosave][version] = "2.2"

projects[bean][subdir] = "contrib"
projects[bean][version] = 1.7

projects[better_exposed_filters][subdir] = "contrib"
projects[better_exposed_filters][version] = "3.0-beta3"

projects[better_formats][subdir] = "contrib"
projects[better_formats][version] = "1.0-beta1"
projects[better_formats][patch][] = patches/better_format-strict-warning-1717470-11.patch

projects[bootstrap_gallery][subdir] = "contrib"
projects[bootstrap_gallery][version] = "3.0"

projects[captcha][subdir] = "contrib"
projects[captcha][version] = "1.2"

projects[chosen][subdir] = "contrib"
projects[chosen][version] = 2.0-beta4

projects[chr][subdir] = "contrib"
projects[chr][version] = "1.6"
projects[chr][patch][] = patches/chr-deprecated_call-5588.patch
projects[chr][patch][] = patches/chr-patches.patch
projects[chr][patch][] = patches/chr-1.6-patch-rewrite-header-host-without-standard-port-number.patch

projects[ckeditor_link][subdir] = "contrib"
projects[ckeditor_link][version] = "2.3"

projects[ckeditor_lite][subdir] = contrib
projects[ckeditor_lite][version] = 1.0-rc1

projects[coffee][subdir] = "contrib"
projects[coffee][version] = 2.2

projects[collapse_text][subdir] = "contrib"
projects[collapse_text][version] = "2.4"

projects[colorbox][subdir] = "contrib"
projects[colorbox][version] = "2.8"

projects[colors][subdir] = "contrib"
projects[colors][version] = "1.0-beta2"

projects[context][subdir] = "contrib"
projects[context][version] = "3.6"
projects[context][patch][] = patches/context-slow_menu_items-873936-20.patch

projects[context_entity_field][subdir] = "contrib"
projects[context_entity_field][version] = "1.1"
projects[context_entity_field][patch][] = patches/add-entity-references-1847038.patch

projects[css_injector][subdir] = "contrib"
projects[css_injector][version] = "1.10"
projects[css_injector][patch][] = patches/css_injector-add_upload_file-2506775-10.patch

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.7"

projects[customerror][subdir] = "contrib"
projects[customerror][version] = "1.4"

projects[date][subdir] = "contrib"
projects[date][version] = "2.8"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[ds][subdir] = "contrib"
projects[ds][version] = "2.7"

projects[easy_breadcrumb][subdir] = "contrib"
projects[easy_breadcrumb][version] = "2.12"

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

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"

projects[entityreference_prepopulate][subdir] = "contrib"
projects[entityreference_prepopulate][version] = "1.5"
projects[entityreference_prepopulate][patch][] = patches/entityreference_prepopulate-ajax-prepopulation-1958800-1.5.patch

projects[eu-cookie-compliance][subdir] = "contrib"
projects[eu-cookie-compliance][version] = "1.12"
projects[eu-cookie-compliance][patch][] = patches/eu_cookie_compliance-unified_cookie-3449.patch

projects[extlink][subdir] = "contrib"
projects[extlink][version] = "1.18"

projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.5"

projects[fblikebutton][subdir] = "contrib"
projects[fblikebutton][version] = "2.3"

projects[features][subdir] = "contrib"
projects[features][version] = "2.3"
projects[features][patch][] = patches/features-var-export-object-1437264-12.patch

projects[feeds][subdir] = "contrib"
projects[feeds][version] = "2.0-alpha8"

projects[feeds_tamper][subdir] = "contrib"
projects[feeds_tamper][version] = "1.0"

projects[feeds_xpathparser][subdir] = "contrib"
projects[feeds_xpathparser][version] = "1.0-beta4"
projects[feeds_xpathparser][patch][] = patches/feeds_xpathparser-undefined_index_unique-1998194-2.patch

projects[field_collection][subdir] = "contrib"
projects[field_collection][version] = "1.0-beta7"
projects[field_collection][patch][] = patches/field_collection-check-before-adding-index-2141781-27.patch

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.4"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-beta1"

projects[filefield_sources][subdir] = "contrib"
projects[filefield_sources][version] = "1.9"

projects[filefield_sources_plupload][subdir] = "contrib"
projects[filefield_sources_plupload][version] = "1.1"

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.5"

projects[flexslider][subdir] = "contrib"
projects[flexslider][version] = "2.0-alpha3"

projects[flexslider_views_slideshow][download][revision] = "0b1f8e7e24c168d1820ccded63c319327d57a97e"
projects[flexslider_views_slideshow][download][type] = "git"
projects[flexslider_views_slideshow][download][url] = "http://git.drupal.org/project/flexslider_views_slideshow.git"
projects[flexslider_views_slideshow][subdir] = "contrib"
projects[fpa][subdir] = "contrib"
projects[fpa][version] = "2.6"

projects[freepager][download][revision] = "698effdfaf7573426ce24acf0ec622bfbf75fc73"
projects[freepager][download][type] = "git"
projects[freepager][download][url] = "http://git.drupal.org/project/freepager.git"
projects[freepager][subdir] = "contrib"

projects[fullcalendar][subdir] = "contrib"
projects[fullcalendar][version] = "2.0"
projects[fullcalendar][patch][] = patches/fullcalendar-ajax_date_format-2185449-11.patch
projects[fullcalendar][patch][] = patches/fullcalendar-views_dom_id_check-1803770-4.patch

projects[hidden_captcha][subdir] = "contrib"
projects[hidden_captcha][version] = "1.0"

projects[i18n][subdir] = "contrib"
projects[i18n][version] = "1.13"
projects[i18n][patch][] = patches/i18n-hide_language_field-3996.patch

projects[i18nviews][download][revision] = "26bd52c4664b0fec8155273f0c0f3ab8a5a2ef66"
projects[i18nviews][download][type] = "git"
projects[i18nviews][download][url] = "http://git.drupal.org/project/i18nviews.git"
projects[i18nviews][subdir] = "contrib"

projects[inline_entity_form][subdir] = "contrib"
projects[inline_entity_form][version] = 1.5

projects[job_scheduler][subdir] = "contrib"
projects[job_scheduler][version] = "2.0-alpha3"

projects[jplayer][subdir] = "contrib"
projects[jplayer][version] = "2.0-beta1"

projects[jqmulti][subdir] = "contrib"
projects[jqmulti][version] = "1.0"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.6"

projects[js_injector][subdir] = "contrib"
projects[js_injector][version] = "2.1"

projects[l10n_update][subdir] = "contrib"
projects[l10n_update][version] = "1.1"

projects[language_cookie][subdir] = "contrib"
projects[language_cookie][version] = "1.6"

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.2"

projects[link][subdir] = "contrib"
projects[link][version] = "1.2"

projects[linkchecker][subdir] = "contrib"
projects[linkchecker][version] = "1.2"
projects[linkchecker][patch][] = patches/linkchecker-001-bean-integration-2127731-0.patch
projects[linkchecker][patch][] = patches/linkchecker-003-linkchecker_max_redirects-3576.patch

projects[mail_edit][subdir] = "contrib"
projects[mail_edit][version] = "1.0"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = "2.34"

projects[maxlength][subdir] = "contrib"
projects[maxlength][version] = "3.0-beta1"
projects[maxlength][patch][] = patches/maxlength-indefined_index-2235.patch
projects[maxlength][patch][] = patches/maxlength-prevent_undefined_index_error-1416608-3.patch

projects[media][subdir] = contrib
projects[media][download][branch] = 7.x-2.x
projects[media][download][revision] = 64c5102
projects[media][download][type] = git
projects[media][patch][] = patches/media-wysiwyg-override-white-list-MULTISITE-2607.patch

; Issue #2401811: With Media WYSIWYG enabled - "Contextual links" are shown for anonymous users.
; https://www.drupal.org/node/2401811
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-3650
projects[media][patch][] = http://www.drupal.org/files/issues/file_entity-remove-contextual-links-2401811-11.patch

projects[media_crop][subdir] = "contrib"
projects[media_crop][version] = "1.4"

projects[media_dailymotion][subdir] = "contrib"
projects[media_dailymotion][version] = "1.0"
projects[media_dailymotion][patch][] = patches/media_dailymotion-handle_protocol-4103.patch

projects[media_flickr][subdir] = "contrib"
projects[media_flickr][version] = "1.0-alpha4"
projects[media_flickr][patch][] = patches/media_flickr-Media_v2_removed_XML_APIs-2089665-1.patch
projects[media_flickr][patch][] = patches/media_flickr-fix_photoset_url_issue-2183.patch
projects[media_flickr][patch][] = patches/media_flickr-missing_thumbnail-2494.patch
projects[media_flickr][patch][] = patches/media_flickr-undefined_index-2183.patch

projects[media_node][subdir] = "contrib"
projects[media_node][version] = "1.0-rc2"
projects[media_node][patch][] = patches/media_node-incorrect_permission_check-4273.patch

projects[media_vimeo][subdir] = "contrib"
projects[media_vimeo][version] = "2.0"

projects[media_youtube][subdir] = "contrib"
projects[media_youtube][version] = "2.0-rc5"

projects[menu_attributes][subdir] = "contrib"
projects[menu_attributes][version] = "1.0-rc2"
projects[menu_attributes][patch][] = patches/menu_attributes-add_icon_for_menu_item-2327.patch
projects[menu_attributes][patch][] = patches/menu_attributes-option_to_disable_css_class-2988.patch

projects[menu_block][subdir] = "contrib"
projects[menu_block][version] = "2.4"
projects[menu_block][patch][] = patches/menu_block-jqueryUI_issue-5211.patch

projects[menu_token][subdir] = "contrib"
projects[menu_token][version] = "1.0-beta5"
projects[menu_token][patch][] = patches/menu_token-link_uuid_menu_items_can_not_be_edited-2005556-2.patch

projects[message][subdir] = "contrib"
projects[message][version] = "1.7"

projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.6"

projects[migrate][subdir] = "contrib"
projects[migrate][version] = "2.7"

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.0-beta3"

projects[node_export][subdir] = "contrib"
projects[node_export][version] = "3.0"

projects[og][download][branch] = 7.x-2.x
projects[og][download][revision] = fba6dda
projects[og][download][type] = git
projects[og][subdir] = "contrib"

projects[og_linkchecker][download][branch] = 7.x-1.x
projects[og_linkchecker][download][revision] = 7257d0e
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][subdir] = "contrib"
projects[og_linkchecker][patch][] = patches/og_linkchecker-001-og_linkchecker-og-2-x-compatibility-2214661-2.patch

projects[om_maximenu][subdir] = "contrib"
projects[om_maximenu][version] = "1.44"

projects[password_policy][subdir] = "contrib"
projects[password_policy][version] = "2.0-alpha4"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"
projects[pathauto][patch][] = patches/pathauto-admin_patterns-1267966-140.patch
projects[pathauto][patch][] = patches/pathauto-automatic_url_alias_issue-1847444-10.patch

projects[pathauto_persist][subdir] = "contrib"
projects[pathauto_persist][version] = "1.3"

projects[piwik][subdir] = "contrib"
projects[piwik][version] = "2.7"

projects[plupload][subdir] = "contrib"
projects[plupload][version] = "1.3"

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
projects[realname][version] = "1.1"

projects[registration][subdir] = "contrib"
projects[registration][version] = "1.3"

projects[registry_autoload][subdir] = "contrib"
projects[registry_autoload][version] = 1.2

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.8"

projects[scheduler][subdir] = "contrib"
projects[scheduler][version] = 1.2

projects[scheduler_workbench][subdir] = "contrib"
projects[scheduler_workbench][version] = 1.2

projects[select_or_other][subdir] = "contrib"
projects[select_or_other][version] = 2.22

projects[simplenews][subdir] = "contrib"
projects[simplenews][version] = "1.1"
projects[simplenews][patch][] = patches/simplenews-fieldset-weight-4330.patch

projects[site_map][subdir] = "contrib"
projects[site_map][version] = "1.0"

projects[smart_trim][subdir] = "contrib"
projects[smart_trim][version] = 1.4

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
projects[tmgmt][download][revision] = c76ced1
projects[tmgmt][download][type] = git
projects[tmgmt][subdir] = contrib

projects[token][subdir] = "contrib"
projects[token][version] = "1.6"

projects[token_filter][subdir] = "contrib"
projects[token_filter][version] = 1.1

projects[translation_overview][subdir] = "contrib"
projects[translation_overview][version] = "2.0-beta1"

projects[translation_table][subdir] = "contrib"
projects[translation_table][version] = "1.0-beta1"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.2"

projects[tweetbutton][subdir] = "contrib"
projects[tweetbutton][version] = "2.0-beta1"

projects[user_dashboard][subdir] = "contrib"
projects[user_dashboard][version] = "1.3"

projects[user_field_privacy][subdir] = "contrib"
projects[user_field_privacy][version] = "1.2"

projects[uuid][subdir] = "contrib"
projects[uuid][version] = "1.0-alpha5"

projects[variable][subdir] = "contrib"
projects[variable][version] = "2.5"

projects[video][subdir] = "contrib"
projects[video][version] = "2.11"
projects[video][patch][] = patches/video-revert_issue-1891012-0.patch
projects[video][patch][] = patches/video-security-883.patch

projects[views][subdir] = "contrib"
projects[views][version] = "3.11"
projects[views][patch][] = patches/views-exposed-ajax-not-working-2425099-52.patch
projects[views][patch][] = patches/views-exposed_groupfilter_views-1818176-11.patch
projects[views][patch][] = patches/views-includes_handlers-1752062-6.patch
projects[views][patch][] = patches/views-localization-bug-1685144-9.patch

projects[views_ajax_history][subdir] = "contrib"
projects[views_ajax_history][version] = "1.0"

projects[views_bootstrap][subdir] = "contrib"
projects[views_bootstrap][version] = "3.1"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.3"

projects[views_data_export][subdir] = "contrib"
projects[views_data_export][version] = "3.0-beta7"

projects[views_datasource][download][revision] = "6e9b6b980fc2826b09391ae1c2ec0c5a85c6c24a"
projects[views_datasource][download][type] = "git"
projects[views_datasource][download][url] = "http://git.drupal.org/project/views_datasource.git"
projects[views_datasource][subdir] = "contrib"

projects[views_litepager][subdir] = "contrib"
projects[views_litepager][version] = "3.0"

projects[views_slideshow][subdir] = "contrib"
projects[views_slideshow][version] = "3.0"

projects[views_slideshow_slider][subdir] = "contrib"
projects[views_slideshow_slider][version] = "3.0"

projects[votingapi][subdir] = "contrib"
projects[votingapi][version] = "2.11"

projects[webform][subdir] = "contrib"
projects[webform][version] = "4.0"
projects[webform][patch][] = patches/webform-use_ecas_link-1235.patch

projects[webform_rules][subdir] = "contrib"
projects[webform_rules][version] = "1.6"

projects[workbench][subdir] = "contrib"
projects[workbench][version] = "1.2"

projects[workbench_access][subdir] = "contrib"
projects[workbench_access][version] = "1.2"
projects[workbench_access][patch][] = patches/workbench_access-fix_php_issues-4517.patch

projects[workbench_email][subdir] = "contrib"
projects[workbench_email][version] = "3.3"

projects[workbench_moderation][subdir] = "contrib"
projects[workbench_moderation][version] = "1.4"
projects[workbench_moderation][patch][] = patches/workbench_moderation-001-wm-field_translations-2285931-1.patch
projects[workbench_moderation][patch][] = patches/workbench_moderation-002-attachment_fix-1084436-47.patch
projects[workbench_moderation][patch][] = patches/workbench_moderation-005-workbench_moderation.rules-5054.patch
projects[workbench_moderation][patch][] = https://www.drupal.org/files/issues/support_for_migrate-1445824-35.patch

projects[workbench_og][subdir] = "contrib"
projects[workbench_og][version] = "2.0-beta1"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.2"
projects[wysiwyg][patch][] = patches/wysiwyg-ckeditor4-bug-version-1799.patch
projects[wysiwyg][patch][] = patches/wysiwyg-ckeditor_ie_fix-1914904-5.patch
projects[wysiwyg][patch][] = patches/wysiwyg-local_css_file_paths-1793704-14.patch

projects[xml_field][subdir] = "contrib"
projects[xml_field][version] = "1.5"

projects[xmlsitemap][subdir] = "contrib"
projects[xmlsitemap][version] = "2.0"

; =========
; Libraries
; =========

; chosen 1.1.0
libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries

; ckeditor 4.3.2
libraries[ckeditor][download][type]= "file"
libraries[ckeditor][download][request_type]= "get"
libraries[ckeditor][download][file_type] = "zip"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.4.0/ckeditor_4.4.0_full.zip"
libraries[ckeditor][download][sha1] = "4673a4c20e484f0d712ca85fddec6a991cef61d9"
libraries[ckeditor][directory_name] = "ckeditor"

; ckeditor_lite library. Buttons are added in nexteuropa_core_install().
libraries[ckeditor_lite][download][type]= "file"
libraries[ckeditor_lite][download][request_type]= "get"
libraries[ckeditor_lite][download][file_type] = "zip"
libraries[ckeditor_lite][download][url] = http://download.ckeditor.com/lite/releases/lite_1.1.30.zip
libraries[ckeditor_lite][subdir] = ckeditor/plugins
libraries[ckeditor_lite][directory_name] = "lite"

; cycle 3.0.2 (commit d6557ca)
libraries[cycle][download][type] = "git"
libraries[cycle][download][url] = "https://github.com/malsup/cycle.git"
libraries[cycle][download][revision] = f314eff3a0b77902fe2afe7640d7ec0728ff3dc6
libraries[cycle][directory_name] = "jquery.cycle"
libraries[cycle][download][sha1] = "f71640db8972ed6d249f57ea8cce29c389c4a84f"
libraries[cycle][destination] = "libraries"

; history.js v1.8b2
libraries[history][download][type] = "git"
libraries[history][download][url] = "https://github.com/browserstate/history.js/"
libraries[history][directory_name] = "history.js"
libraries[history][destination] = "libraries"
libraries[history][download][tag] = "1.8.0b2"

; mpdf 5.7
libraries[mpdf][download][type]= "file"
libraries[mpdf][download][request_type]= "get"
libraries[mpdf][download][file_type] = "zip"
libraries[mpdf][download][url] = "http://mpdf1.com/repos/MPDF57.zip"
libraries[mpdf][destination] = "libraries"

; tcpdf 6.0.013
libraries[tcpdf][download][type] = "git"
libraries[tcpdf][download][url] = "http://git.code.sf.net/p/tcpdf/code"
libraries[tcpdf][download][tag] = "6.0.053"
libraries[tcpdf][directory_name] = "tcpdf"
libraries[tcpdf][destination] = "libraries"


; ======
; Themes
; ======

projects[bootstrap][type] = theme
projects[bootstrap][download][type] = get
projects[bootstrap][download][url] = http://ftp.drupal.org/files/projects/bootstrap-7.x-3.0.zip
