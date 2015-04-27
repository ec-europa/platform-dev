includes[multisite] = "../multisite.make"

projects[og][subdir] = "contrib"
projects[og][version] = "2.6"

projects[workbench_og][subdir] = "contrib"
projects[workbench_og][version] = "2.0-beta1"

projects[og-delete][subdir] = "contrib"
projects[og-delete][download][type] = "git"
projects[og-delete][download][url] = "http://git.drupal.org/project/OG-Delete.git"
projects[og-delete][download][revision] = "c759e354d89b7ec280836047569acc75843eed38"

projects[og_linkchecker][subdir] = contrib
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][download][revision] = 7257d0e
projects[og_linkchecker][download][branch] = 7.x-1.x 

includes[] = "../multisite_drupal_core/patches.make"
includes[] = "patches.make"
