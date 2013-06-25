<?php

$permissions = array(
  'access administration pages',
  'access site in maintenance mode',
  'access site reports',
  'access toolbar',
  'administer actions',
  'administer blocks',  
  'administer CAPTCHA settings',
  'administer ckeditor link',
  'administer comments',
  'administer contact forms',
  'administer content types',
  'administer contexts',
  'administer custom breadcrumbs',
  'administer facets',
  'administer feature sets',
  'administer fieldgroups',
  'administer file types',
  'administer files',
  'administer filters',
  'administer image styles',
  'administer languages',
  'administer linkchecker',
  'administer menu',
  'administer nodes',
  'administer password policy',
  'administer pathauto',
  'administer permissions',
  'administer print',
  'administer quicktabs',
  'administer realname',
  'administer rules',
  'administer search',
  'administer site configuration',
  'administer taxonomy',
  'administer themes',
  'administer tmgmt',
  'administer url aliases',
  'administer users',
  'administer uuid',
  'administer video presets',
  'administer views',
  'administer voting api',
  'administer workbench',
  'administer workbench moderation',
  'cancel account',
  'configure sweaver',
  'translate admin strings',
);

$administrator_rid = get_rid('administrator');
$action = drush_get_option('action');

switch($action) {
  case 'revoke':
    user_role_revoke_permissions($administrator_rid, $permissions);
    print "administators permissions revoked !\n";
    break;
  case 'grant':
    user_role_grant_permissions($administrator_rid, $permissions);
    print "administators permissions granted !\n";
    break;
}



