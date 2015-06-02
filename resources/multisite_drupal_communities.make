includes[] = "multisite_drupal_standard.make"

projects[og-delete][download][revision] = "c759e354d89b7ec280836047569acc75843eed38"
projects[og-delete][download][type] = "git"
projects[og-delete][download][url] = "http://git.drupal.org/project/OG-Delete.git"
projects[og-delete][subdir] = "contrib"
projects[og-delete][patch][] = patches/og_delete-remove_community-4481-2.patch
projects[og-delete][patch][] = patches/og_delete-warning_fix-issue-3629.patch

projects[og][patch][] = patches/og-og_field_access-bypass_field_access-5159.patch

projects[og_linkchecker][download][branch] = 7.x-1.x 
projects[og_linkchecker][download][revision] = 7257d0e
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][subdir] = contrib

projects[workbench_og][subdir] = "contrib"
projects[workbench_og][version] = "2.0-beta1"
