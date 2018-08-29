api = 2
core = 7.x

; =========================
; Multisite Drupal Standard
; =========================

includes[] = "multisite_drupal_standard.make"

; ===================
; Contributed modules
; ===================

projects[og-delete][download][revision] = "c759e354d89b7ec280836047569acc75843eed38"
projects[og-delete][download][type] = "git"
projects[og-delete][download][url] = "http://git.drupal.org/project/OG-Delete.git"
projects[og-delete][subdir] = "contrib"
projects[og-delete][patch][] = patches/og_delete-remove_community-4481-2.patch
projects[og-delete][patch][] = patches/og_delete-warning_fix-issue-3629.patch

# Issue #2411041: Group manager always given default default role as og_is_member arguments wrong.
# https://www.drupal.org/node/2411041
# https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-6319
projects[og][patch][] = http://www.drupal.org/files/issues/2411041-og-og_is_member-2.patch

projects[og_linkchecker][download][branch] = 7.x-2.x
projects[og_linkchecker][download][revision] = 976f7ef
projects[og_linkchecker][download][type] = git
projects[og_linkchecker][subdir] = "contrib"

; ==============
; Custom modules
; ==============

projects[nexteuropa_poetry][subdir] = "contrib"
projects[nexteuropa_poetry][type] = module
projects[nexteuropa_poetry][download][type] = git
projects[nexteuropa_poetry][download][url] = https://github.com/ec-europa/nexteuropa_poetry.git
projects[nexteuropa_poetry][download][branch] = master
