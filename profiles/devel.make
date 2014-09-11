; Drush Make API version
api = 2

; Drupal core version
core = 7.x

; Dependencies

; enable this for development
; install it in a libraries directory ("sites/all/libraries") not "enabled" it as a module.
projects[grammar_parser][type] = "library"
projects[grammar_parser][download][type] = "git"
projects[grammar_parser][download][url] = "https://drupal.org/project/grammar_parser"
projects[grammar_parser][download][branch] = "7.x-1.x"
projects[grammar_parser][download][tag] = "1.2"

projects[libraries][subdir] = "contributed"
projects[libraries][version] = 2.0

projects[devel][subdir] = "contributed"
projects[devel][version] = "1.5"

;projects[devel_themer][subdir] = "contributed"
;projects[devel_themer][version] = "1.x-dev"

projects[coder][subdir] = "contributed"
projects[coder][version] = "2.2"

projects[mail_logger][subdir] = "contributed"
projects[mail_logger][version] = "1.x-dev"

projects[simplehtmldom][subdir] = "contributed"
projects[simplehtmldom][version] = "1.12"

projects[drupalforfirebug][subdir] = "contributed"
projects[drupalforfirebug][version] = "1.4"

projects[coffee][subdir] = "contributed"
projects[coffee][version] = "2.2"

projects[module_filter][subdir] = "contributed"
projects[module_filter][version] = "2.0-alpha2"

projects[devel_debug_log][subdir] = "contributed"
projects[devel_debug_log][version] = "1.2"

projects[search_krumo][subdir] = "contributed"
projects[search_krumo][version] = "1.5"

projects[realistic_dummy_content][subdir] = "contributed"
projects[realistic_dummy_content][version] = "1.x-dev"

