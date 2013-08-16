; Drush Make API version
api = 2

; Drupal core version
core = 7.x

; Dependencies

; enable this for development
projects[grammar_parser][type] = library
projects[grammar_parser][download][type] = git
projects[grammar_parser][download][url] = http://git.drupal.org/project/grammar_parser.git
projects[grammar_parser][download][branch] = 7.x-1.x
projects[grammar_parser][download][tag] = 1.2

projects[libraries][subdir] = "contributed"
projects[libraries][version] = 2.0

projects[devel][subdir] = "contributed"
projects[devel][version] = "1.3"

projects[devel_themer][subdir] = "contributed"
projects[devel_themer][version] = "1.x-dev"

projects[coder][subdir] = "contributed"
projects[coder][version] = "2.0-beta2"

projects[mail_logger][subdir] = "contributed"
projects[mail_logger][version] = "1.x-dev"

projects[simplehtmldom][subdir] = "contributed"
projects[simplehtmldom][version] = "1.12"

projects[drupalforfirebug][subdir] = "contributed"
projects[drupalforfirebug][version] = "1.4"

