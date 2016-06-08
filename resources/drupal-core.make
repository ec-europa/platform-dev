api = 2
core = 7.x

projects[drupal][type] = "core"
projects[drupal][version] = "7.43"
projects[drupal][download][type] = get
projects[drupal][download][url] = http://ftp.drupal.org/files/projects/drupal-7.43.tar.gz

projects[drupal][patch][] = patches/ajax-js_url_suffix.patch
projects[drupal][patch][] = patches/menu-conflict_with_menu_token-2534.patch
projects[drupal][patch][] = patches/node-node_access_views_relationship-1349080.patch
projects[drupal][patch][] = patches/user-drupal.d7.user-password-reset-logged-in-889772.patch
projects[drupal][patch][] = patches/user-request_password_behaviour-2205.patch
projects[drupal][patch][] = patches/core-locale-prevent-remote-loading.patch

; Move local configuration directives out of the Git repository.
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-3154
projects[drupal][patch][] = patches/default-settings-php-include-local-settings-3154.patch

; Allow management of visibility for pseudo-fields.
; https://www.drupal.org/node/1256368
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-3996
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-n1256368-91.patch

; Allow DRUPAL_MAXIMUM_TEMP_FILE_AGE to be overridden.
; https://www.drupal.org/node/1399846
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-5641
projects[drupal][patch][] = https://www.drupal.org/files/issues/cleanup-files-1399846-291.patch

; A validation error occurs for anonymous users when $form['#token'] == FALSE.
; https://www.drupal.org/node/1617918
; https://webgate.ec.europa.eu/CITnet/jira/browse/MULTISITE-4863
projects[drupal][patch][] = https://www.drupal.org/files/issues/1617918-33-d7-do-not-test.patch

; Make sure drupal_add_js marks files as external when no type is specified and is_external is true:
; https://www.drupal.org/node/2697611
; https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-9874
; external: projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal_add_js_sanitize_external-2697611-4.patch
projects[drupal][patch][] = patches/drupal_add_js_sanitize_external-2697611-4.patch
