<?php
// replace all administror role by editor role

// get roles id
$contributor_rid = get_rid('contributor');
$editor_rid = get_rid('editor');
$administrator_rid = get_rid('administrator');

// get list of all users uid
$list_uids = db_select('users', 'u')->fields('u', array('uid'));
$result_uids = $list_uids->execute();  

// affect editor role to users with administrator role
$maintenance_roles = array($editor_rid => 'editor');

while ($record = $result_uids->fetchAssoc()) {
  if ($record['uid'] > 1) {
    $user = user_load($record['uid']);  
    $user_role = $user->roles;
    // check if the user has administrator role
    if (isset($user_role[$administrator_rid])) {
      unset($user_role[$administrator_rid]);
      $user_role += $maintenance_roles;
      user_save($user, array('roles' => $user_role));
    }
  }
}
