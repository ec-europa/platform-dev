
api = 2
core = 7.x

;
; Contributed modules =====================================================================
;
projects[og][subdir] = contrib
projects[og][version] = 2.7

projects[linkchecker][subdir] = contrib
projects[linkchecker][version] = 1.2

projects[workbench][subdir] = contrib
projects[workbench][version] = 1.2

; Dev branch is necessary in order to solve https://www.drupal.org/node/1911782
projects[workbench_moderation][subdir] = contrib
projects[workbench_moderation][version] = 1.x-dev

projects[workbench_og][subdir] = contrib
projects[workbench_og][version] = 2.x-dev

projects[scheduler][subdir] = contrib
projects[scheduler][version] = 1.2 

projects[scheduler_workbench][subdir] = contrib
projects[scheduler_workbench][version] = 1.2

projects[rules][subdir] = contrib
projects[rules][version] = 2.7

projects[og_linkchecker][subdir] = contrib
projects[og_linkchecker][version] = 1.0-rc1

projects[og_linkchecker][type] = module
projects[og_linkchecker][subdir] = contrib
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][download][branch] = 7.x-1.x

;
; Custom modules =====================================================================
;
projects[tmgmt_og][type] = module
projects[tmgmt_og][subdir] = custom
projects[tmgmt_og][download][type] = svn
projects[tmgmt_og][download][url] = https://webgate.ec.europa.eu/CITnet/svn/NEXTEUROPA/trunk/profiles/nexteuropa/modules/features/tmgmt_og

;
; Patches =====================================================================
;

; As per https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-204
; https://www.drupal.org/node/2285931#comment-8878187
projects[workbench_moderation][patch][2285931] = https://www.drupal.org/files/issues/wm-field_translations-2285931-1.patch	

; As per https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-53
; https://www.drupal.org/node/2127731#comment-8144377
projects[linkchecker][patch][2127731] = https://www.drupal.org/files/issues/bean-integration-2127731-0.patch

; As per https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-53
; https://www.drupal.org/node/2214661#comment-9113133
projects[og_linkchecker][patch][2214661] = https://www.drupal.org/files/issues/og_linkchecker-og-2-x-compatibility-2214661-2.patch

