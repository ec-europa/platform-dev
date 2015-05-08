
api = 2
core = 7.x

;
; Contributed modules =====================================================================
;
projects[entity_translation][subdir] = contrib
projects[entity_translation][version] = 1.x-dev

projects[title][subdir] = contrib
projects[title][version] = 1.x-dev

projects[variable][subdir] = contrib
projects[variable][version] = 2.5

;
; Patches =====================================================================
;
; As per https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-204

; https://www.drupal.org/node/1707156#comment-8914059
projects[entity_translation][patch][1707156] = https://www.drupal.org/files/issues/et-forward_revisions-1707156-23.patch

;
; Custom modules =====================================================================
;
; projects[tmgmt_workbench][type] = module
; projects[tmgmt_workbench][subdir] = custom
; projects[tmgmt_workbench][download][type] = svn
; projects[tmgmt_workbench][download][url] = https://webgate.ec.europa.eu/CITnet/svn/NEXTEUROPA/trunk/profiles/nexteuropa/modules/custom/tmgmt_workbench

