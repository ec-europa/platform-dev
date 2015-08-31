
; ========================================================================================
;
; This make file is a hard-merge from the distributed make files contained in each 
; NextEuropa feature. It is meant to be a temporary solution, to be included in the 
; main Multisite building script. Hopefully we will not need it soon enough.
; One main change here is renaming contrib into contributed in order to
; comply with Multisite conventions.
;
; This file is currently included by multisite_drupal_standard/build.make
; 
; For more information please check: https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5054
;
; ========================================================================================

api = 2
core = 7.x

;
; Contributed modules =====================================================================
;
projects[bean][subdir] = contributed
projects[bean][version] = 1.7

projects[chosen][subdir] = contributed
projects[chosen][version] = 2.0-beta4

projects[coffee][subdir] = contributed
projects[coffee][version] = 2.2

projects[ds][subdir] = contributed
projects[ds][version] = 2.6

projects[entitycache][subdir] = contributed
projects[entitycache][version] = 1.2

projects[inline_entity_form][subdir] = contributed
projects[inline_entity_form][version] = 1.5

projects[registry_autoload][subdir] = contributed
projects[registry_autoload][version] = 1.2

projects[smart_trim][subdir] = contributed
projects[smart_trim][version] = 1.5

projects[og][subdir] = contributed
projects[og][download][type] = git
projects[og][download][revision] = fba6dda
projects[og][download][branch] = 7.x-2.x 

projects[workbench_og][subdir] = contributed
projects[workbench_og][download][type] = git
projects[workbench_og][download][revision] = a12d332
projects[workbench_og][download][branch] = 7.x-2.x 

projects[scheduler][subdir] = contributed
projects[scheduler][version] = 1.3

projects[scheduler_workbench][subdir] = contributed
projects[scheduler_workbench][version] = 1.2

projects[og_linkchecker][subdir] = contributed
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][download][revision] = 7257d0e
projects[og_linkchecker][download][branch] = 7.x-1.x 

projects[entity_translation][subdir] = contributed
projects[entity_translation][download][type] = git
projects[entity_translation][download][revision] = 221e302
projects[entity_translation][download][branch] = 7.x-1.x 

projects[title][subdir] = contributed
projects[title][download][type] = git
projects[title][download][revision] = 1f89073
projects[title][download][branch] = 7.x-1.x 

projects[variable][subdir] = contributed
projects[variable][version] = 2.5

projects[views_ajax_history][subdir] = "contributed"
projects[views_ajax_history][version] = "1.0"

;
; Libraries =====================================================================
;
libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip
libraries[chosen][directory_name] = chosen
libraries[chosen][destination] = libraries

;history.js v1.8b2
libraries[history][download][type] = "git"
libraries[history][download][url] = "https://github.com/browserstate/history.js/"
libraries[history][directory_name] = "history.js"
libraries[history][destination] = "libraries"
libraries[history][download][tag] = "1.8.0b2"
