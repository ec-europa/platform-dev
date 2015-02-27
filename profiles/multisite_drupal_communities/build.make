includes[multisite] = "../multisite.make"

projects[og][subdir] = "contributed"
projects[og][version] = "2.6"

;projects[og_menu][subdir] = "contributed"
;projects[og_menu][version] = "3.0-rc2"

projects[workbench_og][subdir] = "contributed"
projects[workbench_og][version] = "2.0-beta1"

projects[og-delete][subdir] = "contributed"
;projects[og_delete][version] = "1.0-dev"
projects[og-delete][download][type] = "git"
projects[og-delete][download][url] = "http://git.drupal.org/project/OG-Delete.git"
projects[og-delete][download][revision] = "c759e354d89b7ec280836047569acc75843eed38"

projects[og_linkchecker][subdir] = contributed
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][download][revision] = 7257d0e
projects[og_linkchecker][download][branch] = 7.x-1.x 

includes[] = "../multisite_drupal_core/patches.make"
includes[] = "patches.make"
