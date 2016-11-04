<?php
/**
 * @file
 * Data injection procedure.
 */

inject_data();

/**
 * Creating dummy content during the installation process.
 */
function inject_data() {
  global $base_path;
  $tmp_base_url = variable_get("tmp_base_url");
  $base_path = $tmp_base_url;

  // Populate users fields of dummy users.
  $account = user_load(1);
  $account1 = user_load_by_name("user_administrator");
  $account2 = user_load_by_name("user_contributor");
  $account3 = user_load_by_name("user_editor");

  $account->field_firstname['und'][0]['value'] = 'John';
  $account->field_lastname['und'][0]['value'] = 'Doe';
  user_save($account);

  $account1->field_firstname['und'][0]['value'] = 'John';
  $account1->field_lastname['und'][0]['value'] = 'Smith';
  user_save($account1);

  $account2->field_firstname['und'][0]['value'] = 'John';
  $account2->field_lastname['und'][0]['value'] = 'Name';
  user_save($account2);

  $account3->field_firstname['und'][0]['value'] = 'John';
  $account3->field_lastname['und'][0]['value'] = 'Blake';
  user_save($account3);

  module_enable(array("i18n_taxonomy"));

  // Create content.
  $node = new stdClass();
  $node->type = 'page';
  node_object_prepare($node);

  $node->title    = 'Welcome to your site !';
  $node->language = LANGUAGE_NONE;
  $node->path = array('alias' => 'content/welcome-your-site');
  $node->status = '1';
  $node->uid = '1';
  $node->promote = '0';
  $node->sticky = '0';
  $node->created = '1330594184';
  $node->comment = '1';
  $node->translate = '0';
  $node->revision = 1;

  $node->body[$node->language][0]['value'] = '<p>Notice:</p>
    <p>You have to login in order to perform any of the action described below &gt;&gt; ' . l(t('Login'), 'user') . '</p>
    <p>&nbsp;</p>
    <p>To complete the configuration of your site, here are&nbsp;some additional&nbsp;steps :</p>
    <p>- to access the <strong>Feature set</strong> configuration page which helps you to choose the features you wish to install on your site &gt;&gt; ' . l(t('click here'), 'admin/structure/feature-set') . '</p>
    <p>- to access the <strong>user creation</strong> page in order to add some users and to choose the role you wish to give them &gt;&gt; ' . l(t('click here'), 'admin/people') . '</p>
    <p>&nbsp;</p>
    <p>Some information about&nbsp;roles&nbsp;:</p>
    <p>- admin user can do everything on the site, but will mainly be used to approve/refuse user account creation or community creation</p>
    <p>- community manager will act as admin in its community to approve/refuse membership requests and creation of contents inside the community</p>
    <p>Management will be done through the <strong>Workbench </strong>you can access through this ' . l(t('link'), 'admin/workbench') . '.</p>
    <p>For more information about the various functionalities,&nbsp;a contextual help exists and can be accessed&nbsp;thru the &quot;Help&quot; link.&nbsp;The help section depends on your localisation on the site and gives details about the page.</p>
    ';
  $node->body[$node->language][0]['summary'] = '';
  $node->body[$node->language][0]['format']  = 'full_html';

  $path = 'content/welcome-your-site';
  $node->path = array('alias' => $path);

  if ($node = node_submit($node)) {
    // Prepare node for saving.
    node_save($node);
    echo "Node saved!\n";
  }

  // Delete mails from the update manager module.
  variable_del("update_notify_emails");

  // Manually insert the password policy in database.
  // This process is temporary since the module password_policy.
  $exports = cce_basic_config_default_password_policy();
  db_delete('password_policy')->execute();
  db_insert('password_policy')
    ->fields(array(
      'name' => 'Example policy',
      'config' => $exports['Example policy']->config,
    ))
    ->execute();

  // Add solr facet blocks to the search context.
  global $theme_key;
  if ($theme_key == 'ec_resp') {
    $region = 'sidebar_left';
  }
  else {
    $region = 'sidebar_first';
  }
  multisite_drupal_toolbox_add_block_context('search', $value['info'], 'facetapi', $key, $region);
  multisite_drupal_toolbox_add_block_context('search', 'facetapi-8o8kdtP8CKjahDIu1Wy5LGxnDHg3ZYnT', 'facetapi', '8o8kdtP8CKjahDIu1Wy5LGxnDHg3ZYnT', $region, -14);
  multisite_drupal_toolbox_add_block_context('search', 'facetapi-wWWinJ0eOefOtAMbjo2yl86Mnf1rO12j', 'facetapi', 'wWWinJ0eOefOtAMbjo2yl86Mnf1rO12j', $region, -15);
  multisite_drupal_toolbox_add_block_context('search', 'facetapi-odQxTWyhGW1WU7Sl00ISAnQ21BCdJG3A', 'facetapi', 'odQxTWyhGW1WU7Sl00ISAnQ21BCdJG3A', $region, -17);
  multisite_drupal_toolbox_add_block_context('search', 'facetapi-GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu', 'facetapi', 'GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu', $region, -16);
}
