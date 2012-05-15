<?php
/**
 * @file
 * cce_basic_config.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function cce_basic_config_content_defaults() {
  $content = array();

  $content['welcome_message'] = (object) array(
    'exported_path' => 'content/welcome-your-site',
    'title' => 'Welcome to your site !',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'page',
    'language' => 'en',
    'created' => '1330594184',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'welcome_message',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Notice:</p>
    <p>You have to login in order to perform any of the action described below &gt;&gt; <a href="user">Login</a></p>
    <p>&nbsp;</p>
    <p>To complete the configuration of your site, here are&nbsp;some additional&nbsp;steps :</p>
    <p>- to access the <strong>Feature set</strong> configuration page which helps you to choose the features you wish to install on your site &gt;&gt; <a href="admin/structure/feature-set"><font color="#3366ff">click here</font></a></p>
    <p><font color="#000000">- to access the <strong>user creation</strong> page in order to add some users and to choose the role you wish to give them &gt;&gt;</font> <a href="admin/people"><font color="#3366ff">click here</font></a></p>
    <p>&nbsp;</p>
    <p>Some information about&nbsp;roles&nbsp;:</p>
    <p>- admin user can do everything on the site, but will mainly be used to approve/refuse user account creation or community creation</p>
    <p>- community manager will act as admin in its community to approve/refuse membership requests and creation of contents inside the community</p>
    <p>Management will be done through the <strong>Workbench </strong>you can access thru this <a href="admin/workbench"><font color="#3366ff">link</font></a>.</p>
    <p>For more information about the various functionalities,&nbsp;a contextual help exists and can be accessed&nbsp;thru the &quot;Help&quot; link.&nbsp;The help section depends on your localisation on the site and gives details about the page.</p>
    <p>&nbsp;</p>
    ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p>Notice:<br />
    You have to login in order to perform any of the action described below &gt;&gt; <a href="user">Login</a><br />
     <br />
    To complete the configuration of your site, here are some additional steps :<br />
    - to access the <strong>Feature set</strong> configuration page which helps you to choose the features you wish to install on your site &gt;&gt; <a href="admin/structure/feature-set">click here</a><br />
    - to access the <strong>user creation</strong> page in order to add some users and to choose the role you wish to give them &gt;&gt; <a href="admin/people">click here</a><br />
     <br />
    Some information about roles :<br />
    - admin user can do everything on the site, but will mainly be used to approve/refuse user account creation or community creation<br />
    - community manager will act as admin in its community to approve/refuse membership requests and creation of contents inside the community<br />
    Management will be done through the <strong>Workbench </strong>you can access thru this <a href="admin/workbench">link</a>.<br />
    For more information about the various functionalities, a contextual help exists and can be accessed thru the "Help" link. The help section depends on your localisation on the site and gives details about the page.<br />
     </p>
',
          'safe_summary' => '',
        ),
      ),
    ),
  );

return $content;
}
