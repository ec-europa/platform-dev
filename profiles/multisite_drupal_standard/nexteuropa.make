
; ========================================================================================
;
; This make file is a hard-merge from the distributed make files contained in each 
; NextEuropa feature. It is meant to be a temporary solution, to be included in the 
; main Multisite building script. Hopefully we will not need it soon enough.
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
projects[bean][subdir] = "contrib"
projects[bean][version] = 1.7

projects[chosen][subdir] = "contrib"
projects[chosen][version] = 2.0-beta4

projects[coffee][subdir] = "contrib"
projects[coffee][version] = 2.2

projects[ds][subdir] = "contrib"
projects[ds][version] = 2.6

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = 1.2

projects[inline_entity_form][subdir] = "contrib"
projects[inline_entity_form][version] = 1.5

projects[registry_autoload][subdir] = "contrib"
projects[registry_autoload][version] = 1.2

projects[smart_trim][subdir] = "contrib"
projects[smart_trim][version] = 1.4

projects[taxonomy_revision][subdir] = "contrib"
projects[taxonomy_revision][version] = 1.2

projects[token_filter][subdir] = "contrib"
projects[token_filter][version] = 1.1

projects[og][subdir] = "contrib"
projects[og][download][type] = git
projects[og][download][revision] = fba6dda
projects[og][download][branch] = 7.x-2.x 

projects[workbench_og][subdir] = "contrib"
projects[workbench_og][download][type] = git
projects[workbench_og][download][revision] = a12d332
projects[workbench_og][download][branch] = 7.x-2.x 

projects[scheduler][subdir] = "contrib"
projects[scheduler][version] = 1.2 

projects[scheduler_workbench][subdir] = "contrib"
projects[scheduler_workbench][version] = 1.2

projects[og_linkchecker][subdir] = "contrib"
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][download][revision] = 7257d0e
projects[og_linkchecker][download][branch] = 7.x-1.x 

projects[entity_translation][subdir] = "contrib"
projects[entity_translation][download][type] = git
projects[entity_translation][download][revision] = 221e302
projects[entity_translation][download][branch] = 7.x-1.x 

projects[title][subdir] = "contrib"
projects[title][download][type] = git
projects[title][download][revision] = 1f89073
projects[title][download][branch] = 7.x-1.x 

projects[variable][subdir] = "contrib"
projects[variable][version] = 2.5

projects[views_ajax_history][subdir] = "contrib"
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
