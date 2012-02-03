<?php
/*
* hook_workbench_moderation_transition
*/
function communities_workbench_moderation_transition($node, $previous_state, $new_state) {
  global $base_url;

  $transition_made = $previous_state."__".$new_state;  
  
  // transistions settings
  $transitions_settings = array(
    "draft__needs_review" => array(
	  "message" => get_mail_template('draft__needs_review'),
	  "subject" => "creation of community request",
	),
	"needs_review__draft" => array(
	  "message" => get_mail_template('needs_review__draft'),
	  "subject" => "community refused",	
	),
  );  
  
  if(isset($transitions_settings[$transition_made])) { // if there are settings for the transition => process send mail  
    // get all administrators
    $query = db_select('users', 'u');
    $query->join('users_roles', 'ur', 'u.uid = ur.uid');
    $query->join('role', 'r', 'r.rid = ur.rid');
    $query->condition('r.name', "administrator",'=');
    $query->fields('u', array('uid'));
    $result = $query->execute();

    while($record = $result->fetchAssoc()) {
      $admin_users[] = $record['uid'];
    }
  
    $params = array(
	  "to_creator" => $node->uid,
      "to_admin" => $admin_users,
      "nid" => $node->nid,  
    );
    $params += $transitions_settings[$transition_made];
	
    _send_mail($params); // send mail
  }
   
}

/*
* send mail function
*/
function _send_mail($params) {
  $module = 'communities';
  $key = 'workbench_moderation_workflow';

  $from = variable_get('site_mail', 'admin@example.com');

  $language = language_default();
  $send = TRUE;

  foreach($params['to_admin'] as $uid) {
    $user = user_load($uid);
    $params['admin_uid'] = $uid;
    $result = drupal_mail($module, $key, $user->mail, $language, $params, $from, $send);
  }

  if ($result['result'] == TRUE) {
    drupal_set_message(t('Your message has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
  }

}


/*
* hook_mail
*/
function communities_mail($key, &$message, $params) {
  global $user, $base_url;

  $admin_user = user_load($params['admin_uid']);
  $creator_user = user_load($params['to_creator']);

  $node = node_load($params['nid']);

  if(isset($admin_user->field_firstname['und'][0]['value']))
    $admin_name = $admin_user->field_firstname['und'][0]['value']." ".$admin_user->field_lastname['und'][0]['value'];
  else
    $admin_name = $admin_user->name;
  if(isset($creator_user->field_firstname['und'][0]['value']))
    $creator_name = $creator_user->field_firstname['und'][0]['value']." ".$creator_user->field_lastname['und'][0]['value'];
  else
    $creator_name = $creator_user->name;

  $variables = array(
    '%admin_user' => $admin_name, 
    '%creator_user' => $creator_name,
    '%community_link' => l($node->title, $base_url."/en/node/".$node->nid), 
    '%site_url' => $base_url,
  );

  $message['headers']['Content-Type'] = "text/html; charset=iso-8859-1";
  $message['headers']['Mime-Version'] = "1.0";

  switch ($key) {
    case 'workbench_moderation_workflow':
      $message['subject'] = $params["subject"];
      $message['body'][] = check_plain(strtr($params['message'], $variables));
      break;
  }
}

/*
* provide the template mail
*/
function get_mail_template($key) {
  $output = "";
  switch ($key) {
	case 'draft__needs_review': 
      $output = "Dear %admin_user,<br><p>%creator_user requests a community creation : %community_link<br></p><p><a href=\"%site_url/en/admin/workbench\">Go to administration</a>.</p>";
 	  break;
	case 'needs_review__draft': 
      $output = "Dear %creator_user,<br><p>Your community %community_link has been refused.<br></p>";
	  break;
  }
  return $output;
}