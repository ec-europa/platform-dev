
api = 2
core = 7.x

;
; Contributed modules =====================================================================
;
projects[bean][subdir] = contrib
projects[bean][version] = 1.7

projects[chosen][subdir] = contrib
projects[chosen][version] = 2.0-beta4

projects[coffee][subdir] = contrib
projects[coffee][version] = 2.2

projects[ds][subdir] = contrib
projects[ds][version] = 2.6

projects[entitycache][subdir] = contrib
projects[entitycache][version] = 1.2

projects[smart_trim][subdir] = contrib
projects[smart_trim][version] = 1.4

projects[registry_autoload][subdir] = contributed
projects[registry_autoload][version] = 1.2

projects[taxonomy_revision][subdir] = contrib
projects[taxonomy_revision][version] = 1.2

projects[ckeditor_lite][subdir] = contrib
projects[ckeditor_lite][version] = 1.0-rc1

;
; Custom modules ===============================================================
;
projects[tmgmt_og][type] = module
projects[tmgmt_og][subdir] = custom
projects[tmgmt_og][download][type] = svn
projects[tmgmt_og][download][url] = https://webgate.ec.europa.eu/CITnet/svn/NEXTEUROPA/trunk/profiles/nexteuropa/modules/custom/tmgmt_og

projects[tmgmt_workbench][type] = module
projects[tmgmt_workbench][subdir] = custom
projects[tmgmt_workbench][download][type] = svn
projects[tmgmt_workbench][download][url] = https://webgate.ec.europa.eu/CITnet/svn/NEXTEUROPA/trunk/profiles/nexteuropa/modules/custom/tmgmt_workbench


;
; Patches =====================================================================
;
; Add --info-style option to drush features-components (fc)
; https://www.drupal.org/node/1536218
; projects[features][patch][1536218] = https://www.drupal.org/files/features-component-list-as-info.patch

;
; Libraries =====================================================================
;
libraries[chosen][download][type] = "get"
libraries[chosen][download][url] = "https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip"
libraries[chosen][directory_name] = "chosen"
libraries[chosen][destination] = "libraries"

libraries[ckeditor_lite][download][type]= svn
libraries[ckeditor_lite][download][url] = https://github.com/loopindex/ckeditor-track-changes/trunk/src/lite
libraries[ckeditor_lite][download][sha1] = "2325e728878c9840c7b2fa59b30c4fc682f7c118"
libraries[ckeditor_lite][subdir] = ckeditor/plugins
libraries[ckeditor_lite][directory_name] = "lite"
