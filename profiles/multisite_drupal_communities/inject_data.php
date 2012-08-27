<?php

inject_data();

function inject_data() {
  // populate users fields of dummy users
  $account = user_load_by_name("admin");
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

  // multilingual support -----------------------------------------------------------------------------------------
  // set the main-menu as multilingual 
  /*
  db_update('menu_custom')
    ->fields(array('i18n_mode' => 5))
    ->condition('menu_name', 'main-menu')
    ->execute();

 $main_menu = menu_load("main-menu");
 module_invoke_all('menu_update', $main-menu);
*/
	
  // allow menu items to be translatables
/*
  $links = menu_load_links('main-menu');
  foreach ($links as $link) {
    //$menu = module_invoke('i18n_menu', 'menu_link_update', $link);
	//menu_link_save($link);
	//i18n_string_object_update('menu_link', $link);
  }

  menu_cache_clear_all();
*/
	
  
  //custom Filter and custom Ckeditor profile activation for comments
  $html_update = db_insert('ckeditor_input_format') // Table name no longer needs {}
    ->fields(array(
      'name' => 'Basic',
      'format' => 'basic_html',
    ))
    ->execute();
    
  module_enable(array("i18n_taxonomy"));
}



