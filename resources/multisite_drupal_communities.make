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
